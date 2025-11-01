#pragma once
#include "User.h"
#include "DuplicateUsernameException.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Event {
public:
    Event(const string& title, const string& description, const string& dateTime, const vector<User>& participants, const User& organizer);

    void setTitle(const string& title);
    void setDescription(const string& description);
    void setDateTime(const string& dateTime);
    void setParticipants(const vector<User>& participants);
    void setOrganizer(const User& organizer);

    const string& getTitle() const;
    const string& getDescription() const;
    const string& getDateTime() const;
    const vector<User>& getParticipants() const;
    const User& getOrganizer() const;

    void addParticipant(const User& user);

private:
    string title_;
    string description_;
    string dateTime_;
    vector<User> participants_;
    User organizer_;
};
