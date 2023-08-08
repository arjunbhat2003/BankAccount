#include <iostream>
#include <string>
#include <sstream>
#include "bank_account.hpp"
using std::string;
using std::cin;
using std::cout;
using std::endl;

void deposit(double& balance, const double& amount) { balance += amount; }

bool withdraw(double& balance, const double& amount) {
  if (balance >= amount) {  // if able to withdraw
    balance -= amount;
    return true;
  }
  return false;  // else
}

void overdraft(double& balance, const double& amount) {
  balance -= amount + 35;
}

double interest_for_month(const double& balance, const double& apr) {
  int new_bal_cents = static_cast<int>(
      (apr / 1200) * (balance * 100));  // finds new balance in cents
  return static_cast<double>(new_bal_cents) /
         100;  // returns balance in dollars
}

void string_date_to_int_ptrs(const string& date, int* year, int* month,
                             int* day) {
  *year = stoi(date.substr(0, 4));
  *month = stoi(date.substr(5, 2));
  *day = stoi(date.substr(8, 2));
}

void string_date_to_ints(const string& date, int& year, int& month, int& day) {
  year = stoi(date.substr(0, 4));
  month = stoi(date.substr(5, 2));
  day = stoi(date.substr(8, 2));
}

int number_of_first_of_months(const string& date_1, const string& date_2) {
  int year_1, year_2, month_1, month_2, day_1, day_2;
  string_date_to_ints(date_1, year_1, month_1, day_1);
  string_date_to_ints(date_2, year_2, month_2, day_2);
  return (year_2 - year_1) * 12 + (month_2 - month_1);  // returns total months
}

double interest_earned(const double& balance, const double& apr,
                       const string& date_1, const string& date_2) {
  int months_interest = number_of_first_of_months(date_1, date_2);
  double new_balance = balance;
  for (int i = 0; i < months_interest; ++i) {
    new_balance += interest_for_month(new_balance, apr);
  }
  if (balance < -1) {  // no interest earned
    return 0;
  }
  return new_balance - balance;
}

string process_command(const string& line, string& prev_date, double& balance,
                       const double& apr) {
  string command = line.substr(11, line.find(" ", 11) - 11),
         new_date = line.substr(0, 10);  // inits variables
  if (prev_date.empty()) {
    prev_date = new_date;
  }
  string output = "On " + new_date + ": Instructed to perform \"" +
                  line.substr(11, static_cast<int>(line.size()) - 11) + "\"";
  double amount =
      stod(line.substr(line.find("$") + 1,
                       static_cast<int>(line.size()) - (line.find("$") + 1)));
  int months_interest = number_of_first_of_months(prev_date, new_date);
  if (months_interest > 0) {
    double interest = interest_earned(balance, apr, prev_date, new_date);
    output += "\nSince " + prev_date + ", interest has accrued " +
              std::to_string(months_interest) + " times.\n$";
    output += std::to_string(interest)
                  .substr(0, std::to_string(interest).find(".") + 3) +
              " interest has been earned.";
    balance += interest;
  }
  if (command == "Deposit") {
    deposit(balance, amount);
  } else if (command == "Withdraw") {
    if (!withdraw(balance, amount)) {
      overdraft(balance, amount);
      output += "\nOverdraft!";
    }
  }
  output +=
      "\nBalance: " +
      std::to_string(balance).substr(0, std::to_string(balance).find(".") + 3) +
      "\n";
  prev_date = new_date;
  return output;
}

string process_commands(const string& input, const double& apr) {
  string output = "", prev_date = "", temp_string;
  double balance = 0;
  std::istringstream is(input);  // inits input stringstream
  while (std::getline(is, temp_string)) {
    output += process_command(temp_string, prev_date, balance, apr);
  }
  return output;
}