#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <string>
#include <unordered_map>

enum class RoundingPolicy
{
    HalfUp,
    HalfEven
};

// Function prototypes
void Show(int ms);
double Apply_Deposite(double balance, double amount);
double Apply_withdrawal(double balance, double amount);
double Apply_Fee(double balance, double fee);
double Simple_Interest(double principal, double rate, double time);
double Compound_Amount(double principal, double rate, double time);
double Fx_convert(double value, double fx_rate);
double Percent_Of(double value, double percent);

// Balance operations
int apply_deposit(int balance, int amount);
int apply_withdrawal(int balance, int amount);
int apply_fee(int balance, int fee);

// Interest
int simple_interest(int base, double apr, int days, int day_count_basis, RoundingPolicy rounding);
int compound_amount(int principal, double apr, int years, int compounds_per_year, RoundingPolicy rounding);

// Currency conversion
int fx_convert(int amount, const std::string &from_currency, const std::string &to_currency,
               const std::unordered_map<std::string, double> &fx_table, RoundingPolicy rounding);

// Utilities
int percent_of(int amount, double rate, RoundingPolicy rounding);
bool validate_rate(double rate);
bool validate_non_negative(int amount);

#endif // HEADER_HPP
