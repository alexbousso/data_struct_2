#include "../hash_table.h"
#include "assert.h"
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

std::string location;

class Modulo {
	int n;

public:
	Modulo(int n) :
			n(n) {
	}

	int operator()(int num) {
		return num % n;
	}
};

static void setUp(HashTable<int, Modulo> &hashTable) {
	for (int i = 0; i <= 10000; i++) {
		hashTable.insert(i);
	}
}

static bool testRandom() {
	HashTable<int, Modulo> hashTable;

	srand(time(NULL));

	for (int i = 0; i < 100000; i++) {
		try {
			switch (rand() % 2) {
			case 0:
				hashTable.insert(rand() % 1000);
				break;
			case 1:
				hashTable.remove(rand() % 1000);
				break;
			}
		} catch (DataAlreadyExsists& e) {
		} catch (DataDoesNotExsist& e) {
		}
	}

	return true;
}

static bool testInsert() {
	HashTable<int, Modulo> hashTable;

	ASSERT_NO_THROW(hashTable.insert(5));
	ASSERT_DATA_ALREADY_EXISTS(hashTable.insert(5));

	ASSERT_NO_THROW(hashTable.insert(15));
	ASSERT_NO_THROW(hashTable.insert(13));
	ASSERT_NO_THROW(hashTable.insert(25));

	ASSERT_DATA_ALREADY_EXISTS(hashTable.insert(5));

	ASSERT_NO_THROW(hashTable.reset());

	setUp(hashTable);
	ASSERT_NO_THROW(hashTable.reset());

	return true;
}

static bool testRemove() {
	HashTable<int, Modulo> hashTable;

	ASSERT_DATA_DOES_NOT_EXIST(hashTable.remove(10));

	setUp(hashTable);

	ASSERT_NO_THROW(hashTable.remove(10));
	ASSERT_DATA_DOES_NOT_EXIST(hashTable.remove(10));
	ASSERT_NO_THROW(hashTable.insert(10));
	ASSERT_NO_THROW(hashTable.remove(10));

	return true;
}

int main() {
	RUN_TEST(testRandom());
	RUN_TEST(testInsert());
	RUN_TEST(testRemove());

	return 0;
}