/*
 * union_find.h
 *
 *  Created on: Dec 24, 2014
 *      Author: alex
 */

#ifndef UNIONFIND_H_
#define UNIONFIND_H_

template<typename T, typename Compare>
class UnionFind {
	class Node;

	Node *tree;

	UnionFind(const UnionFind&);
	UnionFind& operator=(const UnionFind&);

public:
	UnionFind(int size);
	~UnionFind();

	const T& find(int i);
	void unite(int, int);
	int getRoot(int);
	const T& getMax(int);
};

template<typename T, typename Compare>
class UnionFind<T, Compare>::Node {
	int size;
	int parent;
	T data;
	int max;
};

#endif /* UNIONFIND_H_ */
