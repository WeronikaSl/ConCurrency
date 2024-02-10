#pragma once
#include "ExchangeCurrency.hpp"
#include <utility>

class FromForeignToPLN : public ExchangeCurrency
{
public:
	FromForeignToPLN(std::shared_ptr<CashRegister> cashRegister);
	std::pair<double, double> currencyExchange(double amount, std::string currencyCode) override;
	std::pair<double, double> changeForeignToPLN(double amount, std::string currencyCode);
	double checkHUFandJPY(std::string currencyCode);
}; 