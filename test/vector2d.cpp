#include <gtest/gtest.h>

#include <kui/vector2d.hpp>

using namespace kui;

TEST(Vector_2d, Construction) {
    // Default constructor
    Vector_2d<int> v1;

    EXPECT_EQ(v1.rows(), 0);
    EXPECT_EQ(v1.columns(), 0);

    Vector_2d<int> v2(1, 2);
    EXPECT_EQ(v2.rows(), 1);
    EXPECT_EQ(v2.columns(), 2);

    Vector_2d<int> v3(100, 25);
    EXPECT_EQ(v3.rows(), 100);
    EXPECT_EQ(v3.columns(), 25);

    Vector_2d<int> v4(6, 5, 4);
    EXPECT_EQ(v4.rows(), 6);
    EXPECT_EQ(v4.columns(), 5);
    EXPECT_EQ(v4(0, 0), 4);

    Vector_2d<int> v5(2, 3, {
            100, 200, 300,
            10, 20, 30
    });
    EXPECT_EQ(v5.rows(), 2);
    EXPECT_EQ(v5.columns(), 3);
    EXPECT_EQ(v5(0, 0), 100);
    EXPECT_EQ(v5(0, 1), 200);
    EXPECT_EQ(v5(0, 2), 300);

    EXPECT_EQ(v5(1, 0), 10);
    EXPECT_EQ(v5(1, 1), 20);
    EXPECT_EQ(v5(1, 2), 30);
}

TEST(Vector_2d, ElementAccess) {
    Vector_2d<int> v(3, 4);

    for(unsigned int r = 0; r < v.rows(); r++) {
        for(unsigned int c = 0; c < v.columns(); c++) {
            v(r, c) = r*100 + c;
        }
    }

    EXPECT_EQ(v(0, 0), 0);
    EXPECT_EQ(v(0, 1), 1);
    EXPECT_EQ(v(1, 0), 100);
    EXPECT_EQ(v(2, 3), 203);
}

TEST(Vector_2d, Copy) {
    Vector_2d<int> v1(2, 3, {
            1, 2, 3,
            4, 5, 6,
    });
    Vector_2d<int> v2(v1);
    Vector_2d<int> v3;
    v3 = v1;

    EXPECT_EQ(v1.rows(), 2);
    EXPECT_EQ(v1.columns(), 3);

    EXPECT_EQ(v2.rows(), 2);
    EXPECT_EQ(v2.columns(), 3);

    EXPECT_EQ(v3.rows(), 2);
    EXPECT_EQ(v3.columns(), 3);

    for(unsigned int r = 0; r < v1.rows(); r++) {
        for(unsigned int c = 0; c < v1.columns(); c++) {
            EXPECT_EQ(v1(r, c), v2(r, c));
            EXPECT_EQ(v1(r, c), v3(r, c));
        }
    }
}

TEST(Vector_2d, Move) {

}

TEST(Vector_2d, Resize) {
    Vector_2d<int> v(2, 2, {
            1, 2,
            3, 4
    });

    v.resize(3, 3, 0);
    EXPECT_EQ(v.rows(), 3);
    EXPECT_EQ(v.columns(), 3);
    EXPECT_EQ(v(0, 0), 1);
    EXPECT_EQ(v(1, 1), 4);
    EXPECT_EQ(v(2, 2), 0);
}

TEST(Vector_2d, Boolean) {
    Vector_2d<bool> v(2, 2, {
            true, false,
            false, true
    });

    EXPECT_EQ(v.rows(), 2);
    EXPECT_EQ(v.columns(), 2);
    EXPECT_EQ(v(0, 0), true);
    EXPECT_EQ(v(0, 1), false);
    EXPECT_EQ(v(1, 0), false);
    EXPECT_EQ(v(1, 1), true);
}

