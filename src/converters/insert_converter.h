#pragma once

#include "abstract_converter.h"

class RawInsertConverter : public RawAbstractConverter{
public:
    void convert(const std::string& command, const ConverterParams& params) const override;

    ~RawInsertConverter() override = default;
};
