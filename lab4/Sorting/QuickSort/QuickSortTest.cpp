#include <gtest/gtest.h>
#include "QuickSort.h"
#include "Person.h"

TEST(QuickSortTest, PivotSelectionVectorString) {
    vector<string> vec = { "banana", "apple", "cherry", "date" };
    size_t pivot_index = PivotSelection(vec, 0, vec.size() - 1);

    string pivot_value = vec[pivot_index];
    for (size_t i = 0; i < pivot_index; ++i) {
        EXPECT_LE(vec[i], pivot_value);
    }
    for (size_t i = pivot_index + 1; i < vec.size(); ++i) {
        EXPECT_GE(vec[i], pivot_value);
    }
}

TEST(QuickSortTest, PivotSelectionArrayInt) {
    int arr[] = { 3, 1, -4, 1, 5, 9, 2, -6 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t pivot_index = PivotSelection(arr, 0, n - 1);

    int pivot_value = arr[pivot_index];
    for (size_t i = 0; i < pivot_index; ++i) {
        EXPECT_LE(arr[i], pivot_value);
    }
    for (size_t i = pivot_index + 1; i < n; ++i) {
        EXPECT_GE(arr[i], pivot_value);
    }
}

TEST(QuickSortTest, QuickSortVectorInt) {
    vector<int> vec = { 3, 1, -4, 1, 5, 9, 2, -6 };
    vector<int> expected = vec;
    sort(expected.begin(), expected.end());

    QuickSort(vec, 0, vec.size() - 1);

    EXPECT_EQ(vec, expected);
}

TEST(QuickSortTest, QuickSortVectorString) {
    vector<string> vec = { "banana", "apple", "cherry", "date", "apple" };
    vector<string> expected = vec;
    sort(expected.begin(), expected.end());

    QuickSort(vec, 0, vec.size() - 1);

    EXPECT_EQ(vec, expected);
}

TEST(QuickSortTest, QuickSortArrayInt) {
    int arr[] = { 3, 1, -4, 1, 5, 9, 2, -6 };
    int expected[] = { -6, -4, 1, 1, 2, 3, 5, 9 };
    size_t n = sizeof(arr) / sizeof(arr[0]);

    QuickSort(arr, 0, n - 1);

    for (size_t i = 0; i < n; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(QuickSortTest, QuickSortArrayPerson) {
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

    QuickSort(people, 0, n - 1);

    for (size_t i = 0; i < n; i++) {
        EXPECT_TRUE(people[i] == expected[i]);
    }
}

TEST(QuickSortTest, QuickSortVectorPersonSameAge) {
    vector<Person> people = {
        Person("Charlie", 25),
        Person("Alice", 25),
        Person("Bob", 25)
    };

    vector<Person> expected = people;
    sort(expected.begin(), expected.end());

    QuickSort(people, 0, people.size() - 1);

    for (size_t i = 0; i < people.size(); i++) {
        EXPECT_TRUE(people[i] == expected[i]);
    }
}

TEST(QuickSortTest, QuickSortPartialRange) {
    vector<int> vec = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    vector<int> expected = vec;

    QuickSort(vec, 2, 6);
    sort(expected.begin() + 2, expected.begin() + 7);

    EXPECT_EQ(vec, expected);
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "RU");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}