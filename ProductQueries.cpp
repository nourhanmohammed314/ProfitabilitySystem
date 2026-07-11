#include "ProductQueries.h"
#include "CostComponent.h"
using namespace std;

ProductQueries::ProductQueries(DatabaseManager &db) : db(db)
{
}

Product *ProductQueries::getProductById(int productId)
{
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getConnection(), &stmt);
    stringstream query;
    query << "SELECT Name, SellingPrice FROM Products WHERE ProductID = " << productId;
    string sql = query.str();
    SQLExecDirectA(stmt, (SQLCHAR *)sql.c_str(), SQL_NTS);
    if (SQLFetch(stmt) != SQL_SUCCESS)
    {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return nullptr;
    }
    char name[100];
    double sellingPrice;
    SQLGetData(stmt, 1, SQL_C_CHAR, name, sizeof(name), NULL);
    SQLGetData(stmt, 2, SQL_C_DOUBLE, &sellingPrice, 0, NULL);
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    vector<CostComponent> costs;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getConnection(), &stmt);
    stringstream costQuery;
    costQuery << "SELECT Name, Amount, Type FROM CostComponents WHERE ProductID = " << productId;
    string costSql = costQuery.str();
    SQLExecDirectA(stmt, (SQLCHAR *)costSql.c_str(), SQL_NTS);
    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        char costName[100];
        double amount;
        char type[20];
        SQLGetData(stmt, 1, SQL_C_CHAR, costName, sizeof(costName), NULL);
        SQLGetData(stmt, 2, SQL_C_DOUBLE, &amount, 0, NULL);
        SQLGetData(stmt, 3, SQL_C_CHAR, type, sizeof(type), NULL);
        CostType costType;
        if (string(type) == "fixed")
            costType = CostType::fixed;
        else
            costType = CostType::variable;
        costs.push_back(CostComponent(costName, amount, costType));
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLAllocHandle(SQL_HANDLE_STMT, db.getConnection(), &stmt);
    stringstream physicalQuery;
    physicalQuery << "SELECT StorageCost, StockQuantity " << "FROM PhysicalProducts WHERE ProductID = " << productId;
    string physicalSql = physicalQuery.str();
    SQLExecDirectA(stmt, (SQLCHAR *)physicalSql.c_str(), SQL_NTS);
    if (SQLFetch(stmt) == SQL_SUCCESS)
    {
        double storageCost;
        int stockQuantity;
        SQLGetData(stmt, 1, SQL_C_DOUBLE, &storageCost, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_LONG, &stockQuantity, 0, NULL);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return new PhysicalProduct(name, productId, sellingPrice, costs, storageCost, stockQuantity);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    SQLAllocHandle(SQL_HANDLE_STMT, db.getConnection(), &stmt);
    stringstream serviceQuery;
    serviceQuery << "SELECT HoursPerUnit, HourlyLaborRate " << "FROM ServiceOfferings WHERE ProductID = " << productId;
    string serviceSql = serviceQuery.str();
    SQLExecDirectA(stmt, (SQLCHAR *)serviceSql.c_str(), SQL_NTS);
    if (SQLFetch(stmt) == SQL_SUCCESS)
    {
        int hours;
        double rate;
        SQLGetData(stmt, 1, SQL_C_LONG, &hours, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_DOUBLE, &rate, 0, NULL);
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        return new ServiceOffering(name, productId, sellingPrice, costs, hours, rate);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return nullptr;
}

vector<Product *> ProductQueries::getAllProducts()
{
    vector<Product *> products;
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getConnection(), &stmt);
    SQLExecDirectA(stmt, (SQLCHAR *)"SELECT ProductID FROM Products", SQL_NTS);
    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        int id;
        SQLGetData(stmt, 1, SQL_C_LONG, &id, 0, NULL);
        Product *product = getProductById(id);
        if (product != nullptr)
        {
            products.push_back(product);
        }
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return products;
}

vector<pair<int, string>> ProductQueries::getProductList()
{
    vector<pair<int, string>> products;
    SQLHSTMT stmt;
    SQLAllocHandle(SQL_HANDLE_STMT, db.getConnection(), &stmt);
    SQLExecDirectA(stmt, (SQLCHAR *)"SELECT ProductID, Name FROM Products", SQL_NTS);
    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        int id;
        char name[100];
        SQLGetData(stmt, 1, SQL_C_LONG, &id, 0, NULL);
        SQLGetData(stmt, 2, SQL_C_CHAR, name, sizeof(name), NULL);
        products.push_back({id, name});
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return products;
}
