#pragma once

#include <string>
#include <map>
#include <utility>
#include <vector>
#include "converters/all_converters.h"

// Key - command name, pair - description + examples of command
using CommandsDescription = std::map<std::string_view, std::pair<std::string_view, std::vector<std::string_view>>>;

class ConvertersFactory{
public:
    ConvertersFactory();

    [[nodiscard]] Converter create_converter(const std::string_view& command_name) const;

    [[nodiscard]] const CommandsDescription& get_commands_description() const;

    ~ConvertersFactory();
private:
    struct Impl;
    Impl* _pimpl;
};
