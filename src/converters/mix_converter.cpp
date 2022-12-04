#include "mix_converter.h"

#include <iostream>

void RawMixConverter::convert(std::string_view command,
                              Streams::OutputStream& output_stream,
                              Streams::InputStream& input_stream,
                              const ConverterParams& params) const{
    std::cout << "Mixer!\n";
}
