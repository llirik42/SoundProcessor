#pragma once

#include "abstract_converter.h"

class RawCutConverter : public RawAbstractConverter{
public:
    void convert(const ConverterParams& params) const override;

    ~RawCutConverter() override = default;
};
