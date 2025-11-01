#include <gtest/gtest.h>
#include "WeatherCondition.h"

using namespace std;

class WeatherConditionTest : public ::testing::Test {
protected:
    WeatherCondition* weather;

    void SetUp() override {
        weather = new WeatherCondition("Москва", "Ясно", "Низкий", 20.5, 15.0);
    }

    void TearDown() override {
        delete weather;
    }
};

TEST_F(WeatherConditionTest, ConstructorInitializesValuesCorrectly) {
    EXPECT_EQ(weather->getLocation(), "Москва");
    EXPECT_EQ(weather->getCondition(), "Ясно");
    EXPECT_EQ(weather->getAlertLevel(), "Низкий");
    EXPECT_DOUBLE_EQ(weather->getTemperature(), 20.5);
    EXPECT_DOUBLE_EQ(weather->getWindSpeed(), 15.0);
}

TEST_F(WeatherConditionTest, SettersWorkCorrectly) {
    weather->setLocation("Санкт-Петербург");
    weather->setCondition("Дождь");
    weather->setAlertLevel("Средний");
    weather->setTemperature(10.0);
    weather->setWindSpeed(25.0);

    EXPECT_EQ(weather->getLocation(), "Санкт-Петербург");
    EXPECT_EQ(weather->getCondition(), "Дождь");
    EXPECT_EQ(weather->getAlertLevel(), "Средний");
    EXPECT_DOUBLE_EQ(weather->getTemperature(), 10.0);
    EXPECT_DOUBLE_EQ(weather->getWindSpeed(), 25.0);
}

TEST_F(WeatherConditionTest, IsSafeForFlightReturnsTrueForNormalConditions) {
    weather->setCondition("Ясно");
    weather->setAlertLevel("Низкий");
    weather->setWindSpeed(30.0);
    EXPECT_TRUE(weather->isSafeForFlight());
}
TEST_F(WeatherConditionTest, UpdateChangesConditionCorrectly) {
    weather->update("Облачно");
    EXPECT_EQ(weather->getCondition(), "Облачно");
}