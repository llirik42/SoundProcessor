#pragma once

#include "abstract_converter.h"

class RawInsertConverter : public RawAbstractConverter{
public:
    void convert(const ConverterParams& params) const override;

    ~RawInsertConverter() override = default;
};
