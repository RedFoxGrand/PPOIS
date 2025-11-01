#include <gtest/gtest.h>
#include "CheckIn.h"

class CheckInTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport; Passenger* passenger; AircraftModel* model;
    Aircraft* aircraft; Schedule* schedule; Flight* flight; CheckIn* checkIn;
    time_t birthDate, issueDate, expiryDate, departure, arrival;

    void SetUp() override {
        birthDate = time(nullptr) - 86400 * 365 * 25;
        issueDate = time(nullptr) - 86400 * 200;
        expiryDate = time(nullptr) + 86400 * 365;
        departure = time(nullptr) + 3600;
        arrival = departure + 7200;

        contact = new ContactInfo("test@mail.com", "+79991112233", "Москва");
        visa = new Visa("VISA001", "Германия", issueDate, expiryDate, VisaType::Tourist);
        passport = new Passport("PP123456", "Россия", "Сергей Иванов", issueDate, expiryDate, *visa, MaritalStatus::NotMarried);
        passenger = new Passenger("Сергей", "Иванов", birthDate, *contact, "PAX001", *passport);

        model = new AircraftModel("Boeing 737", 180, "Boeing", 5000, 2500, "Turbofan", 850);
        aircraft = new Aircraft("RA-12345", *model, 5000, AircraftStatus::Available, true);
        schedule = new Schedule({}, departure, arrival, departure - 3600, departure - 7200, true);

        vector<string> passengers = { "PAX001" };
        flight = new Flight("SU100", "Москва", "Берлин", *aircraft, *schedule, 1800, passengers);

        checkIn = new CheckIn("CHK001", *passenger, *flight, CheckInStatus::NotStarted);
    }

    void TearDown() override {
        delete checkIn; delete flight; delete schedule; delete aircraft;
        delete model; delete passenger; delete passport; delete visa; delete contact;
    }
};

TEST_F(CheckInTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(checkIn->getCheckInId(), "CHK001");
    EXPECT_EQ(checkIn->getPassenger().getPassengerId(), "PAX001");
    EXPECT_EQ(checkIn->getFlight().getFlightNumber(), "SU100");
    EXPECT_EQ(checkIn->getStatus(), CheckInStatus::NotStarted);
}

TEST_F(CheckInTest, SettersWorkCorrectly) {
    Passenger newPassenger("Иван", "Петров", birthDate, *contact, "PAX999", *passport);
    AircraftModel newModel("Airbus A320", 160, "Airbus", 4500, 2000, "Jet", 800);
    Aircraft newAircraft("RA-77777", newModel, 3000, AircraftStatus::Available, true);
    Schedule newSchedule({}, departure + 7200, arrival + 10800, departure, departure - 3600, true);
    Flight newFlight("SU200", "Санкт-Петербург", "Париж", newAircraft, newSchedule, 2200, { "PAX999" });

    checkIn->setCheckInId("CHK999");
    checkIn->setPassenger(newPassenger);
    checkIn->setFlight(newFlight);
    checkIn->setStatus(CheckInStatus::InProgress);

    EXPECT_EQ(checkIn->getCheckInId(), "CHK999");
    EXPECT_EQ(checkIn->getPassenger().getPassengerId(), "PAX999");
    EXPECT_EQ(checkIn->getFlight().getFlightNumber(), "SU200");
    EXPECT_EQ(checkIn->getStatus(), CheckInStatus::InProgress);
}

TEST_F(CheckInTest, PerformCompletesWhenAircraftAvailable) {
    checkIn->perform();
    EXPECT_EQ(checkIn->getStatus(), CheckInStatus::Completed);
}
TEST_F(CheckInTest, PerformFailsWhenAircraftUnavailable) {
    aircraft->setIsAvailable(false);

    Flight failedFlight("SU100", "Москва", "Берлин", *aircraft, *schedule, 1800, { "PAX001" });
    checkIn->setFlight(failedFlight);

    checkIn->perform();

    EXPECT_EQ(checkIn->getStatus(), CheckInStatus::Failed);
}

TEST_F(CheckInTest, IssueBoardingPassSetsClosedStatusWhenCompleted) {
    checkIn->setStatus(CheckInStatus::Completed);
    checkIn->issueBoardingPass();
    EXPECT_EQ(checkIn->getStatus(), CheckInStatus::Closed);
}

TEST_F(CheckInTest, IssueBoardingPassThrowsIfNotCompleted) {
    checkIn->setStatus(CheckInStatus::Failed);
    EXPECT_THROW(checkIn->issueBoardingPass(), InvalidStatusException);
}
