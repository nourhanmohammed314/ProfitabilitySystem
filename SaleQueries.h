#pragma once
#include "DatabaseManager.h"
#include "SaleTransaction.h"
#include "DateRange.h"

class SaleQueries
{
private:
    DatabaseManager &db;

public:
    SaleQueries(DatabaseManager &db);
    std::vector<SaleTransaction> getSalesByProduct(int productId);
    std::vector<SaleTransaction> getSalesByMonth(int month,int year);
    std::vector<SaleTransaction> getSalesByProductAndMonth(int productId,int month,int year);
    std::vector<SaleTransaction> getSalesInRange(const DateRange &range);
    std::vector<SaleTransaction> getSalesByProductInRange(int productId,const DateRange &range);
};