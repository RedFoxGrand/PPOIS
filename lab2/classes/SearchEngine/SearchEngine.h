#pragma once
#include "User.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Session {
public:
    Session(const string& token, const string& createdDate, const string& duration, const User& user);

    void setToken(const string& token);
    void setCreatedDate(const string& createdDate);
    void setDuration(const string& duration);
    void setUser(const User& user);

    const string& getToken() const;
    const string& getCreatedDate() const;
    const string& getDuration() const;
    const User& getUser() const;

    bool isValidSession() const;
    void extendDuration();
    void invalidateSession();

private:
    string token_;
    string createdDate_;
    string duration_;
    User user_;
};
