#include "gtest/gtest.h"
#include "../src/wav_file.h"
#include "../src/exceptions.h"

// incorrect path
TEST(WavTests, test_incorrect_path){
    EXPECT_THROW(WAVFile("<incorrect path>"), IncorrectWavError);
}

// empty file
TEST(WavTests, test_empty){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/empty.wav"), IncorrectWavError);
}

// no riff-chunk
TEST(WavTests, test_no_riff){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/no_riff.wav"), IncorrectWavError);
}

// chunk_size in riff-chunk != size of file - 8 (=0)
TEST(WavTests, test_incorrect_riff_size){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/incorrect_riff_size.wav"), IncorrectWavError);
}

// format in riff-chunk != WAVE
TEST(WavTests, test_incorrect_riff_format){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/incorrect_riff_format.wav"), IncorrectWavError);
}

// no fmt-subchunk
TEST(WavTests, test_no_fmt){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/no_fmt.wav"), IncorrectWavError);
}

// subchunk_size != 16 (=0)
TEST(WavTests, test_incorrect_fmt_subchunk_size){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/incorrect_fmt_subchunk_size.wav"), IncorrectWavError);
}

// format != 1 (=0)
TEST(WavTests, test_incorrect_audio_format){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/incorrect_audio_format.wav"), IncorrectWavError);
}

// number of channels != 1 (=2)
TEST(WavTests, test_incorrect_number_of_channels){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/incorrect_number_of_channels.wav"), IncorrectWavError);
}

// sample rate != 44100 (=88200)
TEST(WavTests, test_incorrect_sample_rate){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/incorrect_sample_rate.wav"), IncorrectWavError);
}

// byte rate != 88200 (=176400)
TEST(WavTests, test_incorrect_byte_rate){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/incorrect_byte_rate.wav"), IncorrectWavError);
}

// block align != 2(=3)
TEST(WavTests, test_incorrect_block_align){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/incorrect_block_align.wav"), IncorrectWavError);
}

// bits per sample != 16 (=8)
TEST(WavTests, test_incorrect_bits_per_sample){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/incorrect_bits_per_sample.wav"), IncorrectWavError);
}

// no data
TEST(WavTests, test_no_data){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/no_data.wav"), IncorrectWavError);
}

// riff chunk must go firstly
TEST(WavTests, riff_chunk_is_not_the_first_one){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/riff_chunk_is_not_the_first_one.wav"), IncorrectWavError);
}

// unknown subchunk in the end ""UNKNOWN_SUBCHUNK"
TEST(WavTests, unkown_subchunk){
    EXPECT_THROW(WAVFile("../tests/audio_for_tests/unknown_subchunk.wav"), IncorrectWavError);
}

// Order: riff-fmt-data
TEST(WavTests, correct_riff_fmt_data){
    EXPECT_NO_THROW(WAVFile("../tests/audio_for_tests/riff_fmt_data.wav"));
}

// Order: riff-data-fmt
TEST(WavTests, correct_riff_data_fmt){
    EXPECT_NO_THROW(WAVFile("../tests/audio_for_tests/riff_data_fmt.wav"));
}

// Order: riff-fmt-extra_data-data
TEST(WavTests, correct_riff_fmt_extra_data_data){
    EXPECT_NO_THROW(WAVFile("../tests/audio_for_tests/riff_fmt_extra_data_data.wav"));
}

// Order: riff-fmt-data-extra_data
TEST(WavTests, correct_riff_fmt_data_extra_data){
    EXPECT_NO_THROW(WAVFile("../tests/audio_for_tests/riff_fmt_data_extra_data.wav"));
}

// Order: riff-extra_data-fmt-data
TEST(WavTests, correct_riff_extra_data_fmt_data){
    EXPECT_NO_THROW(WAVFile("../tests/audio_for_tests/riff_extra_data_fmt_data.wav"));
}

// Order: riff-extra_data-data-fmt
TEST(WavTests, correct_riff_extra_data_data_fmt){
    EXPECT_NO_THROW(WAVFile("../tests/audio_for_tests/riff_extra_data_data_fmt.wav"));
}

// Order: riff-data-extra_data-fmt
TEST(WavTests, correct_riff_data_extra_data_fmt){
    EXPECT_NO_THROW(WAVFile("../tests/audio_for_tests/riff_data_extra_data_fmt.wav"));
}

// Order: riff-data-fmt-extra_data
TEST(WavTests, correct_riff_data_fmt_extra_data){
    EXPECT_NO_THROW(WAVFile("../tests/audio_for_tests/riff_data_fmt_extra_data.wav"));
}
