#pragma once
#include "Media.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Story {
public:
    Story(int viewsCount, const string& timestamp, const string& duration, const vector<Media>& media);

    void setViewsCount(int viewsCount);
    void setTimestamp(const string& timestamp);
    void setDuration(const string& duration);
    void setMedia(const vector<Media>& media);

    int getViewsCount() const;
    const string& getTimestamp() const;
    const string& getDuration() const;
    const vector<Media>& getMedia() const;

    bool isExpired() const;
    void expire();

private:
    int viewsCount_;
    string timestamp_;
    string duration_;
    vector<Media> media_;
};
