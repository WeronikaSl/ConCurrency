#include "pch.h"
#include"..\ConCurrency\FromForeignToPLN.hpp"
#include"..\ConCurrency\FromForeignToForeign.hpp"
#include"..\ConCurrency\DataBase.hpp"
#include"..\ConCurrency\ExchangeCurrency.hpp"
#include"..\ConCurrency\FromPLNToForeign.hpp"
#include"..\ConCurrency\Cashier.hpp"
#include"..\ConCurrency\CashRegister.hpp"
#include "..\ConCurrency\OutOfCashException.hpp"
class TestFromForeignToForeign : public ::testing::Test
{
protected:

	TestFromForeignToForeign()
		:cashRegistersForCurrencies{ {"PLN",100000.0}, {"USD",5000.0}, {"AUD",5000.0}, {"CAD",5000.0},{"EUR",5000.0}, {"HUF",500000.0},
									 {"CHF",5000.0},{"GBP",5000.0}, {"JPY",500000.0}, {"CZK",5000.0}, {"DKK",5000.0}, {"NOK",5000.0},
									 {"SEK",5000.0}, {"XDR",5000.0} },
		cashRegister(std::make_shared<CashRegister>(cashRegistersForCurrencies)),
		exchangeTest(cashRegister)
	{};

	std::map<std::string, double> cashRegistersForCurrencies;
	std::shared_ptr <CashRegister> cashRegister;
	FromForeignToForeign exchangeTest;
};
TEST_F(TestFromForeignToForeign, exchange_FromEURToUSD_test100EUR)
{

	auto result = exchangeTest.currencyExchange(100, "EURUSD");

	EXPECT_EQ(95, result.first);
	EXPECT_EQ(0.49, result.second);
}
TEST_F(TestFromForeignToForeign, exchange_FromAUDToCAD_test6000AUD)
{
	EXPECT_THROW(exchangeTest.currencyExchange(6000, "AUDCAD"), OutOfCashException);
}

TEST_F(TestFromForeignToForeign, exchange_FromGBPToDKK_test550GBP)
{
	auto result = exchangeTest.currencyExchange(550, "GBPDKK");
	EXPECT_EQ(4572, result.first);
	EXPECT_EQ(0.54, result.second);
}

TEST_F(TestFromForeignToForeign, exchange_FromUSDToEUR_test10USD)
{
	auto result = exchangeTest.currencyExchange(10, "USDEUR");
	EXPECT_EQ(10, result.first);
	EXPECT_EQ(0.51, result.second);
}
TEST_F(TestFromForeignToForeign, exchange_FromUSDToEUR_test5000USD)
{
	EXPECT_THROW(exchangeTest.currencyExchange(5000, "USDEUR"), OutOfCashException);
}

TEST_F(TestFromForeignToForeign, exchange_FromJPYToHUF_test10000JPY)
{
	auto result = exchangeTest.currencyExchange(10000, "JPYHUF");
	EXPECT_EQ(28087, result.first);
	EXPECT_EQ(0, result.second);
}


TEST_F(TestFromForeignToForeign, exchange_FromCZKToUSD_test5CZK)
{
	auto result = exchangeTest.currencyExchange(5, "CZKUSD");
	EXPECT_EQ(0, result.first);
	EXPECT_EQ(0.98, result.second);

}
TEST_F(TestFromForeignToForeign, exchange_FromJPYToCHF_test10JPY)
{
	auto result = exchangeTest.currencyExchange(10, "JPYCHF");
	EXPECT_EQ(0, result.first);
	EXPECT_EQ(0.34, result.second);

}
TEST_F(TestFromForeignToForeign, exchange_FromHUFToGBP_test80HUF)
{
	auto result = exchangeTest.currencyExchange(80, "HUFGBP");
	EXPECT_EQ(0, result.first);
	EXPECT_EQ(0.92, result.second
	);
}
TEST_F(TestFromForeignToForeign, exchange_FromSEKToCHF_test1500SEK)
{
	auto result = exchangeTest.currencyExchange(1500, "SEKCHF");
	EXPECT_EQ(129, result.first);
	EXPECT_EQ(1.23, result.second);
}
TEST_F(TestFromForeignToForeign, exchange_FromGBPToCZK_test190GBP)
{
	EXPECT_THROW(exchangeTest.currencyExchange(190, "GBPCZK"), OutOfCashException);
}