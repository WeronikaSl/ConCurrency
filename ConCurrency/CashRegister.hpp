#pragma once
#include "JSONReader.hpp"
#include "JSONWriter.hpp"
#include <map>
#include <string>
#include <vector>
#include <fstream>


class CashRegister
{
private:

	std::map<std::string, double> _cashRegistersForCurrencies = {};
	JSONReader _jSONReader;
	JSONWriter _jSONWriter;

public:
	CashRegister();
	CashRegister(std::map<std::string, double> cashRegistersForCurrencies);
	std::map<std::string, double> getCashRegistersForCurrencies() const;
	void setCashRegistersForCurrencies(std::map<std::string, double> cashRegistersForCurrencies);
	void updateCurrenciesAmountsFromFile();
	void writeCurrenciesAmountsToJSONFile() const;


};