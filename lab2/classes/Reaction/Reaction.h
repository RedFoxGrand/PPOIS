#pragma once
#include "Emoji.h"
#include "Like.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Reaction {
public:
    Reaction(const string& timestamp, const Emoji& emoji, const Like& like);

    void setTimestamp(const string& timestamp);
    void setEmoji(const Emoji& emoji);
    void setLike(const Like& like);

    const string& getTimestamp() const;
    const Emoji& getEmoji() const;
    const Like& getLike() const;

    void addReaction(const Emoji& emoji, const Like& like);
private:
    string timestamp_;
    Emoji emoji_;
    Like like_;
};
