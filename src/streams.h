#pragma once

#include "wav.h"

namespace Streams{
    class InputStream{
    public:
        explicit InputStream(WAVManagement::WAVReader& reader);

        [[nodiscard]] WAVFormatInfo::Sample get_element();

        [[nodiscard]] bool available() const;

        ~InputStream();
    private:
        struct Impl;
        Impl* _pimpl;
    };

    class OutputStream{
    public:
        explicit OutputStream(WAVManagement::WARWriter& writer);

        ~OutputStream();
    private:
        struct Impl;
        Impl* _pimpl;
    };
}
