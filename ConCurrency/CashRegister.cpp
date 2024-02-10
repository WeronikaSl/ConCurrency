#include "CashRegister.hpp"

CashRegister::CashRegister()
{
    std::ifstream ifs("currenciesInCashRegister.json");
    _cashRegistersForCurrencies = _jSONReader.readFromFile(ifs);
}

CashRegister::CashRegister(std::map<std::string, double> cashRegistersForCurrencies):
    _cashRegistersForCurrencies(cashRegistersForCurrencies)
{
}

std::map<std::string, double> CashRegister::getCashRegistersForCurrencies() const
{
	return _cashRegistersForCurrencies;
}

void CashRegister::setCashRegistersForCurrencies(std::map<std::string, double> cashRegistersForCurrencies)
{
	this->_cashRegistersForCurrencies = cashRegistersForCurrencies;
}


void CashRegister::updateCurrenciesAmountsFromFile()
{
    std::ifstream ifs("currenciesInCashRegister.json");
    _cashRegistersForCurrencies = _jSONReader.readFromFile(ifs);
}

void CashRegister::writeCurrenciesAmountsToJSONFile() const
{
    std::ofstream o("currenciesInCashRegister.json");
    _jSONWriter.writeToFile(o, _cashRegistersForCurrencies);
}
