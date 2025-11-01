#pragma once
#include "User.h"
#include "UserNotFoundException.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <exception>

using namespace std;

class RecommendationEngine {
public:
    RecommendationEngine(const string& algorithm, const string& lastRun, const vector<User>& suggestions);

    void setAlgorithm(const string& algorithm);
    void setLastRun(const string& lastRun);
    void setSuggestions(const vector<User>& suggestions);

    const string& getAlgorithm() const;
    const string& getLastRun() const;
    const vector<User>& getSuggestions() const;

    void generateRecommendations(User& user);
    void updateAlgorithm(const string& newAlgorithm);

private:
    string algorithm_;
    string lastRun_;
    vector<User> suggestions_;
};
