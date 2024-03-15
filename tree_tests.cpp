#include <gtest/gtest.h>
#include "tree_list.cpp"
#include <stdexcept>
#include <iostream>

using namespace trees;
using namespace std;

TEST(SetTest, constructor) {
	Set<int> x;
	x.insert(5);
	x.insert(6);
	x.insert(1);
	x.insert(2);
	x.insert(70);
	x.print();
}

TEST(SetTest, insertTest) {
	Set<int> x;
	bool a = x.insert(55);
	EXPECT_EQ(a, true);
}

TEST(SetTest, insertTest2) {
	Set<int> x;
	x.insert(55);
	bool a = x.insert(55);
	EXPECT_EQ(a, false);
}

TEST(SetTest, coontainsTest) {
	Set<int> x;
	x.insert(5);
	x.insert(6);
	x.insert(1);
	x.insert(2);
	x.insert(70);
	bool a = x.contains(1);
	EXPECT_EQ(a, true);
}

TEST(SetTest, coontainsTest2) {
	Set<int> x;
	x.insert(5);
	x.insert(6);
	x.insert(1);
	x.insert(2);
	x.insert(70);
	bool a = x.contains(-1);
	EXPECT_EQ(a, false);
}

TEST(SetTest, eraseTest) {
	Set<int> x;
	x.insert(5);
	x.insert(6);
	x.insert(1);
	x.insert(2);
	x.insert(70);
	bool a = x.erase(1);
	x.print();
	EXPECT_EQ(a, true);
}

TEST(SetTest, eraseTest2) {
	Set<int> x;
	x.insert(5);
	x.insert(6);
	x.insert(1);
	x.insert(2);
	x.insert(70);
	bool a = x.erase(12);
	x.print();
	EXPECT_EQ(a, false);
}
