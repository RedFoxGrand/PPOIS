#include "FriendRequest.h"

FriendRequest::FriendRequest(const string& sentDate, const string& responseDate, const User& sender, const User& receiver, const FriendRequestStatus& status) :
    sentDate_(sentDate),
    responseDate_(""),
    sender_(sender),
    receiver_(receiver),
    status_(status) {
}

void FriendRequest::setSentDate(const string& sentDate) {
    sentDate_ = sentDate;
}
void FriendRequest::setResponseDate(const string& responseDate) {
    responseDate_ = responseDate;
}
void FriendRequest::setSender(const User& sender) {
    sender_ = sender;
}
void FriendRequest::setReceiver(const User& receiver) {
    receiver_ = receiver;
}
void FriendRequest::setStatus(FriendRequestStatus status) {
    status_ = status;
}

const string& FriendRequest::getSentDate() const {
    return sentDate_;
}
const string& FriendRequest::getResponseDate() const {
    return responseDate_;
}
const User& FriendRequest::getSender() const {
    return sender_;
}
const User& FriendRequest::getReceiver() const {
    return receiver_;
}
FriendRequestStatus FriendRequest::getStatus() const {
    return status_;
}

void FriendRequest::accept() {
    if (status_ == FriendRequestStatus::ACCEPTED) return;

    status_ = FriendRequestStatus::ACCEPTED;

    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);

    tm timeInfo;
    localtime_s(&timeInfo, &time);

    stringstream ss;
    ss << put_time(&timeInfo, "%d.%m.%Y %H:%M:%S");
    responseDate_ = ss.str();
}


void FriendRequest::reject() {
    if (status_ != FriendRequestStatus::PENDING) return;

    status_ = FriendRequestStatus::REJECTED;

    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);

    tm timeInfo;
    localtime_s(&timeInfo, &time);

    stringstream ss;
    ss << put_time(&timeInfo, "%d.%m.%Y %H:%M:%S");
    responseDate_ = ss.str();
}
