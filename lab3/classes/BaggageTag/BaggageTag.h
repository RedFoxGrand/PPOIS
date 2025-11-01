#pragma once
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class BaggageTag {
public:
    BaggageTag(const string& tagCode, const string& baggageId,
        const string& flightNumber, const string& destination);

    void setTagCode(const string& tagCode);
    void setBaggageId(const string& baggageId);
    void setFlightNumber(const string& flightNumber);
    void setDestination(const string& destination);

    const string& getTagCode() const;
    const string& getBaggageId() const;
    const string& getFlightNumber() const;
    const string& getDestination() const;

    void printTag() const;

private:
    string tagCode_;
    string baggageId_;
    string flightNumber_;
    string destination_;
};
