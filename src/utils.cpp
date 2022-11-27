#include <algorithm>
#include "utils.h"

bool contains(const std::vector<std::string>& vector, const std::string& string){
    return std::any_of(
            vector.begin(),
            vector.end(),
            [&](const auto& x){return x == string;}
    );
}

size_t get_file_size(std::ifstream& file){
    auto start_pos = file.tellg();

    file.seekg(0, std::fstream::end);

    size_t result = static_cast<size_t>(file.tellg());

    file.seekg(start_pos);

    return result;
}

bool is_file_empty(std::ifstream& file){
    return !get_file_size(file);
}
