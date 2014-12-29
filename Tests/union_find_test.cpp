/*
 * union_find_test.cpp
 *
 *  Created on: Dec 27, 2014
 *      Author: Miri
 */

#include "../union_find.h"
#include "test_utils.h"
//#include "assert.h"
#include <string>

std::string location;

class CompareInt {
public:
	int operator ()(int a, int b) const {
		return a - b;
	}
};

class IncreaseInt {
	int x;
public:
	IncreaseInt(int x) : x(x) {};
	void operator ()(int& y){
		y += x;
	}
};
/*
class Intiger{
	int id;
public:
	Intiger() : id(){}
};
*/

static bool testUnionFindFind(){

	UnionFind <int, CompareInt> uf(10);
	ASSERT_EQUALS(4, uf.find(4));
	ASSERT_THROWS(DataDoesNotExist, uf.find(10));

	ASSERT_NO_THROW(uf.unite(9, 8));
	//cout << "parent of 6 is: " << uf.getParent(6) << "\n";
	//cout << "parent of 9 is: " << uf.getParent(9) << "\n";
	ASSERT_NO_THROW(uf.unite(9, 6));
	ASSERT_EQUALS(9, uf.find(6));
	ASSERT_EQUALS(9, uf.find(9));
	ASSERT_EQUALS(9, uf.getParent(6));
	ASSERT_EQUALS(9, uf.getParent(8));

	ASSERT_NO_THROW(uf.unite(4, 0));
	ASSERT_NO_THROW(uf.unite(5, 1));
	ASSERT_NO_THROW(uf.unite(4, 5));
	ASSERT_EQUALS(4, uf.getParent(5));
	ASSERT_NO_THROW(uf.unite(2, 9));
	ASSERT_EQUALS(9, uf.getParent(2));

	ASSERT_NO_THROW(uf.unite(9, 5));
	ASSERT_NO_THROW(uf.find(1));
	ASSERT_EQUALS(9, uf.getParent(5));
	ASSERT_EQUALS(9, uf.getParent(4));
	ASSERT_EQUALS(9, uf.getParent(1));

	ASSERT_NO_THROW(uf.find(0));
	ASSERT_EQUALS(9, uf.getParent(0));

	return true;
}

static bool testUnionFindUnite(){

	UnionFind <int, CompareInt> uf(7);

	ASSERT_NO_THROW(uf.unite(2,3));
	ASSERT_EQUALS(2, uf.getParent(3));
	ASSERT_EQUALS(-1, uf.getParent(2));
	ASSERT_EQUALS(2, uf.getGroupSize(2));

	ASSERT_NO_THROW(uf.unite(4,5));
	ASSERT_EQUALS(2, uf.getGroupSize(4));
	ASSERT_EQUALS(5, uf.getMaxIndex(4));
	ASSERT_EQUALS(5, uf.getMaxIndex(5));

	ASSERT_THROWS(Failure, uf.unite(4, 1));	//4 isn't the max of it's tree
	ASSERT_THROWS(Failure, uf.unite(1, 2));	//2 isn't the max of it's tree
	ASSERT_THROWS(InvalidInput, uf.unite(10, 1));	//10>7=size
	ASSERT_THROWS(InvalidInput, uf.unite(1, 9));	//9>7=size

	ASSERT_NO_THROW(uf.unite(5, 1));
	ASSERT_EQUALS(5, uf.getMaxIndex(1));
	ASSERT_EQUALS(5, uf.getMaxIndex(4));
	ASSERT_EQUALS(5, uf.getMaxIndex(5));
	ASSERT_EQUALS(4, uf.getParent(1));
	ASSERT_EQUALS(-1, uf.getGroupSize(1));
	ASSERT_EQUALS(3, uf.getGroupSize(4));
	ASSERT_EQUALS(-1, uf.getParent(4));

	ASSERT_NO_THROW(uf.unite(3, 5));
	ASSERT_EQUALS(4, uf.getParent(2));
	//cout << "\n wanted print: \n";
	ASSERT_EQUALS(4, uf.find(3));
	//ASSERT_NO_THROW(uf.printUF());
	ASSERT_EQUALS(4, uf.getParent(3)); //check if after the previous find, the routes shrank
	ASSERT_EQUALS(5, uf.getMaxIndex(3));
	ASSERT_EQUALS(5, uf.getMaxIndex(2));
	ASSERT_EQUALS(5, uf.getMaxIndex(4));
	ASSERT_EQUALS(-1, uf.getGroupSize(2));


	return true;
}

static bool testUnionFindUpdateElement(){

	UnionFind <int, CompareInt> uf(10);
//	ASSERT_NO_THROW(uf.printUF());

	ASSERT_NO_THROW(uf.unite(4, 9));
	ASSERT_EQUALS(4, uf.getParent(9));
	ASSERT_EQUALS(9, uf.getMaxIndex(4));
	ASSERT_EQUALS(9, uf.getMaxIndex(9));

	ASSERT_NO_THROW(uf.unite(7, 8));
	ASSERT_EQUALS(8, uf.getMaxIndex(7));
	ASSERT_NO_THROW(uf.unite(6, 1));
	ASSERT_EQUALS(6, uf.getMaxIndex(1));
	//uf.printUF();
	ASSERT_NO_THROW(uf.unite(8, 6));
	//cout << "after unite: \n";

	ASSERT_EQUALS(8, uf.getMaxIndex(1));
	ASSERT_EQUALS(8, uf.getMaxIndex(6));
	ASSERT_EQUALS(-1, uf.getGroupSize(6));
	ASSERT_EQUALS(7, uf.getParent(6));
	ASSERT_EQUALS(4, uf.getGroupSize(7));

	ASSERT_NO_THROW(uf.updateElement(1, IncreaseInt(20)));
	ASSERT_EQUALS(1, uf.getMaxIndex(7));

	ASSERT_NO_THROW(uf.unite(9, 1));
	ASSERT_EQUALS(7, uf.getParent(4));
	ASSERT_EQUALS(6, uf.getGroupSize(7));

	ASSERT_NO_THROW(uf.updateElement(9, IncreaseInt(30)));
	ASSERT_EQUALS(39, uf.getData(9));
	ASSERT_EQUALS(9, uf.getMaxIndex(7));
	ASSERT_EQUALS(9, uf.getMaxIndex(1));

	return true;
}

int main(){

	RUN_TEST(testUnionFindFind());
	RUN_TEST(testUnionFindUnite());
	RUN_TEST(testUnionFindUpdateElement());

	return 0;
}
