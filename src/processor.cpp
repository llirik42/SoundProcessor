#include "processor.h"
#include "wav_file.h"
#include "config_parser.h"
#include <iostream>

struct Processor::Imple{
    std::string output_file_path;

    WAVFile input_file;

    std::vector<WAVFile> additional_files;

    ConfigParser config_parser;

    const ConvertersFactory& factory;
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
        factory
    };
}

void Processor::Process(){





    for (const auto& command : _pimple->config_parser){
        std::cout << command.command_name << ' ';

        for (const auto& arg: command.command_args){
            std::cout << arg << ' ';
        }
        std::cout << '\n';
    }
}

Processor::~Processor(){
    delete _pimple;
}
