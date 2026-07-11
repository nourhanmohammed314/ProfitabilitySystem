#include "ProfitabilityReport.h"
using namespace std;
void ProfitabilityReport::print(const Product &product,double revenue,double totalCost,double profit,double breakEven,double marginOfSafety,ProfitabilityStatus status)
{
    cout << fixed << setprecision(2);
    cout << "\n========== PRODUCT ==========\n";
    product.display();
    cout << "\n========== ANALYSIS ==========\n";
    cout << "Revenue            : " << revenue << '\n';
    cout << "Total Cost         : " << totalCost << '\n';
    cout << "Profit             : " << profit << '\n';
    cout << "Break-even Units   : " << breakEven << '\n';
    cout << "Margin Of Safety   : " << marginOfSafety << "%" << '\n';
    cout << "Classification     : ";
    switch (status)
    {
    case ProfitabilityStatus::LOSS:
        cout << "LOSS";
        break;
    case ProfitabilityStatus::CRITICAL:
        cout << "CRITICAL";
        break;
    case ProfitabilityStatus::STABLE:
        cout << "STABLE";
        break;
    case ProfitabilityStatus::STRONG:
        cout << "STRONG";
        break;
    }
    cout << '\n';
}