# RoboBank Portfolio

## Overview
RoboBank Portfolio is the final stage of a modular C++ banking system, built on top of:
- RoboBankCalculator (P1): handles all money math.
- RoboBankLedger (P2): stores and provides transaction records.
- RoboBankAccount (P3): represents individual bank accounts.
- RoboBankPortfolio (P4): manages multiple accounts and applies transactions across them.

This project demonstrates Inheritance, Polymorphism, and STL Containers through a realistic multi-account banking workflow.

---

## Features
- Polymorphic `IAccount` interface with specialized account types:
  - `CheckingAccount`
  - `SavingsAccount`
- Transaction management with:
  - `Deposit`, `Withdrawal`, `Fee`, `Interest`, and `Transfer`
- Batch processing of transactions via `std::vector<TxRecord>`
- Portfolio manager with:
  - `std::unordered_map<std::string, std::unique_ptr<IAccount>>` for account storage
  - Balance and summary reports
- Integration with previous modules for full system simulation

---

## Project Structure
## License
This project is open-source and available under the MIT License.

## Author
Nourhan Ahmed El-Shiekh  
