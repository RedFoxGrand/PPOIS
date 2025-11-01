#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

enum class MediaType { TEXT, PHOTO, VIDEO, AUDIO, DOCUMENT };
enum class MediaFormat { TXT, JPEG, MP4, MP3, PDF };

class Media {
public:
    Media(int sizeKb, const string& name, const string& url, MediaType type, MediaFormat format);

    void setSizeKb(int sizeKb);
    void setName(const string& name);
    void setUrl(const string& url);
    void setType(MediaType type);
    void setFormat(MediaFormat format);

    int getSizeKb() const;
    const string& getName() const;
    const string& getUrl() const;
    MediaType getType() const;
    MediaFormat getFormat() const;

    bool validateFormat();
    void compressMedia();

private:
    int sizeKb_;
    string name_;
    string url_;
    MediaType type_;
    MediaFormat format_;
};
