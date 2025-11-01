#pragma once
#include "User.h"
#include "Photo.h"
#include "Video.h"
#include "Audio.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Album {
public:
    Album(const string& title, const User& owner, const vector<Photo>& photos,
          const vector<Video>& videos, const vector<Audio> audios);

    void setTitle(const string& title);
    void setOwner(const User& owner);
    void setPhotos(const vector<Photo>& photos);
    void setVideos(const vector<Video>& videos);
    void setAudios(const vector<Audio>& audios);

    const string& getTitle() const;
    const User& getOwner() const;
    const vector<Photo>& getPhotos() const;
    const vector<Video>& getVideos() const;
    const vector<Audio>& getAudios() const;

    void addPhoto(const Photo& photo);
    void addVideo(const Video& video);
    void addAudio(const Audio& audio);

private:
    string title_;
    vector<Photo> photos_;
    vector<Video> videos_;
    vector<Audio> audios_;
    User owner_;
};
