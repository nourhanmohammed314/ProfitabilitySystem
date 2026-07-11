#pragma once
#include <bits/stdc++.h>
class SaleTransaction
{
private:
    int productId;
    int quantity;
    double salePrice;
    int month;
    int year;

public:
    SaleTransaction(int productId, int quantity, double salePrice, int month, int year);
    int getProductId() const;
    int getQuantity() const;
    double getSalePrice() const;
    int getMonth() const;
    int getYear() const;
};
