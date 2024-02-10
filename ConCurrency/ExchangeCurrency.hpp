#pragma once
#include "DataBase.hpp"
#include <utility>
#include <string>
#include "CashRegister.hpp"

class ExchangeCurrency
{
protected:
	DataBase _database;
	std::shared_ptr<CashRegister> _cashRegister;
public:
	ExchangeCurrency(std::shared_ptr<CashRegister> cashRegister);

	virtual ~ExchangeCurrency() = default;
	virtual std::pair<double, double> currencyExchange(double amount, std::string currencyCode) = 0;

	bool checkCurrencyAvailability(std::pair<double, double> exchangedMoney, std::string currencyCode);
	void updateCurrenciesAmounts(double amount, std::pair<double, double> exchangedMoney, std::string currencyCode);
};