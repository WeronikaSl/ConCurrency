#include "DataBase.hpp"

std::map<std::string, double> DataBase::getMapOfCurrencies()
{
    return _mapOfCurrencies;
}

void DataBase::updateCurrenciesAmountsFromFile()
{
    std::ifstream ifs("currencies.json");
    _mapOfCurrencies = _jSONReader.readFromFile(ifs);
}
