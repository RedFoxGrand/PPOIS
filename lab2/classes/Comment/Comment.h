#pragma once
#include "User.h"
#include "InvalidMessageException.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Comment {
public:
    Comment(const string& content, const string& timestamp, bool isEdited, int likeCount, const User& author);

    void setContent(const string& content);
    void setTimestamp(const string& timestamp);
    void setEdited(bool isEdited);
    void setLikeCount(int likeCount);
    void setAuthor(const User& author);

    const string& getContent() const;
    const string& getTimestamp() const;
    bool getEdited() const;
    int getLikeCount() const;
    const User& getAuthor() const;

    void editComment(const string& newContent);
    void toLike();

private:
    int likeCount_;
    string content_;
    string timestamp_;
    bool isEdited_;
    User author_;
};
