#include "Poll.h"

Poll::Poll(const string& question, const string& deadline, bool isMultipleChoice,
           const vector<string>& options, const map<string, int>& votes) :
    question_(question),
    deadline_(deadline),
    isMultipleChoice_(isMultipleChoice),
    options_(options),
    votes_(votes) {}

void Poll::setQuestion(const string& question) {
    question_ = question;
}
void Poll::setDeadline(const string& deadline) {
    deadline_ = deadline;
}
void Poll::setMultipleChoice(bool isMultipleChoice) {
    isMultipleChoice_ = isMultipleChoice;
}
void Poll::setOptions(const vector<string>& options) {
    options_ = options;
}
void Poll::setVotes(const map<string, int>& votes) {
    votes_ = votes;
}

const string& Poll::getQuestion() const {
    return question_;
}
const string& Poll::getDeadline() const {
    return deadline_;
}
bool Poll::isMultipleChoiceEnabled() const {
    return isMultipleChoice_;
}
const vector<string>& Poll::getOptions() const {
    return options_;
}
const map<string, int>& Poll::getVotes() const {
    return votes_;
}

void Poll::vote(const User& user, const string& option) {
    for (const string& opt : options_) {
        if (opt == option) {
            votes_[option]++;
            return;
        }
    }
}

string Poll::getResults() const {
    if (options_.empty()) return "";

    stringstream result;

    for (const string& opt : options_) {
        int count = votes_.count(opt) ? votes_.at(opt) : 0;
        result << opt << ": " << count << " " << (count == 1 ? "голос" : (count >= 2 && count <= 4 ? "голоса" : "голосов")) << endl;
    }

    return result.str();
}
