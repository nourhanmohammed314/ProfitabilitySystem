#include "PhysicalProduct.h"
#include "Exceptions.h"
using namespace std;
PhysicalProduct::PhysicalProduct(const string &name, int productId, double sellingPrice, const vector<CostComponent> &costComponents, double storageCost, int stockQuantity) : Product(name, productId, sellingPrice, costComponents), storageCost(storageCost), stockQuantity(stockQuantity)
{
    if (storageCost < 0)
    {
        throw InvalidCostException("Storage cost cannot be negative.");
    }
    if (stockQuantity < 0)
    {
        throw invalid_argument("Stock Quantity Can't be negative");
    }
}

double PhysicalProduct::costCalculation() const
{
    double totalCost = storageCost;
    for (const auto &component : getCostComponents())
    {
        totalCost += component.getAmount();
    }
    return totalCost;
}

double PhysicalProduct::getStorageCost() const
{
    return storageCost;
}

int PhysicalProduct::getStockQuantity() const
{
    return stockQuantity;
}

void PhysicalProduct::display() const
{
    cout << "Physical Product\n";
    cout << "Name: " << getName() << '\n';
    cout << "Product ID: " << getProductId() << '\n';
    cout << "Selling Price: " << getSellingPrice() << "\n";
    cout << "Storage Cost: " << storageCost << '\n';
    cout << "Stock Quantity: " << stockQuantity << '\n';
    cout << "Unit Cost: " << costCalculation() << '\n';
}

ProductType PhysicalProduct::getType() const
{
    return ProductType::Physical;
}
