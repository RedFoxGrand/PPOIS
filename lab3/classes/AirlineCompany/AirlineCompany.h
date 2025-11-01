#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Airport.h"
#include "Aircraft.h"
#include "Employee.h"
#include "FlightManager.h"
#include "BookingManager.h"
#include "PassengerManager.h"

using namespace std;

class AirlineCompany {
public:
    AirlineCompany(const string& name, const string& iataCode, const vector<Airport>& airports, 
        const vector<Aircraft>& planes, const vector<Employee>& employees, const FlightManager& flightManager, 
        const BookingManager& bookingManager, const PassengerManager& passengerManager);

    void setName(const string& name);
    void setIataCode(const string& code);
    void setAirports(const vector<Airport>& airports);
    void setPlanes(const vector<Aircraft>& planes);
    void setEmployees(const vector<Employee>& employees);
    void setFlightManager(const FlightManager& fm);
    void setBookingManager(const BookingManager& bm);
    void setPassengerManager(const PassengerManager& pm);

    const string& getName() const;
    const string& getIataCode() const;
    const vector<Airport>& getAirports() const;
    const vector<Aircraft>& getPlanes() const;
    const vector<Employee>& getEmployees() const;
    const FlightManager& getFlightManager() const;
    const BookingManager& getBookingManager() const;
    const PassengerManager& getPassengerManager() const;

    void addAirport(const Airport& airport);
    void hireEmployee(const Employee& employee);
    void generateAnnualReport() const;

private:
    string name_;
    string iataCode_;
    vector<Airport> airports_;
    vector<Aircraft> planes_;
    vector<Employee> employees_;
    FlightManager flightManager_;
    BookingManager bookingManager_;
    PassengerManager passengerManager_;
};
