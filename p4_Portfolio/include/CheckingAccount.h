#pragma once
#include "BaseAccount.h"

class CheckingAccount : public BaseAccount
{
public:
    CheckingAccount(const std::string &id, const AccountSettings &settings, long long opening_balance_cents, const RoboBank::RoboBankCalc &calc)
        : BaseAccount(id, settings, opening_balance_cents, calc) {}

    AccountType type() const override { return AccountType::Checking; }

    // Checking-specific helper: apply monthly fee
    void apply_monthly_fee(long long timestamp, const std::string &note = "Monthly Fee");
};
