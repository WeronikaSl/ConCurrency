#include "FromForeignToPLN.hpp"
#include "OutOfCashException.hpp"
#include <utility>
#include <iostream>

FromForeignToPLN::FromForeignToPLN(std::shared_ptr<CashRegister> cashRegister)
    : ExchangeCurrency(cashRegister)
{
}

std::pair<double, double> FromForeignToPLN::currencyExchange(double amount, std::string currencyCode)
{
    FromForeignToPLN toPLN(_cashRegister);
    auto changedMoney = toPLN.changeForeignToPLN(amount, currencyCode);

    if (checkCurrencyAvailability(changedMoney, currencyCode))
    {
        updateCurrenciesAmounts(amount, changedMoney, currencyCode);
        return changedMoney;
    }
    else
    {
        throw OutOfCashException("Nie udalo sie przeprowadzic transakcji, brak potrzebnej ilości waluty w kasach.");
    }
}

std::pair<double, double> FromForeignToPLN::changeForeignToPLN(double amount, std::string currencyCode)
{
    double currencyRate = checkHUFandJPY(currencyCode);

    double PLNamount = amount * currencyRate;
    double roundedPLNamount = (round(PLNamount * 100)) / 100;

    return std::make_pair(0, roundedPLNamount);
}

double FromForeignToPLN::checkHUFandJPY(std::string currencyCode)
{
    if (currencyCode == "HUFPLN" || currencyCode == "JPYPLN")
    {
        return _database.getMapOfCurrencies().at(currencyCode) / 100.0;
    }
    else
    {
        return _database.getMapOfCurrencies().at(currencyCode);
    }
}
