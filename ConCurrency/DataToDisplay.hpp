#pragma once
#include <string>
#include <vector>
#include "DataBase.hpp"
#include "Currency.hpp"

class DataToDisplay
{
private:
	DataBase _dataBase;
	std::vector<Currency> _vectorOfCurrencies;
	std::vector <std::string> _currencyNames = { "American Dollar", "Australian Dollar", "Canadian Dollar", "Euro", "Forint (100)", "Swiss franc", "British Pound", "Yen (100)", "Czech Koruna", "Danish Krone", "Norwegian Krone", "Swedish Krona", "SDR (MFW)" };
	std::vector <std::string> _currencyID = { "USD", "AUD", "CAD", "EUR", "HUF", "CHF", "GBP", "JPY", "CZK", "DKK", "NOK", "SEK", "XDR" };
public:
	DataToDisplay();
	void setVectorOfCurrencies(std::vector<Currency> vectorOfCurrencies);
	std::vector<Currency> getVectorOfCurrencies();
};
