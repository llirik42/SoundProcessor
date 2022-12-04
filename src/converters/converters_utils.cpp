#include "converters_utils.h"

size_t calculate_sample_index_by_time(float time, Streams::InputStream& input_stream){
    float tmp = static_cast<float>(input_stream.get_size()) /
                static_cast<float>(input_stream.get_duration_s());

    return static_cast<size_t>(time * tmp);
}

void check_time_fragment(size_t start_sample, size_t end_sample, Streams::InputStream& input_stream){
    if (end_sample < start_sample || end_sample >= input_stream.get_size() || start_sample >= input_stream.get_size()){
        throw Exceptions::IncorrectCommandsParams();
    }
}
