#include "SearchEngine.h"

SearchEngine::SearchEngine(int indexSize, const string& lastUpdate, const string& stopWords, const string& rankingAlgorithm, const vector<string>& indexedTerms) :
    indexSize_(indexSize),
    lastUpdate_(lastUpdate),
    stopWords_(stopWords),
    rankingAlgorithm_(rankingAlgorithm),
    indexedTerms_(indexedTerms) {
}

void SearchEngine::setIndexSize(int indexSize) {
    indexSize_ = indexSize;
}
void SearchEngine::setLastUpdate(const string& lastUpdate) {
    lastUpdate_ = lastUpdate;
}
void SearchEngine::setStopWords(const string& stopWords) {
    stopWords_ = stopWords;
}
void SearchEngine::setRankingAlgorithm(const string& rankingAlgorithm) {
    rankingAlgorithm_ = rankingAlgorithm;
}
void SearchEngine::setIndexedTerms(const vector<string>& indexedTerms) {
    indexedTerms_ = indexedTerms;
}

int SearchEngine::getIndexSize() const {
    return indexSize_;
}
const string& SearchEngine::getLastUpdate() const {
    return lastUpdate_;
}
const string& SearchEngine::getStopWords() const {
    return stopWords_;
}
const string& SearchEngine::getRankingAlgorithm() const {
    return rankingAlgorithm_;
}
const vector<string>& SearchEngine::getIndexedTerms() const {
    return indexedTerms_;
}

vector<string> SearchEngine::search(const string& query) {
    if (query.empty()) return {};

    vector<string> results;
    for (const auto& term : indexedTerms_) if (term.find(query) != string::npos) results.push_back(term);

    return results;
}

void SearchEngine::reindex() {
    indexedTerms_.clear();

    string term;

    while (true) {
        if (term.empty()) break;

        indexedTerms_.push_back(term);
    }

    if (indexedTerms_.empty()) return ;

    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);

    tm timeInfo;
    localtime_s(&timeInfo, &time);

    stringstream ss;
    ss << put_time(&timeInfo, "%d.%m.%Y %H:%M:%S");
    lastUpdate_ = ss.str();
}
