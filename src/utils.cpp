#include <algorithm>
#include "exceptions.h"
#include "utils.h"

size_t get_file_size(std::ifstream& file){
    auto start_pos = file.tellg();

    file.seekg(0, std::fstream::end);

    size_t result = static_cast<size_t>(file.tellg());

    file.seekg(start_pos);

    return result;
}

const size_t BUFFER_SIZE = 1024;

bool contains(const std::vector<std::string>& vector, const std::string& string){
    return std::any_of(
            vector.begin(),
            vector.end(),
            [&](const auto& x){return x == string;}
    );
}

bool is_file_empty(std::ifstream& file){
    return !get_file_size(file);
}

template<typename T>
void write_value(std::ofstream& file, T value){
    file.write(reinterpret_cast<char*>(&value), sizeof(value));
}

/*
void write_default_wav_headers(std::ofstream& file, size_t samples_count){
    static const size_t size_of_min_headers = 44;

    auto file_size = static_cast<uint32_t>(samples_count * SUPPORTED_BLOCK_ALIGN + size_of_min_headers - 8);

    write_value(file, RIFF_ID);
    write_value(file, file_size);
    write_value(file, SUPPORTED_RIFF_FORMAT);

    write_value(file, FMT_ID);
    write_value(file, SUPPORTED_FMT_SUBCHUNK_SIZE);
    write_value(file, SUPPORTED_FMT_AUDIO_FORMAT);
    write_value(file, SUPPORTED_NUMBER_OF_CHANNELS);
    write_value(file, SUPPORTED_SAMPLE_RATE);
    write_value(file, SUPPORTED_BYTE_RATE);
    write_value(file, SUPPORTED_BLOCK_ALIGN);
    write_value(file, SUPPORTED_BITS_PER_SAMPLE);

    write_value(file, DATA_ID);
    write_value(file, static_cast<uint32_t>(samples_count * 2));
}
*/
/*
void write_sample(std::ofstream& file, Sample sample){
    write_value(file, sample);
}*/

void copy_file(const std::string& to, const std::string& from){
    std::ofstream out(to, std::fstream::binary);
    std::ifstream in(from, std::fstream::binary);

    if (!out.is_open() || !in.is_open()){
        throw Exceptions::IOError();
    }

    char buffer[BUFFER_SIZE];

    while (!in.eof()){
        in.read(buffer, BUFFER_SIZE);

        out.write(buffer, in.gcount());
    }
}
