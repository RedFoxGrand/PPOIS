#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

enum class VideoFormat { MP4, MOV, AVI, WMV, MPEG };

class Video {
public:
    Video(int duration, int soundVolume, int bitrate, int sizeMb,
          const string& url, bool hasSubtitles, VideoFormat format,
          pair<int, int> resolution);

    void setDuration(int duration);
    void setSoundVolume(int soundVolume);
    void setBitrate(int bitrate);
    void setSizeMb(int sizeMb);
    void setUrl(const string& url);
    void setHasSubtitles(bool hasSubtitles);
    void setFormat(VideoFormat format);
    void setResolution(pair<int, int> resolution);

    int getDuration() const;
    int getSoundVolume() const;
    int getBitrate() const;
    int getSizeMb() const;
    const string& getUrl() const;
    bool getHasSubtitles() const;
    VideoFormat getFormat() const;
    pair<int, int> getResolution() const;

    int findoutUrl();
    void toggleSubtitles(const string& subtitles);

private:
    int duration_;
    int soundVolume_;
    int bitrate_;
    int sizeMb_;
    string url_;
    bool hasSubtitles_;
    VideoFormat format_;
    pair<int, int> resolution_;
};
