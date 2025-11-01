#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Passenger.h"
#include "BaggageTag.h"

using namespace std;

enum class BaggageStatus { NotCheckedIn, CheckedIn, Loaded, InTransit, Delivered, Lost, Damaged };

class Baggage {
public:
    Baggage(const string& baggageId, double weight, const Passenger& owner,  
        const BaggageTag& tag, BaggageStatus status, const vector<string>& items);

    void setBaggageId(const string& baggageId);
    void setWeight(double weight);
    void setOwner(const Passenger& owner);
    void setTag(const BaggageTag& tag);
    void setStatus(BaggageStatus status);
    void setItems(const vector<string>& items);

    const string& getBaggageId() const;
    double getWeight() const;
    const Passenger& getOwner() const;
    const BaggageTag& getTag() const;
    BaggageStatus getStatus() const;
    const vector<string>& getItems() const;

    void assignTag(const BaggageTag& tag);
    void addItem(const string& item);
    void postItem(const string& item);
    void markLost();

private:
    string baggageId_;
    double weight_;
    Passenger owner_;
    BaggageTag tag_;
    BaggageStatus status_;
    vector<string> items_;
};
