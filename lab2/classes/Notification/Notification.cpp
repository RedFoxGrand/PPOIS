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

class Notification {
public:
    Notification(const string& message, const string& createdDate, bool isRead, const User& recipient);

    void setMessage(const string& message);
    void setCreatedDate(const string& createdDate);
    void setIsRead(bool isRead);
    void setRecipient(const User& recipient);

    const string& getMessage() const;
    const string& getCreatedDate() const;
    bool getIsRead() const;
    const User& getRecipient() const;

    void markAsRead();

private:
    string message_;
    string createdDate_;
    bool isRead_;
    User recipient_;
};
