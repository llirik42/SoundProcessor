#pragma once

#include <vector>
#include <string>
#include <limits>

struct Command{
    std::string command_name;
    std::vector<std::string> command_args;
};

class ConfigParser{
public:
    using ConfigParserIterator = std::vector<Command>::const_iterator;

    explicit ConfigParser(const std::string& config_path);

    [[nodiscard]] ConfigParserIterator begin() const;

    [[nodiscard]] ConfigParserIterator end() const;

    ~ConfigParser();
private:
    struct Imple;
    Imple* _pimple;
};
