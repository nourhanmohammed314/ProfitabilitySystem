#include "SaleTransaction.h"
#include "Exceptions.h"
using namespace std;
SaleTransaction::SaleTransaction(int productId, int quantity, double salePrice, int month, int year) : productId(productId), quantity(quantity), salePrice(salePrice), month(month), year(year)
{
    if (productId <= 0)
    {
        throw invalid_argument("Invalid product ID.");
    }
    if (quantity <= 0)
    {
        throw InvalidQuantityException("Quantity must be greater than zero.");
    }
    if (salePrice < 0)
    {
        throw InvalidCostException("Sale price cannot be negative.");
    }
    if (month < 1 || month > 12)
    {
        throw invalid_argument("Month must be between 1 and 12.");
    }
    if (year < 2000)
    {
        throw invalid_argument("Year must be greater than 2000.");
    }
}

int SaleTransaction::getProductId() const
{
    return productId;
}

int SaleTransaction::getQuantity() const
{
    return quantity;
}

double SaleTransaction::getSalePrice() const
{
    return salePrice;
}

int SaleTransaction::getMonth() const
{
    return month;
}

int SaleTransaction::getYear() const
{
    return year;
}
