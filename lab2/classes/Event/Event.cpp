#include "Event.h"

Event::Event(const string& title, const string& description, const string& dateTime, const vector<User>& participants, const User& organizer) :
    title_(title),
    description_(description),
    dateTime_(dateTime),
    participants_(participants),
    organizer_(organizer) {
}

void Event::setTitle(const string& title) {
    title_ = title;
}
void Event::setDescription(const string& description) {
    description_ = description;
}
void Event::setDateTime(const string& dateTime) {
    dateTime_ = dateTime;
}
void Event::setParticipants(const vector<User>& participants) {
    participants_ = participants;
}
void Event::setOrganizer(const User& organizer) {
    organizer_ = organizer;
}

const string& Event::getTitle() const {
    return title_;
}
const string& Event::getDescription() const {
    return description_;
}
const string& Event::getDateTime() const {
    return dateTime_;
}
const vector<User>& Event::getParticipants() const {
    return participants_;
}
const User& Event::getOrganizer() const {
    return organizer_;
}

void Event::addParticipant(const User& user) {
    for (const auto& u : participants_) {
        if (u.getId() == user.getId()) throw DuplicateUsernameException("Пользователь уже участвует в событии");
    }

    participants_.push_back(user);
}
