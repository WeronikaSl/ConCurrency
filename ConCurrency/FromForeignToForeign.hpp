#pragma once
#include "ExchangeCurrency.hpp"
#include <utility>

class FromForeignToForeign : public ExchangeCurrency
{
public:
	FromForeignToForeign(std::shared_ptr<CashRegister> cashRegister);
	std::pair<double, double> currencyExchange(double amount, std::string currencyCode) override;
};