#include "../utils.h"
#include "../exceptions.h"
#include "../wav_format_info.h"
#include "volume_converter.h"

void convert_volume(std::ofstream& output, WAVFile& input, float coefficient, size_t start_sample, size_t stop_sample){
    write_default_wav_headers(output, input.get_samples_count());

    for (size_t i = 0; i < input.get_samples_count(); i++){
        Sample sample = input.get_sample();

        if (i >= start_sample && i <= stop_sample){
            sample = static_cast<Sample>(static_cast<float>(sample) * coefficient);
        }

        write_sample(output, sample);
    }
}

void RawVolumeConverter::convert([[maybe_unused]] const std::string& command, [[maybe_unused]] const ConverterParams& params) const{
    if (params.size() != 3 && params.size() != 5){
        throw IncorrectCommandsParams();
    }

    const std::string& output_path = params[0];

    std::ofstream output_file(output_path, std::fstream::binary);

    if (!output_file.is_open()){
        throw IOError();
    }

    WAVFile input_file(params[1]);

    size_t start_s = 0;
    size_t stop_s = input_file.get_duration_s();

    float volume_coefficient;

    try{
        volume_coefficient = std::stof(params[2]);

        if (params.size() == 5){
            if (params[3] != "<-"){
                int tmp = std::stoi(params[3]);

                if (tmp < 0){
                    throw IncorrectCommandsParams();
                }

                start_s = static_cast<size_t>(tmp);
            }

            if (params[4] != "->"){
                int tmp = std::stoi(params[4]);

                if (tmp < 0){
                    throw IncorrectCommandsParams();
                }

                stop_s = static_cast<size_t>(tmp);
            }
        }
    }
    catch(...){
        throw IncorrectCommandsParams();
    }


    if (volume_coefficient < 0 || start_s >= stop_s || stop_s > input_file.get_duration_s()){
        throw IncorrectCommandsParams();
    }

    convert_volume(output_file, input_file, volume_coefficient, start_s * SUPPORTED_SAMPLE_RATE, stop_s * SUPPORTED_SAMPLE_RATE);
}
