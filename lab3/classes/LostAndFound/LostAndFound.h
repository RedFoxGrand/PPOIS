#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Baggage.h"
#include "Passenger.h"

using namespace std;

enum class LostAndFoundStatus { Reported, Located, Claimed, Unclaimed, Disposed };

class LostAndFound {
public:
    LostAndFound(const string& reportID, const string& locationFound, LostAndFoundStatus status, 
        const vector<Baggage>& lostItems, const vector<Baggage>& foundItems);

    void setReportID(const string& reportID);
    void setLocationFound(const string& locationFound);
    void setStatus(LostAndFoundStatus status);
    void setlostItems(const vector<Baggage>& lostItems);
    void setFoundItems(const vector<Baggage>& foundItems);

    const string& getReportID() const;
    const string& getLocationFound() const;
    LostAndFoundStatus getStatus() const;
    const vector<Baggage>& getLostItems() const;
    const vector<Baggage>& getFoundItems() const;

    void reportLost(const Baggage& baggage);
    void reportFound(const Baggage& baggage);
    void claimItem(const Passenger& passenger);

private:
    string reportID_;
    string locationFound_;
    LostAndFoundStatus status_;
    vector<Baggage> lostItems_;
    vector<Baggage> foundItems_;
};
