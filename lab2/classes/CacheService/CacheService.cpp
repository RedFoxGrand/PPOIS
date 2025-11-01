#include "CacheService.h"

CacheService::CacheService(int cacheSize, int ttlSeconds, const map<string, string>& entries) :
    cacheSize_(cacheSize),
    ttlSeconds_(ttlSeconds),
    entries_(entries) {}

void CacheService::setCacheSize(int cacheSize) {
    cacheSize_ = cacheSize;
}
void CacheService::setTtlSeconds(int ttlSeconds) {
    ttlSeconds_ = ttlSeconds;
}
void CacheService::setEntries(const map<string, string>& entries) {
    entries_ = entries;
}

int CacheService::getCacheSize() const {
    return cacheSize_;
}
int CacheService::getTtlSeconds() const {
    return ttlSeconds_;
}
const map<string, string>& CacheService::getEntries() const {
    return entries_;
}

void CacheService::put(const string& key, const string& value) {
    if (key.empty()) return;
    if (entries_.size() >= static_cast<size_t>(cacheSize_)) entries_.erase(entries_.begin());

    entries_[key] = value;
}

string CacheService::get(const string& key) const {
    if (key.empty()) return "";

    auto it = entries_.find(key);
    if (it != entries_.end()) return it->second;

    return "";
}
