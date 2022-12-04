#include "streams.h"

struct Streams::InputStream::Impl{

};

Streams::InputStream::InputStream(WAVManagement::WAVReader& reader){

}

WAVFormatInfo::Sample Streams::InputStream::get_element(){
    return 0;
}

bool Streams::InputStream::available() const{
    return false;
}

struct Streams::OutputStream::Impl{

};

Streams::InputStream::~InputStream(){
    delete _pimpl;
}

Streams::OutputStream::OutputStream(WAVManagement::WARWriter& writer){

}

Streams::OutputStream::~OutputStream(){
    delete _pimpl;
}
