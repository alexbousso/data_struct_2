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
/*
class Intiger{
	int id;
public:
	Intiger() : id(){}
};
*/

static bool testUnionFindFind(){

	UnionFind <int, CompareInt> uf(10);
//	ASSERT_NO_THROW(uf.printUF());
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

	ASSERT_NO_THROW(uf.unite(9, 4));
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

	ASSERT_THROWS(InvalidInput, uf.unite(5, 1));	//5 isn't a root
	ASSERT_THROWS(InvalidInput, uf.unite(10, 1));	//10>7=size
	ASSERT_THROWS(InvalidInput, uf.unite(1, 9));	//9>7=size

	ASSERT_NO_THROW(uf.unite(4, 1));
	ASSERT_EQUALS(5, uf.getMaxIndex(1));
	ASSERT_EQUALS(5, uf.getMaxIndex(4));
	ASSERT_EQUALS(5, uf.getMaxIndex(5));
	ASSERT_EQUALS(4, uf.getParent(1));
	ASSERT_EQUALS(-1, uf.getGroupSize(1));
	ASSERT_EQUALS(3, uf.getGroupSize(4));
	ASSERT_EQUALS(-1, uf.getParent(4));

	ASSERT_NO_THROW(uf.unite(2, 4));
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

int main(){

	RUN_TEST(testUnionFindFind());
	RUN_TEST(testUnionFindUnite());

	return 0;
}
