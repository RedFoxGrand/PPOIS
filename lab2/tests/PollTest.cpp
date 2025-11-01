#include <gtest/gtest.h>
#include "Poll.h"
#include "UserProfile.h"
#include "Settings.h"
#include "Wallet.h"
#include "FriendList.h"
#include "BlockList.h"
#include "Permission.h"
#include "Currency.h"
using namespace std;

class PollTest : public ::testing::Test {
protected:
    UserProfile* profile; Settings* settings; Currency* currency; Wallet* wallet; FriendList* friends; BlockList* blocks; vector<Permission>* permissions; User* user; Poll* poll;

    void SetUp() override {
        profile = new UserProfile("Иван", "Иванов", "01.01.2000", "01.01.2020", "+79990001122", "Россия", "Москва", { "Игры", "Программирование" });
        settings = new Settings(18, "Русский", true, true, false, true, Theme::LIGHT);
        currency = new Currency("RUB", "Российский рубль", 1.0);
        wallet = new Wallet(1000.0, {}, {}, *currency);
        friends = new FriendList({}, {}, {});
        blocks = new BlockList({}, {});
        permissions = new vector<Permission>{ Permission("READ", "Чтение данных", true), Permission("WRITE", "Изменение данных", true) };
        user = new User(1, "ivan", "ivan@example.com", "pass123", true, *profile, *settings, *wallet, *friends, *blocks, UserRole::USER, *permissions);
        poll = new Poll("Ваш любимый язык программирования?", "2025-12-31", false, { "C++", "Python", "JavaScript" }, { {"C++", 2}, {"Python", 1} });
    }

    void TearDown() override {
        delete poll; delete user; delete permissions; delete blocks; delete friends; delete wallet; delete settings; delete currency; delete profile;
    }
};

TEST_F(PollTest, ConstructorInitializesCorrectly) {
    EXPECT_EQ(poll->getQuestion(), "Ваш любимый язык программирования?");
    EXPECT_EQ(poll->getDeadline(), "2025-12-31");
    EXPECT_FALSE(poll->isMultipleChoiceEnabled());
    auto options = poll->getOptions(); ASSERT_EQ(options.size(), 3); EXPECT_EQ(options[0], "C++"); EXPECT_EQ(options[1], "Python"); EXPECT_EQ(options[2], "JavaScript");
    auto votes = poll->getVotes(); EXPECT_EQ(votes.at("C++"), 2); EXPECT_EQ(votes.at("Python"), 1);
}

TEST_F(PollTest, SettersWorkCorrectly) {
    poll->setQuestion("Новый вопрос?"); poll->setDeadline("2026-01-01"); poll->setMultipleChoice(true); poll->setOptions({ "A", "B" }); poll->setVotes({ {"A", 10}, {"B", 5} });
    EXPECT_EQ(poll->getQuestion(), "Новый вопрос?"); EXPECT_EQ(poll->getDeadline(), "2026-01-01"); EXPECT_TRUE(poll->isMultipleChoiceEnabled());
    auto options = poll->getOptions(); ASSERT_EQ(options.size(), 2); EXPECT_EQ(options[0], "A"); EXPECT_EQ(options[1], "B");
    auto votes = poll->getVotes(); EXPECT_EQ(votes.at("A"), 10); EXPECT_EQ(votes.at("B"), 5);
}

TEST_F(PollTest, VoteAddsVoteToOption) {
    poll->vote(*user, "Python");
    auto votes = poll->getVotes(); EXPECT_EQ(votes.at("Python"), 2);
}

TEST_F(PollTest, VoteDoesNothingIfOptionInvalid) {
    auto votesBefore = poll->getVotes(); poll->vote(*user, "Rust"); auto votesAfter = poll->getVotes(); EXPECT_EQ(votesAfter, votesBefore);
}

TEST_F(PollTest, GetResultsGeneratesCorrectOutput) {
    string expected = "C++: 2 голоса\nPython: 1 голос\nJavaScript: 0 голосов\n";
    EXPECT_EQ(poll->getResults(), expected);
}

TEST_F(PollTest, GetResultsEmptyOptionsReturnsEmptyString) {
    poll->setOptions({}); EXPECT_EQ(poll->getResults(), "");
}
