#include <gtest/gtest.h>
#include "BaggageTag.h"

class BaggageTagTest : public ::testing::Test {
protected:
    BaggageTag* tag;

    void SetUp() override {
        tag = new BaggageTag("TAG123", "BG567", "SU100", "Paris");
    }

    void TearDown() override {
        delete tag;
    }
};

TEST_F(BaggageTagTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(tag->getTagCode(), "TAG123");
    EXPECT_EQ(tag->getBaggageId(), "BG567");
    EXPECT_EQ(tag->getFlightNumber(), "SU100");
    EXPECT_EQ(tag->getDestination(), "Paris");
}

TEST_F(BaggageTagTest, SettersAndGettersWorkCorrectly) {
    tag->setTagCode("TAG999");
    tag->setBaggageId("BG888");
    tag->setFlightNumber("SU200");
    tag->setDestination("Berlin");

    EXPECT_EQ(tag->getTagCode(), "TAG999");
    EXPECT_EQ(tag->getBaggageId(), "BG888");
    EXPECT_EQ(tag->getFlightNumber(), "SU200");
    EXPECT_EQ(tag->getDestination(), "Berlin");
}

TEST_F(BaggageTagTest, PrintTagOutputsCorrectly) {
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    tag->printTag();

    std::cout.rdbuf(oldCout);

    std::string result = output.str();

    EXPECT_NE(result.find("¡¿√¿∆Õ¿ﬂ Ã≈“ ¿"), std::string::npos);
    EXPECT_NE(result.find("TAG123"), std::string::npos);
    EXPECT_NE(result.find("BG567"), std::string::npos);
    EXPECT_NE(result.find("SU100"), std::string::npos);
    EXPECT_NE(result.find("Paris"), std::string::npos);
}
