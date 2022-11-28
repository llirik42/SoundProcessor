#include <map>
#include <algorithm>
#include "exceptions.h"
#include "utils.h"
#include "processor.h"
#include "config_parser.h"

// {Commands of converter} -> converter
using ConvertersMap = std::map<std::vector<std::string>, Converter>;

// Creates map where every converter will be nullptr
ConvertersMap create_converters_map(const ConvertersInfo& converters_info){
    ConvertersMap result;

    for (const auto& [converter_name, description_commands] : converters_info){
        const auto& [description, commands] = description_commands;
        result[commands] = nullptr;
    }

    return result;
}

struct Processor::Impl{
    std::string output_file_path;

    std::string input_file_path;

    std::vector<std::string> additional_files_paths;

    ConfigParser config_parser;

    const ConvertersFactory& factory;

    ConvertersMap converters_map;

    // fill map of converters according to config (create only needed converters)
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

            // Met unknown command
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

    void replace_params(ConverterParams& params){
        for (auto& param : params){
            if (param[0] == '$'){
                try{
                    auto file_index = static_cast<size_t>(strtoul(param.c_str() + 1, nullptr, 10));

                    if (file_index == 0 || file_index > additional_files_paths.size()){
                        throw IncorrectCommandsParams();
                    }

                    param = additional_files_paths[file_index - 1];
                }
                catch(...){
                    throw IncorrectCommandsParams();
                }
            }
        }
    }
};

Processor::Processor(const string& config,
                     const string& out,
                     const string& in,
                     const std::vector<string>& additional_files,
                     const ConvertersFactory& factory){

    _pimpl = new Impl{
        out,
        in,
        additional_files,
        ConfigParser(config),
        factory,
        {},
    };

    _pimpl->prepare_converters();
}

void Processor::process() const{
    std::string path_of_tmp1 = "tmp1.wav";
    std::string path_of_tmp2 = "tmp2.wav";

    copy_file(path_of_tmp1, _pimpl->input_file_path);

    std::string path_of_final_output = path_of_tmp2;

    for (const auto& [command_name, command_args] : _pimpl->config_parser){
        ConverterParams params;

        std::copy(command_args.begin(), command_args.end(),
                  std::back_inserter(params));

        _pimpl->replace_params(params);

        params.insert(params.begin(), path_of_tmp1);
        params.insert(params.begin(), path_of_tmp2);

        _pimpl->find_converter_by_single_command(command_name)->convert(command_name, params);

        path_of_final_output = path_of_tmp2;

        std::swap(path_of_tmp1, path_of_tmp2);
    }

    copy_file(_pimpl->output_file_path, path_of_final_output);

    try{
        std::remove(path_of_tmp1.c_str());
        std::remove(path_of_tmp2.c_str());
    }
    catch(...){
        throw IOError();
    }
}

Processor::~Processor(){
    delete _pimpl;
}
