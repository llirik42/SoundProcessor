//#include <argparse/argparse.hpp>

#include <fstream>
#include <iostream>

#define SIZE 4

struct WAVHeader{
    uint32_t chunk_id; // RIFF
    uint32_t chunk_size; // file size - 8
    uint32_t format; // 1163280727 = "WAVE"
    uint32_t subchunk1_id; // contains "fmt"
    uint32_t subchunk1_size; // 16 for PCM
    uint16_t audio_format; // 1 for PCM
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate; // Number of bytes transmitted per second of playback
    uint16_t block_align; // size of one block
    uint16_t bits_per_sample; // bits in one sample (depth)
    uint32_t subchunk2_id; // contains "LIST"
    uint32_t subchunk2_size;
};

int main(){
    std::ifstream ifstream("../audio/lol.wav", std::ios::binary);

    WAVHeader header{};

    ifstream.read(reinterpret_cast<char*>(&header), sizeof(header));

    std::cout << "chunk_id: " << static_cast<char>((header.chunk_id & 0b00000000000000000000000011111111) >> 0) <<
                              static_cast<char>((header.chunk_id & 0b00000000000000001111111100000000) >> 8) <<
                              static_cast<char>((header.chunk_id & 0b00000000111111110000000000000000) >> 16) <<
                              static_cast<char>((header.chunk_id & 0b11111111000000000000000000000000) >> 24) << '\n';
    std::cout << "chunk_size: " << header.chunk_size << '\n';
    std::cout << "format: " << static_cast<char>((header.format & 0b00000000000000000000000011111111) >> 0) <<
            static_cast<char>((header.format & 0b00000000000000001111111100000000) >> 8) <<
            static_cast<char>((header.format & 0b00000000111111110000000000000000) >> 16) <<
            static_cast<char>((header.format & 0b11111111000000000000000000000000) >> 24) << '\n';
    std::cout << "subchunk1_id: " << static_cast<char>((header.subchunk1_id & 0b00000000000000000000000011111111) >> 0) <<
                                  static_cast<char>((header.subchunk1_id & 0b00000000000000001111111100000000) >> 8) <<
                                  static_cast<char>((header.subchunk1_id & 0b00000000111111110000000000000000) >> 16) <<
                                  static_cast<char>((header.subchunk1_id & 0b11111111000000000000000000000000) >> 24) << '\n';
    std::cout << "subchunk1_size: " << header.subchunk1_size << '\n';
    std::cout << "audio_format: " << header.audio_format << '\n';
    std::cout << "num_channels: " << header.num_channels << '\n';
    std::cout << "sample_rate: " << header.sample_rate << '\n';
    std::cout << "byte_rate: " << header.byte_rate << '\n';
    std::cout << "block_align: " << header.block_align << '\n';
    std::cout << "bits_per_sample: " << header.bits_per_sample << '\n';
    std::cout << "subchunk2_id: " << static_cast<char>((header.subchunk2_id & 0b00000000000000000000000011111111) >> 0) <<
                                  static_cast<char>((header.subchunk2_id & 0b00000000000000001111111100000000) >> 8) <<
                                  static_cast<char>((header.subchunk2_id & 0b00000000111111110000000000000000) >> 16) <<
                                  static_cast<char>((header.subchunk2_id & 0b11111111000000000000000000000000) >> 24) << '\n';
    std::cout << "subchunk2_size: " << header.subchunk2_size << '\n';

    char* data = new char[header.subchunk2_size];

    ifstream.read(data, header.subchunk2_size);

    for (unsigned int i = 0; i < header.subchunk2_size; i++){
        std::cout << data[i];
    }
    std::cout << '\n';

    char buffer[SIZE + 1] = {'\0'};
    ifstream.read(buffer, SIZE);

    std::cout << buffer << '\n';

    std::ofstream ofstream("../audio/tmp.wav", std::ios::binary);

    ofstream.write(reinterpret_cast<char*>(&header), sizeof(header));

    ofstream.write(data, header.subchunk2_size);
    ofstream.write(buffer, SIZE);

    delete[] data; // "INFOIART", artist, comment, ICOP§ copyright,  data created, genre, title, product, technician


    int16_t min_sample = 1;
    int16_t max_sample = -1;

    unsigned int count = 0;
    while (!ifstream.eof()){
        count++;

        int16_t sample;

        ifstream.read(reinterpret_cast<char*>(&sample), sizeof(sample));

        min_sample = std::min(sample, min_sample);
        max_sample = std::max(sample, max_sample);

        ofstream.write(reinterpret_cast<char*>(&sample), sizeof(sample));
    }

    std::cout << count << '\n';
    std::cout << min_sample << '\n';
    std::cout << max_sample << '\n';

    //buffer[0] =  header.format & 0b11111111000000000000000000000000;

    /*
    char* data = new char[header.subchunk2_size];

    ifstream.read(data, header.subchunk2_size);

    unsigned int count = 0;
    while (!ifstream.eof()){
        count++;
        int16_t sample;
        ifstream.read(reinterpret_cast<char*>(&sample), sizeof(sample));
    }

    std::ofstream ofstream("../audio/tmp.wav");

    std::cout << sizeof(header) << '\n';

    ofstream.write(reinterpret_cast<char*>(&header), sizeof(header));
    ofstream.write(data, header.subchunk2_size);

    for (unsigned int i = 0; i < count; i++){
        ofstream.put(1);
        ofstream.put(1);
    }

    delete[] data;
    */

    //std::cout << count << '\n';

    /*
    argparse::ArgumentParser program("SoundProcessor");
    program.add_description("The program performs audio conversions specified in the config "
                            "file and saves result to an output file.\n"
                            "Supports only WAV files with: "
                            "audio-format - PCM (without encoding), "
                            "1 channel (mono), "
                            "bit depth - signed 16 bit (little endian), "
                            "sample rate - 44100 Hz");

    program.add_argument("output_file")
            .help("The output file")
            .required();

    program.add_argument("input_file")
            .help("The input file")
            .required();

    program.add_argument("auxiliary_files")
            .help("auxiliary_files")
            .nargs(argparse::nargs_pattern::any);

    program.add_argument("-c", "--config")
            .help("Specify config file")
            .required();

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        return 1;
    }

    auto config_file = program.get<std::string>("-c");
    auto output_file = program.get<std::string>("output_file");
    auto input_file = program.get<std::string>("input_file");
    auto auxiliary_files = program.get<std::vector<std::string>>("auxiliary_files");
    */

    return 0;
}
