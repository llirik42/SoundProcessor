#pragma once

#include "abstract_converter.h"

class RawVolumeConverter : public RawAbstractConverter{
public:
    void convert(const std::string& command, const ConverterParams& params) const override;

    ~RawVolumeConverter() override = default;
};
