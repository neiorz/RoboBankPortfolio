#include "RoboBankLedger.h"
#include <iostream>

using namespace std;

int main()
{
    char ac_account_id[MAX_ACCOUNTS][MAX_LEN] = {};
    int ac_balance[MAX_ACCOUNTS] = {};
    int ac_count = 0;

    char tx_account_id[MAX_TX][MAX_LEN] = {
        "CHK-001", "CHK-001", "SAV-010", "SAV-010", "CHK-002", "CHK-001", "CHK-001"};
    int tx_type[MAX_TX] = {0, 1, 0, 3, 4, 5, 2};
    int tx_amount_cents[MAX_TX] = {100000, 25000, 500000, 2000, 30000, 30000, 1500};
    int tx_count = 7;

    apply_all(tx_account_id, tx_type, tx_amount_cents, tx_count,
              ac_account_id, ac_balance, MAX_ACCOUNTS, ac_count);

    cout << "Balances after apply_all:\n";
    for (int i = 0; i < ac_count; i++)
    {
        cout << ac_account_id[i] << " = " << ac_balance[i] << endl;
    }

    int total_deposits, total_withdrawals, total_fees, total_interest, net_exposure;
    bank_summary(tx_type, tx_amount_cents, tx_count,
                 ac_balance, ac_count,
                 &total_deposits, &total_withdrawals,
                 &total_fees, &total_interest, &net_exposure);

    cout << "\nBank Summary:\n";
    cout << "Deposits: " << total_deposits << endl;
    cout << "Withdrawals: " << total_withdrawals << endl;
    cout << "Fees: " << total_fees << endl;
    cout << "Interest: " << total_interest << endl;
    cout << "Net Exposure: " << net_exposure << endl;

    return 0;
}
