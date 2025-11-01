#include "CateringOrder.h"

CateringOrder::CateringOrder(const Passenger& passenger, const vector<string>& items,
    double totalCost, bool isDelivered, time_t orderTime) : 
    passenger_(passenger),
    items_(items),
    totalCost_(totalCost),
    isDelivered_(isDelivered),
    orderTime_(orderTime) {
}

void CateringOrder::setPassenger(const Passenger& passenger) { 
    passenger_ = passenger; 
}
void CateringOrder::setItems(const vector<string>& items) { 
    items_ = items; 
}
void CateringOrder::setTotalCost(double totalCost) { 
    totalCost_ = totalCost; 
}
void CateringOrder::setDelivered(bool delivered) { 
    isDelivered_ = delivered; 
}
void CateringOrder::setOrderTime(time_t orderTime) {
    orderTime_ = orderTime; 
}

const Passenger& CateringOrder::getPassenger() const { 
    return passenger_; 
}
const vector<string>& CateringOrder::getItems() const { 
    return items_; 
}
double CateringOrder::getTotalCost() const { 
    return totalCost_; 
}
bool CateringOrder::getIsDelivered() const { 
    return isDelivered_; 
}
time_t CateringOrder::getOrderTime() const { 
    return orderTime_; 
}

void CateringOrder::addItem(const string& item) {
    items_.push_back(item);
}

void CateringOrder::calculateTotalPrice(double pricePerItem) {
    if (pricePerItem < 0) throw InvalidBalanceException("Цена не может быть отрицательной");
    totalCost_ += static_cast<double>(items_.size()) * pricePerItem;
}


