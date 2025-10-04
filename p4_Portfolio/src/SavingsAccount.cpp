#include "SavingsAccount.h"

void SavingsAccount::apply_monthly_interest(int days, int basis, long long timestamp, const std::string &note)
{
    if (settings_.apr > 0)
    {
        post_simple_interest(days, basis, timestamp, note);
    }
}
