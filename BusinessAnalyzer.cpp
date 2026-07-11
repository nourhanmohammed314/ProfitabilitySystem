#include "BusinessAnalyzer.h"
using namespace std;
BusinessAnalyzer::BusinessAnalyzer(ProductQueries &productQueries, SaleQueries &saleQueries, MonthlyFixedCostQueries &fixedCostQueries) : productQueries(productQueries), saleQueries(saleQueries), fixedCostQueries(fixedCostQueries)
{
}

double BusinessAnalyzer::calculateVariableCost(const Product *product) const
{
    double total = 0;
    for (const auto &component : product->getCostComponents())
    {
        if (component.getType() == CostType::variable)
        {
            total += component.getAmount();
        }
    }
    return total;
}

double BusinessAnalyzer::calculateRevenue(int productId, const DateRange &range) const
{
    double revenue = 0;
    vector<SaleTransaction> sales = saleQueries.getSalesByProductInRange(productId, range);
    for (const auto &sale : sales)
    {
        revenue += sale.getQuantity() * sale.getSalePrice();
    }
    return revenue;
}

double BusinessAnalyzer::calculateTotalCost(int productId, const DateRange &range) const
{
    Product *product = productQueries.getProductById(productId);
    double variableCost = calculateVariableCost(product);
    vector<SaleTransaction> sales = saleQueries.getSalesByProductInRange(productId, range);
    int totalUnits = 0;
    for (const auto &sale : sales)
    {
        totalUnits += sale.getQuantity();
    }
    double totalVariableCost = variableCost * totalUnits;
    double fixedCost = calculateAllocatedFixedCost(productId, range);
    if (product->getType() == ProductType::Physical)
    {
        PhysicalProduct *physical = static_cast<PhysicalProduct *>(product);
        totalVariableCost += physical->getStorageCost();
    }
    delete product;
    return totalVariableCost + fixedCost;
}

double BusinessAnalyzer::calculateAllocatedFixedCost(int productId, const DateRange &range) const
{
    vector<SaleTransaction> allSales = saleQueries.getSalesInRange(range);
    if (allSales.empty())
    {
        throw InsufficientDataException("No sales data available.");
    }
    int totalUnits = 0;
    for (const auto &sale : allSales)
    {
        totalUnits += sale.getQuantity();
    }
    if (totalUnits == 0)
    {
        throw InsufficientDataException("Total units sold cannot be zero.");
    }
    vector<SaleTransaction> productSales = saleQueries.getSalesByProductInRange(productId, range);
    int productUnits = 0;
    for (const auto &sale : productSales)
    {
        productUnits += sale.getQuantity();
    }
    double totalFixedCost = fixedCostQueries.getTotalFixedCostInRange(range);
    if (totalFixedCost == 0)
    {
        throw InsufficientDataException("No fixed costs available.");
    }
    return (static_cast<double>(productUnits) / totalUnits) * totalFixedCost;
}

double BusinessAnalyzer::calculateProfit(int productId, const DateRange &range) const
{
    double revenue = calculateRevenue(productId, range);
    double totalCost = calculateTotalCost(productId, range);
    return revenue - totalCost;
}

double BusinessAnalyzer::calculateBreakEven(int productId, const DateRange &range) const
{
    Product *product = productQueries.getProductById(productId);
    double sellingPrice = product->getSellingPrice();
    double variableCost = calculateVariableCost(product);
    double fixedCost = calculateAllocatedFixedCost(productId, range);
    double contributionMargin = sellingPrice - variableCost;
    if (contributionMargin <= 0)
    {
        delete product;
        throw InvalidCostException("Contribution margin must be greater than zero.");
    }
    double result = fixedCost / contributionMargin;
    delete product;
    return result;
}

double BusinessAnalyzer::calculateMarginOfSafety(int productId, const DateRange &range) const
{
    vector<SaleTransaction> sales = saleQueries.getSalesByProductInRange(productId, range);
    int actualUnits = 0;
    for (const auto &sale : sales)
    {
        actualUnits += sale.getQuantity();
    }
    if (actualUnits == 0)
    {
        throw InsufficientDataException("No sales for this product.");
    }
    double breakEvenUnits = calculateBreakEven(productId, range);
    return ((actualUnits - breakEvenUnits) / actualUnits) * 100;
}

ProfitabilityStatus BusinessAnalyzer::classifyProfitability(int productId, const DateRange &range) const
{
    double margin = calculateMarginOfSafety(productId, range);
    if (margin < 0)
        return ProfitabilityStatus::LOSS;
    else if (margin <= 10)
        return ProfitabilityStatus::CRITICAL;
    else if (margin <= 30)
        return ProfitabilityStatus::STABLE;
    else
        return ProfitabilityStatus::STRONG;
}