#pragma once

#include <exception>

const unsigned int INCORRECT_WAV_ERROR_CODE = 1;

class AbstractException : public std::exception{
public:
    [[nodiscard]] const char* what() const noexcept override = 0;
    [[nodiscard]] virtual int code() const noexcept = 0;
private:
};

class IncorrectWavError : public AbstractException{
public:
    [[nodiscard]] const char* what() const noexcept override {return "Incorrect .wav file";}
    [[nodiscard]] int code() const noexcept override {return INCORRECT_WAV_ERROR_CODE;}
};
