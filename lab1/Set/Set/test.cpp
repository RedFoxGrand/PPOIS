#include <gtest/gtest.h>
#include "Set.h"
#include <iostream>
#include <string>
#include <vector>

class SetTest : public ::testing::Test {
protected:
    void SetUp() override {
        emptySet = Set();
        simpleSet = Set("{a, b, c}");
        simpleSetTwo = Set("{d, c, a, e}");
        nestedSet = Set("{{x, y}, z}");
        nestedSetTwo = Set("{x, y, {}, {x, y}, z}");
    }

    Set emptySet, simpleSet, simpleSetTwo, nestedSet, nestedSetTwo;
};

TEST_F(SetTest, DefaultConstructor) {
    EXPECT_TRUE(emptySet.EmptyCheck());
    EXPECT_EQ(emptySet.Cardinality(), 0);
    EXPECT_EQ(emptySet.ToString(), "{}");
}

TEST(SetTStringConstructorEmpty, StringConstructorEmpty) {
    Set set("{}");
    EXPECT_TRUE(set.EmptyCheck());
    EXPECT_EQ(set.Cardinality(), 0);
}

TEST_F(SetTest, StringConstructorSimple) {
    EXPECT_FALSE(simpleSet.EmptyCheck());
    EXPECT_EQ(simpleSet.Cardinality(), 3);
    EXPECT_TRUE(simpleSet.Contains(Set::SetElement("a")));
    EXPECT_TRUE(simpleSet.Contains(Set::SetElement("b")));
    EXPECT_TRUE(simpleSet.Contains(Set::SetElement("c")));
    EXPECT_FALSE(simpleSet.Contains(Set::SetElement("d")));
}

TEST_F(SetTest, StringConstructorNested) {
    EXPECT_EQ(nestedSet.Cardinality(), 2);

    vector<Set::SetElement> innerElems = {
        Set::SetElement("x"),
        Set::SetElement("y")
    };
    Set::SetElement innerSet(innerElems);

    EXPECT_TRUE(nestedSet.Contains(innerSet));
    EXPECT_TRUE(nestedSet.Contains(Set::SetElement("z")));
    EXPECT_FALSE(nestedSet.Contains(Set::SetElement("Z")));
}

TEST_F(SetTest, CopyConstructor) {
    Set copy(simpleSet);
    EXPECT_EQ(copy, simpleSet);
    EXPECT_EQ(copy.Cardinality(), simpleSet.Cardinality());
}

TEST_F(SetTest, AddElement) {
    Set set = emptySet;
    set.AddElement(Set::SetElement("test"));
    EXPECT_EQ(set.Cardinality(), 1);
    EXPECT_TRUE(set.Contains(Set::SetElement("test")));
}

TEST_F(SetTest, AddElementNested) {
    Set set = nestedSet;

    vector<Set::SetElement> innerElems = {
        Set::SetElement("test1"),
        Set::SetElement("test2")
    };
    Set::SetElement innerSet(innerElems);

    set.AddElement(innerSet);
    EXPECT_EQ(set.Cardinality(), 3);
    EXPECT_TRUE(set.Contains(innerSet));
}


TEST_F(SetTest, AddDuplicateElement) {
    Set set = simpleSet;
    size_t initialSize = set.Cardinality();
    set.AddElement(Set::SetElement("a"));
    EXPECT_EQ(set.Cardinality(), initialSize);
}

TEST_F(SetTest, AddDuplicateElementNested) {
    Set set = nestedSet;

    size_t initialSize = set.Cardinality();
    vector<Set::SetElement> innerElems = {
        Set::SetElement("x"),
        Set::SetElement("y")
    };
    Set::SetElement innerSet(innerElems);

    set.AddElement(innerSet);
    EXPECT_EQ(set.Cardinality(), initialSize);
}

TEST_F(SetTest, RemoveElement) {
    Set set = simpleSet;
    set.RemoveElement(Set::SetElement("b"));
    EXPECT_EQ(set.Cardinality(), 2);
    EXPECT_FALSE(set.Contains(Set::SetElement("b")));
    EXPECT_TRUE(set.Contains(Set::SetElement("a")));
    EXPECT_TRUE(set.Contains(Set::SetElement("c")));
}

TEST_F(SetTest, RemoveElementNested) {
    Set set = nestedSet;

    vector<Set::SetElement> innerElems = {
        Set::SetElement("x"),
        Set::SetElement("y")
    };
    Set::SetElement innerSet(innerElems);

    set.RemoveElement(innerSet);
    EXPECT_EQ(set.Cardinality(), 1);
}

TEST_F(SetTest, RemoveNonExistentElement) {
    Set set = simpleSet;
    size_t initialSize = set.Cardinality();
    set.RemoveElement(Set::SetElement("x"));
    EXPECT_EQ(set.Cardinality(), initialSize);
}

TEST_F(SetTest, UnionOperation) {
    Set unionSet = simpleSet + simpleSetTwo;
    EXPECT_EQ(unionSet.Cardinality(), 5);
    EXPECT_TRUE(unionSet.Contains(Set::SetElement("a")));
    EXPECT_TRUE(unionSet.Contains(Set::SetElement("b")));
    EXPECT_TRUE(unionSet.Contains(Set::SetElement("c")));
    EXPECT_FALSE(unionSet.Contains(Set::SetElement("u")));
}

TEST_F(SetTest, UnionOperationNested) {
    Set unionSet = nestedSet + nestedSetTwo;
    EXPECT_EQ(unionSet.Cardinality(), 5);

    vector<Set::SetElement> innerElems = {
        Set::SetElement("x"),
        Set::SetElement("y")
    };
    Set::SetElement innerSet(innerElems);

    EXPECT_TRUE(unionSet.Contains(innerSet));
    EXPECT_TRUE(unionSet.Contains(Set::SetElement("x")));
    EXPECT_TRUE(unionSet.Contains(Set::SetElement("z")));
    EXPECT_FALSE(unionSet.Contains(Set::SetElement("i")));
}

TEST_F(SetTest, IntersectionOperation) {
    Set intersection = simpleSet * simpleSetTwo;
    EXPECT_EQ(intersection.Cardinality(), 2);
    EXPECT_TRUE(intersection.Contains(Set::SetElement("a")));
    EXPECT_TRUE(intersection.Contains(Set::SetElement("c")));
    EXPECT_FALSE(intersection.Contains(Set::SetElement("b")));
    EXPECT_FALSE(intersection.Contains(Set::SetElement("d")));
    EXPECT_FALSE(intersection.Contains(Set::SetElement("e")));
}

TEST_F(SetTest, IntersectionOperationNested) {
    Set intersection = nestedSet * nestedSetTwo;
    EXPECT_EQ(intersection.Cardinality(), 2);

    vector<Set::SetElement> innerElems = {
        Set::SetElement("x"),
        Set::SetElement("y")
    };
    Set::SetElement innerSet(innerElems);

    EXPECT_TRUE(intersection.Contains(innerSet));
    EXPECT_TRUE(intersection.Contains(Set::SetElement("z")));
    EXPECT_FALSE(intersection.Contains(Set::SetElement("y")));
}

TEST_F(SetTest, DifferenceOperation) {
    Set difference = simpleSetTwo - simpleSet;
    EXPECT_EQ(difference.Cardinality(), 2);
    EXPECT_TRUE(difference.Contains(Set::SetElement("d")));
    EXPECT_TRUE(difference.Contains(Set::SetElement("e")));
    EXPECT_FALSE(difference.Contains(Set::SetElement("a")));
    EXPECT_FALSE(difference.Contains(Set::SetElement("b")));
    EXPECT_FALSE(difference.Contains(Set::SetElement("c")));
}

TEST_F(SetTest, DifferenceOperationNested) {
    Set difference = nestedSetTwo - nestedSet;
    EXPECT_EQ(difference.Cardinality(), 3);

    vector<Set::SetElement> innerElems = {
        Set::SetElement("x"),
        Set::SetElement("y")
    };
    Set::SetElement innerSet(innerElems);
    Set::SetElement emptySetElement{ vector<Set::SetElement>{} };

    EXPECT_FALSE(difference.Contains(innerSet));
    EXPECT_TRUE(difference.Contains(emptySetElement));
    EXPECT_TRUE(difference.Contains(Set::SetElement("x")));
}

TEST_F(SetTest, UnionAssignment) {
    simpleSet += simpleSetTwo;
    EXPECT_EQ(simpleSet.Cardinality(), 5);
    EXPECT_TRUE(simpleSet.Contains(Set::SetElement("a")));
    EXPECT_TRUE(simpleSet.Contains(Set::SetElement("b")));
    EXPECT_TRUE(simpleSet.Contains(Set::SetElement("c")));
    EXPECT_TRUE(simpleSet.Contains(Set::SetElement("d")));
    EXPECT_TRUE(simpleSet.Contains(Set::SetElement("e")));
}

TEST_F(SetTest, IntersectionAssignment) {
    simpleSet *= simpleSetTwo;
    EXPECT_EQ(simpleSet.Cardinality(), 2);
    EXPECT_TRUE(simpleSet.Contains(Set::SetElement("a")));
    EXPECT_TRUE(simpleSet.Contains(Set::SetElement("c")));
    EXPECT_FALSE(simpleSet.Contains(Set::SetElement("b")));
    EXPECT_FALSE(simpleSet.Contains(Set::SetElement("d")));
    EXPECT_FALSE(simpleSet.Contains(Set::SetElement("e")));
}

TEST_F(SetTest, DifferenceAssignment) {
    simpleSetTwo -= simpleSet;
    EXPECT_EQ(simpleSetTwo.Cardinality(), 2);
    EXPECT_TRUE(simpleSetTwo.Contains(Set::SetElement("e")));
    EXPECT_TRUE(simpleSetTwo.Contains(Set::SetElement("d")));
    EXPECT_FALSE(simpleSetTwo.Contains(Set::SetElement("b")));
    EXPECT_FALSE(simpleSetTwo.Contains(Set::SetElement("a")));
    EXPECT_FALSE(simpleSetTwo.Contains(Set::SetElement("c")));
}

TEST_F(SetTest, AssignmentOperationsWithNestedSets) {
    Set setA = nestedSetTwo;

    setA += nestedSet;
    EXPECT_EQ(setA.Cardinality(), 5);

    Set setB = nestedSetTwo;
    setB *= nestedSet;
    EXPECT_EQ(setB.Cardinality(), 2);
    EXPECT_TRUE(setB.Contains(Set::SetElement("z")));

    Set setC = nestedSetTwo;
    setC -= nestedSet;
    EXPECT_EQ(setC.Cardinality(), 3);
    EXPECT_TRUE(setC.Contains(Set::SetElement("x")));
    EXPECT_TRUE(setC.Contains(Set::SetElement("y")));

    Set::SetElement emptySetElement{ vector<Set::SetElement>{} };
    EXPECT_TRUE(setC.Contains(emptySetElement));
}

TEST(SetEquality, EqualityOperator) {
    Set A("{a, b, c}");
    Set B("{c, b, a}");
    Set C("{a, b}");

    EXPECT_TRUE(A == B);
    EXPECT_FALSE(A == C);
    EXPECT_FALSE(B == C);

    EXPECT_FALSE(A != B);
    EXPECT_TRUE(A != C);
    EXPECT_TRUE(B != C);
}

TEST(SetEquality, EqualityWithNestedSets) {
    Set set1("{{x, y}, z}");
    Set set2("{{x, y}, z}");
    EXPECT_TRUE(set1 == set2);
    EXPECT_FALSE(set1 != set2);

    Set set3("{{y, x}, z}");
    Set set4("{{x, y}, z}");
    EXPECT_TRUE(set3 == set4);

    Set set5("{z, {x, y}}");
    Set set6("{{x, y}, z}");
    EXPECT_TRUE(set5 == set6);
}

TEST(SetTestContainsOperator, ContainsOperator) {
    Set set("{x, y, z}");

    EXPECT_TRUE(set[Set::SetElement("x")]);
    EXPECT_TRUE(set[Set::SetElement("y")]);
    EXPECT_FALSE(set[Set::SetElement("w")]);
}

TEST_F(SetTest, PowerSetEmpty) {
    Set power = emptySet.PowerSet();

    EXPECT_EQ(power.Cardinality(), 1);
    EXPECT_TRUE(power.Contains(Set::SetElement(vector<Set::SetElement>())));
}

TEST(SetTestBulean, PowerSetSingleton) {
    Set single("{a}");
    Set power = single.PowerSet();

    EXPECT_EQ(power.Cardinality(), 2);

    EXPECT_TRUE(power.Contains(Set::SetElement(vector<Set::SetElement>())));

    vector<Set::SetElement> innerElems = {
        Set::SetElement("a"),
    };
    Set::SetElement innerSet(innerElems);

    EXPECT_TRUE(power.Contains(innerSet));
}

TEST(SetTestBulean, PowerSetTwoElements) {
    Set set("{1, 2}");
    Set power = set.PowerSet();

    EXPECT_EQ(power.Cardinality(), 4);

    vector<Set::SetElement> innerElem1 = {
        Set::SetElement("1"),
    };
    Set::SetElement innerSet1(innerElem1);

    vector<Set::SetElement> innerElem2 = {
        Set::SetElement("2"),
    };
    Set::SetElement innerSet2(innerElem2);

    EXPECT_TRUE(power.Contains(Set::SetElement(vector<Set::SetElement>())));
    EXPECT_TRUE(power.Contains(innerSet1));
    EXPECT_TRUE(power.Contains(innerSet2));

    vector<Set::SetElement> both = { Set::SetElement("1"), Set::SetElement("2") };
    EXPECT_TRUE(power.Contains(Set::SetElement(both)));
}

TEST(SetTestString, ToStringFromString) {
    string original = "{a, {b, c}, d}";
    Set set = Set::FromString(original);
    string converted = set.ToString();

    EXPECT_EQ(original, converted);
}

TEST_F(SetTest, StreamOutput) {
    Set set = simpleSet;
    stringstream out;
    out << set;

    string result = out.str();
    EXPECT_NE(result.find("a"), string::npos);
    EXPECT_NE(result.find("b"), string::npos);
    EXPECT_NE(result.find("c"), string::npos);
    EXPECT_EQ('{', result.front());
    EXPECT_EQ('}', result.back());
}

TEST_F(SetTest, StreamInput) {
    stringstream in("{{a, b}, c}");
    Set set;
    in >> set;

    EXPECT_EQ(set.Cardinality(), 2);

    vector<Set::SetElement> inner = {
        Set::SetElement("a"),
        Set::SetElement("b")
    };
    EXPECT_TRUE(set.Contains(Set::SetElement(inner)));
    EXPECT_TRUE(set.Contains(Set::SetElement("c")));
}

TEST_F(SetTest, AssignmentOperator) {
    Set A("{a, b}");
    Set B("{x, y, z}");

    B = A;

    EXPECT_EQ(A, B);
    EXPECT_EQ(B.Cardinality(), 2);
}

TEST_F(SetTest, SelfAssignment) {
    Set set("{1, 2, 3}");
    set = set;

    EXPECT_EQ(set.Cardinality(), 3);
}

TEST(SetException, InvalidFormatThrowsException) {
    EXPECT_THROW(Set invalid("invalid format"), invalid_argument);
    EXPECT_THROW(Set incorrect1("{a, b"), invalid_argument);
    EXPECT_THROW(Set incorrect2("a, b}"), invalid_argument);
}

TEST(SetException, InvalidCharacters) {
    EXPECT_THROW(Set invalid("{a, b@c}"), invalid_argument);
    EXPECT_THROW(Set invalid("{a, b!c}"), invalid_argument);
}

TEST(SetException, UnexpectedBraceInToken) {
    EXPECT_THROW(Set invalid("{a, b{c}"), invalid_argument);
}

TEST(SetException, EmptyStringThrowsException) {
    EXPECT_THROW(Set empty(""), invalid_argument);
}

TEST(SetComplexNestedSets, ComplexNestedSets) {
    Set complex("{{{a, b}}, {c, {d, e}}}");

    EXPECT_EQ(complex.Cardinality(), 2);

    string result = complex.ToString();
    EXPECT_NE(result.find("a"), string::npos);
    EXPECT_NE(result.find("b"), string::npos);
    EXPECT_NE(result.find("c"), string::npos);
    EXPECT_NE(result.find("d"), string::npos);
    EXPECT_NE(result.find("e"), string::npos);
}

TEST(SetTestDuplicateRemoval, DuplicateRemoval) {
    Set withDuplicates("{a, a, b, b, c, a}");
    EXPECT_EQ(withDuplicates.Cardinality(), 3);
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "RU");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}