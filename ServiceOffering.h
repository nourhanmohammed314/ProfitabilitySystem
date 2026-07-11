#pragma once
#include "Product.h"
class ServiceOffering : public Product
{
private:
    int hoursPerUnit;
    double hourlyLaborRate;

public:
    ServiceOffering(const std::string &name, int productId, double sellingPrice, const std::vector<CostComponent> &costcomponents, int hoursPerUnit, double hourlyLaborRate);
    double costCalculation() const override;
    int getHoursPerUnit() const;
    double getHourlyLaborRate() const;
    void display() const override;
    ProductType getType() const override;
};