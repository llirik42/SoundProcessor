#pragma once

#include "wav.h"

namespace Streams{
    class InputStream{
    public:
        explicit InputStream(WAVManagement::WAVReader& reader);

        [[nodiscard]] WAVFormatInfo::Sample get_element();

        [[nodiscard]] bool available() const;
    private:
        WAVManagement::WAVReader& _reader;
    };

    class OutputStream{
    public:
        explicit OutputStream(WAVManagement::WARWriter& writer);

        void write(WAVFormatInfo::Sample sample);
    private:
        WAVManagement::WARWriter& _writer;
    };
}
