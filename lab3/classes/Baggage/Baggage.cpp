#include "Baggage.h"

Baggage::Baggage(const string& baggageId, double weight, const Passenger& owner, 
    const BaggageTag& tag, BaggageStatus status, const vector<string>& items) : 
    baggageId_(baggageId),
    weight_(weight),
    owner_(owner),
    tag_(tag),
    status_(status), items_(items){
}

void Baggage::setBaggageId(const string& baggageId) { 
    baggageId_ = baggageId; 
}
void Baggage::setWeight(double weight) { 
    weight_ = weight; 
}
void Baggage::setOwner(const Passenger& owner) { 
    owner_ = owner; 
}
void Baggage::setTag(const BaggageTag& tag) { 
    tag_ = tag; 
}
void Baggage::setStatus(BaggageStatus status) { 
    status_ = status; 
}
void Baggage::setItems(const vector<string>& items) { 
    items_ = items; 
}

const string& Baggage::getBaggageId() const { 
    return baggageId_; 
}
double Baggage::getWeight() const { 
    return weight_; 
}
const Passenger& Baggage::getOwner() const { 
    return owner_; 
}
const BaggageTag& Baggage::getTag() const {
    return tag_; 
}
BaggageStatus Baggage::getStatus() const { 
    return status_; 
}
const vector<string>& Baggage::getItems() const { 
    return items_; 
}

void Baggage::assignTag(const BaggageTag& tag) {
    tag_ = tag;
    status_ = BaggageStatus::CheckedIn;
}

void Baggage::addItem(const string& item) {
    items_.push_back(item);
}

void Baggage::postItem(const string& item) {
    auto it = find(items_.begin(), items_.end(), item);
    if (it != items_.end()) items_.erase(it);
}

void Baggage::markLost() {
    status_ = BaggageStatus::Lost;
}
