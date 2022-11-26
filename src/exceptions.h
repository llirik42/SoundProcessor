#pragma once

#include <exception>
#include "error_codes.h"

class AbstractException : public std::exception{
public:
    [[nodiscard]] const char* what() const noexcept override = 0;
    [[nodiscard]] virtual int code() const noexcept = 0;
};

class IncorrectWavError : public AbstractException{
public:
    [[nodiscard]] const char* what() const noexcept override {return "Incorrect .wav files";}
    [[nodiscard]] int code() const noexcept override {return INCORRECT_WAV_ERROR_CODE;}
};

class IncorrectConfigError : public AbstractException{
public:
    [[nodiscard]] const char* what() const noexcept override {return "Incorrect config file";}
    [[nodiscard]] int code() const noexcept override {return INCORRECT_CONFIG_ERROR_CODE;}
};
