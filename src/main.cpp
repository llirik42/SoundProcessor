#include <argparse/argparse.hpp>
#include <iostream>

int main(){ /*
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
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    auto config_file = program.get<std::string>("-c");
    auto output_file = program.get<std::string>("output_file");
    auto input_file = program.get<std::string>("input_file");
    auto auxiliary_files = program.get<std::vector<std::string>>("auxiliary_files");
    */
    return 0;
}
