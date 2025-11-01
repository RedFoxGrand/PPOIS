#include "AirlineCompany.h"
#include <iomanip>
#include <ctime>

AirlineCompany::AirlineCompany(const string& name, const string& iataCode,
    const vector<Airport>& airports, const vector<Aircraft>& planes,
    const vector<Employee>& employees, const FlightManager& flightManager,
    const BookingManager& bookingManager, const PassengerManager& passengerManager) : name_(name),
    iataCode_(iataCode),
    airports_(airports),
    planes_(planes),
    employees_(employees),
    flightManager_(flightManager),
    bookingManager_(bookingManager),
    passengerManager_(passengerManager) {
}

void AirlineCompany::setName(const string& name) { 
    name_ = name; 
}
void AirlineCompany::setIataCode(const string& code) { 
    iataCode_ = code; 
}
void AirlineCompany::setAirports(const vector<Airport>& airports) { 
    airports_ = airports; 
}
void AirlineCompany::setPlanes(const vector<Aircraft>& planes) { 
    planes_ = planes; 
}
void AirlineCompany::setEmployees(const vector<Employee>& employees) { 
    employees_ = employees; 
}
void AirlineCompany::setFlightManager(const FlightManager& fm) { 
    flightManager_ = fm; 
}
void AirlineCompany::setBookingManager(const BookingManager& bm) { 
    bookingManager_ = bm; 
}
void AirlineCompany::setPassengerManager(const PassengerManager& pm) { 
    passengerManager_ = pm; 
}

const string& AirlineCompany::getName() const { 
    return name_; 
}
const string& AirlineCompany::getIataCode() const { 
    return iataCode_; 
}
const vector<Airport>& AirlineCompany::getAirports() const { 
    return airports_; 
}
const vector<Aircraft>& AirlineCompany::getPlanes() const { 
    return planes_; 
}
const vector<Employee>& AirlineCompany::getEmployees() const { 
    return employees_; 
}
const FlightManager& AirlineCompany::getFlightManager() const { 
    return flightManager_; 
}
const BookingManager& AirlineCompany::getBookingManager() const { 
    return bookingManager_; 
}
const PassengerManager& AirlineCompany::getPassengerManager() const { 
    return passengerManager_; 
}

void AirlineCompany::addAirport(const Airport& airport) {
    airports_.push_back(airport);
}

void AirlineCompany::hireEmployee(const Employee& employee) {
    employees_.push_back(employee);
}

void AirlineCompany::generateAnnualReport() const {
    cout << "Годовой отчет — " << name_ << " (" << iataCode_ << ")\n";
    cout << "Всего аэропортов: " << airports_.size() << endl;
    cout << "Всего самолетов: " << planes_.size() << endl;
    cout << "Всего сотрудников: " << employees_.size() << endl;
    cout << "Управляемые рейсы: " << flightManager_.getFlights().size() << endl;
    cout << "Бронирований: " << bookingManager_.getBookings().size() << endl;
    cout << "Зарегистрированных пассажиров: " << passengerManager_.getPassengers().size() << endl;
    time_t now = time(nullptr);
    cout << "Сгенерировано в: " << put_time(localtime(&now), "%Y-%m-%d %H:%M:%S") << endl;
}