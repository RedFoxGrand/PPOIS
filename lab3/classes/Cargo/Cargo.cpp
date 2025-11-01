#include "Cargo.h"

Cargo::Cargo(double weight, const string& description, const Passenger& owner) : 
    weight_(weight), 
    description_(description), 
    owner_(owner) {
}

void Cargo::setWeight(double weight) { 
    weight_ = weight; 
}
void Cargo::setDescription(const string& description) { 
    description_ = description; 
}
void Cargo::setOwner(const Passenger& owner) { 
    owner_ = owner; 
}

double Cargo::getWeight() const { 
    return weight_; 
}
const string& Cargo::getDescription() const { 
    return description_; 
}
const Passenger& Cargo::getOwner() const {
    return owner_; 
}
