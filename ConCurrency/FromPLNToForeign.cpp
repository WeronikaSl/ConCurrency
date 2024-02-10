#include "FromPLNToForeign.hpp"
#include "OutOfCashException.hpp"
#include <utility>
#include <iostream>

FromPLNToForeign::FromPLNToForeign(std::shared_ptr<CashRegister> cashRegister)
    : ExchangeCurrency(cashRegister)
{
}

std::pair<double, double> FromPLNToForeign::currencyExchange(double amount, std::string currencyCode)
{
    FromPLNToForeign fromPLN(_cashRegister);
    auto changedMoney = fromPLN.changePLNtoForeign(amount, currencyCode);

    if (checkCurrencyAvailability(changedMoney, currencyCode))
    {
        updateCurrenciesAmounts(amount, changedMoney, currencyCode);
        return changedMoney;
    }
    else
    {
        throw OutOfCashException("Nie udalo sie przeprowadzic transakcji, brak potrzebnej ilosci waluty w kasach.");
    }
}

std::pair<double, double> FromPLNToForeign::changePLNtoForeign(double amount, std::string currencyCode)
{
    double currencyRate = checkHUFandJPY(currencyCode);

    double foreignAmount = floor(amount / currencyRate);
    double PLNamount = amount - (foreignAmount * currencyRate);
    double roundedPLNamount = (round(PLNamount * 100)) / 100.0;

    return std::make_pair(foreignAmount, roundedPLNamount);
}

double FromPLNToForeign::checkHUFandJPY(std::string currencyCode)
{
    if (currencyCode == "PLNHUF" || currencyCode == "PLNJPY")
    {
        return _database.getMapOfCurrencies().at(currencyCode) / 100.0;
    }
    else
    {
        return _database.getMapOfCurrencies().at(currencyCode);
    }
}
