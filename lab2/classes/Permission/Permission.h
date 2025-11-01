#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <algorithm>

class User;

using namespace std;

class Permission {
public:
    Permission(const string& name, const string& description, bool isRevocable);

    void setName(const string& name);
    void setDescription(const string& description);
    void setRevocable(bool isRevocable);

    const string& getName() const;
    const string& getDescription() const;
    bool getRevocable() const;

    void grantTo(User& user);
    void revokeFrom(User& user);

private:
    string name_;
    string description_;
    bool isRevocable_;
};
