#include "Portfolio.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include <iostream> // For logging/debugging

Portfolio::Portfolio(const RoboBank::RoboBankCalc &calc)
    : calculator_(calc) {}

void Portfolio::add_account(std::unique_ptr<IAccount> account)
{
    if (account)
    {
        accounts_[account->id()] = std::move(account);
    }
}

IAccount *Portfolio::get_account(const std::string &account_id) const
{
    auto it = accounts_.find(account_id);
    if (it != accounts_.end())
    {
        return it->second.get();
    }
    return nullptr;
}

IAccount *Portfolio::create_default_account(const std::string &account_id)
{
    // Default to Checking account with default settings
    AccountSettings default_settings(AccountType::Checking, 0.0, 0);
    auto new_account = std::make_unique<CheckingAccount>(account_id, default_settings, 0, calculator_);
    IAccount *raw_ptr = new_account.get();
    add_account(std::move(new_account));
    return raw_ptr;
}

void Portfolio::apply_all(const std::vector<TxRecord> &txs)
{
    for (const auto &tx : txs)
    {
        IAccount *account = get_account(tx.account_id);
        if (!account && auto_create_missing_accounts_)
        {
            std::cout << "Auto-creating account: " << tx.account_id << std::endl;
            account = create_default_account(tx.account_id);
        }

        if (account)
        {
            account->apply(tx);
            batch_audit_.push_back(tx); // Record in portfolio's audit
        }
        else
        {
            std::cerr << "Error: Account " << tx.account_id << " not found and auto-creation is disabled. Skipping transaction." << std::endl;
        }
    }
}

void Portfolio::apply_from_ledger(const char tx_account_id[][MAX_LEN], const int tx_type[], const int tx_amount_cents[], int tx_count)
{
    std::vector<TxRecord> txs;
    for (int i = 0; i < tx_count; ++i)
    {
        // Assuming a timestamp is needed, using a placeholder for now.
        // In a real scenario, Ledger might provide timestamps or a default could be generated.
        long long current_timestamp = calculator_.timestamp(); // Using calculator's timestamp for consistency
        txs.emplace_back(static_cast<TxKind>(tx_type[i]), tx_amount_cents[i], current_timestamp, "From Ledger", tx_account_id[i]);
    }
    apply_all(txs);
}

bool Portfolio::transfer(const TransferRecord &tr)
{
    IAccount *from_account = get_account(tr.from_id);
    IAccount *to_account = get_account(tr.to_id);

    if (!from_account || !to_account)
    {
        std::cerr << "Error: Transfer failed. One or both accounts not found (From: " << tr.from_id << ", To: " << tr.to_id << ")." << std::endl;
        return false; // Policy: return false if either side missing
    }

    // Perform withdrawal from 'from_account'
    from_account->withdraw(tr.amount_cents, tr.timestamp, tr.note + " (Transfer Out)");
    // Perform deposit to 'to_account'
    to_account->deposit(tr.amount_cents, tr.timestamp, tr.note + " (Transfer In)");

    // Record transfer in portfolio's audit (optional, but good for completeness)
    batch_audit_.emplace_back(TxKind::TransferOut, tr.amount_cents, tr.timestamp, tr.note, tr.from_id);
    batch_audit_.emplace_back(TxKind::TransferIn, tr.amount_cents, tr.timestamp, tr.note, tr.to_id);

    return true;
}

long long Portfolio::balance_of(const std::string &account_id) const
{
    IAccount *account = get_account(account_id);
    return account ? account->balance_cents() : 0;
}

long long Portfolio::total_exposure() const
{
    long long total = 0;
    for (const auto &pair : accounts_)
    {
        total = calculator_.add(total, pair.second->balance_cents());
    }
    return total;
}

std::unordered_map<AccountType, long long> Portfolio::totals_by_type() const
{
    std::unordered_map<AccountType, long long> totals;
    for (const auto &pair : accounts_)
    {
        totals[pair.second->type()] = calculator_.add(totals[pair.second->type()], pair.second->balance_cents());
    }
    return totals;
}

std::vector<std::string> Portfolio::list_account_ids() const
{
    std::vector<std::string> ids;
    for (const auto &pair : accounts_)
    {
        ids.push_back(pair.first);
    }
    return ids;
}
