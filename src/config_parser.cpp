#include "config_parser.h"
#include "exceptions.h"
#include "utils.h"

ConfigParser::ConfigParser(const std::string& config_path){
    std::ifstream config_file(config_path);

    if (!config_file.is_open() || is_file_empty(config_file)){
        throw IncorrectConfigError();
    }
}

ConfigParser::ConfigParserIterator ConfigParser::begin() const{
    return _commands.begin();
}

ConfigParser::ConfigParserIterator ConfigParser::end() const{
    return _commands.end();
}
