#pragma once
#include<windows.h>
#include<sql.h>
#include<sqlext.h>
class DatabaseManager
{
private:
    SQLHENV env;
    SQLHDBC dbc;
public:
    DatabaseManager();
    ~DatabaseManager();
    bool connect();
    void disconnect();
    SQLHDBC getConnection() const;
};