#pragma once
#include <string>
#include "Enums.h"
#include "p3_Account/include/structs.h"

// Extend P3's TxRecord with account_id for Portfolio routing
struct TxRecord : public p3_TxRecord
{ // Assuming p3_TxRecord has kind, amount_cents, timestamp, note
    std::string account_id;

    // Default constructor
    TxRecord() : p3_TxRecord(), account_id("") {}

    // Constructor matching the description
    TxRecord(TxKind k, long long amt, long long ts, const std::string &n, const std::string &id)
        : p3_TxRecord(static_cast<int>(k), amt, ts, n.c_str()), account_id(id) {}

    // Constructor for p3_TxRecord conversion (if needed)
    TxRecord(const p3_TxRecord &p3_tx, const std::string &id)
        : p3_TxRecord(p3_tx), account_id(id) {}
};
