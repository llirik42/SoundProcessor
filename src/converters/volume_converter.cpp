#include "../utils.h"
#include "../exceptions.h"
#include "volume_converter.h"

/*
void convert_volume(std::ofstream& output, WAVFile& input, float volume_coefficient, size_t start_sample, size_t stop_sample){
    write_default_wav_headers(output, input.get_samples_count());

    for (size_t i = 0; i < input.get_samples_count(); i++){
        Sample sample = input.get_sample();

        if (start_sample <= i && i <= stop_sample){
            sample = static_cast<Sample>(static_cast<float>(sample) * volume_coefficient);
        }

        write_sample(output, sample);
    }
}
*/
void RawVolumeConverter::convert([[maybe_unused]] const std::string& command, [[maybe_unused]] const ConverterParams& params) const{
    /*
    ConverterParams new_params = params;

    if (command == "mute"){
        new_params.insert(new_params.begin() + 2, "0");
    }

    if (new_params.size() != 3 && new_params.size() != 5){
        throw IncorrectCommandsParams();
    }

    std::ofstream output_file(new_params[0], std::fstream::binary);
    if (!output_file.is_open()){
        throw IOError();
    }

    WAVFile input_file(new_params[1]);

    size_t start_seconds = 0;
    size_t stop_seconds = input_file.get_duration_s();

    float volume_coefficient;

    try{
        volume_coefficient = std::stof(new_params[2]);

        if (new_params.size() == 5){
            if (new_params[3] != "<-"){
                int tmp = std::stoi(new_params[3]);

                if (tmp < 0){
                    throw IncorrectCommandsParams();
                }

                start_seconds = static_cast<size_t>(tmp);
            }

            if (new_params[4] != "->"){
                int tmp = std::stoi(new_params[4]);

                if (tmp < 0){
                    throw IncorrectCommandsParams();
                }

                stop_seconds = static_cast<size_t>(tmp);
            }
        }
    }
    catch(...){
        throw IncorrectCommandsParams();
    }

    if (volume_coefficient < 0 || start_seconds >= stop_seconds || stop_seconds > input_file.get_duration_s()){
        throw IncorrectCommandsParams();
    }

    convert_volume(
            output_file,
            input_file,
            volume_coefficient,
            start_seconds * SUPPORTED_SAMPLE_RATE,
            stop_seconds * SUPPORTED_SAMPLE_RATE
            );*/
}
