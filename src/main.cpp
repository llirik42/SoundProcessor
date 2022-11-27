#include <vector>
#include <string>
#include <argparse/argparse.hpp>
#include "error_codes.h"
#include "exceptions.h"
#include "converters_factory.h"
#include "processor.h"

std::string get_program_description(const ConvertersInfo& converters_info){
    std::string program_description = "The program performs audio conversions specified in the config "
                                      "file and saves result to an output file.\n\n"
                                      "Supports only WAV files with:\n"
                                      "  audio-format - PCM (without encoding)\n"
                                      "  1 channel (mono)\n"
                                      "  bit depth - signed 16 bit (little endian)\n"
                                      "  sample rate - 44100 Hz\n\n"
                                      "Converters:\n";

    const unsigned int default_padding = 22;
    for (const auto& [name, description_commands] : converters_info){
        const auto length = name.length();

        const auto& [description, _] = description_commands;

        program_description.append("  ");
        program_description.append(name);
        program_description.append(default_padding - length, ' ');
        program_description.append(description);
        program_description.append(1, '\n');
    }
    return program_description;
}

int main(int argc, char** argv){
    ConvertersFactory factory;

    const ConvertersInfo& converters_info = factory.get_converters_info();

    std::string program_description = get_program_description(converters_info);

    argparse::ArgumentParser program("SoundProcessor");
    program.add_description(program_description);

    program.add_argument("output_file")
            .help("The output file")
            .required();

    program.add_argument("input_file")
            .help("The input file")
            .required();

    program.add_argument("additional_files")
            .help("Additional files")
            .nargs(argparse::nargs_pattern::any);

    program.add_argument("-c", "--config")
            .help("Specify config file")
            .required();

    try {
        program.parse_args(argc, argv);

        auto config_path = program.get<std::string>("-c");
        auto output_file = program.get<std::string>("output_file");
        auto input_file = program.get<std::string>("input_file");
        auto additional_files = program.get<std::vector<std::string>>("additional_files");

        Processor processor(config_path, output_file, input_file, additional_files, factory);

        processor.process();
    }
    catch(const AbstractException& exception){
        std::cerr << exception.what() << '\n';
        return exception.code();
    }
    catch (const std::runtime_error& err){ // Incorrect args
        std::cerr << err.what() << '\n';
        return INCORRECT_ARGS_ERROR_CODE;
    }
    catch(...){ // Something bad happened ..
        std::cerr << "Something really bad and unpredicted happened ...\n";
        return UNEXPECTED_ERROR_CODE;
    }

    return 0;
}
