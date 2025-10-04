#pragma once
#include <string>
#include <vector>
#include <memory> // For std::unique_ptr
#include "Enums.h"
#include "AccountSettings.h"
#include "TxRecord.h"

// Forward declaration of RoboBankCalc to avoid circular dependency if RoboBankCalc.hpp includes IAccount.h
namespace RoboBank
{
    class RoboBankCalc;
}

class IAccount
{
public:
    virtual ~IAccount() = default;

    // Identity & metadata
    virtual const std::string &id() const = 0;
    virtual AccountType type() const = 0;
    virtual long long balance_cents() const = 0;

    // Operations (Calculator-backed)
    virtual void deposit(long long amount_cents, long long timestamp, const std::string &note = "") = 0;
    virtual void withdraw(long long amount_cents, long long timestamp, const std::string &note = "") = 0;
    virtual void charge_fee(long long fee_cents, long long timestamp, const std::string &note = "") = 0;
    virtual void post_simple_interest(int days, int basis, long long timestamp, const std::string &note = "") = 0;
    virtual void apply(const TxRecord &tx) = 0;

    // Audit trail
    virtual const std::vector<TxRecord> &audit_data() const = 0;
    virtual int audit_size() const = 0;
};
