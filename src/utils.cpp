#include <random>
#include "exceptions.h"
#include "utils.h"

char digit_to_char(unsigned int digit){
    return static_cast<char>(digit + '0');
}

char generate_random_letter(){
    static std::random_device device;
    static std::mt19937 engine(device());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0,51); // size of english alphabet * 2
    auto value = distribution(engine);
    auto result = value <= 25 ? value + 'a' : (value - 26) + 'A';
    return static_cast<char>(result);
}

char generate_random_digit(){
    static  std::random_device device;
    static std::mt19937 engine(device());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0,9); // 0, 1, ..., 9
    return digit_to_char(distribution(engine));
}

char generate_random_alphanumeric(){
    static  std::random_device device;
    static std::mt19937 engine(device());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0,1);
    auto value = distribution(engine);
    return value ? generate_random_letter() : generate_random_digit();
}

size_t Utils::get_file_size(std::ifstream& file){
    auto start_pos = file.tellg();

    file.seekg(0, std::fstream::end);

    auto result = static_cast<size_t>(file.tellg());

    file.seekg(start_pos);

    return result;
}

bool Utils::is_file_empty(std::ifstream& file){
    return !get_file_size(file);
}

std::string Utils::generate_random_wav_file_name(){
    static const size_t file_name_length = 128;

    std::string result;

    for (unsigned int i = 0; i < file_name_length; i++){
        result.append(1, generate_random_alphanumeric());
    }

    result.append(".wav");

    return result;
}

void Utils::rename_file(std::string_view old_name, std::string_view new_name){
    if(std::rename(old_name.data(), new_name.data())){
        throw Exceptions::IOError();
    }
}

void Utils::copy_file(std::string_view from, std::string_view to){
    static const size_t copying_buffer_size = 1024;

    std::ofstream out(to.data(), std::fstream::binary);
    std::ifstream in(from.data(), std::fstream::binary);

    if (!out.is_open() || !in.is_open()){
        throw Exceptions::IOError();
    }

    char buffer[copying_buffer_size];

    while (!in.eof()){
        in.read(buffer, copying_buffer_size);

        out.write(buffer, in.gcount());

        if (in.fail() || out.fail()){
            throw Exceptions::IOError();
        }
    }
}
