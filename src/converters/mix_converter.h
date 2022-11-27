#pragma once

#include "abstract_converter.h"

class RawMixConverter : public RawAbstractConverter{
public:
    void convert(const std::string& command, const ConverterParams& params) const override;

    ~RawMixConverter() override = default;
};
