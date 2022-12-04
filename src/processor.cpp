#include <filesystem>
#include "streams.h"
#include "exceptions.h"
#include "utils.h"
#include "processor.h"
#include "config_parser.h"

struct Processor::Impl{
    std::string_view output_file_path;

    std::string_view input_file_path;

    std::vector<std::string_view> additional_files_paths;

    ConfigParser config_parser;

    const ConvertersFactory& factory;

    std::string_view get_file_path_by_arg(const char* string);

    ConverterParams create_params(const std::vector<std::string>& command_args);
};

std::string_view Processor::Impl::get_file_path_by_arg(const char* string){
    auto file_index = Utils::string_to_positive_number(string);

    if (file_index == 0 || file_index > additional_files_paths.size()){
        throw Exceptions::IncorrectCommandsParams();
    }

    return additional_files_paths[file_index - 1];
}

ConverterParams Processor::Impl::create_params(const std::vector<std::string>& command_args){
    ConverterParams result;

    for (const auto& current_arg : command_args){
        if (current_arg[0] == '$'){
            try{
                // offset by 1 to except '$'
                std::string_view file_path = get_file_path_by_arg(current_arg.data() + 1);

                result.push_back(Streams::OutputStream(file_path));
            }
            // errors of conversion
            catch(const std::runtime_error&){
                throw Exceptions::IncorrectCommandsParams();
            }
        }
        else{
            try{
                result.push_back(std::stof(current_arg));
            }
            catch(...){
                throw Exceptions::IncorrectCommandsParams();
            }
        }
    }

    return result;
}

Processor::Processor(const std::string_view& config,
                     const std::string_view& out,
                     const std::string_view& in,
                     const std::vector<std::string_view>& additional_files,
                     const ConvertersFactory& factory){

    _pimpl = new Impl{
        out,
        in,
        additional_files,
        ConfigParser(config),
        factory,
    };
}

void Processor::process() const{
    std::string tmp_path_1 = Utils::generate_random_wav_file_name();
    std::string tmp_path_2 = Utils::generate_random_wav_file_name();

    std::string_view current_input_path = tmp_path_1;
    std::string_view current_output_path = tmp_path_2;

    Utils::copy_file(_pimpl->input_file_path, tmp_path_1);

    for (const auto& [command_name, command_args] : _pimpl->config_parser){
        try{
            const Converter& current_converter = _pimpl->factory.create_converter(command_name);

            auto current_params = _pimpl->create_params(command_args);

            Streams::InputStream input_stream(current_input_path);
            Streams::OutputStream output_stream(current_output_path);

            current_converter->convert(
                    command_name,
                    output_stream,
                    input_stream,
                    current_params
            );

            std::swap(current_input_path, current_output_path);
        }
        catch(...){
            Utils::remove_file(current_input_path);
            Utils::remove_file(current_output_path);
            throw;
        }
    }

    Utils::remove_file(current_output_path);

    if (std::filesystem::exists(_pimpl->output_file_path)){
        Utils::remove_file(_pimpl->output_file_path);
    }

    Utils::rename_file(current_input_path, _pimpl->output_file_path);
}

Processor::~Processor(){
    delete _pimpl;
}
