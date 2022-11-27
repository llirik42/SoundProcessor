#include <map>
#include <algorithm>
#include "exceptions.h"
#include "utils.h"
#include "processor.h"
#include "wav_file.h"
#include "config_parser.h"

// Commands of converter -> converter
using ConvertersMap = std::map<std::vector<std::string>, Converter>;

ConvertersMap create_converters_map(const ConvertersInfo& converters_info){
    ConvertersMap result;

    for (const auto& [converter_name, description_commands] : converters_info){
        const auto& [description, commands] = description_commands;
        result[commands] = nullptr;
    }

    return result;
}

struct Processor::Imple{
    std::string output_file_path;

    WAVFile input_file;

    std::vector<WAVFile> additional_files;

    ConfigParser config_parser;

    const ConvertersFactory& factory;

    ConvertersMap converters_map;

    void prepare_converters(){
        const ConvertersInfo& converters_info = factory.get_converters_info();

        converters_map = create_converters_map(converters_info);

        for (const auto& [command_name, command_args]: config_parser){

            bool found_converter = false; // whether converter for this command was found or not
            for (auto& [converter_commands, converter]: converters_map){
                if (contains(converter_commands, command_name)){
                    found_converter = true;

                    if (converter == nullptr){
                        converter = factory.create_converter(command_name);
                    }

                    break;
                }
            }

            if (!found_converter){
                throw UnknownCommandError();
            }
        }
    }

    const Converter& find_converter_by_single_command(const std::string& command_name){
        for (const auto& [commands_vector, converter] : converters_map){
            if (contains(commands_vector, command_name)){
                return converter;
            }
        }

        // It's impossible that there will be no converter for command, because then command is incorrect
        // and was thrown away while preparing converters
        return converters_map[{}];
    }
};

Processor::Processor(const string& config,
                     const string& out,
                     const string& in,
                     const std::vector<string>& additional_files,
                     const ConvertersFactory& factory){

    std::vector<WAVFile> additional_wav_files;
    for (const auto& path : additional_files){
        additional_wav_files.emplace_back(path);
    }

    _pimple = new Imple{
        out,
        WAVFile(in),
        additional_wav_files,
        ConfigParser(config),
        factory,
        {},
    };

    _pimple->prepare_converters();
}

void Processor::process() const{
    for (const auto& [command_name, command_args] : _pimple->config_parser){
        _pimple->find_converter_by_single_command(command_name)->convert();
    }
}

Processor::~Processor(){
    delete _pimple;
}
