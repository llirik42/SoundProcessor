#include <functional>
#include <vector>
#include "utils.h"
#include "exceptions.h"
#include "converters_factory.h"

struct ConvertersFactory::Impl{
    struct CommandInfo{
        std::string_view description;
        std::vector<std::string_view> examples;
        std::function<Converter(void)> converter_creation;
    };

    std::map<std::string_view, CommandInfo> commands_full_info;

    CommandsDescription commands_description;
};

template<typename T>
Converter create(){
    return std::make_unique<T>();
}

ConvertersFactory::ConvertersFactory(){
    _pimpl = new Impl;

    _pimpl->commands_full_info["mute"] = {
            "mutes fragment of file",
            {"mute <input_file> <place_in_file>"},
            create<RawVolumeConverter>
    };

    _pimpl->commands_full_info["volume"] = {
            "sets certain level of volume in fragment of file with coefficient",
            {"volume <input_file> <coefficient> <place_in_file>"},
            create<RawVolumeConverter>
    };

    _pimpl->commands_full_info["mix"] = {
            "mixes two files",
            {"<input_file_1> <input_file_2> <place_in_file_1> <place_in_file_2>"},
            create<RawMixConverter>
    };

    _pimpl->commands_full_info["cut"] = {
            "removes fragment of file",
            {"<input_file> <place_in_file>"},
            create<RawCutConverter>
    };

    _pimpl->commands_full_info["front"] = {
            "Appends fragment of file (file2) to other one (file1)",
            {"<input_file_1> <input_file_2> <place_in_file_2>"},
            create<RawInsertConverter>
    };

    _pimpl->commands_full_info["back"] = {
            "inserts at the beginning fragment of file (file2) to other one (file1)",
            {"<input_file_1> <input_file_2> <place_in_file_2>"},
            create<RawInsertConverter>
    };

    _pimpl->commands_full_info["insert"] = {
            "inserts fragment of file (file2) to certain place of other one (file1)",
            {"<input_file_1> <input_file_2> <place_in_file_1> <place_in_file_2>"},
            create<RawInsertConverter>
    };

    for (const auto& [name, data] : _pimpl->commands_full_info){
        _pimpl->commands_description[name] = {data.description, data.examples};
    }
}

Converter ConvertersFactory::create_converter(const std::string_view& command_name) const{
    return create<RawMixConverter>();
}

const CommandsDescription& ConvertersFactory::get_commands_description() const{
    return _pimpl->commands_description;
}

ConvertersFactory::~ConvertersFactory(){
    delete _pimpl;
}
