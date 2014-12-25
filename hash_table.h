/*
 * hash_table.h
 *
 *  Created on: Dec 24, 2014
 *      Author: alex
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "list.h"
#include "exceptions.h"
#include <cassert>

/**
 * TODO: Explain in a better way.
 *
 * The HashFunction needs to have a constructor with one argument, witch
 * receives an integer that delimits the spread of the array that contains the
 * data and a function with the following title:
 * 		int operator()(T);
 * that returns the index that is desired to insert the data.
 */
template<typename T, typename HashFunction>
class HashTable {
public:
	HashTable();
	~HashTable();

	// TODO: Documentation
	void insert(T data);
	void remove(T data);
	bool find(T data);

private:
	/**
	 * The maximum load factor is defined as the maximum value of:
	 * 		(the number of elements in use) / (the size of the table)
	 *
	 * In the case of this class:
	 * 		LOAD_FACTOR = max(numberOfElements / tableSize)
	 */
	static const int MAXIMUM_LOAD_FACTOR = 10;

	/**
	 * The minimum load factor is symmetric to MAXIMUM_LOAD_FACTOR, but defines
	 * the minimum value of:
	 * 		(the number of elements in use) / (the size of the table)
	 *
	 * In the case of this class:
	 * 		LOAD_FACTOR = min(numberOfElements / tableSize)
	 */
	static const int MINIMUM_LOAD_FACTOR = 2;

	/**
	 * The multiply factor defines the size of the new array of lists in case
	 * of overloading of the table.
	 * If the load is greater than MAXIMUM_LOAD_FACTOR or smaller than
	 * MINIMUM_LOAD_FACTOR, then the new size of the array
	 * *table will be:
	 * 		tableSize * MAXIMUM_LOAD_FACTOR
	 * or
	 * 		tableSize / MINIMUM_LOAD_FACTOR
	 * accordingly.
	 */
	static const int MULTIPLY_FACTOR = 2;

	/**
	 * The initial size of the table.
	 */
	static const int INITIAL_TABLE_SIZE = 10;

	List<T> *table;
	int numberOfElements;
	int tableSize;
	HashFunction index;

	/**
	 * Check the load of the table and, if required, changes the size of the
	 * array *table.
	 */
	void checkLoad();

	// TODO: Documentation
	void enlargeTable();
	void shrinkTable();
	void copyTableTo(List<T>*, int size) const;

	/**
	 * Checks if the sum of sizes of every list is equal to 'numberOfElements'.
	 */
	bool checkHashTable() const;
};

template<typename T, typename HashFunction>
inline HashTable<T, HashFunction>::HashTable() :
		table(new List<T> [INITIAL_TABLE_SIZE]), numberOfElements(0), tableSize(
				INITIAL_TABLE_SIZE), index(INITIAL_TABLE_SIZE) {
}

template<typename T, typename HashFunction>
inline HashTable<T, HashFunction>::~HashTable() {
	assert(checkHashTable());
	delete[] table;
}

template<typename T, typename HashFunction>
inline void HashTable<T, HashFunction>::insert(T data) {
	if (find(data)) {
		throw DataAlreadyExsists();
	}
	table[index(data)].pushFront(data);
	numberOfElements++;
	checkLoad();
}

template<typename T, typename HashFunction>
void HashTable<T, HashFunction>::remove(T data) {
	if (!find(data)) {
		throw DataDoesNotExsist();
	}
	assert(numberOfElements > 0);
	for (typename List<T>::Iterator it(table[index(data)].begin());
			it != table[index(data)].end(); ++it) {
		if (*it == data) {
			table[index(data)].remove(it);
			numberOfElements--;
			break;
		}
	}
	checkLoad();
}

template<typename T, typename HashFunction>
inline void HashTable<T, HashFunction>::checkLoad() {
	assert(checkHashTable());
	if (numberOfElements / tableSize > MAXIMUM_LOAD_FACTOR) {
		enlargeTable();
	} else if (numberOfElements / tableSize < MINIMUM_LOAD_FACTOR) {
		shrinkTable();
	}
	index = HashFunction(tableSize);
}

template<typename T, typename HashFunction>
void HashTable<T, HashFunction>::enlargeTable() {
	List<T> *newTable(new List<T> [tableSize * MULTIPLY_FACTOR]);
	copyTableTo(newTable, tableSize * MULTIPLY_FACTOR);
	tableSize *= MULTIPLY_FACTOR;
	delete[] table;
	table = newTable;
}

template<typename T, typename HashFunction>
void HashTable<T, HashFunction>::shrinkTable() {
	if (tableSize > INITIAL_TABLE_SIZE) {
		List<T> *newTable(new List<T> [tableSize / MULTIPLY_FACTOR]);
		copyTableTo(newTable, tableSize / MULTIPLY_FACTOR);
		tableSize /= MULTIPLY_FACTOR;
		delete[] table;
		table = newTable;
	}
}

template<typename T, typename HashFunction>
inline void HashTable<T, HashFunction>::copyTableTo(List<T> *copy,
		int size) const {
	for (int i = 0; i < tableSize; i++) {
		for (typename List<T>::Iterator it(table[i].begin());
				it != table[i].end(); ++it) {
			copy[*it % size].pushFront(*it);
		}
	}
}

template<typename T, typename HashFunction>
bool HashTable<T, HashFunction>::checkHashTable() const {
	int sum(0);
	for (int i = 0; i < tableSize; i++) {
		sum += table[i].size();
	}
	return sum == numberOfElements;
}

#endif /* HASHTABLE_H_ */

