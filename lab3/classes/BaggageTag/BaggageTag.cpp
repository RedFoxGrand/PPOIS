#include "BaggageTag.h"

BaggageTag::BaggageTag(const string& tagCode, const string& baggageId,
    const string& flightNumber, const string& destination) : 
    tagCode_(tagCode),
    baggageId_(baggageId),
    flightNumber_(flightNumber),
    destination_(destination) {
}

void BaggageTag::setTagCode(const string& tagCode) { 
    tagCode_ = tagCode; 
}
void BaggageTag::setBaggageId(const string& baggageId) { 
    baggageId_ = baggageId; 
}
void BaggageTag::setFlightNumber(const string& flightNumber) { 
    flightNumber_ = flightNumber; 
}
void BaggageTag::setDestination(const string& destination) { 
    destination_ = destination; 
}

const string& BaggageTag::getTagCode() const { 
    return tagCode_; 
}
const string& BaggageTag::getBaggageId() const { 
    return baggageId_; 
}
const string& BaggageTag::getFlightNumber() const { 
    return flightNumber_; 
}
const string& BaggageTag::getDestination() const { 
    return destination_; 
}

void BaggageTag::printTag() const {
    cout << "===== БАГАЖНАЯ МЕТКА =====" << endl;
    cout << "Код метки:        " << tagCode_ << endl;
    cout << "ID багажа:        " << baggageId_ << endl;
    cout << "Номер рейса:      " << flightNumber_ << endl;
    cout << "Пункт назначения: " << destination_ << endl;
    cout << "===========================" << endl;
}

