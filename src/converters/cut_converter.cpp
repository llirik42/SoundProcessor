#include "../exceptions.h"
#include "converters_utils.h"
#include "cut_converter.h"

void cut(Streams::OutputStream& output_stream,
         Streams::InputStream& input_stream,
         size_t start_sample,
         size_t end_sample){

    for (size_t i = 0; i < start_sample; i++){
        output_stream.write(input_stream.read_element());
    }

    for (size_t i = start_sample; i < end_sample; i++){
        input_stream.read_element();
    }

    while (input_stream.available()){
        output_stream.write(input_stream.read_element());
    }
}

void RawCutConverter::convert(std::string_view command,
                              Streams::OutputStream& output_stream,
                              Streams::InputStream& input_stream,
                              const ConverterParams& params) const{

    if (command != "cut" || params.size() != 2){
        throw Exceptions::IncorrectCommandsParams();
    }

    auto start_sample = calculate_sample_index_by_time(
            convert_any<float>(params[0]),
            input_stream
    );

    auto end_sample = calculate_sample_index_by_time(
            convert_any<float>(params[1]),
            input_stream
    );

    check_time_fragment(start_sample, end_sample, input_stream);

    cut(output_stream, input_stream, start_sample, end_sample);
}
