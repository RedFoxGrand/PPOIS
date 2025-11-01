#include "gtest/gtest.h"
#include "LostAndFound.h"

class LostAndFoundTest : public ::testing::Test {
protected:
    ContactInfo* contact; Visa* visa; Passport* passport; Passenger* passenger1;
    Passenger* passenger2;  BaggageTag* tag1;  BaggageTag* tag2; Baggage* baggage1;
    Baggage* baggage2; LostAndFound* lostAndFound; time_t now;

    void SetUp() override {
        now = time(nullptr);

        contact = new ContactInfo("ivanov@example.com", "+79991234567", "Россия, Москва");
        visa = new Visa("V001", "Италия", now - 500000, now + 500000, VisaType::Tourist);
        passport = new Passport("PP123456", "Россия", "Иван Иванов", now - 1000000, now + 2000000, *visa, MaritalStatus::Married);
        passenger1 = new Passenger("Иван", "Иванов", now - 1000000000, *contact, "P001", *passport);

        ContactInfo contact2("petrov@example.com", "+79995553322", "Россия, Санкт-Петербург");
        Visa visa2("V002", "Германия", now - 400000, now + 700000, VisaType::Business);
        Passport passport2("PP654321", "Россия", "Пётр Петров", now - 1200000, now + 1800000, visa2, MaritalStatus::NotMarried);
        passenger2 = new Passenger("Пётр", "Петров", now - 900000000, contact2, "P002", passport2);

        tag1 = new BaggageTag("T001", "B001", "SU123", "Москва");
        tag2 = new BaggageTag("T002", "B002", "SU321", "Санкт-Петербург");

        vector<string> items1 = { "Куртка", "Обувь" };
        vector<string> items2 = { "Ноутбук", "Книга" };

        baggage1 = new Baggage("B001", 15.5, *passenger1, *tag1, BaggageStatus::Lost, items1);
        baggage2 = new Baggage("B002", 20.0, *passenger2, *tag2, BaggageStatus::CheckedIn, items2);

        vector<Baggage> lostItems = { *baggage1 };
        vector<Baggage> foundItems = {};

        lostAndFound = new LostAndFound("R001", "Москва — Шереметьево", LostAndFoundStatus::Reported, lostItems, foundItems);
    }

    void TearDown() override {
        delete contact; delete visa; delete passport;  delete passenger1; delete passenger2; 
        delete tag1; delete tag2; delete baggage1; delete baggage2; delete lostAndFound;
    }
};

TEST_F(LostAndFoundTest, ConstructorInitializesFieldsCorrectly) {
    EXPECT_EQ(lostAndFound->getReportID(), "R001");
    EXPECT_EQ(lostAndFound->getLocationFound(), "Москва — Шереметьево");
    EXPECT_EQ(lostAndFound->getStatus(), LostAndFoundStatus::Reported);
    EXPECT_EQ(lostAndFound->getLostItems().size(), 1);
    EXPECT_EQ(lostAndFound->getLostItems()[0].getBaggageId(), "B001");
}

TEST_F(LostAndFoundTest, SettersWorkCorrectly) {
    vector<Baggage> newLost = { *baggage2 };
    vector<Baggage> newFound = { *baggage1 };

    lostAndFound->setReportID("R777");
    lostAndFound->setLocationFound("Сочи — Адлер");
    lostAndFound->setStatus(LostAndFoundStatus::Located);
    lostAndFound->setlostItems(newLost);
    lostAndFound->setFoundItems(newFound);

    EXPECT_EQ(lostAndFound->getReportID(), "R777");
    EXPECT_EQ(lostAndFound->getLocationFound(), "Сочи — Адлер");
    EXPECT_EQ(lostAndFound->getStatus(), LostAndFoundStatus::Located);
    EXPECT_EQ(lostAndFound->getLostItems().size(), 1);
    EXPECT_EQ(lostAndFound->getFoundItems().size(), 1);
    EXPECT_EQ(lostAndFound->getFoundItems()[0].getBaggageId(), "B001");
}

TEST_F(LostAndFoundTest, ReportLostAddsItemAndChangesStatus) {
    size_t oldSize = lostAndFound->getLostItems().size();
    lostAndFound->reportLost(*baggage2);

    EXPECT_EQ(lostAndFound->getLostItems().size(), oldSize + 1);
    EXPECT_EQ(lostAndFound->getStatus(), LostAndFoundStatus::Reported);
    EXPECT_EQ(lostAndFound->getLostItems().back().getBaggageId(), "B002");
}

TEST_F(LostAndFoundTest, ReportFoundAddsItemAndChangesStatus) {
    size_t oldSize = lostAndFound->getFoundItems().size();
    lostAndFound->reportFound(*baggage1);

    EXPECT_EQ(lostAndFound->getFoundItems().size(), oldSize + 1);
    EXPECT_EQ(lostAndFound->getStatus(), LostAndFoundStatus::Located);
    EXPECT_EQ(lostAndFound->getFoundItems().back().getBaggageId(), "B001");
}

TEST_F(LostAndFoundTest, ClaimItemRemovesBaggageAndSetsStatusClaimed) {
    lostAndFound->reportFound(*baggage1);
    EXPECT_EQ(lostAndFound->getFoundItems().size(), 1);

    lostAndFound->claimItem(*passenger1);

    EXPECT_EQ(lostAndFound->getStatus(), LostAndFoundStatus::Claimed);
    EXPECT_TRUE(lostAndFound->getFoundItems().empty());
}

TEST_F(LostAndFoundTest, ClaimItemDoesNothingIfBaggageNotFound) {
    size_t oldSize = lostAndFound->getFoundItems().size();
    lostAndFound->claimItem(*passenger2);

    EXPECT_EQ(lostAndFound->getFoundItems().size(), oldSize);
    EXPECT_NE(lostAndFound->getStatus(), LostAndFoundStatus::Claimed);
}
