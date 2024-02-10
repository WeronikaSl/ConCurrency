#pragma once
#include "ExchangeCurrency.hpp"
#include <utility>

class FromPLNToForeign : public ExchangeCurrency
{
public:
	FromPLNToForeign(std::shared_ptr<CashRegister> cashRegister);
	std::pair<double, double> currencyExchange(double amount, std::string currencyCode) override;
	std::pair<double, double> changePLNtoForeign(double amount, std::string currencyCode);
	double checkHUFandJPY(std::string currencyCode);
};
