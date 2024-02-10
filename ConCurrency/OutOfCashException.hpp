#pragma once
#include <exception>

class OutOfCashException : public std::exception
{
private:
    const char* _message;
public:
    OutOfCashException(const char* message) : _message(message)
    {}
    const char* what() const override
    {
        return _message;
    }
};