#pragma once

#include <memory>
#include "../config_parser.h"

class RawAbstractConverter;

using Converter = std::unique_ptr<RawAbstractConverter>;

class RawAbstractConverter{

};
