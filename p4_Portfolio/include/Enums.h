#pragma once

enum class AccountType
{
    Checking = 0,
    Savings = 1
};

enum class TxKind
{
    Deposit = 0,
    Withdrawal = 1,
    Fee = 2,
    Interest = 3,
    TransferIn = 4,
    TransferOut = 5
};
