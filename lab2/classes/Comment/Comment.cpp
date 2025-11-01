#include "Comment.h"

Comment::Comment(const string& content, const string& timestamp, bool isEdited, int likeCount, const User& author) :
    content_(content),
    timestamp_(timestamp),
    isEdited_(isEdited),
    likeCount_(likeCount),
    author_(author) {
}

void Comment::setContent(const string& content) {
    content_ = content;
}
void Comment::setTimestamp(const string& timestamp) {
    timestamp_ = timestamp;
}
void Comment::setEdited(bool isEdited) {
    isEdited_ = isEdited;
}
void Comment::setLikeCount(int likeCount) {
    likeCount_ = likeCount;
}
void Comment::setAuthor(const User& author) {
    author_ = author;
}

const string& Comment::getContent() const {
    return content_;
}
const string& Comment::getTimestamp() const {
    return timestamp_;
}
bool Comment::getEdited() const {
    return isEdited_;
}
int Comment::getLikeCount() const {
    return likeCount_;
}
const User& Comment::getAuthor() const {
    return author_;
}

void Comment::editComment(const string& newContent) {
    if (newContent.empty()) throw InvalidMessageException("Комментарий не может быть пустым");
    if (newContent == content_) throw InvalidMessageException("Новое содержимое совпадает с текущим. Редактирование отменено");

    content_ = newContent;
    isEdited_ = true;
}

void Comment::toLike() {
    likeCount_++;
}
