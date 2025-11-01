#include <gtest/gtest.h>
#include "FlightAttendant.h"

using namespace std;

class FlightAttendantTest : public ::testing::Test {
protected:
    ContactInfo* contact;
    FlightAttendant* attendant;
    time_t birthDate;

    void SetUp() override {
        birthDate = time(nullptr) - 30 * 365 * 24 * 60 * 60;
        contact = new ContactInfo("anna@mail.com", "+79998887766", "Москва, Россия");

        attendant = new FlightAttendant(
            "Анна", "Петрова", birthDate, *contact,
            120000.0, true, 7, { "Английский", "Французский" }
        );
    }

    void TearDown() override {
        delete attendant;
        delete contact;
    }
};

TEST_F(FlightAttendantTest, ConstructorInitializesAllFields) {
    EXPECT_EQ(attendant->getName(), "Анна");
    EXPECT_EQ(attendant->getSurname(), "Петрова");
    EXPECT_DOUBLE_EQ(attendant->getSalary(), 120000.0);
    EXPECT_TRUE(attendant->getIsAvailable());
    EXPECT_EQ(attendant->getServiceYears(), 7);

    const auto& langs = attendant->getLanguages();
    ASSERT_EQ(langs.size(), 2);
    EXPECT_EQ(langs[0], "Английский");
    EXPECT_EQ(langs[1], "Французский");

    EXPECT_EQ(attendant->getContactInfo().getEmail(), "anna@mail.com");
    EXPECT_EQ(attendant->getContactInfo().getPhone(), "+79998887766");
    EXPECT_EQ(attendant->getContactInfo().getAddress(), "Москва, Россия");
}

TEST_F(FlightAttendantTest, SetServiceYearsChangesValue) {
    attendant->setServiceYears(10);
    EXPECT_EQ(attendant->getServiceYears(), 10);
}

TEST_F(FlightAttendantTest, SetLanguagesReplacesAll) {
    vector<string> newLangs = { "Испанский", "Итальянский" };
    attendant->setLanguages(newLangs);

    const auto& langs = attendant->getLanguages();
    ASSERT_EQ(langs.size(), 2);
    EXPECT_EQ(langs[0], "Испанский");
    EXPECT_EQ(langs[1], "Итальянский");
}

TEST_F(FlightAttendantTest, AddLanguageAddsNewOne) {
    size_t before = attendant->getLanguages().size();
    attendant->addLanguage("Немецкий");

    const auto& langs = attendant->getLanguages();
    EXPECT_EQ(langs.size(), before + 1);
    EXPECT_EQ(langs.back(), "Немецкий");
}

TEST_F(FlightAttendantTest, InheritedMethodsWorkCorrectly) {
    attendant->setSalary(150000.0);
    attendant->setIsAvailable(false);

    EXPECT_DOUBLE_EQ(attendant->getSalary(), 150000.0);
    EXPECT_FALSE(attendant->getIsAvailable());

    attendant->markUnavailable();
    EXPECT_FALSE(attendant->getIsAvailable());
}

TEST_F(FlightAttendantTest, PersonMethodsWorkCorrectly) {
    attendant->setName("Ольга");
    attendant->setSurname("Иванова");

    EXPECT_EQ(attendant->getFullName(), "Ольга Иванова");
    EXPECT_GT(attendant->getAge(), 20);
}
