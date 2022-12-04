#pragma once

#include "abstract_converter.h"

class RawCutConverter : public RawAbstractConverter{
public:
    void convert(std::string_view command,
                 Streams::OutputStream& output_stream,
                 Streams::InputStream& input_stream,
                 const ConverterParams& params) const override;

    ~RawCutConverter() override = default;
};
