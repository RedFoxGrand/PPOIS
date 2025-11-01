#include "Reaction.h"

Reaction::Reaction(const string& timestamp, const Emoji& emoji, const Like& like) :
    timestamp_(timestamp),
    emoji_(emoji),
    like_(like) {
}

void Reaction::setTimestamp(const string& timestamp) {
    timestamp_ = timestamp;
}
void Reaction::setEmoji(const Emoji& emoji) {
    emoji_ = emoji;
}
void Reaction::setLike(const Like& like) {
    like_ = like;
}

const string& Reaction::getTimestamp() const {
    return timestamp_;
}
const Emoji& Reaction::getEmoji() const {
    return emoji_;
}
const Like& Reaction::getLike() const {
    return like_;
}

void Reaction::addReaction(const Emoji& emoji, const Like& like) {
    emoji_ = emoji;
    like_ = like;
}
