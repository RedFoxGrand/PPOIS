#include "Media.h"

Media::Media(int sizeKb, const string& name, const string& url, MediaType type, MediaFormat format) :
    sizeKb_(sizeKb),
    name_(name),
    url_(url),
    type_(type),
    format_(format) {}

void Media::setSizeKb(int sizeKb) {
    sizeKb_ = sizeKb;
}
void Media::setName(const string& name) {
    name_ = name;
}
void Media::setUrl(const string& url) {
    url_ = url;
}
void Media::setType(MediaType type) {
    type_ = type;
}
void Media::setFormat(MediaFormat format) {
    format_ = format;
}

int Media::getSizeKb() const {
    return sizeKb_;
}
const string& Media::getName() const {
    return name_;
}
const string& Media::getUrl() const {
    return url_;
}
MediaType Media::getType() const {
    return type_;
}
MediaFormat Media::getFormat() const {
    return format_;
}

bool Media::validateFormat() {
    switch (type_) {
    case MediaType::TEXT: return format_ == MediaFormat::TXT;
    case MediaType::PHOTO: return format_ == MediaFormat::JPEG;
    case MediaType::VIDEO: return format_ == MediaFormat::MP4;
    case MediaType::AUDIO: return format_ == MediaFormat::MP3;
    case MediaType::DOCUMENT: return format_ == MediaFormat::PDF;
    default: return false;
    }
}

void Media::compressMedia() {
    if (sizeKb_ > 1024) {
        int originalSize = sizeKb_;

        switch (type_) {
        case MediaType::PHOTO: sizeKb_ = sizeKb_ * 70 / 100; break;
        case MediaType::VIDEO: sizeKb_ = sizeKb_ * 60 / 100; break;
        case MediaType::AUDIO: sizeKb_ = sizeKb_ * 80 / 100; break;
        case MediaType::TEXT:
        case MediaType::DOCUMENT: sizeKb_ = sizeKb_ * 90 / 100; break;
        }
    }
}
