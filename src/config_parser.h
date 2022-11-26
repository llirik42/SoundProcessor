#pragma once

#include <vector>
#include <string>
#include <limits>

using Time = unsigned int; // Presents time in a .wav files
const Time BEFORE_TIME = std::numeric_limits<Time>::max() - 1; // <-
const Time AFTER_TIME = std::numeric_limits<Time>::max(); // ->

struct Command{
    std::string command_name;
    std::vector<unsigned int> command_args;
};

class ConfigParser{
public:
    using ConfigParserIterator = std::vector<Command>::const_iterator;

    explicit ConfigParser(const std::string& config_path);

    [[nodiscard]] ConfigParserIterator begin() const;

    [[nodiscard]] ConfigParserIterator end() const;
private:
    std::vector<Command> _commands;
};
