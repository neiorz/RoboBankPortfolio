#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory> // For std::unique_ptr

#include "p1_Calc/include/RoboBankCalc.hpp"
#include "p2_Ledger/include/RoboBankLedger.h" // For Ledger's MAX_LEN, etc.

#include "Portfolio.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include "AccountSettings.h"
#include "TxRecord.h"
#include "TransferRecord.h"

// Helper function to print balance
void print_balance(const std::string &account_id, long long balance)
{
    std::cout << account_id << " balance: $" << std::fixed << std::setprecision(2) << static_cast<double>(balance) / 100.0 << std::endl;
}

int main()
{
    RoboBank::RoboBankCalc calculator; // Instantiate the calculator

    // 1. Create portfolio and accounts
    Portfolio portfolio(calculator);
    portfolio.set_auto_create_missing_accounts(true); // Enable auto-creation for Ledger path

    // Add CHK-001 (Checking, fee=150)
    AccountSettings chk_settings(AccountType::Checking, 0.0, 150);
    portfolio.add_account(std::make_unique<CheckingAccount>("CHK-001", chk_settings, 0, calculator));

    // Add SAV-010 (Savings, apr=5%)
    AccountSettings sav_settings(AccountType::Savings, 0.05, 0);
    portfolio.add_account(std::make_unique<SavingsAccount>("SAV-010", sav_settings, 0, calculator));

    std::cout << "--- Acceptance Example 1: Create portfolio and accounts ---" << std::endl;
    std::cout << "Portfolio size: " << portfolio.count_accounts() << std::endl; // Expected: 2
    std::cout << "----------------------------------------------------------" << std::endl
              << std::endl;

    // 2. Apply transactions (vector path)
    std::cout << "--- Acceptance Example 2: Apply transactions (vector path) ---" << std::endl;
    std::vector<TxRecord> txs_vector = {
        {TxKind::Deposit, 100000LL, 20250101100000LL, "Initial Deposit", "CHK-001"},
        {TxKind::Withdrawal, 25000LL, 20250102120000LL, "ATM Withdrawal", "CHK-001"},
        {TxKind::Fee, 1500LL, 20250104180000LL, "Monthly Service Fee", "CHK-001"}};
    portfolio.apply_all(txs_vector);
    print_balance("CHK-001", portfolio.balance_of("CHK-001")); // Expected: $735.00 (73500 cents)
    std::cout << "----------------------------------------------------------" << std::endl
              << std::endl;

    // 3. Savings interest
    std::cout << "--- Acceptance Example 3: Savings interest ---" << std::endl;
    // Initial deposit for SAV-010
    portfolio.get_account("SAV-010")->deposit(500000LL, 20250101000000LL, "Initial Savings Deposit");
    SavingsAccount *sav_acc = dynamic_cast<SavingsAccount *>(portfolio.get_account("SAV-010"));
    if (sav_acc)
    {
        sav_acc->apply_monthly_interest(31, 365, 20250131235959LL, "January Interest");
    }
    print_balance("SAV-010", portfolio.balance_of("SAV-010")); // Expected: ~502123 cents ($5021.23)
    std::cout << "----------------------------------------------------------" << std::endl
              << std::endl;

    // 4. Transfer between accounts
    std::cout << "--- Acceptance Example 4: Transfer between accounts ---" << std::endl;
    TransferRecord tr("SAV-010", "CHK-001", 30000LL, 20250201090000LL, "Transfer to Checking");
    if (portfolio.transfer(tr))
    {
        std::cout << "Transfer successful." << std::endl;
    }
    else
    {
        std::cout << "Transfer failed." << std::endl;
    }
    print_balance("CHK-001", portfolio.balance_of("CHK-001")); // CHK-001: 73500 + 30000 = 103500
    print_balance("SAV-010", portfolio.balance_of("SAV-010")); // SAV-010: 502123 - 30000 = 472123
    std::cout << "----------------------------------------------------------" << std::endl
              << std::endl;

    // 5. Apply transactions (Ledger path)
    std::cout << "--- Acceptance Example 5: Apply transactions (Ledger path) ---" << std::endl;
    // Mock Ledger-style arrays
    char tx_account_id_ledger[MAX_TX][MAX_LEN] = {
        "CHK-001", "CHK-001", "SAV-010", "SAV-010", "CHK-002", "CHK-001", "CHK-001"};
    int tx_type_ledger[MAX_TX] = {
        static_cast<int>(TxKind::Deposit),     // 0: Deposit
        static_cast<int>(TxKind::Withdrawal),  // 1: Withdrawal
        static_cast<int>(TxKind::Deposit),     // 0: Deposit
        static_cast<int>(TxKind::Interest),    // 3: Interest
        static_cast<int>(TxKind::Deposit),     // 4: TransferIn (used as deposit for new account)
        static_cast<int>(TxKind::TransferOut), // 5: TransferOut
        static_cast<int>(TxKind::Fee)          // 2: Fee
    };
    long long tx_amount_cents_ledger[MAX_TX] = {
        100000, // CHK-001 Deposit
        25000,  // CHK-001 Withdrawal
        500000, // SAV-010 Deposit (this will be added to existing balance)
        2000,   // SAV-010 Interest (this will be added to existing balance)
        30000,  // CHK-002 Deposit (new account)
        30000,  // CHK-001 TransferOut (this will be a withdrawal)
        1500    // CHK-001 Fee
    };
    int tx_count_ledger = 7;

    portfolio.apply_from_ledger(tx_account_id_ledger, tx_type_ledger, tx_amount_cents_ledger, tx_count_ledger);

    // Expected balances after Ledger transactions (based on example description)
    // CHK-001: 103500 (from prev) + 100000 - 25000 - 30000 - 1500 = 147000
    // SAV-010: 472123 (from prev) + 500000 + 2000 = 974123
    // CHK-002: 30000 (new account)
    print_balance("CHK-001", portfolio.balance_of("CHK-001")); // Expected: $1470.00
    print_balance("SAV-010", portfolio.balance_of("SAV-010")); // Expected: $9741.23
    print_balance("CHK-002", portfolio.balance_of("CHK-002")); // Expected: $300.00
    std::cout << "----------------------------------------------------------" << std::endl
              << std::endl;

    // 6. Totals
    std::cout << "--- Acceptance Example 6: Totals ---" << std::endl;
    print_balance("Total Exposure", portfolio.total_exposure()); // Sum of all balances
    std::cout << "----------------------------------------------------------" << std::endl
              << std::endl;

    return 0;
}
