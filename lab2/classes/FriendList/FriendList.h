#pragma once
#include "DuplicateUsernameException.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <algorithm>

class User;

using namespace std;

class FriendList {
public:
    FriendList(const vector<User>& friends,
        const vector<User>& pendingRequestFriends,
        const vector<User>& suggestedFriends);

    void setFriends(const vector<User>& friends);
    void setPendingRequests(const vector<User>& pendingRequestFriends);
    void setSuggestedFriends(const vector<User>& suggestedFriends);

    const vector<User>& getFriends() const;
    const vector<User>& getPendingRequests() const;
    const vector<User>& getSuggestedFriends() const;

    void addFriend(const User& user);
    void removeFriend(const User& user);
    void sendFriendRequest(const User& user);

private:
    vector<User> friends_;
    vector<User> pendingRequestFriends_;
    vector<User> suggestedFriends_;
};
