#pragma once
#include <string>

struct Currency
{
	std::string _name;
	std::string _currencyCode;
	double _currencyRateBuy;
	double _currencyRateSell;

	Currency(std::string name, std::string currencyCode, double currencRateBuy, double currencyRateSell);
};