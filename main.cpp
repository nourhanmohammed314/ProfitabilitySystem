#include "DatabaseManager.h"
#include "ProductQueries.h"
#include "SaleQueries.h"
#include "MonthlyFixedCostQueries.h"
#include "BusinessAnalyzer.h"
#include "DateRange.h"
#include "ProfitabilityReport.h"
using namespace std;

int main()
{
    DatabaseManager db;
    if (!db.connect())
    {
        cout << "Database Connection Failed.\n";
        return 1;
    }
    cout << "Connected Successfully!\n";
    ProductQueries productQueries(db);
    SaleQueries saleQueries(db);
    MonthlyFixedCostQueries fixedCostQueries(db);
    BusinessAnalyzer analyzer(productQueries, saleQueries, fixedCostQueries);
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
                Product *product = productQueries.getProductById(productId);
                if (product == nullptr)
                {
                    cout << "\nProduct not found.\n";
                    break;
                }
                double revenue = analyzer.calculateRevenue(productId, range);
                double totalCost = analyzer.calculateTotalCost(productId, range);
                double profit = analyzer.calculateProfit(productId, range);
                double breakEven = analyzer.calculateBreakEven(productId, range);
                double margin = analyzer.calculateMarginOfSafety(productId, range);
                ProfitabilityStatus status = analyzer.classifyProfitability(productId, range);
                ProfitabilityReport::print(*product,revenue,totalCost,profit,breakEven,margin,status);
                delete product;
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
    db.disconnect();
    return 0;
}