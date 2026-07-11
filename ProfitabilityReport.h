#pragma once
#include "Product.h"
#include "BusinessAnalyzer.h"
class ProfitabilityReport
{
public:
    static void print(const Product &product,double revenue,double totalCost,double profit,double breakEven,double marginOfSafety,ProfitabilityStatus status);
};