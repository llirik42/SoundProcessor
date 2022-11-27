#pragma once

#include <memory>
#include "../config_parser.h"

class RawAbstractConverter;

using Converter = std::unique_ptr<RawAbstractConverter>;

class RawAbstractConverter{
public:
    virtual void convert() const = 0;

    virtual ~RawAbstractConverter() = default;
};
