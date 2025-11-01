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

enum class ReportTargetType { USER, POST, COMMENT };

class Report {
public:
    Report(const string& reason, const string& timestamp, bool isResolved,
           bool isEscalated, const User& reporter, const User& target, ReportTargetType targetType);

    void setReason(const string& reason);
    void setTimestamp(const string& timestamp);
    void setResolved(bool isResolved);
    void setReporter(const User& reporter);
    void setTarget(const User& target);
    void setTargetType(ReportTargetType targetType);

    const string& getReason() const;
    const string& getTimestamp() const;
    bool getResolved() const;
    const User& getReporter() const;
    const User& getTarget() const;
    ReportTargetType getTargetType() const;

    int getId() const;
    void markAsResolved();
    void setEscalated(bool escalated);

private:
    string reason_;
    string timestamp_;
    bool isResolved_;
    bool isEscalated_;
    User reporter_;
    User target_;
    ReportTargetType targetType_;
};
