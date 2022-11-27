#pragma once

#include <string>
#include <vector>
#include "converters_factory.h"

using std::string;

class Processor{
public:
    Processor(
            const string& config,
            const string& out,
            const string& in,
            const std::vector<string>& additional_files,
            const ConvertersFactory& factory
            );
    void Process();

    ~Processor();
private:
    struct Imple;
    Imple* _pimple;
};
