#pragma once
#include "DuplicateUsernameException.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <algorithm>

class User;

using namespace std;

class BlockList {
public:
    BlockList(const vector<User>& blockedUsers, const vector<string>& reasons);

    void setBlockedUsers(const vector<User>& blockedUsers);
    void setBlockReasons(const vector<string>& reasons);

    const vector<User>& getBlockedUsers() const;
    const vector<string>& getBlockReasons() const;

    void blockUser(const User& user, const string& reason);
    void unblockUser(const User& user);

private:
    vector<User> blockedUsers_;
    vector<string> reasons_;
};
