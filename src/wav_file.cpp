#include <memory>
#include "wav_file.h"
#include "exceptions.h"
#include "utils.h"
#include "wav_format_info.h"

const size_t BUFFER_SIZE = 1024; // In samples (not in bytes)

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

struct WAVFile::Impl{
    std::ifstream file;

    size_t duration_s;

    size_t samples_count;

    Sample buffer[BUFFER_SIZE];

    size_t index_in_buffer;

    void read_to_buffer(){
        file.read(reinterpret_cast<char*>(&buffer), sizeof(buffer));
    }
};

void validate_riff_chunk(const RIFFChunk& riff_chunk, size_t file_size){
    const bool check1 = static_cast<size_t>(riff_chunk.chunk_size) == file_size - 8;
    const bool check2 = riff_chunk.format == SUPPORTED_RIFF_FORMAT;

    const bool is_valid = check1 && check2;

    if (!is_valid){
        throw IncorrectWavError();
    }
}
void read_riff_chunk(std::ifstream& wav_file){
    RIFFChunk riff_chunk{};

    wav_file.read(reinterpret_cast<char*>(&riff_chunk), sizeof(riff_chunk));

    size_t file_size = get_file_size(wav_file);

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
void read_fmt_subchunk(std::ifstream& wav_file){
    FMTSubchunk fmt_subchunk{};

    wav_file.read(reinterpret_cast<char*>(&fmt_subchunk), sizeof(fmt_subchunk));

    validate_fmt_subchunk(fmt_subchunk);
}

void read_extra_data_subchunk(std::ifstream& wav_file){
    uint32_t subchunk_size;

    wav_file.read(reinterpret_cast<char*>(&subchunk_size), sizeof(subchunk_size));

    auto buffer = new char[subchunk_size];

    wav_file.read(buffer, subchunk_size);

    delete[] buffer;
}
void read_data_subchunk(std::ifstream& wav_file, fpos_t& data_start_position, size_t& samples_count){
    uint32_t data_subchunk_samples_count;

    wav_file.read(reinterpret_cast<char*>(&data_subchunk_samples_count), sizeof(data_subchunk_samples_count));

    data_subchunk_samples_count /= 2; // One sample = 2 bytes and after reading it contains size in bytes

    data_start_position = wav_file.tellg();
    samples_count = data_subchunk_samples_count;

    for (unsigned int i = 0; i < data_subchunk_samples_count; i++){
        uint16_t sample;
        wav_file.read(reinterpret_cast<char*>(&sample), sizeof(sample));
    }
}

WAVFile::WAVFile(const std::string& file_path){
    fpos_t data_start_position;
    size_t samples_count;

    std::ifstream wav_file(file_path, std::ios::binary);

    if (!wav_file.is_open() || is_file_empty(wav_file)){
        throw IncorrectWavError();
    }

    bool met_riff = false;
    bool met_fmt = false;
    bool met_data = false;
    bool met_extra_data = false;

    uint32_t current_id;
    while (wav_file.read(reinterpret_cast<char*>(&current_id), ID_SIZE) && wav_file){
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
                read_riff_chunk(wav_file);
                break;
            case FMT_ID:
                met_fmt = true;
                read_fmt_subchunk(wav_file);
                break;
            case EXTRA_DATA_ID:
                met_extra_data = true;
                read_extra_data_subchunk(wav_file);
                break;
            case DATA_ID:
                met_data = true;
                read_data_subchunk(wav_file, data_start_position, samples_count);
                break;
            default:
                throw IncorrectWavError();
        }
    }

    // Error occurred while reading file
    if (!wav_file.eof()){
        throw IncorrectWavError();
    }

    wav_file.clear();

    wav_file.seekg(0);

    _pimpl = new Impl{
        std::move(wav_file),
        samples_count / SUPPORTED_SAMPLE_RATE,
        samples_count,
        {},
        0
    };

    _pimpl->read_to_buffer();
}

size_t WAVFile::get_duration_s() const{
    return _pimpl->duration_s;
}

Sample WAVFile::get_sample() const{
    Sample result = _pimpl->buffer[_pimpl->index_in_buffer++];

    if (_pimpl->index_in_buffer == BUFFER_SIZE){
        _pimpl->index_in_buffer = 0;

        _pimpl->read_to_buffer();
    }

    return result;
}

size_t WAVFile::get_samples_count() const{
    return _pimpl->samples_count;
}

WAVFile::~WAVFile(){
    delete _pimpl;
}

