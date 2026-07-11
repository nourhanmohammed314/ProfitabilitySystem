#pragma once

#include "ProductQueries.h"
#include "SaleQueries.h"
#include "MonthlyFixedCostQueries.h"
#include "DateRange.h"
#include "Exceptions.h"
enum class ProfitabilityStatus
{

    LOSS,

    CRITICAL,

    STABLE,

    STRONG

};
class BusinessAnalyzer
{

private:
    ProductQueries &productQueries;
    SaleQueries &saleQueries;
    MonthlyFixedCostQueries &fixedCostQueries;
    double calculateVariableCost(const Product *product) const;
    double calculateAllocatedFixedCost(int productId, const DateRange &range) const;

public:
    BusinessAnalyzer(ProductQueries &productQueries, SaleQueries &saleQueries, MonthlyFixedCostQueries &fixedCostQueries);
    double calculateRevenue(int productId, const DateRange &range) const;
    double calculateTotalCost(int productId, const DateRange &range) const;
    double calculateProfit(int productId, const DateRange &range) const;
    double calculateBreakEven(int productId, const DateRange &range) const;
    double calculateMarginOfSafety(int productId, const DateRange &range) const;
    ProfitabilityStatus classifyProfitability(int productId, const DateRange &range) const;
};