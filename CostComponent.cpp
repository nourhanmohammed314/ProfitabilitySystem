#include "CostComponent.h"
#include "Exceptions.h"
using namespace std;
CostComponent::CostComponent(const string &name, double amount, CostType type) : name(name), amount(amount), type(type)
{
    if (name.empty())
    {
        throw invalid_argument("Cost Component name can't be empty.");
    }
    if (amount < 0)
    {
        throw InvalidCostException("Cost amount can't be negative.");
    }
}

double CostComponent::getAmount() const
{
    return amount;
}

string CostComponent::getName() const
{
    return name;
}

CostType CostComponent::getType() const
{
    return type;
}
