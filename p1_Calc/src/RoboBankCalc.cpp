#include "RoboBankCalc.hpp"
#include <thread>
#include <chrono>
#include <cmath>
#include <stdexcept>

static int round_cents(double value, RoundingPolicy policy)
{
    switch (policy)
    {
    case RoundingPolicy::HalfUp:
        return static_cast<int>(std::floor(value + 0.5));
    case RoundingPolicy::HalfEven:
    {
        int int_part = static_cast<int>(value);
        double frac = value - int_part;
        if (frac > 0.5 || (frac == 0.5 && (int_part % 2 != 0)))
            return int_part + 1;
        else
            return int_part;
    }
    default:
        throw std::invalid_argument("Unknown rounding policy");
    }
}

void Show(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

double Apply_Deposite(double balance, double amount)
{
    return balance + amount;
}

double Apply_withdrawal(double balance, double amount)
{
    if (amount > balance)
    {
        std::cout << "Insufficient funds!" << std::endl;
        return balance;
    }
    return balance - amount;
}

double Apply_Fee(double balance, double fee)
{
    if (fee > balance)
    {
        std::cout << "Fee exceeds balance!" << std::endl;
        return balance;
    }
    return balance - fee;
}

double Simple_Interest(double principal, double rate, double time)
{
    return principal * rate * time / 100.0;
}

double Compound_Amount(double principal, double rate, double time)
{
    return principal * pow(1 + rate / 100.0, time);
}

double Fx_convert(double value, double fx_rate)
{
    return value * fx_rate;
}

double Percent_Of(double value, double percent)
{
    return value * percent / 100.0;
}

// Balance operations
int apply_deposit(int balance, int amount)
{
    return balance + amount;
}
int apply_withdrawal(int balance, int amount)
{
    return balance - amount;
}
int apply_fee(int balance, int fee)
{
    return balance - fee;
}

// Interest
int simple_interest(int base, double apr, int days, int day_count_basis, RoundingPolicy rounding)
{
    double interest = base * apr * days / day_count_basis;
    return round_cents(interest, rounding);
}
int compound_amount(int principal, double apr, int years, int compounds_per_year, RoundingPolicy rounding)
{
    double rate_per_period = apr / compounds_per_year;
    int periods = years * compounds_per_year;
    double amount = principal * std::pow(1.0 + rate_per_period, periods);
    return round_cents(amount, rounding);
}

// Currency conversion
int fx_convert(int amount, const std::string &from_currency, const std::string &to_currency,
               const std::unordered_map<std::string, double> &fx_table, RoundingPolicy rounding)
{
    if (fx_table.count(from_currency) == 0 || fx_table.count(to_currency) == 0)
        throw std::invalid_argument("Currency code not found");
    double usd_amount = amount / fx_table.at(from_currency);
    double target_amount = usd_amount * fx_table.at(to_currency);
    return round_cents(target_amount, rounding);
}

// Utilities
int percent_of(int amount, double rate, RoundingPolicy rounding)
{
    return round_cents(amount * rate, rounding);
}
bool validate_rate(double rate)
{
    return rate >= 0.0 && rate <= 1.0;
}
bool validate_non_negative(int amount)
{
    return amount >= 0;
}
