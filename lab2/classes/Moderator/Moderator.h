#pragma once
#include "Report.h"
#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

class Moderator {
public:
    Moderator(const string& areaOfResponsibility, const vector<Report>& assignedReports, const User& user);

    void setAreaOfResponsibility(const string& area);
    void setAssignedReports(const vector<Report>& reports);
    void setUser(const User& user);

    const string& getAreaOfResponsibility() const;
    const vector<Report>& getAssignedReports() const;
    const User& getUser() const;

    void resolveReport(int reportId);
    void escalateReport(int reportId);

private:
    string areaOfResponsibility_;
    vector<Report> assignedReports_;
    User user_;
};
