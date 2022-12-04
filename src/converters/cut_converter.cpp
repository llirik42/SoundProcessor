#include "cut_converter.h"

#include <iostream>

void RawCutConverter::convert(std::string_view command,
                              Streams::OutputStream& output_stream,
                              Streams::InputStream& input_stream,
                              const ConverterParams& params) const{
    std::cout << "Cutter!\n";
}
