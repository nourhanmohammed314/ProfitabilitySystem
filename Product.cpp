#include "product.h"
#include "Exceptions.h"
using namespace std;
Product::Product(const std::string &name, int productId, double sellingPrice, const std::vector<CostComponent> &costComponents) : name(name), productId(productId), sellingPrice(sellingPrice), costComponents(costComponents)
{
    if (name.empty())
    {
        throw invalid_argument("Product Name can't be empty.");
    }
    if (productId < 0)
    {
        throw invalid_argument("Invalid Product ID.");
    }
    if (sellingPrice < 0)
    {
        throw InvalidCostException("Selling price cannot be negative.");
    }
}

std::string Product::getName() const
{
    return name;
}

int Product::getProductId() const
{
    return productId;
}

double Product::getSellingPrice() const
{
    return sellingPrice;
}
const std::vector<CostComponent> &Product::getCostComponents() const
{
    return costComponents;
}

void Product::setSellingPrice(double price)
{
    if (price < 0)
    {
        throw InvalidCostException("Selling price cannot be negative.");
    }
    sellingPrice = price;
}

void Product::setProductId(int id)
{
    if (id <= 0)
    {
        throw invalid_argument("Invalid Product ID.");
    }
    productId = id;
}