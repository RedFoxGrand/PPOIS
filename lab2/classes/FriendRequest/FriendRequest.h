#pragma once
#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <exception>

using namespace std;

enum class FriendRequestStatus { PENDING, ACCEPTED, REJECTED };

class FriendRequest {
public:
    FriendRequest(const string& sentDate, const string& responseDate, const User& sender, const User& receiver, const FriendRequestStatus& status);

    void setSentDate(const string& sentDate);
    void setResponseDate(const string& responseDate);
    void setSender(const User& sender);
    void setReceiver(const User& receiver);
    void setStatus(FriendRequestStatus status);

    const string& getSentDate() const;
    const string& getResponseDate() const;
    const User& getSender() const;
    const User& getReceiver() const;
    FriendRequestStatus getStatus() const;

    void accept();
    void reject();

private:
    string sentDate_;
    string responseDate_;
    User sender_;
    User receiver_;
    FriendRequestStatus status_;
};
