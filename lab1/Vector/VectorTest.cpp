#include "gtest/gtest.h"
#include "Vector.h"
#include <iostream>
#include <cmath>

class VectorTest : public ::testing::Test {
protected:
    void SetUp() override {
        vec0 = Vector(0, 0, 0, 0, 0, 0);
        vec1 = Vector(0, 0, 0, 1, 1, 1);
        vec2 = Vector(0, 0, 0, 5, 5, 5);
        vec3 = Vector(-1, -2.1, -3, -7.55, -2.16, -8);
    }

    Vector vec0, vec1, vec2, vec3;
};

TEST(VectorConstruction, DefaultConstructor) {
    Vector vec;
    EXPECT_DOUBLE_EQ(vec.LengthCalculate(), 0);
}

TEST(VectorConstruction, ParameterizedConstructor) {
    Vector vec(0, 0, 0, 3, 4, 0);
    EXPECT_DOUBLE_EQ(vec.LengthCalculate(), 5);
}

TEST_F(VectorTest, BooleanChecks) {
    Vector vec = vec1;

    EXPECT_TRUE(vec1 == vec);
    EXPECT_FALSE(vec1 == vec2);
    EXPECT_TRUE(vec1.LengthCalculate() > 0);
    EXPECT_TRUE(vec0 == vec0);
}

TEST_F(VectorTest, CopyConstructor) {
    Vector copy(vec1);
    EXPECT_TRUE(copy == vec1);
}

TEST_F(VectorTest, SetCoordinatesBeg) {
    Vector vec;
    vec.SetÑoordinatesBeg(1.5, 2.5, 3.5);

    EXPECT_DOUBLE_EQ(vec.GetXBeg(), 1.5);
    EXPECT_DOUBLE_EQ(vec.GetYBeg(), 2.5);
    EXPECT_DOUBLE_EQ(vec.GetZBeg(), 3.5);
}

TEST_F(VectorTest, SetCoordinatesEnd) {
    Vector vec;
    vec.SetÑoordinatesEnd(4.5, 5.5, 6.5);

    EXPECT_DOUBLE_EQ(vec.GetXEnd(), 4.5);
    EXPECT_DOUBLE_EQ(vec.GetYEnd(), 5.5);
    EXPECT_DOUBLE_EQ(vec.GetZEnd(), 6.5);
}

TEST(VectorLengthCalculate, LengthCalculateBasic) {
    Vector vec(0, 0, 0, 3, 4, 0);
    EXPECT_DOUBLE_EQ(vec.LengthCalculate(), 5);
}

TEST_F(VectorTest, LengthCalculateBasic3D) {
    EXPECT_DOUBLE_EQ(vec1.LengthCalculate(), sqrt(3));
}

TEST(VectorLengthCalculate, LengthCalculate3D) {
    Vector vec(0, 0, 0, 1, 2, 2);
    EXPECT_DOUBLE_EQ(vec.LengthCalculate(), 3);
}

TEST_F(VectorTest, LengthCalculateZero) {
    EXPECT_DOUBLE_EQ(vec0.LengthCalculate(), 0);
}

TEST_F(VectorTest, AdditionOperatorSameOrigin) {
    Vector result = vec1 + vec2;
    Vector expected(0, 0, 0, 6, 6, 6);
    EXPECT_TRUE(result == expected);
}

TEST_F(VectorTest, AdditionOperatorDifferentOrigin) {
    Vector result = vec1 + vec3;
    Vector expected(0, 0, 0, -5.55, 0.94, -4);
    EXPECT_TRUE(result == expected);
}

TEST_F(VectorTest, AdditionAssignmentOperator) {
    Vector vec = vec1;
    vec += vec2;
    Vector expected(0, 0, 0, 6, 6, 6);
    EXPECT_TRUE(vec == expected);
}

TEST_F(VectorTest, AdditionWithZeroVector) {
    Vector result = vec1 + vec0;
    EXPECT_TRUE(result == vec1);
}

TEST_F(VectorTest, SubtractionOperatorSameOrigin) {
    Vector result = vec2 - vec1;
    Vector expected(0, 0, 0, 4, 4, 4);
    EXPECT_TRUE(result == expected);
}

TEST_F(VectorTest, SubtractionOperatorDifferentOrigin) {
    Vector result = vec3 - vec1;
    Vector expected(-1, -2.1, -3, -8.55, -3.16, -9);
    EXPECT_TRUE(result == expected);
}

TEST_F(VectorTest, SubtractionAssignmentOperator) {
    Vector vec = vec3;
    vec -= vec1;
    Vector expected(-1, -2.1, -3, -8.55, -3.16, -9);
    EXPECT_TRUE(vec == expected);
}

TEST_F(VectorTest, SubtractionFromZeroVector) {
    Vector result = vec0 - vec1;
    Vector expected(0, 0, 0, -1, -1, -1);
    EXPECT_TRUE(result == expected);
}

TEST_F(VectorTest, ScalarMultiplicationPositive) {
    Vector result = vec3 * 3;
    Vector expected(-1, -2.1, -3, -20.65, -2.28, -18);
}

TEST_F(VectorTest, ScalarMultiplicationNegative) {
    Vector result = vec2 * (-2);
    Vector expected(0, 0, 0, -10, -10, -10);
    EXPECT_TRUE(result == expected);
}

TEST_F(VectorTest, ScalarMultiplicationZero) {
    Vector result = vec1 * 0;
    Vector expected(0, 0, 0, 0, 0, 0);
    EXPECT_TRUE(result == expected);
}

TEST_F(VectorTest, ScalarMultiplicationAssignment) {
    Vector vec = vec1;
    vec *= 2.97;
    Vector expected(0, 0, 0, 2.97, 2.97, 2.97);
    EXPECT_TRUE(vec == expected);
}

TEST_F(VectorTest, ScalarDivisionPositive) {
    ;
    Vector result = vec2 / 5;
    Vector expected(0, 0, 0, 1, 1, 1);
    EXPECT_TRUE(result == expected);
}

TEST_F(VectorTest, ScalarDivisionNegative) {
    Vector result = vec1 / (-0.4);
    Vector expected(0, 0, 0, -2.5, -2.5, -2.5);
    EXPECT_TRUE(result == expected);
}

TEST_F(VectorTest, ScalarDivisionAssignment) {
    Vector vec = vec2;
    vec /= 10;
    Vector expected(0, 0, 0, 0.5, 0.5, 0.5);
    EXPECT_TRUE(vec == expected);
}

TEST_F(VectorTest, DivisionByZeroThrowsException) {
    EXPECT_THROW(vec3 / 0, runtime_error);
    EXPECT_THROW(vec0 /= 0, runtime_error);
}

TEST_F(VectorTest, DotProductPerpendicular) {
    double dotProduct = vec0 * vec3;
    EXPECT_DOUBLE_EQ(dotProduct, 0);
}

TEST_F(VectorTest, DotProductParallel) {
    double dotProduct = vec1 * vec2;
    EXPECT_DOUBLE_EQ(dotProduct, 15);
}

TEST_F(VectorTest, DotProductDifferent) {
    double dotProduct = vec2 * vec3;
    EXPECT_DOUBLE_EQ(dotProduct, -58.05);
}

TEST_F(VectorTest, CrossProductBasic) {
    Vector cross = vec0 % vec3;
    Vector expected(0, 0, 0, 0, 0, 0);
    EXPECT_TRUE(cross == expected);
}

TEST_F(VectorTest, CrossProductAntiCommutative) {
    Vector cross = vec1 % vec2;
    Vector expected(0, 0, 0, 0, 0, 0);
    EXPECT_TRUE(cross == expected);
}

TEST_F(VectorTest, CrossProductWithItself) {
    Vector cross = vec2 % vec3;
    Vector expected(0, 0, 0, -24.7, -7.75, 32.45);
    EXPECT_TRUE(cross == expected);
}

TEST_F(VectorTest, CosineAnglePerpendicular) {
    EXPECT_THROW(vec0 ^ vec3, runtime_error);
}

TEST_F(VectorTest, CosineAngleParallel) {
    Vector v2(0, 0, 0, 2, 0, 0);
    double cosAngle = vec1 ^ vec2;
    EXPECT_DOUBLE_EQ(cosAngle, 1);
}

TEST_F(VectorTest, CosineAngle45Degrees) {
    Vector v(0, 0, 0, 1, 1, 0);
    double cosAngle = vec2 ^ vec3;
    EXPECT_NEAR(cosAngle, -0.8134, 1e-4);
}

TEST_F(VectorTest, EqualityOperator) {
    Vector vec1_copy = vec1;
    EXPECT_TRUE(vec1 == vec1_copy);
    EXPECT_FALSE(vec1 == vec2);
}

TEST_F(VectorTest, InequalityOperator) {
    EXPECT_TRUE(vec1 != vec2);
    EXPECT_FALSE(vec1 != vec1);
}

TEST_F(VectorTest, ComparisonEqualLength) {
    Vector shortVec(0, 0, 0, 1, 0, 0);
    Vector longVec(0, 0, 0, 2, 0, 0);

    EXPECT_TRUE(shortVec < longVec);
    EXPECT_TRUE(shortVec <= longVec);
    EXPECT_TRUE(longVec > shortVec);
    EXPECT_TRUE(longVec >= shortVec);
    EXPECT_TRUE(vec2 > vec3);
    EXPECT_TRUE(vec3 < vec2);
    EXPECT_TRUE(vec3 >= vec0);
    EXPECT_TRUE(vec0 <= vec3);
}

TEST(VectorOutputInput, OutputOperatorPrecision) {
    Vector vec(1.123, 2.234, 3.345, 4.456, 5.567, 6.678);
    stringstream out;
    out << vec;

    string result = out.str();
    EXPECT_NE(result.find("1.123"), string::npos);
    EXPECT_NE(result.find("6.678"), string::npos);
}

TEST(VectorOutputInput, InputOperatorValidData) {
    Vector vec;
    stringstream in("1.5 2.5 3.5 4.5 5.5 6.5");
    in >> vec;

    Vector expected(1.5, 2.5, 3.5, 4.5, 5.5, 6.5);
    EXPECT_TRUE(vec == expected);
}

TEST(VectorOutputInput, InputOperatorWithScientificNotation) {
    Vector vec;
    stringstream in("1e-3 2e+3 3.5e2 4.5 5.5 6.5");
    in >> vec;

    stringstream output;
    output << vec;
    EXPECT_FALSE(output.str().empty());
}

TEST_F(VectorTest, AssignmentOperatorBasic) {
    Vector vec;
    vec = vec1;
    EXPECT_TRUE(vec == vec1);
}

TEST_F(VectorTest, SelfAssignment) {
    Vector vec = vec1;
    vec = vec;
    EXPECT_TRUE(vec == vec1);
}

TEST_F(VectorTest, CombinedOperations) {
    Vector result = (vec1 + vec2) * 2;
    Vector expected(0, 0, 0, 12, 12, 12);
    EXPECT_TRUE(result == expected);
}

TEST_F(VectorTest, ChainedOperations) {
    Vector vec = vec1;
    vec += vec2;
    vec *= 2;
    vec /= 5;
    Vector expected(0, 0, 0, 2.4, 2.4, 2.4);
    EXPECT_TRUE(vec == expected);
}

TEST_F(VectorTest, ComplexExpression) {
    double result = (vec1 * 2 + vec2) * (vec3 - vec1);
    EXPECT_TRUE(isfinite(result));
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "RU");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
