#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <exception>

using namespace std;

class CacheService {
public:
    CacheService(int cacheSize, int ttlSeconds, const map<string, string>& entries);

    void setCacheSize(int cacheSize);
    void setTtlSeconds(int ttlSeconds);
    void setEntries(const map<string, string>& entries);

    int getCacheSize() const;
    int getTtlSeconds() const;
    const map<string, string>& getEntries() const;

    void put(const string& key, const string& value);
    string get(const string& key) const;

private:
    int cacheSize_;
    int ttlSeconds_;
    map<string, string> entries_;
};
