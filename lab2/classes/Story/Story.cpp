#include "Story.h"

Story::Story(int viewsCount, const string& timestamp, const string& duration, const vector<Media>& media) :
    viewsCount_(viewsCount),
    timestamp_(timestamp),
    duration_(duration),
    media_(media) {
}

void Story::setViewsCount(int viewsCount) {
    viewsCount_ = viewsCount;
}
void Story::setTimestamp(const string& timestamp) {
    timestamp_ = timestamp;
}
void Story::setDuration(const string& duration) {
    duration_ = duration;
}
void Story::setMedia(const vector<Media>& media) {
    media_ = media;
}

int Story::getViewsCount() const {
    return viewsCount_;
}
const string& Story::getTimestamp() const {
    return timestamp_;
}
const string& Story::getDuration() const {
    return duration_;
}
const vector<Media>& Story::getMedia() const {
    return media_;
}

bool Story::isExpired() const {
    return duration_ == "0";
}

void Story::expire() {
    if (isExpired()) return;

    duration_ = "0";
}
