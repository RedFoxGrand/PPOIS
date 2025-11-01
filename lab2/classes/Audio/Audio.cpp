#include "Album.h"

Album::Album(const string& title, const User& owner, const vector<Photo>& photos,
             const vector<Video>& videos, const vector<Audio> audios) :
    title_(title),
    photos_(photos),
    videos_(videos),
    audios_(audios),
    owner_(owner) {
}

void Album::setTitle(const string& title) {
    title_ = title;
}
void Album::setOwner(const User& owner) {
    owner_ = owner;
}
void Album::setPhotos(const vector<Photo>& photos) {
    photos_ = photos;
}
void Album::setVideos(const vector<Video>& videos) {
    videos_ = videos;
}
void Album::setAudios(const vector<Audio>& audios) {
    audios_ = audios;
}

const string& Album::getTitle() const {
    return title_;
}
const User& Album::getOwner() const {
    return owner_;
}
const vector<Photo>& Album::getPhotos() const {
    return photos_;
}
const vector<Video>& Album::getVideos() const {
    return videos_;
}
const vector<Audio>& Album::getAudios() const {
    return audios_;
}

void Album::addPhoto(const Photo& photo) {
    photos_.push_back(photo);
}

void Album::addVideo(const Video& video) {
    videos_.push_back(video);
}

void Album::addAudio(const Audio& audio) {
    audios_.push_back(audio);
}
