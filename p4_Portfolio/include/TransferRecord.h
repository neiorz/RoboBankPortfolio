#pragma once
#include <string>

struct TransferRecord
{
    std::string from_id;
    std::string to_id;
    long long amount_cents;
    long long timestamp;
    std::string note;

    TransferRecord(const std::string &from, const std::string &to, long long amt,
                   long long ts, const std::string &n)
        : from_id(from), to_id(to), amount_cents(amt), timestamp(ts), note(n) {}
};
