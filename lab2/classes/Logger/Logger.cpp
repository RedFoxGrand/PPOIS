#include "Logger.h"

Logger::Logger(const string& logLevel, const vector<string>& logs) :
    logLevel_(logLevel),
    logs_(logs) {
}

void Logger::setLogLevel(const string& logLevel) {
    logLevel_ = logLevel;
}
void Logger::setLogs(const vector<string>& logs) {
    logs_ = logs;
}

const string& Logger::getLogLevel() const {
    return logLevel_;
}
const vector<string>& Logger::getLogs() const {
    return logs_;
}

void Logger::log(const string& message) {
    if (message.empty()) return;

    string entry = "[" + logLevel_ + "] " + message;
    logs_.push_back(entry);

    cout << entry << endl;
}

void Logger::setLevel(const string& level) {
    logLevel_ = level;
}

void Logger::clearLogs() {
    if (logs_.empty()) return;
    logs_.clear();
}
