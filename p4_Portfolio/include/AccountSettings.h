#pragma once
#include "Enums.h"

struct AccountSettings
{
    AccountType type;
    double apr;               // Annual Percentage Rate
    long long fee_flat_cents; // Flat fee in cents

    // Constructor for convenience
    AccountSettings(AccountType t = AccountType::Checking, double a = 0.0, long long f = 0)
        : type(t), apr(a), fee_flat_cents(f) {}
};
