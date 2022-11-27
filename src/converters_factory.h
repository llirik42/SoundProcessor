#pragma once

#include <string>
#include <map>
#include <utility>
#include "converters/all_converters.h"

// Key - converter, pair - contains description and vector of commands
using ConvertersInfo = std::map<std::string, std::pair<std::string, std::vector<std::string>>>;

class ConvertersFactory{
public:
    ConvertersFactory();

    [[nodiscard]] Converter create_converter(const std::string& command_name) const;

    [[nodiscard]] const ConvertersInfo& get_converters_info() const;

    ~ConvertersFactory();
private:
    struct Imple;
    Imple* _pimple;
};
