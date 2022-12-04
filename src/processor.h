#pragma once

#include <string>
#include <vector>
#include "converters_factory.h"

namespace Processing{
    class Processor{
    public:
        Processor(const std::string_view& config,
                  const std::string_view& out,
                  const std::string_view& in,
                  const std::vector<std::string>& additional_files,
                  const Factory::ConvertersFactory& factory);

        void process() const;

        ~Processor();
    private:
        struct Impl;
        Impl* _pimpl;
    };

}
