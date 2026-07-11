#include "ServiceOffering.h"
#include "Exceptions.h"
using namespace std;
ServiceOffering::ServiceOffering(const string &name, int productId, double sellingPrice, const vector<CostComponent> &costcomponents, int hoursPerUnit, double hourlyLaborRate) : Product(name, productId, sellingPrice, costcomponents), hoursPerUnit(hoursPerUnit), hourlyLaborRate(hourlyLaborRate)
{
    if (hoursPerUnit <= 0)
    {
        throw invalid_argument("Hours Per Unit must be greater than zero.");
    }
    if (hourlyLaborRate < 0)
    {
        throw InvalidCostException("Hourly labor rate cannot be negative.");
    }
}

double ServiceOffering::costCalculation() const
{
    double totalCost = hoursPerUnit * hourlyLaborRate;
    for (const auto &component : getCostComponents())
    {
        totalCost += component.getAmount();
    }
    return totalCost;
}

int ServiceOffering::getHoursPerUnit() const
{
    return hoursPerUnit;
}

double ServiceOffering::getHourlyLaborRate() const
{
    return hourlyLaborRate;
}

void ServiceOffering::display() const
{
    cout << "Service Offering\n";
    cout << "Name: " << getName() << '\n';
    cout << "Product ID: " << getProductId() << '\n';
    cout << "Selling Price: " << getSellingPrice() << "\n";
    cout << "Hours Per Unit: " << hoursPerUnit << '\n';
    cout << "Hourly Labor Rate: " << hourlyLaborRate << '\n';
    cout << "Total Cost: " << costCalculation() << '\n';
}

ProductType ServiceOffering::getType() const
{
    return ProductType::Service;
}
