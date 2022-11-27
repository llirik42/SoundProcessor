#pragma once

#include <cstdint>

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