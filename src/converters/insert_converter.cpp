#include "insert_converter.h"

#include <iostream>

void RawInsertConverter::convert(std::string_view command,
                                 Streams::OutputStream& output_stream,
                                 Streams::InputStream& input_stream,
                                 const ConverterParams& params) const{
    std::cout << "Inserter!\n";
}
