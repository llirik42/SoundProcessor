#pragma once

#include "abstract_converter.h"

class RawMuteConverter : public RawAbstractConverter{
public:
    void convert(const std::string& command, const ConverterParams& params) const override;

    ~RawMuteConverter() override = default;
};
