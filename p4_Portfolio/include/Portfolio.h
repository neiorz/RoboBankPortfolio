#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <memory> // For std::unique_ptr

#include "IAccount.h"
#include "TxRecord.h"
#include "TransferRecord.h"
#include "AccountSettings.h"
#include "p1_Calc/include/RoboBankCalc.hpp"
#include "p2_Ledger/include/RoboBankLedger.h" // For Ledger's MAX_LEN, etc.

class Portfolio
{
private:
    std::unordered_map<std::string, std::unique_ptr<IAccount>> accounts_;
    std::vector<TxRecord> batch_audit_;        // Audit trail for all transactions applied via Portfolio
    const RoboBank::RoboBankCalc &calculator_; // Reference to the shared calculator

    // Policy: Whether to auto-create accounts if missing during apply()
    bool auto_create_missing_accounts_ = false;

public:
    Portfolio(const RoboBank::RoboBankCalc &calc);

    // Life-cycle
    void add_account(std::unique_ptr<IAccount> account);
    IAccount *get_account(const std::string &account_id) const;
    size_t count_accounts() const { return accounts_.size(); }

    // Application (two paths)
    void apply_all(const std::vector<TxRecord> &txs);
    void apply_from_ledger(const char tx_account_id[][MAX_LEN], const int tx_type[], const int tx_amount_cents[], int tx_count);

    // Transfers
    bool transfer(const TransferRecord &tr);

    // Reports
    long long balance_of(const std::string &account_id) const;
    long long total_exposure() const;
    std::unordered_map<AccountType, long long> totals_by_type() const;
    std::vector<std::string> list_account_ids() const;

    // Configuration for policies
    void set_auto_create_missing_accounts(bool enable) { auto_create_missing_accounts_ = enable; }

private:
    // Helper to create a default account if auto_create_missing_accounts_ is true
    IAccount *create_default_account(const std::string &account_id);
};
