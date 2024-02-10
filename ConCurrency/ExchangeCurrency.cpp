#include "ExchangeCurrency.hpp"

ExchangeCurrency::ExchangeCurrency(std::shared_ptr<CashRegister> cashRegister)
    : _cashRegister(cashRegister)
{
}

bool ExchangeCurrency::checkCurrencyAvailability(std::pair<double, double> exchangedMoney, std::string currencyCode)
{
    std::string currencyCode1 = currencyCode.substr(0, 3);
    std::string currencyCode2 = currencyCode.substr(3, 3);

    double cashRegisterForCurrency1 = _cashRegister->getCashRegistersForCurrencies().at(currencyCode1);
    double cashRegisterForCurrency2 = _cashRegister->getCashRegistersForCurrencies().at(currencyCode2);
    double cashRegisterForCurrencyPLN = _cashRegister->getCashRegistersForCurrencies().at("PLN");

    if (currencyCode1 == "PLN")
    {
        return ((exchangedMoney.first <= cashRegisterForCurrency2) && (exchangedMoney.second <= cashRegisterForCurrency1));
    }
    else if (currencyCode2 == "PLN")
    {
        return ((exchangedMoney.first <= cashRegisterForCurrency1) && (exchangedMoney.second <= cashRegisterForCurrency2));
    }
    else
    {
        return ((exchangedMoney.first <= cashRegisterForCurrency2) && (exchangedMoney.second <= cashRegisterForCurrencyPLN));
    }
}

void ExchangeCurrency::updateCurrenciesAmounts(double amount, std::pair<double, double> exchangedMoney, std::string currencyCode)
{
    std::string currencycode1 = currencyCode.substr(0, 3);
    std::string currencycode2 = currencyCode.substr(3, 3);

    std::map<std::string, double> cashRegistersCopy = _cashRegister->getCashRegistersForCurrencies();

    cashRegistersCopy.at(currencycode1) += amount;

    if (currencycode1 == "PLN")
    {
        cashRegistersCopy.at(currencycode1) -= exchangedMoney.second;
        cashRegistersCopy.at(currencycode2) -= exchangedMoney.first;
    }
    else if (currencycode2 == "PLN")
    {
        cashRegistersCopy.at(currencycode2) -= exchangedMoney.second;

    }
    else
    {
        cashRegistersCopy.at("PLN") -= exchangedMoney.second;
        cashRegistersCopy.at(currencycode2) -= exchangedMoney.first;
    }

    _cashRegister->setCashRegistersForCurrencies(cashRegistersCopy);
}
