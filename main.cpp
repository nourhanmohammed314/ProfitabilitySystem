#include "DatabaseManager.h"
#include "ProductQueries.h"
#include "SaleQueries.h"
#include "MonthlyFixedCostQueries.h"
#include "BusinessAnalyzer.h"
#include "DateRange.h"
#include "ProfitabilityReport.h"
#include <memory>
using namespace std;
string statusToString(ProfitabilityStatus status)
{
    switch (status)
    {
    case ProfitabilityStatus::LOSS:
        return "LOSS";
    case ProfitabilityStatus::CRITICAL:
        return "CRITICAL";
    case ProfitabilityStatus::STABLE:
        return "STABLE";
    case ProfitabilityStatus::STRONG:
        return "STRONG";
    }
    return "UNKNOWN";
}
void analyzeProduct(BusinessAnalyzer &analyzer, int productId, const DateRange &range, double &revenue, double &totalCost, double &profit, double &breakEven, double &margin, ProfitabilityStatus &status)
{
    revenue = analyzer.calculateRevenue(productId, range);
    totalCost = analyzer.calculateTotalCost(productId, range);
    profit = analyzer.calculateProfit(productId, range);
    breakEven = analyzer.calculateBreakEven(productId, range);
    margin = analyzer.calculateMarginOfSafety(productId, range);
    status = analyzer.classifyProfitability(productId, range);
}
string escapeJson(string text)
{
    string result;
    for (char c : text)
    {
        if (c == '"')
            result += "\\\"";
        else if (c == '\\')
            result += "\\\\";
        else
            result += c;
    }
    return result;
}
int main(int argc, char *argv[])
{
    DatabaseManager db;
    if (!db.connect())
    {
        if (argc == 6 || (argc == 2 && string(argv[1]) == "products"))
            cout << "{\"error\":\"Database Connection Failed\"}";
        else
            cout << "Database Connection Failed.\n";
        return 1;
    }
    if (argc != 6 && argc != 2)
    {
        cout << "Connected Successfully!\n";
    }
    ProductQueries productQueries(db);
    SaleQueries saleQueries(db);
    MonthlyFixedCostQueries fixedCostQueries(db);
    BusinessAnalyzer analyzer(productQueries, saleQueries, fixedCostQueries);
    if (argc == 2 && string(argv[1]) == "products")
    {
        auto products = productQueries.getProductList();
        cout << "[";
        for (size_t i = 0; i < products.size(); i++)
        {
            cout << "{";
            cout << "\"id\":" << products[i].first << ",";
            cout << "\"name\":\"" << escapeJson(products[i].second) << "\"";
            cout << "}";
            if (i < products.size() - 1)
                cout << ",";
        }
        cout << "]";
        return 0;
    }
    if (argc == 6)
    {
        try
        {
            int productId = stoi(argv[1]);
            int startMonth = stoi(argv[2]);
            int startYear = stoi(argv[3]);
            int endMonth = stoi(argv[4]);
            int endYear = stoi(argv[5]);
            DateRange range(startMonth, startYear, endMonth, endYear);
            auto product = unique_ptr<Product>(productQueries.getProductById(productId));
            if (product == nullptr)
            {
                cout << "{\"error\":\"Product Not Found\"}";
                return 0;
            }
            double revenue, totalCost, profit, breakEven, margin;
            ProfitabilityStatus status;
            analyzeProduct(analyzer, productId, range, revenue, totalCost, profit, breakEven, margin, status);
            cout << "{";
            cout << "\"name\":\"" << escapeJson(product->getName()) << "\",";
            cout << "\"revenue\":" << revenue << ",";
            cout << "\"totalCost\":" << totalCost << ",";
            cout << "\"profit\":" << profit << ",";
            cout << "\"breakEven\":" << breakEven << ",";
            cout << "\"margin\":" << margin << ",";
            cout << "\"status\":\"" << statusToString(status) << "\"";
            cout << "}";
            return 0;
        }
        catch (const exception &ex)
        {
            cout << "{\"error\":\"" << ex.what() << "\"}";
            return 0;
        }
    }

    int choice;
    do
    {
        cout << "\n=====================================\n";
        cout << "     PRODUCT PROFITABILITY SYSTEM\n";
        cout << "=====================================\n";
        cout << "1. Analyze Product\n";
        cout << "2. Display All Products\n";
        cout << "3. Exit\n";
        cout << "=====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int productId;
            int startMonth;
            int startYear;
            int endMonth;
            int endYear;
            cout << "\nEnter Product ID: ";
            cin >> productId;
            cout << "Start Month: ";
            cin >> startMonth;
            cout << "Start Year: ";
            cin >> startYear;
            cout << "End Month: ";
            cin >> endMonth;
            cout << "End Year: ";
            cin >> endYear;
            try
            {
                DateRange range(startMonth, startYear, endMonth, endYear);
                auto product = unique_ptr<Product>(productQueries.getProductById(productId));
                if (product == nullptr)
                {
                    cout << "\nProduct not found.\n";
                    break;
                }
                double revenue, totalCost, profit, breakEven, margin;
                ProfitabilityStatus status;
                analyzeProduct(analyzer, productId, range, revenue, totalCost, profit, breakEven, margin, status);
                ProfitabilityReport::print(*product, revenue, totalCost, profit, breakEven, margin, status);
            }
            catch (const exception &ex)
            {
                cout << "\nError: " << ex.what() << endl;
            }
            break;
        }
        case 2:
        {
            vector<pair<int, string>> products = productQueries.getProductList();
            cout << "\n========== Available Products ==========\n\n";
            cout << left << setw(15) << "Product ID" << "Product Name\n";
            cout << "----------------------------------------\n";
            for (const auto &product : products)
            {
                cout << left << setw(15) << product.first << product.second << endl;
            }
            break;
        }
        case 3:
        {
            cout << "\nThank you for using the system.\n";
            break;
        }
        default:
        {
            cout << "\nInvalid Choice.\n";
        }
        }
    } while (choice != 3);
    return 0;
}