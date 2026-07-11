#pragma once
#include "Exceptions.h"
class DateRange
{
private:
    int startMonth;
    int startYear;
    int endMonth;
    int endYear;

public:
    DateRange(int startMonth, int startYear, int endMonth, int endYear);
    int getStartMonth() const;
    int getStartYear() const;
    int getEndMonth() const;
    int getEndYear() const;
    bool contains(int month, int year) const;
};