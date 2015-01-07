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
#include "exceptions.h"#include "list.h"using std::cout;using std::endl;

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

	//returns a reference to the data of the i node
	T& getDataForChange(int i);

public:
	UnionFind(int size);
	~UnionFind();

	//return the index of the group containing i
	int find(int i);

	/*gets 2 groups (!!! roots!!!) and unites them by size,
	 * if the input aren't groups-InvalidInput is thrown
	 */
	void unite(int, int);

	//returns the max value in the tree (!!!!not assuming that the input is a root!!!!!)
	int getMaxIndex(int);

	//returns the data of the node in index i
	const T& getData(int i) const;

	//returns the index of the node who's the parent of the i node.
	int getParent(int i) const;

	/*returns the size of the tree who's root is the i node.
	 * (assuming it gets only roots!!!! cuz otherwise, -1 is returned)
	 */
	int getGroupSize(int i) const;

	/*updates element i.
	 * Func is a fanctor that gets T& and modifies the data.
	 * Func should have operator ()
	 */
	template<typename Func>
	void updateElement(int i, Func func);

	void printUF() const;
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

/**********************************************************
 * FUNCTIONS IMPLEMENTATION
 **********************************************************/


template<typename T, typename Compare>
UnionFind<T, Compare>::UnionFind(int size) :
		ufSize(size), route() {
	tree = new Node[size];

	for (int i = 0; i < size; i++) {
		tree[i].max = i;
	}

}

template<typename T, typename Compare>
UnionFind<T, Compare>::~UnionFind() {
	delete[] tree;
}
template<typename T, typename Compare>
int UnionFind<T, Compare>::find(int i) {

	if (i < 0 || i > ufSize - 1) {
		throw DataDoesNotExist();
	}
	//int i = index - 1;	//this is the index in the 0-based array!
	if (tree[i].parent == -1) {	//if you're a root

		if (route.size() > 0) {	//if there's more then 1 node in the search route
			for (List<int>::Iterator it = route.begin(); it != route.end();
					++it) { //let all the nodes in the route point to the root as their parent
				tree[*it].parent = i;

			}

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
void UnionFind<T, Compare>::printUF() const {
	cout << "\n";
	for (int i = 0; i < ufSize; i++) {
		cout << "index: ";
		cout.width(3);
		cout << i << " | data: " << tree[i].data << " | max: ";
		cout.width(3);
		cout << tree[i].max << " | parent: ";
		cout.width(3);
		cout << tree[i].parent << " | size: ";
		cout.width(3);
		cout << tree[i].size << "\n";
	}
}



template<typename T, typename Compare>
void UnionFind<T, Compare>::unite(int element1, int element2) {
	if (element1 < 0 || element1 > ufSize - 1 || element2 < 0
			|| element2 > ufSize - 1) {
		throw InvalidInput();
	}
	if(tree[find(element1)].max != element1
			|| tree[find(element2)].max != element2){
		throw Failure();
	}

	int root1 = find(element1), root2 = find(element2);
	if(root1 == root2){
		throw Failure();
	}
	//the groups are valid, so check which is the largest
	if (tree[root1].size >= tree[root2].size) { //if the first tree is larger (or equal)
		tree[root1].size += tree[root2].size; //let the sum of the sizes be the size of the root
		tree[root1].max =
				compare(tree[tree[root1].max].data, tree[tree[root2].max].data)
						> 0 ? tree[root1].max : tree[root2].max;
		//tree[group1].max >= tree[group2].max ?
		//tree[group1].max : tree[group2].max; //update the max of the united tree
		tree[root2].parent = root1;	//let the root be the parent
		tree[root2].size = -1;	//make the inner nodes' size irrelevant
	} else { //group2 is the larger, so it is the root
		tree[root2].size += tree[root1].size; //let the sum of the sizes be the size of the root
		tree[root2].max =
				compare(tree[tree[root1].max].data, tree[tree[root2].max].data)
						> 0 ? tree[root1].max : tree[root2].max;
		//tree[group1].max >= tree[group2].max ?
		//	tree[group1].max : tree[group2].max; //update the max of the united tree
		tree[root1].parent = root2;	//let the root be the parent
		tree[root1].size = -1;	//make the inner nodes' size irrelevant
	}
}

template<typename T, typename Compare>
int UnionFind<T, Compare>::getParent(int index) const {
	if (index < 0 || index > ufSize - 1) {
		throw DataDoesNotExist();
	}
	return tree[index].parent;

}

template<typename T, typename Compare>
int UnionFind<T, Compare>::getGroupSize(int index) const {
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

template<typename T, typename Compare>
template<typename Func>
void UnionFind<T, Compare>::updateElement(int i, Func func) {
	if (i < 0 || i >= ufSize) {
		throw DataDoesNotExist();
	}
	func(getDataForChange(i));
	int root = find(i);
	if (compare(tree[tree[root].max].data, tree[i].data) < 0) {//if the i element is larger then the max
		tree[root].max = i;	//let the max be i
	}
}

template<typename T, typename Compare>
T& UnionFind<T, Compare>::getDataForChange(int i) {
	if (i < 0 || i >= ufSize) {
		throw DataDoesNotExist();
	}
	return tree[i].data;
}

template<typename T, typename Compare>
const T& UnionFind<T, Compare>::getData(int i) const {
	return tree[i].data;
}
#endif /* UNIONFIND_H_ */
