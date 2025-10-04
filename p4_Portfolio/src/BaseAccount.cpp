#include "BaseAccount.h"
#include <algorithm>

BaseAccount::BaseAccount(const std::string &id, const AccountSettings &settings, long long opening_balance_cents, const RoboBank::RoboBankCalc &calc)
    : id_(id), settings_(settings), balance_cents_(opening_balance_cents), calculator_(calc) {}

void BaseAccount::record(TxKind kind, long long amount, long long timestamp, const std::string &note, const std::string &account_id)
{
    if (audit_.size() >= kMaxAudit)
    {
        // Drop oldest transaction if capacity is reached
        audit_.erase(audit_.begin());
    }
    audit_.emplace_back(kind, amount, timestamp, note, account_id);
}

void BaseAccount::deposit(long long amount_cents, long long timestamp, const std::string &note)
{
    balance_cents_ = calculator_.apply_deposit(balance_cents_, amount_cents);
    record(TxKind::Deposit, amount_cents, timestamp, note, id_);
}

void BaseAccount::withdraw(long long amount_cents, long long timestamp, const std::string &note)
{
    // Policy: Assume withdrawal can go negative for now, or add checks if needed
    balance_cents_ = calculator_.apply_withdrawal(balance_cents_, amount_cents);
    record(TxKind::Withdrawal, amount_cents, timestamp, note, id_);
}

void BaseAccount::charge_fee(long long fee_cents, long long timestamp, const std::string &note)
{
    balance_cents_ = calculator_.apply_fee(balance_cents_, fee_cents);
    record(TxKind::Fee, fee_cents, timestamp, note, id_);
}

void BaseAccount::post_simple_interest(int days, int basis, long long timestamp, const std::string &note)
{
    long long interest_amount = calculator_.simple_interest(balance_cents_, settings_.apr, days, basis, RoboBank::RoundingPolicy::HalfUp);
    balance_cents_ = calculator_.apply_deposit(balance_cents_, interest_amount);
    record(TxKind::Interest, interest_amount, timestamp, note, id_);
}

void BaseAccount::apply(const TxRecord &tx)
{
    // Note: The amount_cents in TxRecord for Withdrawal/Fee should be positive,
    // and the operation itself handles the subtraction.
    switch (tx.kind)
    {
    case TxKind::Deposit:
    case TxKind::TransferIn: // TransferIn is essentially a deposit
        deposit(tx.amount_cents, tx.timestamp, tx.note);
        break;
    case TxKind::Withdrawal:
    case TxKind::TransferOut: // TransferOut is essentially a withdrawal
        withdraw(tx.amount_cents, tx.timestamp, tx.note);
        break;
    case TxKind::Fee:
        charge_fee(tx.amount_cents, tx.timestamp, tx.note);
        break;
    case TxKind::Interest:
        // For interest, the amount_cents in TxRecord should be the calculated interest.
        // I'll assume the TxRecord already contains the calculated interest amount.
        // If the TxRecord only contains parameters for interest calculation,
        // this would need to be adjusted to call post_simple_interest with appropriate parameters.
        // For simplicity, assuming tx.amount_cents is the interest to be posted.
        deposit(tx.amount_cents, tx.timestamp, tx.note); // Interest increases balance
        break;
    default:
        // Handle unknown transaction kinds or log an error
        break;
    }
}
