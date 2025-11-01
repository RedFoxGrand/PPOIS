#include "Emoji.h"

Emoji::Emoji(const string& code, const string& imageUrl) :
    code_(code),
    imageUrl_(imageUrl) {
}

void Emoji::setCode(const string& code) {
    code_ = code;
}
void Emoji::setImageUrl(const string& imageUrl) {
    imageUrl_ = imageUrl;
}

const string& Emoji::getCode() const {
    return code_;
}
const string& Emoji::getImageUrl() const {
    return imageUrl_;
}

bool Emoji::validateEmojiCode() const
{
    if (code_.empty()) return false;
    if (code_.length() > 10) return false;
    if (code_.find(' ') != string::npos) return false;

    return true;
}
