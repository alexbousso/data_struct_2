/*
 * union_find.h
 *
 *  Created on: Dec 24, 2014
 *      Author: alex
 */

#ifndef UNIONFIND_H_
#define UNIONFIND_H_

#include <cassert>
#include <iostream>
#include <typeinfo>	//TODO remove this' it's only needed for the tests!!!#include "exceptions.h"#include "list.h"
using std::cout;
using std::endl;

template<typename T, typename Compare>
class UnionFind {
	class Node;

	Node *tree;
	int ufSize;
	Compare compare;
	//a list used for route shrinking
	List<int> route;

	UnionFind(const UnionFind&);
	UnionFind& operator=(const UnionFind&);

public:
	UnionFind(int size);
	~UnionFind() {
	} //TODO implement!!

	//return the index of the group containing i
	int find(int i);

	//gets 2 groups (!!! roots!!!) and unites them by size, if the input aren't groups-InvalidInput is thrown
	void unite(int, int);

	//int getRoot(int); TODO check if this is relevant now that we know that the find does that!

	//returns the max value in the tree (!!!!not assuming that the input is a root!!!!!)
	int getMaxIndex(int);

	//returns the data of the node in index i
	const T& getData(int i);

	//returns the index of the node who's the parent of the i node.
	int getParent(int i);

	//returns the size of the tree who's root is the i node. (assuming it gets only roots!!!! cuz otherwise, -1 is returned)
	int getGroupSize(int i);

	void printUF();
};

/*every node starts like this: the node is it's own max, every node is of size 1
 * every nodes' parent is -1.
 * an inner node has a parent (0=<parent value=<ufSize-1)
 *  and the value of the max in it is irrelevant. the value of size is -1.
 * a node that represents a root, has no parent: parent value is -1
 * and it's max value is the max of the whole tree (meaning-it's relevant).
 * the value of size in a root should be > 0
 */
template<typename T, typename Compare>
class UnionFind<T, Compare>::Node {
	friend class UnionFind;
	int size;
	int parent;
	T data;
	int max;

public:
	Node() :
			size(1), parent(-1), data(), max(-1) {
	}
};

/**************************************************
 * FUNCTIONS IMPLEMENTATION
 **************************************************/
//TODO remove the part with the int!!!!!
template<typename T, typename Compare>
UnionFind<T, Compare>::UnionFind(int size) :
		ufSize(size), route() {
	tree = new Node[size];
	if (typeid(T) == typeid(size)) {
		//cout << "it's int\n";
		for (int i = 0; i < size; i++) {
			tree[i].data = i;
		}
	}
	for (int i = 0; i < size; i++) {
		tree[i].max = i;
	}

}

template<typename T, typename Compare>
int UnionFind<T, Compare>::find(int i) {

	if (i < 0 || i > ufSize - 1) {
		throw DataDoesNotExist();
	}
	//int i = index - 1;	//this is the index in the 0-based array!
	if (tree[i].parent == -1) {	//if you're a root
		//assert(tree[i].parent == -1);	//it means you don't have a parent
		//cout << "list size is: " << route.size() << "\n";	//TODO remove!
		if (route.size() > 0) {	//if there's more then 1 node in the search route
			for (List<int>::Iterator it = route.begin(); it != route.end();
					++it) { //let all the nodes in the route point to the root as their parent
				tree[*it].parent = i;
				//cout << *it << "->" << i << " | "; //TODO remove!
			}
			//cout << "\n"; //TODO remove!
		}
		route.reset();
		assert(route.size() == 0);
		return i;
	}
	assert(tree[i].size == -1); //else: you are an inner node' you don't have a size
	route.pushFront(i);
	//cout << "current is: " << i << ", going to parent: " << tree[i].parent << "\n";
	return find(tree[i].parent);
}

template<typename T, typename Compare>
void UnionFind<T, Compare>::printUF() {
	cout << "\n";
	for (int i = 0; i < ufSize; i++) {
		cout << "index: " << i << " | data: " << tree[i].data << " | max: "
				<< tree[i].max << " | parent: " << tree[i].parent << " | size: "
				<< tree[i].size << "\n";
	}
}

template<typename T, typename Compare>
void UnionFind<T, Compare>::unite(int group1, int group2) {
	if (group1 < 0 || group1 > ufSize - 1 || group2 < 0 || group2 > ufSize - 1
			|| tree[group1].parent != -1 || tree[group2].parent != -1) {
		throw InvalidInput();
	}
	//the groups are valid, so check which is the largest
	if (tree[group1].size >= tree[group2].size) { //if the first tree is larger (or equal)
		tree[group1].size += tree[group2].size; //let the sum of the sizes be the size of the root
		tree[group1].max =
				compare(tree[tree[group1].max].data,
						tree[tree[group2].max].data) > 0 ?
						tree[group1].max : tree[group2].max;
		//tree[group1].max >= tree[group2].max ?
		//tree[group1].max : tree[group2].max; //update the max of the united tree
		tree[group2].parent = group1;	//let the root be the parent
		tree[group2].size = -1;	//make the inner nodes' size irrelevant
	} else { //group2 is the larger, so it is the root
		tree[group2].size += tree[group1].size; //let the sum of the sizes be the size of the root
		tree[group2].max =
				compare(tree[tree[group1].max].data,
						tree[tree[group2].max].data) > 0 ?
						tree[group1].max : tree[group2].max;
		//tree[group1].max >= tree[group2].max ?
		//	tree[group1].max : tree[group2].max; //update the max of the united tree
		tree[group1].parent = group2;	//let the root be the parent
		tree[group1].size = -1;	//make the inner nodes' size irrelevant
	}
}

template<typename T, typename Compare>
int UnionFind<T, Compare>::getParent(int index) {
	if (index < 0 || index > ufSize - 1) {
		throw DataDoesNotExist();
	}
	return tree[index].parent;

}

template<typename T, typename Compare>
int UnionFind<T, Compare>::getGroupSize(int index) {
	if (index < 0 || index > ufSize - 1) {
		throw DataDoesNotExist();
	}
	return tree[index].size;

}

template<typename T, typename Compare>
int UnionFind<T, Compare>::getMaxIndex(int index) {
	if (index < 0 || index > ufSize - 1) {
		throw DataDoesNotExist();
	}
	int rootIndex = find(index);
	return tree[rootIndex].max;

}

#endif /* UNIONFIND_H_ */
