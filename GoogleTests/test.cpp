#include "pch.h"

#include "../Space Panic/Math.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(Mathtest,addVector2f) {
	Vector2f v1 = Vector2f(1.5, 0);
	Vector2f v2 = Vector2f(4,1);
	Vector2f sum = v1+v2;
	EXPECT_EQ(sum.x,5.5);
	EXPECT_EQ(sum.y, 1);
}

TEST(Mathtest, multVector2f) {
	Vector2f v1 = Vector2f(1.5, 1);
	int i = 3;
	Vector2f sum = v1 * i;
	EXPECT_EQ(sum.x, 4.5);
	EXPECT_EQ(sum.y, 3);
}

TEST(Mathtest, subVector2f) {
	Vector2f v1 = Vector2f(1.5, 0);
	Vector2f v2 = Vector2f(4, 1);
	Vector2f sum = v2 - v1;
	EXPECT_EQ(sum.x, 2.5);
	EXPECT_EQ(sum.y, 1);
}
