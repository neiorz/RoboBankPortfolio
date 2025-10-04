#include "CheckingAccount.h"

void CheckingAccount::apply_monthly_fee(long long timestamp, const std::string &note)
{
    if (settings_.fee_flat_cents > 0)
    {
        charge_fee(settings_.fee_flat_cents, timestamp, note);
    }
}
