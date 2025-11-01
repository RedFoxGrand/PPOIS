#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Tag {
public:
    Tag(const string& label, const vector<int>& postIds);

    void setLabel(const string& label);
    void setPostIds(const vector<int>& postIds);

    const string& getLabel() const;
    const vector<int>& getPostIds() const;
    
    void addToPost(int postId);

private:
    string label_;
    vector<int> postIds_;
};
