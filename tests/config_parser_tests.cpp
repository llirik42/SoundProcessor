#include "gtest/gtest.h"
#include "../src/config_parser.h"
#include "../src/exceptions.h"

// incorrect path
TEST(ConfigsParserTests, test_incorrect_path){
    EXPECT_THROW(
            ConfigParser("<incorrect path>"),
            Exceptions::IncorrectConfigError
            );
}

// incorrect path
TEST(ConfigsParserTests, test_empty_file){
    EXPECT_THROW(
            ConfigParser("../tests/config_files_for_tests/empty_config.txt"),
            Exceptions::IncorrectConfigError
            );
}
