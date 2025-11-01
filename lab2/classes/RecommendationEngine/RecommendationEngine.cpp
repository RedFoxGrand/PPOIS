#include "RecommendationEngine.h"

RecommendationEngine::RecommendationEngine(const string& algorithm, const string& lastRun, const vector<User>& suggestions) :
    algorithm_(algorithm),
    lastRun_(lastRun),
    suggestions_(suggestions) {
}

void RecommendationEngine::setAlgorithm(const string& algorithm) {
    algorithm_ = algorithm;
}
void RecommendationEngine::setLastRun(const string& lastRun) {
    lastRun_ = lastRun;
}
void RecommendationEngine::setSuggestions(const vector<User>& suggestions) {
    suggestions_ = suggestions;
}

const string& RecommendationEngine::getAlgorithm() const {
    return algorithm_;
}
const string& RecommendationEngine::getLastRun() const {
    return lastRun_;
}
const vector<User>& RecommendationEngine::getSuggestions() const {
    return suggestions_;
}

void RecommendationEngine::generateRecommendations(User& user) {
    if (user.getUsername().empty()) throw UserNotFoundException("Имя пользователя не задано");

    suggestions_.clear();
    suggestions_.push_back(user);

    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);

    tm timeInfo;
    localtime_s(&timeInfo, &time);

    stringstream ss;
    ss << put_time(&timeInfo, "%d.%m.%Y %H:%M:%S");
    lastRun_ = ss.str();
}

void RecommendationEngine::updateAlgorithm(const string& newAlgorithm) {
    algorithm_ = newAlgorithm;
}
