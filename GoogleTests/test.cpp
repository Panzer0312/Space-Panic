#include "pch.h"

#include "../Space Panic/Math.h"


#include "../Space Panic/GameModel.cpp"
#include "../Space Panic/GameView.cpp"
#include "../Space Panic/GameController.cpp"
#include "../Space Panic/GameObject.cpp"
#include "../Space Panic/ObjectAnimation.cpp"
#include "../Space Panic/SpriteBatch.cpp"
#include "../Space Panic/SpriteTechnique.cpp"
#include "../Space Panic/Technique.cpp"
#include "../Space Panic/Textur.cpp"
#include "../Space Panic/QuadArray.cpp"


#include "gtest/gtest.h"

class ModelTest : public testing::Test {
protected:
	void SetUp() override {
		// Code here will be called immediately after the constructor (right
		// before each test).
		obj1ID = m.addObject(Vector2f(0, 0), Vector2i(0, 0), 10, "test1", 10, BRICK);
		obj2ID = m.addObject(Vector2f(2, 2), Vector2i(0, 0), 10, "test2", 10, LADDER);
		obj3ID = m.addObject(Vector2f(4, 4), Vector2i(0, 0), 10, "test3", 10, ENEMY);
		obj4ID = m.addObject(Vector2f(6, 6), Vector2i(0, 0), 10, "test4", 10, BRICK);

	}

	void TearDown() override {
		// Code here will be called immediately after each test (right
		// before the destructor).
		m.deleteAll();
	}
public:
	GameModel m;
	int obj1ID, obj2ID, obj3ID, obj4ID;
};

class ControllerTest : public testing::Test {
protected:
	void SetUp() override {
		// Code here will be called immediately after the constructor (right
		// before each test).

	}

	void TearDown() override {
		// Code here will be called immediately after each test (right
		// before the destructor).
		m.deleteAll();
	}
public:
	GameModel m;
	GameView v;
};

	TEST(BasicMathTest, addVector2f) {
		Vector2f v1 = Vector2f(1.5, 0);
		Vector2f v2 = Vector2f(4, 1);
		Vector2f sum = v1 + v2;
		EXPECT_EQ(sum.x, 5.5);
		EXPECT_EQ(sum.y, 1);
	}

	TEST(BasicMathTest, multVector2f) {
		Vector2f v1 = Vector2f(1.5, 1);
		int i = 3;
		Vector2f sum = v1 * i;
		EXPECT_EQ(sum.x, 4.5);
		EXPECT_EQ(sum.y, 3);
	}
	TEST(BasicMathTest, subVector2f) {
		Vector2f v1 = Vector2f(1.5, 0);
		Vector2f v2 = Vector2f(4, 1);
		Vector2f sum = v2 - v1;
		EXPECT_EQ(sum.x, 2.5);
		EXPECT_EQ(sum.y, 1);
	}
	TEST(BasicMathTest, divVector2f) {
		Vector2f v1 = Vector2f(8, 3);
		int sub = 2;
		Vector2f sum = v1 / sub;
		EXPECT_EQ(sum.x, 4);
		EXPECT_EQ(sum.y, 1.5);
	}
	TEST(BasicMathTest, eqVector2i) {
		Vector2i v1 = Vector2i(5, 2);
		Vector2i v2 = Vector2i(5, 2);
		bool eq = v1 == v2;
		EXPECT_EQ(eq, true);
	}
	TEST(BasicMathTest, neqXVector2i) {
		Vector2i v1 = Vector2i(5, 2);
		Vector2i v2 = Vector2i(15, 2);
		bool eq = v1 == v2;
		EXPECT_EQ(eq, false);
	}
	TEST(BasicMathTest, neqYVector2i) {
		Vector2i v1 = Vector2i(5, 2);
		Vector2i v2 = Vector2i(5, 20);
		bool eq = v1 == v2;
		EXPECT_EQ(eq, false);
	}
	TEST(BasicMathTest, addVector2i) {
		Vector2i v1 = Vector2i(5, 0);
		Vector2i v2 = Vector2i(4, 1);
		Vector2i sum = v1 + v2;
		EXPECT_EQ(sum.x, 9);
		EXPECT_EQ(sum.y, 1);
	}	
	TEST(BasicMathTest, multVector2i) {
		Vector2i v1 = Vector2i(5, 2);
		int i = 3;
		Vector2i sum = v1 * i;
		EXPECT_EQ(sum.x, 15);
		EXPECT_EQ(sum.y, 6);
	}

	TEST_F(ModelTest, testEnv) {
		EXPECT_EQ(m.getObjects().size(), 4);
	}

	TEST_F(ModelTest, addObjects) {
		EXPECT_EQ(obj1ID, 0);
		EXPECT_EQ(obj2ID, 1);
		EXPECT_EQ(obj3ID, 2);
		EXPECT_EQ(obj4ID, 3);
		GameObject* obj1 = m.getObjP(0);
		GameObject* obj2 = m.getObjP(1);
		GameObject* obj3 = m.getObjP(2);
		GameObject* obj4 = m.getObjP(3);
		EXPECT_EQ(obj1->getName(), "test1");
		EXPECT_EQ(obj2->getName(), "test2");
		EXPECT_EQ(obj3->getName(), "test3");
		EXPECT_EQ(obj4->getName(), "test4");
		EXPECT_EQ(obj1->getID(), obj1ID);
		EXPECT_EQ(obj2->getID(), obj2ID);
		EXPECT_EQ(obj3->getID(), obj3ID);
		EXPECT_EQ(obj4->getID(), obj4ID);
	}

	TEST_F(ModelTest, deleteObjects) {
		EXPECT_EQ(m.getSprites().size(),4);

		m.deleteObject(2);
		EXPECT_EQ(m.getSprites().size(), 3);
		m.deleteObject(0);
		EXPECT_EQ(m.getSprites().size(), 2);
	}

	TEST_F(ModelTest, findObjects) {
		int id = m.findObject("test4");
		EXPECT_EQ(id, 3);
	}

	TEST_F(ControllerTest, test1) {
		GameController gc(&m, &v);
		
		EXPECT_EQ(1, 1);
	}

