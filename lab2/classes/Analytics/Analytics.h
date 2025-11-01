#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <exception>

using namespace std;

class Analytics {
public:
    Analytics(const vector<int>& activeUserIds, const map<string, int>& actionsToday);

    void setActiveUserIds(const vector<int>& activeUserIds);
    void setActionsToday(const map<string, int>& actionsToday);

    const vector<int>& getActiveUserIds() const;
    const map<string, int>& getActionsToday() const;

    void recordAction(const string& action);
    int getDailyActiveUsers() const;
    map<string, int> getActions() const;

private:
    vector<int> activeUserIds_;
    map<string, int> actionsToday_;
};
