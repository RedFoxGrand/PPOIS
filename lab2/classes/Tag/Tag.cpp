#include "Tag.h"

Tag::Tag(const string& label, const vector<int>& postIds) :
    label_(label),
    postIds_(postIds) {
}

void Tag::setLabel(const string& label) {
    label_ = label;
}
void Tag::setPostIds(const vector<int>& postIds) {
    postIds_ = postIds;
}

const string& Tag::getLabel() const {
    return label_;
}
const vector<int>& Tag::getPostIds() const {
    return postIds_;
}

void Tag::addToPost(int postId) {
    if (find(postIds_.begin(), postIds_.end(), postId) != postIds_.end()) return;

    postIds_.push_back(postId);
}
