#include "Like.h"

Like::Like(const string& timestamp, const LikeTargetType& targetType, bool isLiked) :
    timestamp_(timestamp),
    targetType_(targetType),
    isLiked_(isLiked) {
}

void Like::setTimestamp(const string& timestamp) {
    timestamp_ = timestamp;
}
void Like::setTargetType(LikeTargetType targetType) {
    targetType_ = targetType;
}
void Like::setIsLiked(bool isLiked) {
    isLiked_ = isLiked;
}

const string& Like::getTimestamp() const {
    return timestamp_;
}
LikeTargetType Like::getTargetType() const {
    return targetType_;
}
bool Like::getIsLiked() const {
    return isLiked_;
}

void Like::toggleLike(LikeTargetType type) {
    targetType_ = type;
    isLiked_ = !isLiked_;
}
