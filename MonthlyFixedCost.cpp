#include "MonthlyFixedCost.h"
#include "Exceptions.h"
using namespace std;
MonthlyFixedCost::MonthlyFixedCost(const string &description, double amount, int month, int year) : description(description), amount(amount), month(month), year(year)
{
    if (description.empty())
    {
        throw invalid_argument("Description can't be empty.");
    }
    if (amount < 0)
    {
        throw InvalidCostException("Monthly fixed cost cannot be negative.");
    }
    if (month < 1 || month > 12)
    {
        throw invalid_argument("Month must be between 1 and 12");
    }
    if (year < 2000)
    {
        throw invalid_argument("Invalid Year.");
    }
}

string MonthlyFixedCost::getDescription() const
{
    return description;
}

double MonthlyFixedCost::getAmount() const
{
    return amount;
}

int MonthlyFixedCost::getMonth() const
{
    return month;
}

int MonthlyFixedCost::getYear() const
{
    return year;
}
