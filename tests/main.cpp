#include <gtest/gtest.h>
#include "../src/long_numbers.cpp"

using namespace std;
using namespace long_numb;

constexpr long double operator""_my_double(long double value) {
    return value;
}

int Factorial(int n) {
    if (!n) return 1;
    return n * Factorial(n - 1);
}

number to_number(long long x) {
    number A;
    A.mantis.resize(com);
    if (x < 0) {
        x *= -1;
        A.sgn = -1;
    }

    vector<int> q;
    while (x) {
        q.push_back(int(x % 10));
        x /= 10;
    }

    A.exp = int(q.size()) - 1;
    for (int i = 0; i < q.size(); i++) {
        A.mantis[q.size() - i - 1] = q[i];
    }

    return A;
}

number from_string(string str) {
    number A;
    A.mantis.resize(com);
    int v = 0;
    if (str[v] == '-') {
        A.sgn = -1;
        v++;
    }

    while (v < str.length() && (str[v] == '0' || str[v] == '.')) {
        A.exp--;
        v++;
    }

    if (A.exp < 0) {
        A.exp++;
        for (int i = 0; i < com && v < str.length(); i++, v++) {
            A.mantis[i] = int(str[v] - '0');
        }
        return A;
    }
    A.exp--;
    int ind = 0;
    bool int_ = true;
    for (int i = 0; i < str.length() && ind < com; i++) {
        if (str[i] == '.') {
            int_ = false;
            continue;
        }

        A.mantis[ind] = int(str[i] - '0');
        A.exp += int_;
        ind++;
    }
    return A;
}

number count_pi() {
    number PI, PLUS;
    PI.mantis.resize(com);
    number E = to_number(1);
    number X_4 = to_number(4);
    number X_8 = to_number(8);
    number X_16 = to_number(16);

    PLUS = E;

    for (int i = 0; i < 82; i++) {
        PI = PI + (X_8 / to_number(8 * i + 2) + X_4 / to_number(8 * i + 3) + X_4 / to_number(8 * i + 4) -
                   E / to_number(8 * i + 7)) / PLUS;
        PLUS = PLUS * X_16;
    }

    PI = PI / to_number(2);

    return PI;
}

number from_literal(double val) {
    double x = 1e18;
    number PLUS, ans;
    PLUS.mantis.resize(com);
    ans.mantis.resize(com);
    PLUS.exp = 18;
    PLUS.mantis[0] = 1;

    if (val < 0) {
        PLUS.sgn *= -1;
        val *= -1;
    }

    while (PLUS.exp >= -15) {
        while (val >= x) {
            val -= x;
            ans = ans + PLUS;
        }
        x /= 10;
        PLUS.exp--;
    }
    return ans;
}

TEST(HelloTest, BasicAssertions) {
EXPECT_EQ(to_number(6) * to_number(7), to_number(42));
}

TEST(HelloTest1, BasicAssertions1) {
EXPECT_NE(to_number(7), to_number(42));
}

TEST(HelloTest2, BasicAssertions2) {
EXPECT_NE(to_number(6) / to_number(7), to_number(6/7));
}

TEST(HelloTest3, BasicAssertions2_Test3) {
EXPECT_EQ(to_number(6) - to_number(7), to_number(6-7));
}

TEST(HelloTest4, BasicAssertions3) {
EXPECT_EQ(from_string("123"), to_number(123));
}

TEST(HelloTest5, BasicAssertions5) {
EXPECT_EQ(from_string("123") / to_number(100), to_number(123) / from_string("100"));
}

TEST(H1, H1) {
EXPECT_EQ(to_number(1) < to_number(2), true);
}

TEST(H2, H3) {
EXPECT_NE(to_number(2) > to_number(2), true);
}

TEST(H5, H5) {
EXPECT_EQ(sqrt(to_number(2)) < to_number(3) / to_number(2), true);
}

TEST(H6, H6) {
EXPECT_EQ(sqrt(to_number(2)) > to_number(7) / to_number(5), true);
}

TEST(G1, G2) {
    EXPECT_EQ(from_string("3.14"), from_literal(3.14_my_double));
}
