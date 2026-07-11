#pragma once
#include"Product.h"
class PhysicalProduct : public Product
{
private:
    double storageCost;
    int stockQuantity;
public:
    PhysicalProduct(const std::string &name, int productId, double sellingPrice, const std::vector<CostComponent> &costComponents,double storageCost,int stockQuantity);
    double costCalculation() const override;
    double getStorageCost() const;
    int getStockQuantity() const;
    void display() const override;
    ProductType getType() const override;
};