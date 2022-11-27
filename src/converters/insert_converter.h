#pragma once

#include "abstract_converter.h"

class RawInsertConverter : public RawAbstractConverter{
public:
    void convert() const override;

    ~RawInsertConverter() override = default;
};
