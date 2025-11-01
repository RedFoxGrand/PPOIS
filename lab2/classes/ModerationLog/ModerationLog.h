#pragma once
#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class ModerationLog {
public:
    ModerationLog(const string& action, const string& reason,
                  const string& timestamp, const User& moderator, const User& target);

    void setAction(const string& action);
    void setReason(const string& reason);
    void setTimestamp(const string& timestamp);
    void setModerator(const User& moderator);
    void setTarget(const User& target);

    const string& getAction() const;
    const string& getReason() const;
    const string& getTimestamp() const;
    const User& getModerator() const;
    const User& getTarget() const;

    void recordAction(const string& action, const string& reason);

private:
    string action_;
    string reason_;
    string timestamp_;
    User moderator_;
    User target_;
};
