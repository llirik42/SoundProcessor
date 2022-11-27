#pragma once

#include <string>
#include <map>
#include "converters/all_converters.h"

using ConvertersInfo = std::map<std::string, std::string>;

class ConvertersFactory{
public:
    ConvertersFactory();

    Converter CreateConverter(const std::string& converter_name);

    const ConvertersInfo& GetConvertersInfo();

    ~ConvertersFactory();
private:
    struct Imple;
    Imple* _pimple;
};
