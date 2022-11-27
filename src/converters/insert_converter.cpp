#include "insert_converter.h"

#include <iostream>

void RawInsertConverter::convert([[maybe_unused]]const ConverterParams& params) const{
    std::cout << "Inserter!\n";
}
