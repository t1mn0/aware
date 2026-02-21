#include <gtest/gtest.h>

#include <aware/math/power/power.hpp>

struct Matrix2x2 {
    int m[2][2];

    Matrix2x2& operator*=(const Matrix2x2& other) {
        int a = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0];
        int b = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1];
        int c = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0];
        int d = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1];
        m[0][0] = a;
        m[0][1] = b;
        m[1][0] = c;
        m[1][1] = d;
        return *this;
    }

    bool operator==(const Matrix2x2& other) const {
        return m[0][0] == other.m[0][0] && m[0][1] == other.m[0][1] && m[1][0] == other.m[1][0] &&
               m[1][1] == other.m[1][1];
    }
};

TEST(MathTest, PowerInteger) {
    int result = awr::math::power(2, 10);
    EXPECT_EQ(result, 1024);
    EXPECT_EQ(awr::math::power(3, 3), 27);
    EXPECT_EQ(awr::math::power(5, 10, 0), 10);
}

TEST(MathTest, PowerMatrix) {
    Matrix2x2 identity = {{{1, 0}, {0, 1}}};

    // Matrix A = {{1, 1}, {1, 0}} (Fibonacci matrix)
    Matrix2x2 A = {{{1, 1}, {1, 0}}};

    // A^2 = {{2, 1}, {1, 1}}
    Matrix2x2 A2 = awr::math::power(A, identity, 2);
    Matrix2x2 expected_A2 = {{{2, 1}, {1, 1}}};
    EXPECT_EQ(A2, expected_A2);

    Matrix2x2 A5 = awr::math::power(A, identity, 5);
    Matrix2x2 expected_A5 = {{{8, 5}, {5, 3}}};
    EXPECT_EQ(A5, expected_A5);
}

TEST(MathTest, PowerFloat) {
    double res = awr::math::power(1.5f, 2);
    EXPECT_FLOAT_EQ(res, 2.25);
}
