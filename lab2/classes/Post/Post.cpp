#include "Post.h"

Post::Post(int postId, int likeCount, int commentCount, int shareCount, int viewCount,
    const string& content, const string& timestamp,
    const vector<Tag>& tags, const vector<Comment>& comments,
    const User& author, PostType type, PostVisibility visibility) :
    postId_(postId),
    likeCount_(likeCount),
    commentCount_(commentCount),
    shareCount_(shareCount),
    viewCount_(viewCount),
    content_(content),
    timestamp_(timestamp),
    tags_(tags),
    comments_(comments),
    author_(author),
    type_(type),
    visibility_(visibility) {
}

void Post::setPostId(int postId) {
    postId_ = postId;
}

void Post::setLikeCount(int likeCount) {
    likeCount_ = likeCount;
}

void Post::setCommentCount(int commentCount) {
    commentCount_ = commentCount;
}

void Post::setShareCount(int shareCount) {
    shareCount_ = shareCount;
}

void Post::setViewCount(int viewCount) {
    viewCount_ = viewCount;
}

void Post::setContent(const string& content) {
    content_ = content;
}

void Post::setTimestamp(const string& timestamp) {
    timestamp_ = timestamp;
}

void Post::setTags(const vector<Tag>& tags) {
    tags_ = tags;
}

void Post::setComments(const vector<Comment>& comments) {
    comments_ = comments;
}

void Post::setAuthor(const User& author) {
    author_ = author;
}

void Post::setType(PostType type) {
    type_ = type;
}

void Post::setVisibility(PostVisibility visibility) {
    visibility_ = visibility;
}

int Post::getPostId() const {
    return postId_;
}

int Post::getLikeCount() const {
    return likeCount_;
}

int Post::getCommentCount() const {
    return commentCount_;
}

int Post::getShareCount() const {
    return shareCount_;
}

int Post::getViewCount() const {
    return viewCount_;
}

const string& Post::getContent() const {
    return content_;
}

const string& Post::getTimestamp() const {
    return timestamp_;
}

const vector<Tag>& Post::getTags() const {
    return tags_;
}

const vector<Comment>& Post::getComments() const {
    return comments_;
}

const User& Post::getAuthor() const {
    return author_;
}

PostType Post::getType() const {
    return type_;
}

PostVisibility Post::getVisibility() const {
    return visibility_;
}

void Post::addComment(const Comment& comment) {
    if (comment.getContent().empty())  return;
   
    comments_.push_back(comment);
    commentCount_ = static_cast<int>(comments_.size());;
}

void Post::addTag(const Tag& tag) {
    for (const Tag& existing : tags_) if (existing.getLabel() == tag.getLabel()) return;

    tags_.push_back(tag);
}
