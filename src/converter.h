#pragma once

#include <memory>

class RawAbstractConverter;

using Converter = std::shared_ptr<RawAbstractConverter>;

class RawAbstractConverter{
public:
    ~RawAbstractConverter()=default;
protected:
    RawAbstractConverter()=default;
private:
};
