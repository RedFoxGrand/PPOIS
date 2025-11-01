#include "Analytics.h"

Analytics::Analytics(const vector<int>& activeUserIds, const map<string, int>& actionsToday) :
    activeUserIds_(activeUserIds),
    actionsToday_(actionsToday) {
}

void Analytics::setActiveUserIds(const vector<int>& activeUserIds) {
    activeUserIds_ = activeUserIds;
}
void Analytics::setActionsToday(const map<string, int>& actionsToday) {
    actionsToday_ = actionsToday;
}

const vector<int>& Analytics::getActiveUserIds() const {
    return activeUserIds_;
}
const map<string, int>& Analytics::getActionsToday() const {
    return actionsToday_;
}

void Analytics::recordAction(const string& action)
{
    if (action.empty()) return;

    actionsToday_[action]++;
    int count = actionsToday_[action];
}

int Analytics::getDailyActiveUsers() const {
    return static_cast<int>(activeUserIds_.size());
}

map<string, int> Analytics::getActions() const {
    return actionsToday_;
}
