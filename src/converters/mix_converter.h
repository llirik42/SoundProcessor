#pragma once

#include "abstract_converter.h"

class RawMixConverter : public RawAbstractConverter{
public:
    void convert() const override;

    ~RawMixConverter() override = default;
};
