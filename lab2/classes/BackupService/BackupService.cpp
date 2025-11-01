#include "BackupService.h"

BackupService::BackupService(const string& lastBackupDate, const string& backupPath, bool isScheduled, BackupType type) :
    lastBackupDate_(lastBackupDate),
    backupPath_(backupPath),
    isScheduled_(isScheduled),
    type_(type) {
}

void BackupService::setLastBackupDate(const string& lastBackupDate) {
    lastBackupDate_ = lastBackupDate;
}
void BackupService::setBackupPath(const string& backupPath) {
    backupPath_ = backupPath;
}
void BackupService::setIsScheduled(bool isScheduled) {
    isScheduled_ = isScheduled;
}
void BackupService::setType(BackupType type) {
    type_ = type;
}

const string& BackupService::getLastBackupDate() const {
    return lastBackupDate_;
}
const string& BackupService::getBackupPath() const {
    return backupPath_;
}
bool BackupService::getIsScheduled() const {
    return isScheduled_;
}
BackupType BackupService::getType() const {
    return type_;
}

void BackupService::performBackup() {
    if (backupPath_.empty()) return;

    switch (type_) {
    case BackupType::FULL: cout << "полное"; break;
    case BackupType::INCREMENTAL: cout << "инкрементальное"; break;
    case BackupType::DIFFERENTIATED: cout << "дифференцированное"; break;
    default: cout << "неизвестное"; break;
    }

    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);

    tm timeInfo;
    localtime_s(&timeInfo, &time);

    stringstream ss;
    ss << put_time(&timeInfo, "%d.%m.%Y %H:%M:%S");
    lastBackupDate_ = ss.str();
}

void BackupService::restoreBackup(const string& backupPath) {
    if (backupPath.empty()) return;

    cout << "Восстановление из резервной копии: " << backupPath << endl;
}
