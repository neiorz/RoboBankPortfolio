#include "RoboBankCalc.hpp"
#include <iostream>
#include <unordered_map>

int main()
{
    int balance = 12345; // $123.45
    int deposit = 700;   // $7.00
    int new_balance = apply_deposit(balance, deposit);
    std::cout << "Deposit: " << balance << " + " << deposit << " = " << new_balance << std::endl;

    int withdrawal = 7500;
    int after_withdrawal = apply_withdrawal(5000, withdrawal);
    std::cout << "Withdrawal: 5000 - 7500 = " << after_withdrawal << std::endl;

    int interest = simple_interest(100000, 0.0425, 365, 365, RoundingPolicy::HalfUp);
    std::cout << "Simple Interest on $1000.00 at 4.25% for 1 year: " << interest << std::endl;

    int compound = compound_amount(100000, 0.05, 2, 12, RoundingPolicy::HalfUp);
    std::cout << "Compound Amount: " << compound << std::endl;

    std::unordered_map<std::string, double> fx = {{"USD", 1.0}, {"EUR", 0.91}};
    int fx_result = fx_convert(10000, "USD", "EUR", fx, RoundingPolicy::HalfUp);
    std::cout << "FX: $100.00 to EUR at 0.91 = " << fx_result << std::endl;

    int percent = percent_of(123, 0.0275, RoundingPolicy::HalfUp);
    std::cout << "Percent Of: 2.75% of 123 = " << percent << std::endl;

    return 0;
}