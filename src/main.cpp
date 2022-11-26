#include <vector>
#include <argparse/argparse.hpp>
#include "error_codes.h"
#include "exceptions.h"
#include "wav_file.h"
#include "config_parser.h"

int main(int argc, char** argv){
    argparse::ArgumentParser program("SoundProcessor");
    program.add_description("The program performs audio conversions specified in the config "
                            "file and saves result to an output file.\n"
                            "Supports only WAV files with: "
                            "audio-format - PCM (without encoding), "
                            "1 channel (mono), "
                            "bit depth - signed 16 bit (little endian), "
                            "sample rate - 44100 Hz");

    program.add_argument("output_file")
            .help("The output file")
            .required();

    program.add_argument("input_file")
            .help("The input file")
            .required();

    program.add_argument("auxiliary_files")
            .help("auxiliary_files")
            .nargs(argparse::nargs_pattern::any);

    program.add_argument("-c", "--config")
            .help("Specify config file")
            .required();

    try {
        program.parse_args(argc, argv);

        auto config_file_path = program.get<std::string>("-c");
        auto output_file_path = program.get<std::string>("output_file");
        auto input_file_path = program.get<std::string>("input_file");
        auto auxiliary_files_paths = program.get<std::vector<std::string>>("auxiliary_files");

        WAVFile input_file(input_file_path);

        std::vector<WAVFile> auxiliary_files;
        for (const auto& path : auxiliary_files_paths){
            auxiliary_files.emplace_back(path);
        }

        ConfigParser config_parser(config_file_path);

        for (const auto& command : config_parser){
            std::cout << command.command_name << '\n';
        }
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
