#pragma once

#include <exception>

class AbstractException : public std::exception{
public:
    [[nodiscard]] const char* what() const noexcept override=0;
    [[nodiscard]] virtual int code() const noexcept=0;
    ~AbstractException()=default;
private:
};

class IncorrectWavError : public AbstractException{
public:
    [[nodiscard]] const char* what() const noexcept override {return "Incorrect .wav file";}
    [[nodiscard]] int code() const noexcept override {return 1;}
};
