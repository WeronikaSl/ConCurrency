#include "MainManager.hpp"

MainManager::MainManager()
{
    _cashier.setCashRegister(_cashRegister);
    setMenuOptions();
}

void MainManager::displayCurrencyCodes() const
{
    std::cout << "Dostepne waluty: ";

    for (const auto& code : _cashRegister->getCashRegistersForCurrencies())
    {
        if (code.first != "PLN")
        {
            std::cout << code.first << " ";
        }
    }

    std::cout << std::endl;
}

void MainManager::setMenuOptions()
{
    _menuOptions.push_back("1 - Tabela kursow walut");
    _menuOptions.push_back("2 - Wyswietlenie stanu kas");
    _menuOptions.push_back("3 - Kup obca walute");
    _menuOptions.push_back("4 - Sprzedaj obca walute");
    _menuOptions.push_back("5 - Wymien obca walute na inna obca walute");
    _menuOptions.push_back("6 - Wyjdz z programu");
}


void MainManager::chooseFromMenu()
{
    std::cout << "Wybierz jedna z dostepnych opcji:" << std::endl << std::endl;

    for (auto const& option : _menuOptions)
    {
        std::cout << option << std::endl;
    }

    std::cout << std::endl << "Twoj wybor: ";
    std::cin >> _usersMenuChoice;
    std::cout << std::endl;
}

void MainManager::takeAmountOfMoneyFromUser()
{
    std::cout << "Podaj kwote do wymiany: ";
    std::cin >> _amountOfMoney;

    exceptionHandlingForAmountOfMoney();
}

void MainManager::takeCurrencyToSellCodeFromUser()
{
    std::cout << "Podaj kod waluty, ktora chcesz sprzedac: ";
    std::cin >> _currencyCode;

    exceptionHandlingForCurrencyCodes();
}

void MainManager::takeCurrencyToBuyCodeFromUser()
{
    std::cout << "Podaj kod waluty, ktora chcesz kupic: ";
    std::cin >> _currencyCode;

    exceptionHandlingForCurrencyCodes();
}

void MainManager::fromPLNToForeign()
{
    std::cout << _menuOptions.at(2) << std::endl;
    takeAmountOfMoneyFromUser();
    displayCurrencyCodes();
    takeCurrencyToBuyCodeFromUser();
    _concatenatedCurrencyCodes = "PLN" + _currencyCode;
    _cantor = std::make_shared<FromPLNToForeign>(_cashRegister);
    moneyExchange();
}

void MainManager::fromForeignToPLN()
{
    std::cout << _menuOptions.at(3) << std::endl;
    takeAmountOfMoneyFromUser();
    displayCurrencyCodes();
    takeCurrencyToSellCodeFromUser();
    _concatenatedCurrencyCodes = _currencyCode + "PLN";
    _cantor = std::make_shared<FromForeignToPLN>(_cashRegister);
    moneyExchange();
}

void MainManager::fromForeignToForeign()
{
    std::cout << _menuOptions.at(4) << std::endl;
    takeAmountOfMoneyFromUser();
    displayCurrencyCodes();
    takeCurrencyToSellCodeFromUser();
    _concatenatedCurrencyCodes = _currencyCode;
    takeCurrencyToBuyCodeFromUser();
    _concatenatedCurrencyCodes += _currencyCode;
    _cantor = std::make_shared<FromForeignToForeign>(_cashRegister);
    moneyExchange();
}

void MainManager::moneyExchange()
{
    _cashier.setExchange(_cantor);
    auto exchangedMoneyAndChange = _cashier.exchangeCurrencyforCashier(_amountOfMoney, _concatenatedCurrencyCodes);
    std::cout << "Kwota w obcej walucie: " << std::get<0>(exchangedMoneyAndChange) << " " << _currencyCode << std::endl;
    std::cout << "Kwota w PLN: " << std::get<1>(exchangedMoneyAndChange) << std::endl;
}

void MainManager::pause() const
{
    char pause = 'a';
    std::cout << std::endl << "Wybierz litere 'x' i nacisnij enter, zeby kontynuowac: ";
    std::cin >> pause;
    std::cout << std::endl;
}

void MainManager::displayTitle() const
{
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "\033[97m       $$$$                            $$$$                                                                  \033[0m" << std::endl;
    std::cout << "\033[97m      $    $                          $    $                                                                 \033[0m" << std::endl;
    std::cout << "\033[97m     $           $$$      $$$$$      $          $      $  $   $  $   $   $$$$   $$$$$     $$$$    $    $     \033[0m" << std::endl;
    std::cout << "     $         $     $    $     $    $          $      $  $ $    $ $    $    $  $    $   $    $   $    $     " << std::endl;
    std::cout << "     $        $       $   $     $    $          $      $  $      $      $$$$$   $    $   $        $    $     " << std::endl;
    std::cout << "     $         $     $    $     $    $          $      $  $      $      $       $    $   $    $    $$$$$     " << std::endl;
    std::cout << "\033[90m      $    $     $$$      $     $     $    $      $$$$    $      $       $$$$   $    $    $$$$         $     \033[0m" << std::endl;
    std::cout << "\033[90m       $$$$                            $$$$                                                          $$$     \033[0m" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

}

void MainManager::exceptionHandlingForCurrencyCodes() const
{
    std::map<std::string, double> tempMapOfCurrencies = _cashRegister->getCashRegistersForCurrencies();
    if ("PLN" == _currencyCode)
    {
        throw std::invalid_argument("Nie mozesz tutaj wybrac PLN.");
    }

    auto it = tempMapOfCurrencies.find(_currencyCode);

    if (it == tempMapOfCurrencies.end())
    {
        throw std::invalid_argument("W kantorze nie ma takiej waluty.");
    }
}

void MainManager::exceptionHandlingForAmountOfMoney() const
{
    if (_amountOfMoney <= 0)
    {
        throw std::invalid_argument("Wprowadzone dane musza byc liczba wieksza od 0.");
    }
}


void MainManager::mainFunction()
{
    displayTitle();
    std::cout << std::endl << "Witaj w aplikacji ConCurrency!" << std::endl << std::endl << std::endl;
    _cashierLogIn.cashierLogInMain();
    _cashier.updateCurrencyRatesInDataBase();

    do
    {
        chooseFromMenu();
        switch (_usersMenuChoice)
        {
        case 1:
            std::cout << _menuOptions.at(0) << std::endl;
            _cashier.displayCurrencyRateTable();
            pause();
            break;
        case 2:
            std::cout << _menuOptions.at(1) << std::endl;
            _cashier.displayUpdatedCashRegisterBalance();
            pause();
            break;
        case 3:
            fromPLNToForeign();
            pause();
            break;
        case 4:
            fromForeignToPLN();
            pause();
            break;
        case 5:
            fromForeignToForeign();
            pause();
            break;
        case 6:
            std::cout << _menuOptions.at(5) << std::endl;
            break;
        default:
            std::cout << "Taka opcja nie jest dostepna." << std::endl;
            break;
        }
        std::cout << std::endl;
    } while ((_usersMenuChoice > 0) && (_usersMenuChoice < 6));




}

