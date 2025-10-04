#pragma once
#include "IAccount.h"
#include "p1_Calc/include/RoboBankCalc.hpp" // actual calculator header
#include <vector>
#include <string>

const int kMaxAudit = 256; // Audit capacity

class BaseAccount : public IAccount
{
protected:
    std::string id_;
    AccountSettings settings_;
    long long balance_cents_;
    std::vector<TxRecord> audit_;
    const RoboBank::RoboBankCalc &calculator_; // Reference to the calculator instance

    // Helper to record transactions
    void record(TxKind kind, long long amount, long long timestamp, const std::string &note, const std::string &account_id);

public:
    BaseAccount(const std::string &id, const AccountSettings &settings, long long opening_balance_cents, const RoboBank::RoboBankCalc &calc);

    const std::string &id() const override { return id_; }
    AccountType type() const override = 0; // Pure virtual
    long long balance_cents() const override { return balance_cents_; }

    void deposit(long long amount_cents, long long timestamp, const std::string &note = "") override;
    void withdraw(long long amount_cents, long long timestamp, const std::string &note = "") override;
    void charge_fee(long long fee_cents, long long timestamp, const std::string &note = "") override;
    void post_simple_interest(int days, int basis, long long timestamp, const std::string &note = "") override;
    void apply(const TxRecord &tx) override;

    const std::vector<TxRecord> &audit_data() const override { return audit_; }
    int audit_size() const override { return audit_.size(); }
};
