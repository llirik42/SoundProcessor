#pragma once

#include <cstdint>
#include <cstdio>
#include <string>

namespace WAVFormatInfo{
    using Sample = int16_t;

    // Every id is presented by 4 bytes in file
    const unsigned int ID_SIZE = 4;
    const uint32_t RIFF_ID = 1179011410;
    const uint32_t FMT_ID = 544501094;
    const uint32_t LIST_ID = 1414744396;
    const uint32_t DATA_ID = 1635017060;

    const uint32_t SUPPORTED_RIFF_FORMAT = 1163280727;
    const uint32_t SUPPORTED_FMT_SUBCHUNK_SIZE = 16;
    const uint16_t SUPPORTED_FMT_AUDIO_FORMAT = 1;
    const uint16_t SUPPORTED_NUMBER_OF_CHANNELS = 1;
    const uint32_t SUPPORTED_SAMPLE_RATE = 44100;
    const uint32_t SUPPORTED_BYTE_RATE = 88200;
    const uint16_t SUPPORTED_BLOCK_ALIGN = 2;
    const uint16_t SUPPORTED_BITS_PER_SAMPLE = 16;
}

namespace WAVManagement{
    struct WAVInfo{
        size_t duration_s;
        size_t samples_count;
        fpos_t data_start_position;
    };

    class WAVParser{
    public:
        static WAVInfo parse(std::string_view file_path);
    };

    class WAVReader{
    public:
        explicit WAVReader(std::string_view file_path);

        [[nodiscard]] size_t get_duration_s();

        [[nodiscard]] size_t get_samples_count();

        [[nodiscard]] WAVFormatInfo::Sample read_sample();

        [[nodiscard]] bool available() const;

        ~WAVReader();
    private:
        struct Impl;
        Impl* _pimpl;
    };

    class WAVWriter{
    public:
        explicit WAVWriter(std::string_view file_path);

        void write_sample(WAVFormatInfo::Sample sample);

        ~WAVWriter();
    private:
        struct Impl;
        Impl* _pimpl;
    };

    size_t get_sample_number_by_time(size_t time_s);
}
