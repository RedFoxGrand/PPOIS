#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Logger {
public:
    Logger(const string& logLevel, const vector<string>& logs);

    void setLogLevel(const string& logLevel);
    void setLogs(const vector<string>& logs);

    const string& getLogLevel() const;
    const vector<string>& getLogs() const;

    void log(const string& message);
    void setLevel(const string& level);
    void clearLogs();

private:
    string logLevel_;
    vector<string> logs_;
};
