#include <functional>
#include "converters_factory.h"

struct ConvertersFactory::Imple{
    struct SingleConverterData{
        std::string description;
        std::function<Converter(void)> create;
    };

    std::map<const std::string, SingleConverterData> converters_full_info;

    ConvertersInfo converters_info;
};

template<typename T>
Converter create(){
    return std::make_unique<T>();
}


ConvertersFactory::ConvertersFactory(){
    _pimple = new Imple;

    _pimple->converters_full_info["mute_converter"] = {
            "Description 1",
            create<RawMuteConverter>
    };

    _pimple->converters_full_info["mix_converter"] = {
            "Description 2",
            create<RawMuteConverter>
    };

    for (const auto& [name, data] : _pimple->converters_full_info){
        _pimple->converters_info[name] = data.description;
    }
}

Converter ConvertersFactory::CreateConverter(const std::string& converter_name){
    return _pimple->converters_full_info[converter_name].create();
}

const ConvertersInfo& ConvertersFactory::GetConvertersInfo(){
    return _pimple->converters_info;
}

ConvertersFactory::~ConvertersFactory(){
    delete _pimple;
}
