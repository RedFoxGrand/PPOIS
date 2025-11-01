#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <exception>

using namespace std;

enum class BackupType { FULL, INCREMENTAL, DIFFERENTIATED };

class BackupService {
public:
    BackupService(const string& lastBackupDate, const string& backupPath, bool isScheduled, BackupType type);

    void setLastBackupDate(const string& lastBackupDate);
    void setBackupPath(const string& backupPath);
    void setIsScheduled(bool isScheduled);
    void setType(BackupType type);

    const string& getLastBackupDate() const;
    const string& getBackupPath() const;
    bool getIsScheduled() const;
    BackupType getType() const;

    void performBackup();
    void restoreBackup(const string& backupPath);

private:
    string lastBackupDate_;
    string backupPath_;
    bool isScheduled_;
    BackupType type_;
};
