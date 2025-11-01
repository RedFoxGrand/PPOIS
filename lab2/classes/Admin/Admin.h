#pragma once
#include "User.h"
#include "Permission.h"
#include "Ban.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Admin {
public:
    Admin(const string& accessLevel, const vector<Permission>& permissions,
          const vector<Ban>& bans, const User& user);

    void setAccessLevel(const string& accessLevel);
    void setPermissions(const vector<Permission>& permissions);
    void setBans(const vector<Ban>& bans);
    void setUser(const User& user);

    const string& getAccessLevel() const;
    const vector<Permission>& getPermissions() const;
    const vector<Ban>& getBans() const;
    const User& getUser() const;

    void banUser(User& user, const string& reason);
    void unbanUser(int userId);

private:
    string accessLevel_;
    vector<Permission> permissions_;
    vector<Ban> bans_;
    User user_;
};
