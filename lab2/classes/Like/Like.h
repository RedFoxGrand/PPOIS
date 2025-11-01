#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

enum class LikeTargetType { POST, COMMENT };

class Like {
public:
    Like(const string& timestamp, const LikeTargetType& targetType, bool isLiked);

    void setTimestamp(const string& timestamp);
    void setTargetType(LikeTargetType targetType);
    void setIsLiked(bool isLiked);

    const string& getTimestamp() const;
    LikeTargetType getTargetType() const;
    bool getIsLiked() const;

    void toggleLike(LikeTargetType type);
private:
    string timestamp_;
    LikeTargetType targetType_;
    bool isLiked_;
};
