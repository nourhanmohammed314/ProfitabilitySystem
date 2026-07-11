#pragma once
#include "CostComponent.h"
enum class ProductType
{
    Physical,
    Service
};
class Product
{
private:
    std::string name;
    int productId;
    double sellingPrice;
    std::vector<CostComponent> costComponents;

public:
    Product(const std::string &name, int productId, double sellingPrice, const std::vector<CostComponent> &costComponents);
    virtual ~Product() = default;
    virtual double costCalculation() const = 0;
    std::string getName() const;
    int getProductId() const;
    double getSellingPrice() const;
    const std::vector<CostComponent> &getCostComponents() const;
    virtual void display() const = 0;
    void setSellingPrice(double price);
    virtual ProductType getType() const = 0;
    void setProductId(int id);
};