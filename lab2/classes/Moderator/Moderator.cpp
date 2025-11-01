#include "Moderator.h"

Moderator::Moderator(const string& areaOfResponsibility, const vector<Report>& assignedReports, const User& user) :
    areaOfResponsibility_(areaOfResponsibility),
    assignedReports_(assignedReports),
    user_(user) {
}

void Moderator::setAreaOfResponsibility(const string& area) {
    areaOfResponsibility_ = area;
}

void Moderator::setAssignedReports(const vector<Report>& reports) {
    assignedReports_ = reports;
}

void Moderator::setUser(const User& user) {
    user_ = user;
}

const string& Moderator::getAreaOfResponsibility() const {
    return areaOfResponsibility_;
}

const vector<Report>& Moderator::getAssignedReports() const {
    return assignedReports_;
}

const User& Moderator::getUser() const {
    return user_;
}

void Moderator::resolveReport(int reportId) {
    for (Report& report : assignedReports_) {
        if (report.getId() == reportId) {
            report.setResolved(true);
            return;
        }
    }
}

void Moderator::escalateReport(int reportId) {
    for (Report& report : assignedReports_) {
        if (report.getId() == reportId) {
            report.setEscalated(true);
            return;
        }
    }
}
