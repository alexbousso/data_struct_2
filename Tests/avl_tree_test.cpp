/*
 * avl_tree_test.cpp
 *
 *  Created on: Dec 26, 2014
 *      Author: Miri
 */

#include "../avl_tree.h"
#include "test_utils.h"
#include "assert.h"
#include <string>

std::string location;

class CompareInt {
public:
	int operator ()(int a, int b) const {
		return a - b;
	}
};


static void setUp(AVLTree<int, CompareInt>& tree) {
	tree.insert(4);
	tree.insert(5);
	tree.insert(2);
	tree.insert(3);
	tree.insert(1);
	tree.insert(6);

}

static void setUp2(AVLTree<int, CompareInt>& tree) {

	tree.insert(20);
	tree.insert(10);
	tree.insert(40);
	tree.insert(5);
	tree.insert(2);
	tree.insert(1);
	tree.insert(60);
	tree.insert(35);
	tree.insert(30);
}
static bool testAVLTreeInsert() {
	CompareInt func;
	AVLTree<int, CompareInt> tree(func);

	ASSERT_NO_THROW(tree.insert(10));
	ASSERT_EQUALS(1, tree.getWeight(10));
	ASSERT_NO_THROW(tree.insert(5));
	ASSERT_EQUALS(1, tree.getWeight(5));
	ASSERT_EQUALS(2, tree.getWeight(10));

	ASSERT_NO_THROW(tree.insert(20));
	ASSERT_EQUALS(1, tree.getWeight(20));
	ASSERT_EQUALS(3, tree.getWeight(10));

	ASSERT_NO_THROW(tree.insert(3));
	ASSERT_EQUALS(1, tree.getWeight(3));
	ASSERT_EQUALS(2, tree.getWeight(5));
	ASSERT_EQUALS(4, tree.getWeight(10));

	ASSERT_NO_THROW(tree.insert(1));
	ASSERT_EQUALS(1, tree.getWeight(1));
	ASSERT_EQUALS(1, tree.getWeight(5));
	ASSERT_EQUALS(3, tree.getWeight(3));
	ASSERT_EQUALS(5, tree.getWeight(10));

	ASSERT_NO_THROW(tree.insert(15));
	ASSERT_EQUALS(1, tree.getWeight(15));
	ASSERT_EQUALS(2, tree.getWeight(20));
	ASSERT_EQUALS(6, tree.getWeight(10));
	ASSERT_NOT_EQUALS(tree.getWeight(3), tree.getWeight(20));

	ASSERT_NO_THROW(tree.insert(17));
	ASSERT_EQUALS(1, tree.getWeight(15));
	ASSERT_EQUALS(1, tree.getWeight(20));
	ASSERT_EQUALS(3, tree.getWeight(17));
	ASSERT_EQUALS(7, tree.getWeight(10));

	ASSERT_NO_THROW(tree.insert(8));
	ASSERT_EQUALS(1, tree.getWeight(8));
	ASSERT_EQUALS(2, tree.getWeight(5));
	ASSERT_EQUALS(4, tree.getWeight(3));
	ASSERT_EQUALS(8, tree.getWeight(10));

	ASSERT_NO_THROW(tree.insert(7));
	ASSERT_EQUALS(1, tree.getWeight(8));
	ASSERT_EQUALS(1, tree.getWeight(5));
	ASSERT_EQUALS(3, tree.getWeight(7));
	ASSERT_EQUALS(5, tree.getWeight(3));
	ASSERT_EQUALS(9, tree.getWeight(10));

	ASSERT_NO_THROW(tree.insert(4));
	ASSERT_EQUALS(1, tree.getWeight(8));
	ASSERT_EQUALS(1, tree.getWeight(4));
	ASSERT_EQUALS(1, tree.getWeight(1));
	ASSERT_EQUALS(6, tree.getWeight(5));
	ASSERT_EQUALS(2, tree.getWeight(7));
	ASSERT_EQUALS(3, tree.getWeight(3));
	ASSERT_EQUALS(10, tree.getWeight(10));

	ASSERT_NO_THROW(tree.insert(9));
	ASSERT_EQUALS(3, tree.getWeight(8));
	ASSERT_EQUALS(1, tree.getWeight(7));
	ASSERT_EQUALS(7, tree.getWeight(5));
	ASSERT_EQUALS(11, tree.getWeight(10));

	return true;
}

static bool testAVLTreeRemove() {

	CompareInt func;
	AVLTree<int, CompareInt> tree(func);

	setUp(tree);

	ASSERT_EQUALS(1, tree.getWeight(3));
	ASSERT_NO_THROW(tree.remove(2));
	ASSERT_EQUALS(2, tree.getWeight(3));
	ASSERT_EQUALS(5, tree.getWeight(4));

	ASSERT_EQUALS(2, tree.getWeight(5));
	ASSERT_NO_THROW(tree.remove(4));
	ASSERT_EQUALS(4, tree.getWeight(5));

	AVLTree<int, CompareInt> tree2(func);
	setUp2(tree2);
	//tree2.printTree();

	ASSERT_EQUALS(1, tree2.getWeight(10));

	ASSERT_EQUALS(3, tree2.getWeight(20));
	ASSERT_EQUALS(6, tree2.getWeight(35));
	ASSERT_NO_THROW(tree2.remove(5));
	ASSERT_EQUALS(8, tree2.getWeight(10));
	ASSERT_EQUALS(2, tree2.getWeight(20));
	ASSERT_EQUALS(5, tree2.getWeight(35));

	ASSERT_NO_THROW(tree2.insert(37));
	ASSERT_EQUALS(3, tree2.getWeight(40));
	ASSERT_EQUALS(6, tree2.getWeight(35));
	ASSERT_EQUALS(9, tree2.getWeight(10));
	//tree2.printTree();

	ASSERT_NO_THROW(tree2.remove(30));
	ASSERT_EQUALS(1, tree2.getWeight(20));
	ASSERT_EQUALS(5, tree2.getWeight(35));
	ASSERT_EQUALS(8, tree2.getWeight(10));

	ASSERT_NO_THROW(tree2.remove(20));
	ASSERT_EQUALS(1, tree2.getWeight(37));
	ASSERT_EQUALS(2, tree2.getWeight(35));
	ASSERT_EQUALS(4, tree2.getWeight(40));
	ASSERT_EQUALS(7, tree2.getWeight(10));

	ASSERT_NO_THROW(tree2.insert(38));
	ASSERT_EQUALS(3, tree2.getWeight(37));
	ASSERT_EQUALS(1, tree2.getWeight(35));
	ASSERT_EQUALS(5, tree2.getWeight(40));
	ASSERT_EQUALS(8, tree2.getWeight(10));

	ASSERT_NO_THROW(tree2.insert(65));
	ASSERT_EQUALS(2, tree2.getWeight(60));
	ASSERT_EQUALS(6, tree2.getWeight(40));
	ASSERT_EQUALS(9, tree2.getWeight(10));

	ASSERT_NO_THROW(tree2.insert(20));
	//tree2.printTree();
	ASSERT_EQUALS(10, tree2.getWeight(37));
	ASSERT_EQUALS(2, tree2.getWeight(35));
	ASSERT_EQUALS(4, tree2.getWeight(40));
	ASSERT_EQUALS(5, tree2.getWeight(10));

	return true;
}

static bool testAVLTreeSelect() {

	CompareInt func;
	AVLTree<int, CompareInt> tree(func);

	setUp2(tree);

	ASSERT_EQUALS(35, tree.select(7));
	ASSERT_EQUALS(30, tree.select(6));
	ASSERT_EQUALS(40, tree.select(8));
	ASSERT_EQUALS(1, tree.select(1));
	ASSERT_THROWS(DataDoesNotExist, tree.select(tree.size() + 1));
	ASSERT_THROWS(DataDoesNotExist, tree.select(0));

	ASSERT_NO_THROW(tree.remove(35));
	ASSERT_EQUALS(40, tree.select(7));
	ASSERT_NO_THROW(tree.insert(25));
	ASSERT_NO_THROW(tree.insert(9));

	ASSERT_EQUALS(5, tree.select(3));
	ASSERT_EQUALS(9, tree.select(4));
	ASSERT_EQUALS(25, tree.select(7));
	ASSERT_EQUALS(40, tree.select(9));
	ASSERT_EQUALS(20, tree.select(6));
	ASSERT_EQUALS(60, tree.select(10));
	ASSERT_EQUALS(10, tree.select(5));
	ASSERT_EQUALS(30, tree.select(8));




	return true;
}

int main() {
	RUN_TEST(testAVLTreeInsert());
	RUN_TEST(testAVLTreeRemove());
	RUN_TEST(testAVLTreeSelect());

	return 0;
}

