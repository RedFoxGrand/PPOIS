#include <gtest/gtest.h>
#include "RecommendationEngine.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Permission.h"
#include "Currency.h"
using namespace std;

class RecommendationEngineTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet; FriendList* friends; BlockList* blocks; vector<Permission>* permissions; User* user; RecommendationEngine* engine;

    void SetUp() override {
        profile = new UserProfile("Иван", "Иванов", "01.01.2000", "01.01.2020", "+79990001122", "Россия", "Москва", { "Программирование","Музыка" });
        settings = new Settings(18, "Русский", true, true, false, true, Theme::LIGHT);
        currency = new Currency("RUB", "Российский рубль", 1.0);
        wallet = new Wallet(5000.0, {}, {}, *currency);
        friends = new FriendList({}, {}, {});
        blocks = new BlockList({}, {});
        permissions = new vector<Permission>{ Permission("READ","Чтение данных",true),Permission("WRITE","Изменение данных",true) };
        user = new User(1, "ivan", "ivan@example.com", "pass123", true, *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);
        engine = new RecommendationEngine("Collaborative", "2025-01-01 10:00:00", {});
    }

    void TearDown() override {
        delete engine; delete user; delete permissions; delete blocks; delete friends; delete wallet; delete settings; delete currency; delete profile;
    }
};

TEST_F(RecommendationEngineTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(engine->getAlgorithm(), "Collaborative"); EXPECT_EQ(engine->getLastRun(), "2025-01-01 10:00:00"); EXPECT_TRUE(engine->getSuggestions().empty());
}

TEST_F(RecommendationEngineTest, SettersWorkCorrectly) {
    vector<User> users = { *user }; engine->setAlgorithm("ContentBased"); engine->setLastRun("2025-02-02 12:00:00"); engine->setSuggestions(users);
    EXPECT_EQ(engine->getAlgorithm(), "ContentBased"); EXPECT_EQ(engine->getLastRun(), "2025-02-02 12:00:00"); EXPECT_EQ(engine->getSuggestions().size(), 1); EXPECT_EQ(engine->getSuggestions()[0].getUsername(), "ivan");
}

TEST_F(RecommendationEngineTest, GenerateRecommendationsAddsUser) {
    engine->generateRecommendations(*user); auto s = engine->getSuggestions(); ASSERT_EQ(s.size(), 1); EXPECT_EQ(s[0].getUsername(), "ivan"); EXPECT_FALSE(engine->getLastRun().empty()); EXPECT_NE(engine->getLastRun(), "2025-01-01 10:00:00");
}

TEST_F(RecommendationEngineTest, GenerateRecommendationsThrowsIfUsernameEmpty) {
    User empty(2, "", "user@example.com", "1234", false, *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions); EXPECT_THROW(engine->generateRecommendations(empty), UserNotFoundException);
}

TEST_F(RecommendationEngineTest, UpdateAlgorithmChangesAlgorithmName) {
    engine->updateAlgorithm("NeuralNetwork"); EXPECT_EQ(engine->getAlgorithm(), "NeuralNetwork");
}
