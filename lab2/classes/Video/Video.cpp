#include "Video.h"

Video::Video(int duration, int soundVolume, int bitrate, int sizeMb,
    const string& url, bool hasSubtitles, VideoFormat format,
    pair<int, int> resolution) :
    duration_(duration),
    soundVolume_(soundVolume),
    bitrate_(bitrate),
    sizeMb_(sizeMb),
    url_(url),
    hasSubtitles_(hasSubtitles),
    format_(format),
    resolution_(resolution) {
}

void Video::setDuration(int duration) {
    duration_ = duration;
}
void Video::setSoundVolume(int soundVolume) {
    soundVolume_ = soundVolume;
}
void Video::setBitrate(int bitrate) {
    bitrate_ = bitrate;
}
void Video::setSizeMb(int sizeMb) {
    sizeMb_ = sizeMb;
}
void Video::setUrl(const string& url) {
    url_ = url;
}
void Video::setHasSubtitles(bool hasSubtitles) {
    hasSubtitles_ = hasSubtitles;
}
void Video::setFormat(VideoFormat format) {
    format_ = format;
}
void Video::setResolution(pair<int, int> resolution) {
    resolution_ = resolution;
}

int Video::getDuration() const {
    return duration_;
}
int Video::getSoundVolume() const {
    return soundVolume_;
}
int Video::getBitrate() const {
    return bitrate_;
}
int Video::getSizeMb() const {
    return sizeMb_;
}
const string& Video::getUrl() const {
    return url_;
}
bool Video::getHasSubtitles() const {
    return hasSubtitles_;
}
VideoFormat Video::getFormat() const {
    return format_;
}

pair<int, int> Video::getResolution() const {
    return resolution_;
}

int Video::findoutUrl() {
    return static_cast<int>(url_.length());
}

void Video::toggleSubtitles(const string& subtitles) {
    hasSubtitles_ = !hasSubtitles_;
}
