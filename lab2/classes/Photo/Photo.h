#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

enum class PhotoFormat { JPEG, PNG, SVG, TIFF, RAW };

class Photo {
public:
    Photo(int sizeKb, const string& url, PhotoFormat format, pair<int, int> resolution);

    void setSizeKb(int sizeKb);
    void setUrl(const string& url);
    void setFormat(PhotoFormat format);
    void setResolution(pair<int, int> resolution);

    int getSizeKb() const;
    const string& getUrl() const;
    PhotoFormat getFormat() const;
    pair<int, int> getResolution() const;

    void changeResolution(pair<int, int> resolution);
    void resize(int newSizeKb);

private:
    int sizeKb_;
    string url_;
    PhotoFormat format_;
    pair<int, int> resolution_;
};
