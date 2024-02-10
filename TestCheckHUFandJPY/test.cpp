#include "pch.h"
#include "../ConCurrency/ExchangeCurrency.hpp"
#include "../ConCurrency/FromPLNToForeign.hpp"
#include "../ConCurrency/DataBase.hpp"
#include "../ConCurrency/CashRegister.hpp"
#include "../ConCurrency/Cashier.hpp"
#include "../ConCurrency/DataToDisplay.hpp"
#include "../ConCurrency/JSONReader.hpp"
#include "../ConCurrency/JSONWriter.hpp"
#include "..\ConCurrency\OutOfCashException.hpp"


class TestCheckHUFandJPY : public ::testing::Test
{
protected:

	TestCheckHUFandJPY()
		:cashRegistersForCurrencies{ {"PLN",1000.0}, {"USD",5000.0}, {"AUD",5000.0}, {"CAD",5000.0},{"EUR",1000.0}, {"HUF",500000.0},
									 {"CHF",5000.0},{"GBP",5000.0}, {"JPY",500000.0}, {"CZK",5000.0}, {"DKK",5000.0}, {"NOK",5000.0},
									 {"SEK",5000.0}, {"XDR",5000.0} },
		cashRegister(std::make_shared<CashRegister>(cashRegistersForCurrencies)),
		exchangeFromPLN(cashRegister)
	{};

	std::map<std::string, double> cashRegistersForCurrencies;
	std::shared_ptr <CashRegister> cashRegister;
	FromPLNToForeign exchangeFromPLN;
};

TEST_F(TestCheckHUFandJPY, checkHUFexchange)
{
	double result = exchangeFromPLN.checkHUFandJPY("PLNHUF");
	EXPECT_NEAR(0.01213, result, 0.01);
}

TEST_F(TestCheckHUFandJPY, checkJPYexchange)
{
	double result = exchangeFromPLN.checkHUFandJPY("PLNJPY");
	EXPECT_NEAR(0.034758, result, 0.01);
}

TEST_F(TestCheckHUFandJPY, checkOtherCurrencyexchangePLNEUR)
{
	double result = exchangeFromPLN.checkHUFandJPY("PLNEUR");
	EXPECT_EQ(4.9152, result);
}

TEST_F(TestCheckHUFandJPY, checkOtherCurrencyexchangePLNNOK)
{
	double result = exchangeFromPLN.checkHUFandJPY("PLNNOK");
	EXPECT_EQ(0.4701, result);
}