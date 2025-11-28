#include <gtest/gtest.h>
#include "SortingNetwork.h"
#include "Person.h"

TEST(SortingNetworkTest, SortingNetworkVectorInt) {
    vector<int> vec = { 3, 1, -4, 1, 5, 9, 2, -6 };
    vector<int> expected = vec;
    sort(expected.begin(), expected.end());

    SortingNetwork(vec);

    EXPECT_EQ(vec, expected);
}

TEST(SortingNetworkTest, SortingNetworkVectorEvenCount) {
    vector<int> vec = { 4, 3, 2, 1 };
    vector<int> expected = { 1, 2, 3, 4 };

    SortingNetwork(vec);

    EXPECT_EQ(vec, expected);
}

TEST(SortingNetworkTest, SortingNetworkVectorOddCount) {
    vector<int> vec = { 5, 3, 1, 4, 2 };
    vector<int> expected = { 1, 2, 3, 4, 5 };

    SortingNetwork(vec);

    EXPECT_EQ(vec, expected);
}

TEST(SortingNetworkTest, SortingNetworkVectorString) {
    vector<string> vec = { "banana", "apple", "cherry", "date", "apple" };
    vector<string> expected = vec;
    sort(expected.begin(), expected.end());

    SortingNetwork(vec);

    EXPECT_EQ(vec, expected);
}

TEST(SortingNetworkTest, SortingNetworkArrayInt) {
    int arr[] = { 3, 1, -4, 1, 5, 9, 2, -6 };
    int expected[] = { -6, -4, 1, 1, 2, 3, 5, 9 };
    size_t n = sizeof(arr) / sizeof(arr[0]);

    SortingNetwork(arr, n);

    for (size_t i = 0; i < n; ++i) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(SortingNetworkTest, SortingNetworkArrayPerson) {
    Person people[] = {
        Person("Alice", 25),
        Person("Bob", 30),
        Person("Charlie", 20)
    };
    Person expected[] = {
        Person("Charlie", 20),
        Person("Alice", 25),
        Person("Bob", 30)
    };
    size_t n = sizeof(people) / sizeof(people[0]);

    SortingNetwork(people, n);

    for (size_t i = 0; i < n; i++) {
        EXPECT_TRUE(people[i] == expected[i]);
    }
}

TEST(SortingNetworkTest, SortingNetworkVectorPersonSameAge) {
    vector<Person> people = {
        Person("Charlie", 25),
        Person("Alice", 25),
        Person("Bob", 25)
    };

    vector<Person> expected = people;
    sort(expected.begin(), expected.end());

    SortingNetwork(people);

    for (size_t i = 0; i < people.size(); ++i) {
        EXPECT_TRUE(people[i] == expected[i]);
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "RU");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}