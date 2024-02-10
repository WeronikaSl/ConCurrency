#include "Cashier.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

Cashier::Cashier()
{
	DataToDisplay data;
	this->_data = data;
}

Cashier::Cashier(std::shared_ptr<ExchangeCurrency> exchange, std::shared_ptr<CashRegister> cashRegister)
	: _exchange(exchange), _cashregister(cashRegister)
{
}

void Cashier::setExchange(std::shared_ptr<ExchangeCurrency> exchange)
{
	_exchange = exchange;
}

void Cashier::setCashRegister(std::shared_ptr<CashRegister> cashregister)
{
	_cashregister = cashregister;
}

std::pair <double, double> Cashier::exchangeCurrencyforCashier(int amount, std::string CurrencyCode)
{
	_cashregister->updateCurrenciesAmountsFromFile();

	std::pair <double, double> exchangedMoney = _exchange->currencyExchange(amount, CurrencyCode);

	_cashregister->writeCurrenciesAmountsToJSONFile();

	return exchangedMoney;
}

void Cashier::displayUpdatedCashRegisterBalance()
{

	//THIRD APPROACH USING TABULATE

	Table table;
	table.add_row({ "CASH REGISTER BALANCE" });
	table.format()
		.corner("$")
		.font_align(FontAlign::center)
		.corner_color(Color::yellow)
		.border_color(Color::yellow);
	table[0].format()
		.font_color(Color::yellow)
		.font_style({ FontStyle::bold });

	Table tableTitle;
	tableTitle.add_row({ "Amount of money", "Currency code" });
	table.format().font_align(FontAlign::center);
	tableTitle.column(0).format().width(27);
	tableTitle.column(1).format().width(27);

	for (size_t i = 0; i < 2; ++i)
	{
		tableTitle[0][i].format()
			.font_align(FontAlign::center);
	}

	table.add_row({ tableTitle });
	std::cout << table << std::endl;

	auto map = _cashregister->getCashRegistersForCurrencies();
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		std::cout << "-------------------------------------------------------------" << std::endl;
		std::cout << "|" << std::setw(15) << std::setprecision(8) << it->second << std::setw(15) << "|" << std::setw(15) << it->first << std::setw(15) << "|" << std::endl;
		std::cout << "-------------------------------------------------------------" << std::endl;
	}
}

void Cashier::displayCurrencyRateTable()
{

	Table main;
	main.add_row({ "CURRENCY RATE TABLE" });
	main.format().font_align(FontAlign::center);

	Table rate;
	rate.add_row({ "Currency name", "Currency code", "Currency rate" });
	rate.column(0).format().width(27);
	rate.column(1).format().width(19);
	rate.column(2).format().width(26);

	Table buySellRate;
	buySellRate.add_row({ "Buy rate", "Sell rate" });
	rate.add_row({ "","",buySellRate });

	for (size_t i = 0; i < 3; ++i)
	{
		rate[0][i].format()
			.font_align(FontAlign::center);
	}

	main.add_row({ rate });
	main.format()
		.corner("$")
		.font_style({ FontStyle::bold })
		.corner_color(Color::yellow)
		.border_color(Color::yellow);
	main[0].format()
		.font_color(Color::yellow)
		.font_style({ FontStyle::bold });

	main[1].format().font_style({ FontStyle::dark });

	std::cout << std::endl;
	std::cout << main << std::endl;

	const int size = _data.getVectorOfCurrencies().size();
	for (int i = 0; i < size; ++i)
	{
		std::cout << "--------------------------------------------------------------------------------" << std::endl;
		std::cout << "|" << std::setw(20) << _data.getVectorOfCurrencies().at(i)._name << std::setw(10) << "|" << std::setw(10) << _data.getVectorOfCurrencies().at(i)._currencyCode << std::setw(10) << "|" << std::setw(8) << _data.getVectorOfCurrencies().at(i)._currencyRateBuy << std::setw(5) << "|" << std::setw(11) << _data.getVectorOfCurrencies().at(i)._currencyRateSell << std::setw(5) << "|" << std::endl;
		std::cout << "--------------------------------------------------------------------------------" << std::endl;
	}
	std::cout << std::endl;
}

void Cashier::updateCurrencyRatesInDataBase()
{
	_dataBase.updateCurrenciesAmountsFromFile();
}

