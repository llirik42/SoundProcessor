#pragma once

#include "abstract_converter.h"

class RawMuteConverter : public RawAbstractConverter{
public:
    void convert() const override;

    ~RawMuteConverter() override = default;
};
