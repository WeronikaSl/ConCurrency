#include "CashierLogIn.hpp"
#include "IncorrectLoginOrPasswordException.hpp"
#include<iostream>
#include <thread>      
#include <chrono>  

bool CashierLogIn::checkCashierLogin()
{
    std::cout << "Dzien dobry. Rozpoczynasz prace. " << std::endl;
    std::cout << std::endl;

    for (int i = 1; i <= numberOfAttempts; ++i)
    {
        std::cout << "Podaj swoj login." << std::endl;
        std::cin >> cashierLogin;
        if (mapOfLoginsAndPasswords.find(cashierLogin) == mapOfLoginsAndPasswords.end())
        {
            std::cout << "podales bledny login - pozostalo ci prob : " << (numberOfAttempts - i) << std::endl;
            displayTime();
            continue;

        }
        return true;
    }
    std::cout << "to byla Twoja ostatnia " << numberOfAttempts << " proba !" << std::endl;
    return false;
}

bool CashierLogIn::checkCashierPassword()
{

    for (int i = 1; i <= numberOfAttempts; i++)
    {
        std::cout << "Podaj swoje haslo." << std::endl;
        std::cin >> cashierPassword;
        if (mapOfLoginsAndPasswords[cashierLogin] != cashierPassword)
        {
            std::cout << "podales bledne haslo - pozostalo ci prob : " << (numberOfAttempts - i) << std::endl;
            displayTime();
            continue;
        }
        std::cout << "Login i haslo zgodne. Mozesz rozpoczac prace." << std::endl;
        std::cout << std::endl;
        return true;
    }
    std::cout << "to byla Twoja ostatnia " << numberOfAttempts << " proba !" << std::endl;
    return false;
}

void CashierLogIn::displayTime()
{
    std::cout << "ponow probe za sekund : " << numberOfSeconds << std::endl;
    for (int i = numberOfSeconds; i > 0; --i) {
        std::cout << " . ";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << std::endl;
}

void CashierLogIn::cashierLogInMain()
{
    CashierLogIn log;
    if (!log.checkCashierLogin() || !log.checkCashierPassword())
    {
        throw IncorrectLoginOrPasswordException("Nie udalo sie zalogowac");
    }
}