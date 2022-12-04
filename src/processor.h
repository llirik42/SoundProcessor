#pragma once

#include <string>
#include <vector>
#include "converters_factory.h"

class Processor{
public:
    Processor(
            const std::string_view& config,
            const std::string_view& out,
            const std::string_view& in,
            const std::vector<std::string_view>& additional_files,
            const ConvertersFactory& factory
            );
    void process() const;

    ~Processor();
private:
    struct Impl;
    Impl* _pimpl;
};
