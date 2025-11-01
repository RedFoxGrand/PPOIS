#include "Report.h"

Report::Report(const string& reason, const string& timestamp, bool isResolved,
    bool isEscalated, const User& reporter, const User& target, ReportTargetType targetType) :
    reason_(reason),
    timestamp_(timestamp),
    isResolved_(isResolved),
    isEscalated_(isEscalated),
    reporter_(reporter),
    target_(target),
    targetType_(targetType) {
}

void Report::setReason(const string& reason) {
    reason_ = reason;
}
void Report::setTimestamp(const string& timestamp) {
    timestamp_ = timestamp;
}
void Report::setResolved(bool isResolved) {
    isResolved_ = isResolved;
}
void Report::setReporter(const User& reporter) {
    reporter_ = reporter;
}
void Report::setTarget(const User& target) {
    target_ = target;
}
void Report::setTargetType(ReportTargetType targetType) {
    targetType_ = targetType;
}

const string& Report::getReason() const {
    return reason_;
}
const string& Report::getTimestamp() const {
    return timestamp_;
}
bool Report::getResolved() const {
    return isResolved_;
}
const User& Report::getReporter() const {
    return reporter_;
}
const User& Report::getTarget() const {
    return target_;
}
ReportTargetType Report::getTargetType() const {
    return targetType_;
}

int Report::getId() const {
    return target_.getId();
}

void Report::markAsResolved() {
    if (isResolved_) return;

    isResolved_ = true;

    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);

    tm timeInfo;
    localtime_s(&timeInfo, &time);

    stringstream ss;
    ss << put_time(&timeInfo, "%d.%m.%Y %H:%M:%S");
    timestamp_ = ss.str();
}

void Report::setEscalated(bool escalated) {
    if (isEscalated_ == escalated) return;

    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);

    tm timeInfo;
    localtime_s(&timeInfo, &time);

    stringstream ss;
    ss << put_time(&timeInfo, "%d.%m.%Y %H:%M:%S");
    timestamp_ = ss.str();

    isEscalated_ = escalated;
}
