#include "MonthlyFixedCostQueries.h"
using namespace std;
MonthlyFixedCostQueries::MonthlyFixedCostQueries(DatabaseManager &db) : db(db)
{
}

vector<MonthlyFixedCost> MonthlyFixedCostQueries::getMonthlyCosts(int month, int year)
{
    vector<MonthlyFixedCost> costs;
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getConnection(), &stmt);
    stringstream query;
    query << "SELECT Description, Amount " << "FROM MonthlyFixedCosts " << "WHERE CostMonth = " << month << " AND CostYear = " << year;
    string sql = query.str();
    SQLExecDirectA(stmt, (SQLCHAR *)sql.c_str(), SQL_NTS);
    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        char description[255];
        double amount;
        SQLGetData(stmt, 1, SQL_C_CHAR, description, sizeof(description), NULL);
        SQLGetData(stmt, 2, SQL_C_DOUBLE, &amount, 0, NULL);
        costs.push_back(MonthlyFixedCost(description, amount, month, year));
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return costs;
}

double MonthlyFixedCostQueries::getTotalFixedCostInRange(const DateRange &range)
{
    double total = 0;
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getConnection(), &stmt);
    SQLExecDirectA(stmt, (SQLCHAR *)"SELECT Amount, CostMonth, CostYear FROM MonthlyFixedCosts", SQL_NTS);
    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        double amount;
        int month;
        int year;
        SQLGetData(stmt, 1, SQL_C_DOUBLE, &amount, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_LONG, &month, 0, NULL);
        SQLGetData(stmt, 3, SQL_C_LONG, &year, 0, NULL);
        if (range.contains(month, year))
        {
            total += amount;
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return total;
}
