#pragma once
#include <bits/stdc++.h>
enum class CostType
{
    fixed,
    variable
};
class CostComponent
{
private:
    std::string name;
    double amount;
    CostType type;

public:
    CostComponent(const std::string &name, double amount, CostType type);
    double getAmount() const;
    std::string getName() const;
    CostType getType() const;
};
