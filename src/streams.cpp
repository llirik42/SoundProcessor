#include "streams.h"

Streams::InputStream::InputStream(WAVManagement::WAVReader& reader): _reader(reader) {}

WAVFormatInfo::Sample Streams::InputStream::get_element(){
    return _reader.get_sample();
}

bool Streams::InputStream::available() const{
    return _reader.available();
}

Streams::OutputStream::OutputStream(WAVManagement::WARWriter& writer): _writer(writer) {}

void Streams::OutputStream::write(WAVFormatInfo::Sample sample){
    _writer.write_sample(sample);
}
