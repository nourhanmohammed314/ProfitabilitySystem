#include "DatabaseManager.h"
using namespace std;
DatabaseManager::DatabaseManager()
{
    env = SQL_NULL_HENV;
    dbc = SQL_NULL_HDBC;
}

DatabaseManager::~DatabaseManager()
{
    disconnect();
}

bool DatabaseManager::connect()
{
    SQLRETURN ret;
    ret = SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&env);
    if (!SQL_SUCCEEDED(ret))
    {
        return false;
    }
    ret = SQLSetEnvAttr(env,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,0);
    if (!SQL_SUCCEEDED(ret))
    {
        disconnect();
        return false;
    }
    ret = SQLAllocHandle(SQL_HANDLE_DBC,env,&dbc);
    if (!SQL_SUCCEEDED(ret))
    {
        disconnect();
        return false;
    }
    SQLWCHAR connStr[] =
        L"DRIVER={ODBC Driver 17 for SQL Server};"
        L"SERVER=localhost\\SQLEXPRESS;"
        L"DATABASE=Profitability_System;"
        L"Trusted_Connection=yes;";
    ret = SQLDriverConnectW(dbc,NULL,connStr,SQL_NTS,NULL,0,NULL,SQL_DRIVER_NOPROMPT);
    if (!SQL_SUCCEEDED(ret))
    {
        disconnect();
        return false;
    }
    return true;
}

void DatabaseManager::disconnect()
{
    if (dbc != SQL_NULL_HDBC)
    {
        SQLDisconnect(dbc);
        SQLFreeHandle(SQL_HANDLE_DBC, dbc);
        dbc = SQL_NULL_HDBC;
    }
    if (env != SQL_NULL_HENV)
    {
        SQLFreeHandle(SQL_HANDLE_ENV, env);
        env = SQL_NULL_HENV;
    }
}

SQLHDBC DatabaseManager::getConnection() const
{
    return dbc;
}
