#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Emoji {
public:
    Emoji(const string& code, const string& imageUrl);

    void setCode(const string& code);
    void setImageUrl(const string& imageUrl);

    const string& getCode() const;
    const string& getImageUrl() const;

    bool validateEmojiCode() const;

private:
    string code_;
    string imageUrl_;
};
