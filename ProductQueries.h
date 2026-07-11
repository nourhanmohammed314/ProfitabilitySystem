#pragma once
#include "DatabaseManager.h"
#include "PhysicalProduct.h"
#include "ServiceOffering.h"

class ProductQueries
{
private:
    DatabaseManager& db;

public:
    ProductQueries(DatabaseManager& db);
    Product* getProductById(int productId);
    std::vector<Product*> getAllProducts();
    std::vector<std::pair<int, std::string>> getProductList();
};