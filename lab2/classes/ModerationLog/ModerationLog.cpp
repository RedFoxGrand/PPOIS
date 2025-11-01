#include "ModerationLog.h"

ModerationLog::ModerationLog(const string& action, const string& reason, 
    const string& timestamp, const User& moderator, const User& target) :
    action_(action),
    reason_(reason),
    timestamp_(timestamp),
    moderator_(moderator),
    target_(target) {
}

void ModerationLog::setAction(const string& action) {
    action_ = action;
}
void ModerationLog::setReason(const string& reason) {
    reason_ = reason;
}
void ModerationLog::setTimestamp(const string& timestamp) {
    timestamp_ = timestamp;
}
void ModerationLog::setModerator(const User& moderator) {
    moderator_ = moderator;
}
void ModerationLog::setTarget(const User& target) {
    target_ = target;
}

const string& ModerationLog::getAction() const {
    return action_;
}
const string& ModerationLog::getReason() const {
    return reason_;
}
const string& ModerationLog::getTimestamp() const {
    return timestamp_;
}
const User& ModerationLog::getModerator() const {
    return moderator_;
}
const User& ModerationLog::getTarget() const {
    return target_;
}

void ModerationLog::recordAction(const string& action, const string& reason) {
    if (action.empty() || reason.empty()) return;

    action_ = action;
    reason_ = reason;
}
