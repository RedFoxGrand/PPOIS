#include "Photo.h"

Photo::Photo(int sizeKb, const string& url, PhotoFormat format, pair<int, int> resolution) :
    sizeKb_(sizeKb),
    url_(url),
    format_(format),
    resolution_(resolution) {
}

void Photo::setSizeKb(int sizeKb) {
    sizeKb_ = sizeKb;
}
void Photo::setUrl(const string& url) {
    url_ = url;
}
void Photo::setFormat(PhotoFormat format) {
    format_ = format;
}
void Photo::setResolution(pair<int, int> resolution) {
    resolution_ = resolution;
}

int Photo::getSizeKb() const {
    return sizeKb_;
}
const string& Photo::getUrl() const {
    return url_;
}
PhotoFormat Photo::getFormat() const {
    return format_;
}
pair<int, int> Photo::getResolution() const {
    return resolution_;
}

void Photo::changeResolution(pair<int, int> resolution) {
    resolution_ = resolution;
}

void Photo::resize(int newSizeKb) {
    sizeKb_ = newSizeKb;
}
