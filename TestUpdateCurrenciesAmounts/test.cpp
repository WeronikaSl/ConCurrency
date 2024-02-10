#include "pch.h"
#include"..\ConCurrency\FromForeignToPLN.hpp"
#include"..\ConCurrency\FromForeignToForeign.hpp"
#include"..\ConCurrency\DataBase.hpp"
#include"..\ConCurrency\ExchangeCurrency.hpp"
#include"..\ConCurrency\FromPLNToForeign.hpp"
#include"..\ConCurrency\Cashier.hpp"
#include"..\ConCurrency\CashRegister.hpp"
#include "..\ConCurrency\OutOfCashException.hpp"

class TestCheckCurrencyAvailibility : public ::testing::Test
{
protected:

	TestCheckCurrencyAvailibility()
		:cashRegistersForCurrencies{ {"PLN",1000.0}, {"USD",180.0}, {"AUD",5000.0}, {"CAD",5000.0},{"EUR",202.99}, {"HUF",16487.99},
									 {"CHF",5000.0},{"GBP",5000.0}, {"JPY",1385.99}, {"CZK",5000.0}, {"DKK",5000.0}, {"NOK",5000.0},
									 {"SEK",5000.0}, {"XDR",5000.0} },
		cashRegister(std::make_shared<CashRegister>(cashRegistersForCurrencies)),
		exchangeToPLN(cashRegister),
		exchangeFromPLN(cashRegister),
		exchangeForeign(cashRegister)
	{};

	std::map<std::string, double> cashRegistersForCurrencies;
	std::shared_ptr <CashRegister> cashRegister;
	FromForeignToPLN exchangeToPLN;
	FromPLNToForeign exchangeFromPLN;
	FromForeignToForeign exchangeForeign;
};

TEST_F(TestCheckCurrencyAvailibility, exchange_FromPLNToEUR_checkCashRegisters)
{
	exchangeFromPLN.updateCurrenciesAmounts(1000.0, std::pair<double, double>(111.0, 4.41), "PLNEUR");
	EXPECT_NEAR(91.99, cashRegister->getCashRegistersForCurrencies().at("EUR"), 0.01);
	EXPECT_EQ(1995.59, cashRegister->getCashRegistersForCurrencies().at("PLN"));
}


TEST_F(TestCheckCurrencyAvailibility, exchange_FromUSDToPLN_checkCashRegisters)
{
	exchangeToPLN.updateCurrenciesAmounts(100.0, std::pair<double, double>(0.0, 496.58), "USDPLN");
	EXPECT_NEAR(503.42, cashRegister->getCashRegistersForCurrencies().at("PLN"), 0.01);
	EXPECT_EQ(280.0, cashRegister->getCashRegistersForCurrencies().at("USD"));
}

TEST_F(TestCheckCurrencyAvailibility, exchange_FromEURToUSD_checkCashRegisters)
{
	exchangeForeign.updateCurrenciesAmounts(100.0, std::pair<double, double>(95.0, 0.49), "EURUSD");
	EXPECT_NEAR(999.51, cashRegister->getCashRegistersForCurrencies().at("PLN"), 0.01);
	EXPECT_EQ(85.0, cashRegister->getCashRegistersForCurrencies().at("USD"));
	EXPECT_NEAR(302.99, cashRegister->getCashRegistersForCurrencies().at("EUR"), 0.1);
}

TEST_F(TestCheckCurrencyAvailibility, exchange_FromHUFToEUR_checkCashRegisters)
{
	exchangeForeign.updateCurrenciesAmounts(10000.0, std::pair<double, double>(23.0, 1.34), "HUFEUR");
	EXPECT_NEAR(998.66, cashRegister->getCashRegistersForCurrencies().at("PLN"), 0.01);
	EXPECT_EQ(179.99, cashRegister->getCashRegistersForCurrencies().at("EUR"));
	EXPECT_NEAR(26487.99, cashRegister->getCashRegistersForCurrencies().at("HUF"), 0.1);
}

TEST_F(TestCheckCurrencyAvailibility, exchange_FromEURToPLN_checkIfLessThenPLNBalance)
{
	EXPECT_THROW(exchangeToPLN.currencyExchange(500, "EURPLN"), OutOfCashException);
}

TEST_F(TestCheckCurrencyAvailibility, exchange_FromHUFToPLN_checkIfLessThenPLNBalance)
{
	EXPECT_THROW(exchangeToPLN.currencyExchange(90000, "HUFPLN"), OutOfCashException);
}

TEST_F(TestCheckCurrencyAvailibility, exchange_FromPLNToEUR_checkIfLessThenEURBalance)
{
	EXPECT_THROW(exchangeFromPLN.currencyExchange(1000, "PLNEUR"), OutOfCashException);
}

TEST_F(TestCheckCurrencyAvailibility, exchange_FromPLNToHUF_checkIfLessThenEURBalance)
{
	EXPECT_THROW(exchangeFromPLN.currencyExchange(200, "PLNHUF"), OutOfCashException);
}

TEST_F(TestCheckCurrencyAvailibility, exchange_FromForeignToForeignEURUSD_checkIfLessThenEURBalance)
{
	EXPECT_THROW(exchangeForeign.currencyExchange(200, "EURUSD"), OutOfCashException);
}

TEST_F(TestCheckCurrencyAvailibility, exchange_FromForeignToForeignEURJPY_checkIfLessThenEURBalance)
{
	EXPECT_THROW(exchangeForeign.currencyExchange(10, "EURJPY"), OutOfCashException);
}