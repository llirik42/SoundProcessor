#pragma once

#include "abstract_converter.h"

class RawCutConverter : public RawAbstractConverter{
public:
    void convert(const std::string& command, const ConverterParams& params) const override;

    ~RawCutConverter() override = default;
};
