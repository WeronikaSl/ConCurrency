#include "DataToDisplay.hpp"
#include "Cashier.hpp"
#include <iostream>

DataToDisplay::DataToDisplay()
{

	for (int i = 0; i < 13; ++i)
	{
		std::string name = _currencyNames.at(i);
		std::string currencyCode = _currencyID.at(i);
		if (currencyCode == "HUF" || currencyCode == "JPY")
		{
			std::string currencyCode = "100 " + _currencyID.at(i);
		}
		else
		{
			std::string currencyCode = _currencyID.at(i);
		}

		std::string strBuy = currencyCode + "PLN";
		if (currencyCode == "HUF" || currencyCode == "JPY")
		{
			double currencyRateBuy = _dataBase.getMapOfCurrencies().at(strBuy);
		}
		double currencyRateBuy = _dataBase.getMapOfCurrencies().at(strBuy);

		std::string strSell = "PLN" + currencyCode;
		double currencyRateSell = _dataBase.getMapOfCurrencies().at(strSell);

		//wypełnianie wektora 13toma obiektami Currency, poprzez iteracje po poszczegolnych elementach
		Currency currency(name, currencyCode, currencyRateBuy, currencyRateSell);
		_vectorOfCurrencies.push_back(currency);
	}
}

void DataToDisplay::setVectorOfCurrencies(std::vector<Currency> vectorOfCurrencies) //wypełnia ektor i-toma elementami
{
	_vectorOfCurrencies = vectorOfCurrencies;
}

std::vector<Currency> DataToDisplay::getVectorOfCurrencies() //tworzy pusty wektor i-tych elementow
{
	return _vectorOfCurrencies;
}
