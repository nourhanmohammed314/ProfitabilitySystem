#include "DateRange.h"
using namespace std;
DateRange::DateRange(int startMonth, int startYear, int endMonth, int endYear) : startMonth(startMonth), startYear(startYear), endMonth(endMonth), endYear(endYear)
{
    if (startMonth < 1 || startMonth > 12 || endMonth < 1 || endMonth > 12)
    {
        throw invalid_argument("Invalid Month.");
    }
    int start = startYear * 12 + startMonth;
    int end = endYear * 12 + endMonth;
    if (start > end)
    {
        throw invalid_argument("Invalid Date Range.");
    }
}

int DateRange::getStartMonth() const
{
    return startMonth;
}

int DateRange::getStartYear() const
{
    return startYear;
}

int DateRange::getEndMonth() const
{
    return endMonth;
}

int DateRange::getEndYear() const
{
    return endYear;
}

bool DateRange::contains(int month, int year) const
{
    if (year < startYear)
        return false;
    if (year == startYear && month < startMonth)
        return false;
    if (year > endYear)
        return false;
    if (year == endYear && month > endMonth)
        return false;
    return true;
}
