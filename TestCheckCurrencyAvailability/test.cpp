#include "pch.h"
#include"..\ConCurrency\FromForeignToPLN.hpp"
#include"..\ConCurrency\FromForeignToForeign.hpp"
#include"..\ConCurrency\DataBase.hpp"
#include"..\ConCurrency\ExchangeCurrency.hpp"
#include"..\ConCurrency\FromPLNToForeign.hpp"
#include"..\ConCurrency\Cashier.hpp"
#include"..\ConCurrency\CashRegister.hpp"

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

TEST_F(TestCheckCurrencyAvailibility, checkIfLessThenEURBalance_returnTrue)
{
	bool result = exchangeFromPLN.checkCurrencyAvailability(std::pair<double, double>(203.0, 2.21), "PLNEUR");
	EXPECT_TRUE(true, result);
}

TEST_F(TestCheckCurrencyAvailibility, checkIfEqualToEURBalance_returnTrue)
{
	bool result = exchangeFromPLN.checkCurrencyAvailability(std::pair<double, double>(406.0, 4.43), "PLNEUR");
	EXPECT_TRUE(true, result);
}
TEST_F(TestCheckCurrencyAvailibility, checkIfMoreThenEURBalance_returnFalse)
{
	bool result = exchangeFromPLN.checkCurrencyAvailability(std::pair<double, double>(407.0, 4.51), "PLNEUR");
	EXPECT_FALSE(false, result);
}

TEST_F(TestCheckCurrencyAvailibility, checkWithEmptyNOKBalance_returnFalse)
{
	bool result = exchangeFromPLN.checkCurrencyAvailability(std::pair<double, double>(0.21, 425.0), "PLNNOK");
	EXPECT_FALSE(false, result);
}

TEST_F(TestCheckCurrencyAvailibility, checkIfLessThenHUFBalance_returnTrue)
{
	bool result = exchangeFromPLN.checkCurrencyAvailability(std::pair<double, double>(0, 16488.0), "PLNHUF");
	EXPECT_TRUE(true, result);
}

TEST_F(TestCheckCurrencyAvailibility, checkIfEqualToHUFBalance_returnTrue)
{
	bool result = exchangeFromPLN.checkCurrencyAvailability(std::pair<double, double>(0, 24732.0), "PLNHUF");
	EXPECT_TRUE(true, result);
}

TEST_F(TestCheckCurrencyAvailibility, checkIfMoreThenHUFBalance_returnFalse)
{
	bool result = exchangeFromPLN.checkCurrencyAvailability(std::pair<double, double>(0.03, 69304), "PLNHUF");
	EXPECT_FALSE(false, result);
}


TEST_F(TestCheckCurrencyAvailibility, checkIfLessThenPLNBalance_returnTrue)
{
	bool result = exchangeToPLN.checkCurrencyAvailability(std::pair<double, double>(0, 1484.77), "USDPLN");
	EXPECT_TRUE(true, result);
}

TEST_F(TestCheckCurrencyAvailibility, checkIfEqualToPLNBalance_returnTrue)
{
	bool result = exchangeToPLN.checkCurrencyAvailability(std::pair<double, double>(0, 1489.74), "USDPLN");
	EXPECT_TRUE(true, result);
}
TEST_F(TestCheckCurrencyAvailibility, checkIfMoreThenPLNBalance_returnFalse)
{
	bool result = exchangeToPLN.checkCurrencyAvailability(std::pair<double, double>(0, 1494.71), "USDPLN");
	EXPECT_FALSE(false, result);
}

TEST_F(TestCheckCurrencyAvailibility, checkIfLessThenCHFBalance_returnTrue)
{
	bool result = exchangeForeign.checkCurrencyAvailability(std::pair<double, double>(3.98, 473), "EURCHF");
	EXPECT_TRUE(true, result);
}
TEST_F(TestCheckCurrencyAvailibility, checkIfEqualToCHFBalance_returnTrue)
{
	bool result = exchangeForeign.checkCurrencyAvailability(std::pair<double, double>(3.73, 474), "EURCHF");
	EXPECT_TRUE(true, result);
}
TEST_F(TestCheckCurrencyAvailibility, checkIfMoreThenCHFBalance_returnFalse)
{
	bool result = exchangeForeign.checkCurrencyAvailability(std::pair<double, double>(2.47, 475), "EURCHF");
	EXPECT_FALSE(false, result);
}

TEST_F(TestCheckCurrencyAvailibility, checkIfLessThenJPYBalance_returnTrue)
{
	bool result = exchangeForeign.checkCurrencyAvailability(std::pair<double, double>(0.03, 69166), "EURJPY");
	EXPECT_TRUE(true, result);
}

TEST_F(TestCheckCurrencyAvailibility, checkIfEqualToJPYBalance_returnTrue)
{
	bool result = exchangeForeign.checkCurrencyAvailability(std::pair<double, double>(0.03, 69304), "EURJPY");
	EXPECT_TRUE(true, result);
}

TEST_F(TestCheckCurrencyAvailibility, checkIfMoreThenJPYBalance_returnFalse)
{
	bool result = exchangeForeign.checkCurrencyAvailability(std::pair<double, double>(0.02, 69443), "EURJPY");
	EXPECT_FALSE(false, result);
}
