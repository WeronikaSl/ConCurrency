#pragma once
#include <string>
#include<map>
constexpr int numberOfAttempts = 3;
constexpr int numberOfSeconds = 3;

class CashierLogIn
{
public:
	bool checkCashierLogin();
	bool checkCashierPassword();
	void displayTime();
	void cashierLogInMain();

private:
	std::map<std::string, std::string> mapOfLoginsAndPasswords{
		{"cashier1","123456"},{"cashier2","678901"},{"cashier3","321456"}
	};
	std::string cashierLogin = {};
	std::string cashierPassword = {};

};

