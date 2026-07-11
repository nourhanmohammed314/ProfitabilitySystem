#pragma once
#include <bits/stdc++.h>
class MonthlyFixedCost
{
private:
    std::string description;
    double amount;
    int month;
    int year;

public:
    MonthlyFixedCost(const std::string &description, double amount, int month, int year);
    std::string getDescription() const;
    double getAmount() const;
    int getMonth() const;
    int getYear() const;
};
