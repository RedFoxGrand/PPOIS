#pragma once
#include "User.h"
#include "Comment.h"
#include "Tag.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

enum class PostType { TEXT, PHOTO, VIDEO, AUDIO, DOCUMENT };
enum class PostVisibility { PUBLIC, FRIENDS };

class Post {
public:
    Post(int postId, int likeCount, int commentCount, int shareCount, int viewCount,
         const string& content, const string& timestamp,
         const vector<Tag>& tags, const vector<Comment>& comments,
         const User& author, PostType type, PostVisibility visibility);

    void setPostId(int postId);
    void setLikeCount(int likeCount);
    void setCommentCount(int commentCount);
    void setShareCount(int shareCount);
    void setViewCount(int viewCount);
    void setContent(const string& content);
    void setTimestamp(const string& timestamp);
    void setTags(const vector<Tag>& tags);
    void setComments(const vector<Comment>& comments);
    void setAuthor(const User& author);
    void setType(PostType type);
    void setVisibility(PostVisibility visibility);

    int getPostId() const;
    int getLikeCount() const;
    int getCommentCount() const;
    int getShareCount() const;
    int getViewCount() const;
    const string& getContent() const;
    const string& getTimestamp() const;
    const vector<Tag>& getTags() const;
    const vector<Comment>& getComments() const;
    const User& getAuthor() const;
    PostType getType() const;
    PostVisibility getVisibility() const;

    void addComment(const Comment& comment);
    void addTag(const Tag& tag);

private:
    int postId_;
    int likeCount_;
    int commentCount_;
    int shareCount_;
    int viewCount_;
    string content_;
    string timestamp_;
    vector<Tag> tags_;
    vector<Comment> comments_;
    User author_;
    PostType type_;
    PostVisibility visibility_;
};
