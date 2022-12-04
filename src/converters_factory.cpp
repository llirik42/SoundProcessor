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

    Converter find_converter_by_command_name(std::string_view command_name);
};

Converter ConvertersFactory::Impl::find_converter_by_command_name(std::string_view command_name){
    for (const auto& [current_command, info] : commands_full_info){
        if (current_command == command_name){
            return info.converter_creation();
        }
    }

    throw Exceptions::UnknownCommandError();
}

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

const Converter& ConvertersFactory::create_converter(std::string_view command_name) const{
    static std::map<std::string_view, Converter> converters;

    if (!Utils::contains(converters, command_name)){
        converters[command_name] = _pimpl->find_converter_by_command_name(command_name);
    }

    return converters.at(command_name);
}

const CommandsDescription& ConvertersFactory::get_commands_description() const{
    return _pimpl->commands_description;
}

ConvertersFactory::~ConvertersFactory(){
    delete _pimpl;
}
