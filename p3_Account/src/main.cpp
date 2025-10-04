#include <iostream>
#include "account.h"

int main()
{
    // Checking account with fee
    AccountSettings settings1 = {Checking, 0.00, 150};
    Account A("CHK-001", settings1, 0);
    A.deposit(100000, 20250101100000);
    A.withdraw(25000, 20250102120000);
    A.charge_fee(1500, 20250104180000);
    std::cout << "A balance: " << A.balance_cents() << std::endl;
    std::cout << "A audit size: " << A.audit_size() << std::endl;

    // Savings interest
    AccountSettings settings2 = {Savings, 0.05, 0};
    Account S("SAV-010", settings2, 500000);
    S.post_simple_interest(31, 365, 20250131235959);
    std::cout << "S balance: " << S.balance_cents() << std::endl;
    const TxRecord *audit = S.audit_data();
    std::cout << "S last audit: kind=" << audit[S.audit_size() - 1].kind << ", amt=" << audit[S.audit_size() - 1].amount_cents << std::endl;

    // Apply prebuilt records
    TxRecord t1 = {Deposit, 100000, 20250101100000, "payroll"};
    TxRecord t2 = {Withdrawal, 25000, 20250102120000, "atm"};
    TxRecord t3 = {Fee, 1500, 20250104180000, "monthly"};
    Account B("CHK-002", settings1, 0);
    B.apply(t1);
    B.apply(t2);
    B.apply(t3);
    std::cout << "B balance: " << B.balance_cents() << std::endl;

    // Audit capacity
    for (int i = 0; i < 260; ++i)
    {
        A.deposit(1, 20250101000000 + i);
    }
    std::cout << "A audit size after 260 ops: " << A.audit_size() << std::endl;
    return 0;
}
