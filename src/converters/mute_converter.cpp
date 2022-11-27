#include "../utils.h"
#include "../exceptions.h"
#include "../wav_format_info.h"
#include "mute_converter.h"

void mute(std::ofstream& output, WAVFile& input, size_t start_sample, size_t stop_sample){
    write_default_wav_headers(output, input.get_samples_count());

    for (size_t i = 0; i < input.get_samples_count(); i++){
        Sample sample = input.get_sample();

        if (i >= start_sample && i <= stop_sample){
            sample = 0;
        }

        write_sample(output, sample);
    }
}

void RawMuteConverter::convert(const ConverterParams& params) const{
    if (params.size() != 2 && params.size() != 4){
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

    if (params.size() == 4){
        try{
            if (params[2] != "<-"){
                start_s = static_cast<size_t>(std::stoi(params[2]));
            }

            if (params[3] != "->"){
                stop_s = static_cast<size_t>(std::stoi(params[3]));
            }
        }
        catch(...){
            throw IncorrectCommandsParams();
        }
    }

    mute(output_file, input_file, start_s * SUPPORTED_SAMPLE_RATE, stop_s * SUPPORTED_SAMPLE_RATE);
}
