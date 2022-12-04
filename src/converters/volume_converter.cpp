#include "../exceptions.h"
#include "volume_converter.h"

void convert_volume(
        Streams::OutputStream& output_stream,
        Streams::InputStream& input_stream,
        float coefficient,
        size_t start_sample,
        size_t end_sample){

    for (size_t i = 0; i < start_sample; i++){
        output_stream.write(input_stream.read_element());
    }

    for (size_t i = start_sample; i < end_sample; i++){
        auto new_value = static_cast<WAVFormatInfo::Sample>(static_cast<float>(input_stream.read_element()) * coefficient);
        output_stream.write(new_value);
    }

    while (input_stream.available()){
        output_stream.write(input_stream.read_element());
    }
}

void RawVolumeConverter::convert(std::string_view command,
                                 Streams::OutputStream& output_stream,
                                 Streams::InputStream& input_stream,
                                 const ConverterParams& params) const{

    if (command != "mute" && command != "volume"){
        throw Exceptions::IncorrectCommandsParams();
    }

    if (command == "mute" && params.size() != 2){
        throw Exceptions::IncorrectCommandsParams();
    }

    if (command == "volume" && params.size() != 3){
        throw Exceptions::IncorrectCommandsParams();
    }

    size_t start_time_index = command == "mute" ? 0 : 1;
    size_t end_time_index = command == "mute" ? 1 : 2;

    float coefficient = command == "volume" ? std::any_cast<float>(params[0]) : 0;

    size_t total_input_stream_size = input_stream.get_size();
    size_t total_input_stream_duration = input_stream.get_duration_s();

    float tmp = static_cast<float>(total_input_stream_size) /
                static_cast<float>(total_input_stream_duration);

    auto start_sample = static_cast<size_t>(std::any_cast<float>(params[start_time_index]) * tmp);

    auto end_sample = static_cast<size_t>(std::any_cast<float>(params[end_time_index]) * tmp);

    if (end_sample < start_sample || end_sample >= input_stream.get_size() || start_sample >= input_stream.get_size()){
        throw Exceptions::IncorrectCommandsParams();
    }

    convert_volume(output_stream, input_stream, coefficient, start_sample, end_sample);
}
