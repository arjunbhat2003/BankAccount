#pragma once
#include <string>

void deposit(double& balance, const double& amount);
bool withdraw(double& balance, const double& amount);
void overdraft(double& balance, const double& amount);
double interest_for_month(const double& balance, const double& apr);
void string_date_to_int_ptrs(const std::string& date, int* year, int* month,
                             int* day);
void string_date_to_ints(const std::string& date, int& year, int& month,
                         int& day);
int number_of_first_of_months(const std::string& date_1,
                              const std::string& date_2);
double interest_earned(const double& balance, const double& apr,
                       const std::string& date_1, const std::string& date_2);
std::string process_command(const std::string& line, std::string& prev_date,
                            double& balance, const double& apr);
std::string process_commands(const std::string& input, const double& apr);
