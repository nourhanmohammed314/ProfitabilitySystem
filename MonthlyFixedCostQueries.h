#pragma once
#include "DatabaseManager.h"
#include "MonthlyFixedCost.h"
#include "DateRange.h"

class MonthlyFixedCostQueries
{
private:
    DatabaseManager &db;

public:
    MonthlyFixedCostQueries(DatabaseManager &db);
    std::vector<MonthlyFixedCost> getMonthlyCosts(int month,int year);
    double getTotalFixedCostInRange(const DateRange &range);
};