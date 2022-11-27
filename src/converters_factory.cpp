#include <functional>
#include <vector>
#include "utils.h"
#include "exceptions.h"
#include "converters_factory.h"

struct ConvertersFactory::Imple{
    struct SingleConverterData{
        std::string description;
        std::function<Converter(void)> create;
        std::vector<std::string> commands;
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
            create<RawMuteConverter>,
            {"mute"}
    };

    _pimple->converters_full_info["mix_converter"] = {
            "Description 2",
            create<RawMixConverter>,
            {"mix"}
    };

    _pimple->converters_full_info["volume_converter"] = {
            "Description 3",
            create<RawVolumeConverter>,
            {"volume"}
    };

    _pimple->converters_full_info["cut_converter"] = {
            "Description 4",
            create<RawCutConverter>,
            {"cut", "extract"}
    };

    _pimple->converters_full_info["insert_converter"] = {
            "Description 5",
            create<RawInsertConverter>,
            {"insert", "front", "back"}
    };

    for (const auto& [name, data] : _pimple->converters_full_info){
        _pimple->converters_info[name] = {data.description, data.commands};
    }
}

Converter ConvertersFactory::create_converter(const std::string& command_name) const{
    for (const auto& [converter_name, info] : _pimple->converters_full_info){
        const auto& commands_vector = info.commands;

        if (contains(commands_vector, command_name)){
            return info.create();
        }
    }

    // Actually, it cannot happen because of the code before this creation)
    throw IncorrectConfigError();
}

const ConvertersInfo& ConvertersFactory::get_converters_info() const{
    return _pimple->converters_info;
}

ConvertersFactory::~ConvertersFactory(){
    delete _pimple;
}
