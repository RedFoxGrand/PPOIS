#pragma once
#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

enum class GroupRole { MEMBER, MODERATOR, ADMIN };

class GroupMember {
public:
    GroupMember(const string& joinedDate, GroupRole role, const User& user);

    void setJoinedDate(const string& joinedDate);
    void setRole(GroupRole  role);
    void setUser(const User& user);

    const string& getJoinedDate() const;
    GroupRole  getRole() const;
    const User& getUser() const;

    string roleToString(GroupRole  role);
    void promoteToAdmin();
    void demoteFromAdmin();

private:
    string joinedDate_;
    GroupRole  role_;
    User user_;
};
