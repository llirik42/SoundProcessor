#pragma once

#include "abstract_converter.h"

class RawVolumeConverter : public RawAbstractConverter{
public:
    void convert() const override;

    ~RawVolumeConverter() override = default;
};
