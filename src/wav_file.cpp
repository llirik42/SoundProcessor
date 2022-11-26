#include <fstream>
#include "exceptions.h"
#include "wav_file.h"

using std::ifstream;

// Every id is presented by 4 bytes in file
const unsigned int ID_SIZE = 4;
const uint32_t RIFF_ID = 1179011410;
const uint32_t FMT_ID = 544501094;
const uint32_t EXTRA_DATA_ID = 1414744396;
const uint32_t DATA_ID = 1635017060;

const uint32_t SUPPORTED_RIFF_FORMAT = 1163280727;
const uint32_t SUPPORTED_FMT_SUBCHUNK_SIZE = 16;
const uint16_t SUPPORTED_FMT_AUDIO_FORMAT = 1;
const uint16_t SUPPORTED_NUMBER_OF_CHANNELS = 1;
const uint32_t SUPPORTED_SAMPLE_RATE = 44100;
const uint32_t SUPPORTED_BYTE_RATE = 88200;
const uint16_t SUPPORTED_BLOCK_ALIGN = 2;
const uint16_t SUPPORTED_BITS_PER_SAMPLE = 16;

#pragma pack(push, 1)
struct RIFFChunk{ // RIFF
    uint32_t chunk_size; // File size - 8
    uint32_t format; // Must contain "WAVE" for .wav files
};

struct FMTSubchunk{ // fmt
    uint32_t subchunk_size; // Size of remaining part of subchunk (16 for PCM)
    uint16_t audio_format; // 1 for PCM
    uint16_t num_channels; // Program only supports 1 (mono)
    uint32_t sample_rate; // Program only supports 44100 hz
    uint32_t byte_rate; // Number of bytes transmitted per second of playback
    uint16_t block_align; // size of one block
    uint16_t bits_per_sample; // bits in one sample (depth). Program only supports 16 bits/sample
};
#pragma pack(pop)

size_t get_file_size(ifstream& ifstream){
    auto start_pos = ifstream.tellg();

    ifstream.seekg(0, std::fstream::end);

    size_t result = static_cast<size_t>(ifstream.tellg());

    if (ifstream.fail()){
        throw IncorrectWavError();
    }

    ifstream.seekg(start_pos);

    return result;
}
bool is_file_empty(ifstream& ifstream){
    return !get_file_size(ifstream);
}

void validate_riff_chunk(const RIFFChunk& riff_chunk, size_t file_size){
    const bool check1 = static_cast<size_t>(riff_chunk.chunk_size) == file_size - 8;
    const bool check2 = riff_chunk.format == SUPPORTED_RIFF_FORMAT;

    const bool is_valid = check1 && check2;

    if (!is_valid){
        throw IncorrectWavError();
    }
}
void read_riff_chunk(ifstream& ifstream){
    RIFFChunk riff_chunk{};

    ifstream.read(reinterpret_cast<char*>(&riff_chunk), sizeof(riff_chunk));

    size_t file_size = get_file_size(ifstream);

    validate_riff_chunk(riff_chunk, file_size);
}

void validate_fmt_subchunk(const FMTSubchunk& fmt_subchunk){
    const bool check1 = fmt_subchunk.subchunk_size == SUPPORTED_FMT_SUBCHUNK_SIZE;
    const bool check2 = fmt_subchunk.audio_format == SUPPORTED_FMT_AUDIO_FORMAT;
    const bool check3 = fmt_subchunk.num_channels == SUPPORTED_NUMBER_OF_CHANNELS;
    const bool check4 = fmt_subchunk.sample_rate == SUPPORTED_SAMPLE_RATE;
    const bool check5 = fmt_subchunk.byte_rate == SUPPORTED_BYTE_RATE;
    const bool check6 = fmt_subchunk.block_align == SUPPORTED_BLOCK_ALIGN;
    const bool check7 = fmt_subchunk.bits_per_sample == SUPPORTED_BITS_PER_SAMPLE;

    const bool is_valid = check1 && check2 && check3 && check4 && check5 && check6 && check7;

    if (!is_valid){
        throw IncorrectWavError();
    }
}
void read_fmt_subchunk(ifstream& ifstream){
    FMTSubchunk fmt_subchunk{};

    ifstream.read(reinterpret_cast<char*>(&fmt_subchunk), sizeof(fmt_subchunk));

    validate_fmt_subchunk(fmt_subchunk);
}

void read_list_subchunk(ifstream& ifstream){
    uint32_t subchunk_size;

    ifstream.read(reinterpret_cast<char*>(&subchunk_size), sizeof(subchunk_size));

    auto buffer = new char[subchunk_size];

    ifstream.read(buffer, subchunk_size);

    delete[] buffer;
}
void read_data_subchunk(ifstream& ifstream){
    uint32_t data_subchunk_samples_count;

    ifstream.read(reinterpret_cast<char*>(&data_subchunk_samples_count), sizeof(data_subchunk_samples_count));

    data_subchunk_samples_count /= 2; // One sample = 2 bytes and after reading it contains size in bytes

    for (unsigned int i = 0; i < data_subchunk_samples_count; i++){
        uint16_t sample;
        ifstream.read(reinterpret_cast<char*>(&sample), sizeof(sample));
    }
}

WAVFile::WAVFile(const std::string& file_path){
    ifstream ifstream(file_path, std::ios::binary);

    if (!ifstream.is_open() || is_file_empty(ifstream)){
        throw IncorrectWavError();
    }

    bool met_riff = false;
    bool met_fmt = false;
    bool met_data = false;
    bool met_extra_data = false;

    uint32_t current_id;
    while (ifstream.read(reinterpret_cast<char*>(&current_id), ID_SIZE) && ifstream){
        const bool incorrect_order_of_chunks = current_id != RIFF_ID && !met_riff;
        if (incorrect_order_of_chunks){
            throw IncorrectWavError();
        }

        const bool separated_chunks = (current_id == RIFF_ID && met_riff) ||
                                      (current_id == FMT_ID && met_fmt) ||
                                      (current_id == DATA_ID && met_data) ||
                                      (current_id == EXTRA_DATA_ID && met_extra_data);

        if (separated_chunks){
            throw IncorrectWavError();
        }

        switch (current_id){
            case RIFF_ID:
                met_riff = true;
                read_riff_chunk(ifstream);
                break;
            case FMT_ID:
                met_fmt = true;
                read_fmt_subchunk(ifstream);
                break;
            case EXTRA_DATA_ID:
                met_extra_data = true;
                read_list_subchunk(ifstream);
                break;
            case DATA_ID:
                met_data = true;
                read_data_subchunk(ifstream);
                break;
            default:
                throw IncorrectWavError();
        }
    }

    if (!ifstream.eof()){
        throw IncorrectWavError();

    }
}
