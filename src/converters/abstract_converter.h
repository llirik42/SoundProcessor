#pragma once

#include <memory>
#include <vector>
#include <string>
#include "../wav_file.h"
#include "../config_parser.h"

class RawAbstractConverter;

using Converter = std::unique_ptr<RawAbstractConverter>;
using ConverterParams = std::vector<std::string>; // "Param" -> value of param

class RawAbstractConverter{
public:
    virtual void convert(const ConverterParams& params) const = 0;

    virtual ~RawAbstractConverter() = default;
};
