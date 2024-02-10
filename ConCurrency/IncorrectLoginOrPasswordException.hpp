#pragma once
#include <exception>

class IncorrectLoginOrPasswordException : public std::exception
{
private:
    const char* _message;
public:
    IncorrectLoginOrPasswordException(const char* message) : _message(message)
    {}
    const char* what() const override
    {
        return _message;
    }
};