#pragma once
#include "BaseAccount.h"

class SavingsAccount : public BaseAccount
{
public:
    SavingsAccount(const std::string &id, const AccountSettings &settings, long long opening_balance_cents, const RoboBank::RoboBankCalc &calc)
        : BaseAccount(id, settings, opening_balance_cents, calc) {}

    AccountType type() const override { return AccountType::Savings; }

    // Savings-specific helper: post monthly interest
    void apply_monthly_interest(int days, int basis, long long timestamp, const std::string &note = "Monthly Interest");
};
