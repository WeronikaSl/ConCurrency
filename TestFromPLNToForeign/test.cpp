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


//UPDATED TESTS

class TestFromPLNToForeign : public ::testing::Test
{
protected:

	TestFromPLNToForeign()
		:cashRegistersForCurrencies{ {"PLN",1000.0}, {"USD",5000.0}, {"AUD",5000.0}, {"CAD",5000.0},{"EUR",1000.0}, {"HUF",500000.0},
									 {"CHF",5000.0},{"GBP",5000.0}, {"JPY",500000.0}, {"CZK",5000.0}, {"DKK",5000.0}, {"NOK",5000.0},
									 {"SEK",5000.0}, {"XDR",5000.0} },
		cashRegister(std::make_shared<CashRegister>(cashRegistersForCurrencies)),
		testedMethod(cashRegister)
	{};

	std::map<std::string, double> cashRegistersForCurrencies;
	std::shared_ptr <CashRegister> cashRegister;
	FromPLNToForeign testedMethod;
};

TEST_F(TestFromPLNToForeign, exchange_FromPLNtoEUR_return0)
{
	auto result = testedMethod.currencyExchange(0, "EURPLN");
	EXPECT_EQ(result.first, 0);
	EXPECT_EQ(result.second, 0);
}
TEST_F(TestFromPLNToForeign, exchange_FromPLNtoEUR_willNotExchange)
{
	auto result = testedMethod.currencyExchange(3, "PLNEUR");
	EXPECT_EQ(result.first, 0);
	EXPECT_EQ(result.second, 3);
}
TEST_F(TestFromPLNToForeign, exchange_FromPLNtoEUR_returnException)
{
	EXPECT_THROW(testedMethod.currencyExchange(10000, "PLNEUR"), OutOfCashException);
}

TEST_F(TestFromPLNToForeign, exchange_FromPLNtoUSD_returnChange)
{
	auto result = testedMethod.currencyExchange(200, "PLNUSD");
	EXPECT_EQ(result.first, 39);
	EXPECT_EQ(result.second, 2.42);
}
TEST_F(TestFromPLNToForeign, exchange_FromPLNtoAUD_returnChange)
{
	auto result = testedMethod.currencyExchange(200, "PLNAUD");
	EXPECT_EQ(result.first, 62);
	EXPECT_EQ(result.second, 2.98);
}

TEST_F(TestFromPLNToForeign, exchange_FromPLNtoCAD_returnChange)
{
	auto result = testedMethod.currencyExchange(200, "PLNCAD");
	EXPECT_EQ(result.first, 54);
	EXPECT_EQ(result.second, 1.98);
}

TEST_F(TestFromPLNToForeign, exchange_FromPLNtoEUR_returnChange)
{
	auto result = testedMethod.currencyExchange(200, "PLNEUR");
	EXPECT_EQ(result.first, 40);
	EXPECT_EQ(result.second, 3.39);
}

//HUF
TEST_F(TestFromPLNToForeign, exchange_FromPLNtoHUF_returnNoChangeCase1)
{
	auto result = testedMethod.currencyExchange(100, "PLNHUF");
	EXPECT_EQ(result.first, 8244);
	EXPECT_EQ(result.second, 0);
}
TEST_F(TestFromPLNToForeign, exchange_FromPLNtoHUF_returnNoChangeCase2)
{
	auto result = testedMethod.currencyExchange(1000, "PLNHUF");
	EXPECT_EQ(result.first, 82440);
	EXPECT_EQ(result.second, 0);
}

TEST_F(TestFromPLNToForeign, exchange_FromPLNtoHUF_returnChangeCornerCase)
{
	auto result = testedMethod.currencyExchange(2000, "PLNHUF");
	EXPECT_EQ(result.first, 164880);
	EXPECT_EQ(result.second, 0.01);
}

TEST_F(TestFromPLNToForeign, exchange_FromPLNtoCHF_returnChange)
{
	auto result = testedMethod.currencyExchange(200, "PLNCHF");
	EXPECT_EQ(result.first, 39);
	EXPECT_EQ(result.second, 2.11);
}

TEST_F(TestFromPLNToForeign, exchange_FromPLNtoGBP_returnChange)
{
	auto result = testedMethod.currencyExchange(200, "PLNGBP");
	EXPECT_EQ(result.first, 35);
	EXPECT_EQ(result.second, 3.85);
}

//JEN
TEST_F(TestFromPLNToForeign, exchange_FromPLNtoJPY_returnNoChange)
{
	auto result = testedMethod.currencyExchange(100, "PLNJPY");
	EXPECT_EQ(result.first, 2877);
	EXPECT_EQ(result.second, 0);
}
TEST_F(TestFromPLNToForeign, exchange_FromPLNtoJPY_returnNoChangeCornerCase)
{
	auto result = testedMethod.currencyExchange(1000, "PLNJPY");
	EXPECT_EQ(result.first, 28770);
	EXPECT_EQ(result.second, 0.01);
}

TEST_F(TestFromPLNToForeign, exchange_FromPLNtoCZK_returnNoChangeCornerCase)
{
	auto result = testedMethod.currencyExchange(200, "PLNCZK");
	EXPECT_EQ(result.first, 998);
	EXPECT_EQ(result.second, 0);
}

TEST_F(TestFromPLNToForeign, exchange_FromPLNtoCZK_returnChange)
{
	auto result = testedMethod.currencyExchange(201, "PLNCZK");
	EXPECT_EQ(result.first, 1002);
	EXPECT_EQ(result.second, 0.2);
}

TEST_F(TestFromPLNToForeign, exchange_FromPLNtoDKK_returnChange)
{
	auto result = testedMethod.currencyExchange(200, "PLNDKK");
	EXPECT_EQ(result.first, 302);
	EXPECT_EQ(result.second, 0.47);
}

TEST_F(TestFromPLNToForeign, exchange_FromPLNtoNOK_returnChange)
{
	auto result = testedMethod.currencyExchange(200, "PLNNOK");
	EXPECT_EQ(result.first, 425);
	EXPECT_EQ(result.second, 0.21);
}

TEST_F(TestFromPLNToForeign, exchange_FromPLNtoSEK_returnChange)
{
	auto result = testedMethod.currencyExchange(200, "PLNSEK");
	EXPECT_EQ(result.first, 448);
	EXPECT_EQ(result.second, 0.19);
}

TEST_F(TestFromPLNToForeign, exchange_FromPLNtoXDR_returnChange)
{
	auto result = testedMethod.currencyExchange(200, "PLNXDR");
	EXPECT_EQ(result.first, 31);
	EXPECT_EQ(result.second, 0.53);
}


//FIRST TESTS ON BASIC FUNCTIONALITY
// 
//class TestFromPLNToEUR : public ::testing::Test
//{
//protected:
//	FromPLNToForeign exchange;
//	std::pair<int, double> result;
//};
//
//TEST_F(TestFromPLNToEUR, exchange_FromPLNtoEUR_returnNoChangeInPLN)
//{
//	result = exchange.currencyExchange(200, "EUR");
//	EXPECT_EQ(std::get<0>(result), 41);
//	EXPECT_EQ(std::get<1>(result), 0.08);
//}
//
//TEST_F(TestFromPLNToEUR, exchange_FromPLNtoEUR_willNotExchange)
//{
//	result = exchange.currencyExchange(3, "EUR");
//	EXPECT_EQ(std::get<0>(result), 0);
//	EXPECT_EQ(std::get<1>(result), 3);
//}
//
//TEST_F(TestFromPLNToEUR, exchange_FromPLNtoEUR_returnChangeInPLN)
//{
//	result = exchange.currencyExchange(10000, "EUR");
//	EXPECT_EQ(std::get<0>(result), 2050);
//	EXPECT_EQ(std::get<1>(result), 3.79);
//}
//
//TEST(TestFromPLNToEUR, exchange_FromPLNtoEUR_return0)
//{
//	FromPLNToForeign exchange;
//	auto result = exchange.currencyExchange(0, "EUR");
//	EXPECT_EQ(std::get<0>(result), 0);
//	EXPECT_EQ(std::get<1>(result), 0);
//}

