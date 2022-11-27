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
    [[nodiscard]] const char* what() const noexcept override {return "Incorrect config file (either path is incorrect or file couldn't be opened)";}
    [[nodiscard]] int code() const noexcept override {return INCORRECT_CONFIG_ERROR_CODE;}
};

class UnknownCommandError : public AbstractException{
public:
    [[nodiscard]] const char* what() const noexcept override {return "Unknown command";}
    [[nodiscard]] int code() const noexcept override {return UNKNOWN_COMMAND_ERROR_CODE;}
};

class IncorrectCommandsParams : public AbstractException{
public:
    [[nodiscard]] const char* what() const noexcept override {return "Incorrect params for command(s)";}
    [[nodiscard]] int code() const noexcept override {return INCORRECT_COMMANDS_PARAMS_ERROR_CODE;}
};

class IOError : public AbstractException{
public:
    [[nodiscard]] const char* what() const noexcept override {return "IO error";}
    [[nodiscard]] int code() const noexcept override {return IO_ERROR_CODE;}
};
