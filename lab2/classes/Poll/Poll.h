#pragma once
#include "User.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <exception>

using namespace std;

class Poll {
public:
    Poll(const string& question, const string& deadline, bool isMultipleChoice,
         const vector<string>& options, const map<string, int>& votes);

    void setQuestion(const string& question);
    void setDeadline(const string& deadline);
    void setMultipleChoice(bool isMultipleChoice);
    void setOptions(const vector<string>& options);
    void setVotes(const map<string, int>& votes);

    const string& getQuestion() const;
    const string& getDeadline() const;
    bool isMultipleChoiceEnabled() const;
    const vector<string>& getOptions() const;
    const map<string, int>& getVotes() const;

    void vote(const User& user, const string& option);
    string getResults() const;

private:
    string question_;
    string deadline_;
    bool isMultipleChoice_;
    vector<string> options_;
    map<string, int> votes_;
};
