#include <regex>
#include "config_parser.h"
#include "exceptions.h"
#include "utils.h"

void reduce_spaces(std::string& string){
    static const std::regex regex(R"(\s+)");

    while (isspace(string[0])){
        string.erase(0, 1);
    }

    while (std::isspace(string.back() - 1)){
        string.erase(string.length() - 1, 1);
    }

    string = std::regex_replace(string, regex, " ");
}

Command extract_command(std::string& command_string){
    static const std::string delimiter = " ";

    Command result;

    if (!isspace(command_string.back())){
        command_string.push_back(' ');
    }

    size_t pos;
    while ((pos = command_string.find(delimiter)) != std::string::npos){
        result.command_args.push_back(command_string.substr(0, pos));
        command_string.erase(0, pos + delimiter.length());
    }

    result.command_name = result.command_args.front();

    result.command_args.erase(result.command_args.begin());

    return result;
}

Command parse_command(std::string& command_string){
    static const std::regex empty_line_regex(R"((#.*)|(\s*))");

    if (std::regex_match(command_string.data(), empty_line_regex)){
        return {};
    }

    reduce_spaces(command_string);

    return extract_command(command_string);
}

struct ConfigParser::Impl{
    std::vector<Command> commands;

    void Parse(std::ifstream& config_file){
        while (!config_file.eof()){
            std::string command_string;
            std::getline(config_file, command_string);

            const Command current_command = parse_command(command_string);

            // Current string's without #
            if (!current_command.command_name.empty()){
                commands.push_back(current_command);
            }
        }
    }
};

ConfigParser::ConfigParser(const std::string& config_path){
    _pimpl = new Impl;

    std::ifstream config_file(config_path);

    if (!config_file.is_open() || is_file_empty(config_file)){
        throw Exceptions::IncorrectConfigError();
    }

    _pimpl->Parse(config_file);
}

ConfigParser::ConfigParserIterator ConfigParser::begin() const{
    return _pimpl->commands.begin();
}

ConfigParser::ConfigParserIterator ConfigParser::end() const{
    return _pimpl->commands.end();
}

ConfigParser::~ConfigParser(){
    delete _pimpl;
}
