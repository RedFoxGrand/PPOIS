#include "MaintenanceLog.h"

MaintenanceLog::MaintenanceLog(const string& recordId, const Aircraft& aircraft,
    const string& description, time_t date) : 
    recordId_(recordId),
    aircraft_(aircraft),
    description_(description),
    date_(date) {
}

void MaintenanceLog::setRecordId(const string& recordId) { 
    recordId_ = recordId;
}
void MaintenanceLog::setAircraft(const Aircraft& aircraft) { 
    aircraft_ = aircraft; 
}
void MaintenanceLog::setDescription(const string& description) { 
    description_ = description; 
}
void MaintenanceLog::setDate(time_t date) {
    date_ = date; 
}

const string& MaintenanceLog::getRecordId() const {
    return recordId_; 
}
const Aircraft& MaintenanceLog::getAircraft() const { 
    return aircraft_; 
}
const string& MaintenanceLog::getDescription() const {
    return description_;
}
time_t MaintenanceLog::getDate() const {
    return date_;
}

void MaintenanceLog::addEntry(const string& text) {
    description_ += text;
}

void MaintenanceLog::printLog() const {
    cout << "\nЗапись журнала технического обслуживания\n";
    cout << "Номер записи: " << recordId_ << endl;
    cout << "Бортовой номер самолёта: " << aircraft_.getTailNumber() << endl;
    cout << "Описание:\n" << description_ << endl;

    tm* tm_info = localtime(&date_);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    cout << "Дата: " << buffer << endl;
}

