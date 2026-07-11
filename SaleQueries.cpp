#include "SaleQueries.h"
using namespace std;

SaleQueries::SaleQueries(DatabaseManager &db) : db(db)
{
}

vector<SaleTransaction> SaleQueries::getSalesByProduct(int productId)
{
    vector<SaleTransaction> sales;
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getConnection(), &stmt);
    stringstream query;
    query << "SELECT Quantity, SalePrice, SaleMonth, SaleYear " << "FROM SaleTransactions " << "WHERE ProductID = " << productId;
    string sql = query.str();
    SQLExecDirectA(stmt, (SQLCHAR *)sql.c_str(), SQL_NTS);
    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        int quantity;
        double salePrice;
        int month;
        int year;
        SQLGetData(stmt, 1, SQL_C_LONG, &quantity, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_DOUBLE, &salePrice, 0, NULL);
        SQLGetData(stmt, 3, SQL_C_LONG, &month, 0, NULL);
        SQLGetData(stmt, 4, SQL_C_LONG, &year, 0, NULL);
        sales.push_back(SaleTransaction(productId, quantity, salePrice, month, year));
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return sales;
}

vector<SaleTransaction> SaleQueries::getSalesByMonth(int month, int year)
{
    vector<SaleTransaction> sales;
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getConnection(), &stmt);
    stringstream query;
    query << "SELECT ProductID, Quantity, SalePrice " << "FROM SaleTransactions " << "WHERE SaleMonth = " << month << " AND SaleYear = " << year;
    string sql = query.str();
    SQLExecDirectA(stmt, (SQLCHAR *)sql.c_str(), SQL_NTS);
    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        int productId;
        int quantity;
        double salePrice;
        SQLGetData(stmt, 1, SQL_C_LONG, &productId, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_LONG, &quantity, 0, NULL);
        SQLGetData(stmt, 3, SQL_C_DOUBLE, &salePrice, 0, NULL);
        sales.push_back(SaleTransaction(productId, quantity, salePrice, month, year));
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return sales;
}

vector<SaleTransaction> SaleQueries::getSalesByProductAndMonth(int productId, int month, int year)
{
    vector<SaleTransaction> sales;
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getConnection(), &stmt);
    stringstream query;
    query << "SELECT Quantity, SalePrice " << "FROM SaleTransactions " << "WHERE ProductID = " << productId << " AND SaleMonth = " << month << " AND SaleYear = " << year;
    string sql = query.str();
    SQLExecDirectA(stmt, (SQLCHAR *)sql.c_str(), SQL_NTS);
    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        int quantity;
        double salePrice;
        SQLGetData(stmt, 1, SQL_C_LONG, &quantity, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_DOUBLE, &salePrice, 0, NULL);
        sales.push_back(SaleTransaction(productId, quantity, salePrice, month, year));
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return sales;
}

vector<SaleTransaction> SaleQueries::getSalesInRange(const DateRange &range)
{
    vector<SaleTransaction> sales;
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getConnection(), &stmt);
    SQLExecDirectA(stmt, (SQLCHAR *)"SELECT ProductID, Quantity, SalePrice, SaleMonth, SaleYear FROM SaleTransactions", SQL_NTS);
    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        int productId;
        int quantity;
        double salePrice;
        int month;
        int year;
        SQLGetData(stmt, 1, SQL_C_LONG, &productId, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_LONG, &quantity, 0, NULL);
        SQLGetData(stmt, 3, SQL_C_DOUBLE, &salePrice, 0, NULL);
        SQLGetData(stmt, 4, SQL_C_LONG, &month, 0, NULL);
        SQLGetData(stmt, 5, SQL_C_LONG, &year, 0, NULL);
        if (range.contains(month, year))
        {
            sales.push_back(SaleTransaction(productId, quantity, salePrice, month, year));
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return sales;
}

vector<SaleTransaction> SaleQueries::getSalesByProductInRange(int productId, const DateRange &range)
{
    vector<SaleTransaction> allSales = getSalesInRange(range);
    vector<SaleTransaction> result;
    for (const auto &sale : allSales)
    {
        if (sale.getProductId() == productId)
        {
            result.push_back(sale);
        }
    }
    return result;
}
