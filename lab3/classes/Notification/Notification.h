#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "Passenger.h"

using namespace std;

class Notification {
public:
    Notification(const Passenger& recipient, const string& message, 
        time_t timestamp, bool isRead);

    void setRecipient(const Passenger& recipient);
    void setMessage(const string& message);
    void setTimestamp(time_t timestamp);
    void setIsRead(bool isRead);

    const Passenger& getRecipient() const;
    const string& getMessage() const;
    time_t getTimestamp() const;
    bool getIsRead() const;

    void markAsRead();

private:
    Passenger recipient_;
    string message_;
    time_t timestamp_;
    bool isRead_;
};
