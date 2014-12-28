/*
 * avl_tree.h
 *
 *  Created on: Nov 15, 2014
 *      Author: Miri
 */

#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <iostream>
#include "exceptions.h"
#include <cassert>

using std::cout;
using std::endl;

template<typename T, class Compare>
class AVLTree {

	class AVLNode;
	AVLNode* root;
	int treeSize;
	Compare compare;
	AVLNode* max;

	class CheckRoot;
	class PrintSubTree;
	class CopyTree;

	//inserting a new object to the tree under a specific root
	void insert(AVLNode*, const T&);

	/*searching for an object in a specific sub tree, if the int is 1,
	 it means the find should substruct 1 from the weight of every node in the search path
	 cuz it's a removal find. else: do a regular find
	 */
	AVLNode* find(AVLNode*, const T&, int) const;

	//removing an object from a specific subtree
	void remove(AVLNode*);

	//in case of removing a node with a single child' use this function
	void removeSingleChild(AVLNode*);

	//calculates the bf of a single node
	int calcBF(AVLNode*);

	//updates the BF after removing an item from the tree
	void updateBFAfterRemove(AVLNode*);

	//returns the max from a tree with a specific root
	T getMax(AVLNode*);

	//sets the max of the tree to be the rightmost node
	void setMax(AVLNode*);

	//returns the min from a tree with a specific root
	T getMin(AVLNode*);

	//returns the min from a tree with a specific root
	int calcWeight(AVLNode*);

	//pre-order walk
	template<typename Function>
	void preOrder(AVLNode*, Function) const;

	//in-order walk
	template<typename Function>
	void inOrder(AVLNode*, Function&);

	//in-order walk operating on the node
	template<typename Function>
	void postOrderNode(AVLNode*, Function);

	//rotating right
	void rotateRight(AVLNode*);

	//rotating left
	void rotateLeft(AVLNode*);

	//rotating RL
	void rotateRL(AVLNode*);

	//rotating LR
	void rotateLR(AVLNode*);

	//rotating LL
	void rotateLL(AVLNode*);

	//rotating RR
	void rotateRR(AVLNode*);

	//updating all the heights in a subtree
	void updateHight(AVLNode*, AVLNode*);

	//updating the weight of all the nodes in a subtree
	void updateWeight(AVLNode*, AVLNode*);

	//finding the next node with bad BF
	AVLNode* findBadBF(AVLNode*);

	//update balance factor of the first broken node from a specific start point
	AVLNode* updateBF(AVLNode*);

	//recursivly looking for the k-th node
	T select(AVLNode*, int);

	class DeleteNode {
	public:
		void operator()(AVLNode* node) {
			delete (node);
		}
	};

public:
	AVLTree() :
			root(NULL), treeSize(0), compare(), max(NULL) {
	}
	AVLTree(Compare func) :
			root(NULL), treeSize(0), compare(func), max(NULL) {
	}

	AVLTree operator=(const AVLTree&);
	~AVLTree();

	//inserting a new object to the tree
	void insert(const T&);

	//removing an object from the tree
	void remove(const T&);

	//finding a specific object in the tree
	T find(const T&) const;

	//returns a copy of a specific object in the tree
	T getData(const T& element) const {
		//T toReturn = find(element);
		return find(element);
	}

	//returning the current size of the tree
	int size() const;

	//prints the whole tree
	void printTree() const;

	//check tree correctness
	bool checkTree();

	//returns the max element in the tree
	T getMax();

	//returns the min element in the tree
	T getMin();

	//returns the weight of a node
	int getWeight(const T&);

	//finds and returns a copy of the data in the k-th node
	T select(int);

	//in-order walk
	template<typename Function>
	void inOrder(Function&);

	//returns bool if an element is in the tree or not
	bool findIsIn(T&);

	//activates the tree's comparison function
	int compareElements(const T&, const T&);
};

template<typename T, class Compare>
inline int AVLTree<T, Compare>::compareElements(const T& element1,
		const T& element2) {
	return compare(element1, element2);
}

template<typename T, class Compare>
class AVLTree<T, Compare>::AVLNode {
	T data;
	AVLNode* left;
	AVLNode* right;
	AVLNode* dad;
	int hight;
	int weight;
	friend class AVLTree;
	friend class Iterator;

	AVLNode(T data) :
			data(data), left(NULL), right(NULL), dad(NULL), hight(0), weight(1) {
	}
	AVLNode(const AVLNode&);
	AVLNode operator=(const AVLNode&);
};

/******************************
 * Functions and Classes Implementation
 ******************************/

template<typename T, class Compare>
class AVLTree<T, Compare>::CopyTree {
	AVLTree<T, Compare> copy;
public:
	CopyTree(AVLTree<T, Compare> tree) :
			copy(tree) {
	}
	void operator()(AVLNode* newNode) {
		copy.insert(newNode->data);
	}
};

template<typename T, class Compare>
AVLTree<T, Compare>::~AVLTree() {
	DeleteNode deleter;
	postOrderNode(root, deleter);
}

/*
 template<typename T, class Compare>
 AVLTree<T, Compare>::AVLTree(const AVLTree& src){
 AVLTree<T, Compare> newTree(src.compare);
 CopyTree copier(newTree);

 preOrder(newTree->root, copier);
 return newTree;
 }
 */
template<typename T, class Compare>
void AVLTree<T, Compare>::insert(const T& element) {

	if (root == NULL) {
		root = new AVLNode(element);
		treeSize++;
	} else {
		insert(root, element);
	}
	setMax(root);
}

template<typename T, class Compare>
void AVLTree<T, Compare>::insert(AVLTree<T, Compare>::AVLNode* currentRoot,
		const T& element) {

	if (compare(element, currentRoot->data) > 0) { //if the data is larger then the roots'
		if (currentRoot->right == NULL) {		//check if the right son is free
			currentRoot->right = new AVLNode(element); //if it is, then set the right son to be the new node
			currentRoot->right->dad = currentRoot;
			currentRoot->weight += 1; //TODO check if i should be here!!! could cause bugs!!!
			treeSize++;
			updateHight(currentRoot, root);
			//updateWeight(currentRoot, root);//update the weight of all nodes in the insert route
			updateBF(currentRoot);
			updateHight(currentRoot, root);	//after the rolls, update heights again
			if (currentRoot->right != NULL) {//fix the weight of the right son if it exists
				updateWeight(currentRoot->right, currentRoot->right);
			}
			if (currentRoot->left != NULL) {//fix the weight of the left son if it exists
				updateWeight(currentRoot->left, currentRoot->left);
			}
			updateWeight(currentRoot, currentRoot);
			return;
		}
		currentRoot->weight += 1;
		return insert(currentRoot->right, element);	//if it isn't, look for a space in the right subtree
	}
	if (compare(element, currentRoot->data) < 0) {//if the data is smaller then the roots'
		if (currentRoot->left == NULL) {		//check if the left son is free
			currentRoot->left = new AVLNode(element); //if it is, then set the left son to be the new node
			currentRoot->left->dad = currentRoot;
			treeSize++;
			currentRoot->weight += 1; //TODO check if i should be here!!! could cause bugs!!!
			updateHight(currentRoot, root);
			//updateWeight(currentRoot, root);//update the weight of all nodes in the insert route
			updateBF(currentRoot);
			updateHight(currentRoot, root);	//after the rolls, update heights again
			if (currentRoot->right != NULL) {//fix the weight of the right son if it exists
				updateWeight(currentRoot->right, currentRoot->right);
			}
			if (currentRoot->left != NULL) {//fix the weight of the left son if it exists
				updateWeight(currentRoot->left, currentRoot->left);
			}
			updateWeight(currentRoot, currentRoot);
			return;
		}
		currentRoot->weight += 1;
		return insert(currentRoot->left, element);//if it isn't, look for a space in the left subtree
	}
	throw DataAlreadyExists();
}

template<typename T, class Compare>
T AVLTree<T, Compare>::find(const T& element) const {
	if (root == NULL) {
		throw DataDoesNotExist();
	}
	return (find(root, element, 0))->data;
}

template<typename T, class Compare>
typename AVLTree<T, Compare>::AVLNode* AVLTree<T, Compare>::find(
		AVLTree<T, Compare>::AVLNode* currentRoot, const T& element,
		int removeFind) const {
	if (currentRoot == NULL) {
		throw DataDoesNotExist();
	}
	if (compare(element, currentRoot->data) == 0) { //if it's the same object
		return currentRoot;
	}
	if (compare(currentRoot->data, element) < 0) { //if the current is smaller, go to the right subtree
		if (removeFind == 1) { //if it's a removal find, substruct 1 from the currentRoot
			currentRoot->weight -= 1;
		}
		return find(currentRoot->right, element, removeFind);
	}
	if (removeFind == 1) { //if it's a removal find, substruct 1 from the currentRoot
		currentRoot->weight -= 1;
	}
	return find(currentRoot->left, element, removeFind); //else: the current is larger-search the left subtree

}

template<typename T, class Compare>
inline int AVLTree<T, Compare>::size() const {
	return treeSize;
}

template<typename T, class Compare>
void AVLTree<T, Compare>::rotateRight(
		AVLTree<T, Compare>::AVLNode* currentRoot) {
	if (currentRoot == NULL) {
		throw InvalidInput();
	}
	currentRoot = currentRoot->left;
	currentRoot->dad->left = currentRoot->right;
	if (currentRoot->right != NULL) {
		currentRoot->right->dad = currentRoot->dad;
	}
	currentRoot->right = currentRoot->dad;
	currentRoot->dad = currentRoot->right->dad;
	currentRoot->right->dad = currentRoot;

	if (currentRoot->dad != NULL) {	//if there's a dad
		if (currentRoot->dad->right == currentRoot->right) {//check if we just switched the dad's right son
			currentRoot->dad->right = currentRoot;
		} else {	//we must have switched the dads' left son
			assert(
					compare(currentRoot->dad->left->data,
							currentRoot->right->data) == 0);
			currentRoot->dad->left = currentRoot;
		}
	}
	updateWeight(currentRoot->right, currentRoot);
}

template<typename T, class Compare>
void AVLTree<T, Compare>::rotateLeft(
		AVLTree<T, Compare>::AVLNode* currentRoot) {
	if (currentRoot == NULL) {
		throw InvalidInput();
	}
	currentRoot = currentRoot->right;
	currentRoot->dad->right = currentRoot->left;
	if (currentRoot->left != NULL) {
		currentRoot->left->dad = currentRoot->dad;
	}
	currentRoot->left = currentRoot->dad;

	currentRoot->dad = currentRoot->left->dad;

	currentRoot->left->dad = currentRoot;

	if (currentRoot->dad != NULL) {	//if there's a dad
		if (currentRoot->dad->right == currentRoot->left) {	//check if we just switched the dad's right son
			currentRoot->dad->right = currentRoot;
		} else {	//we must have switched the dads' left son
			assert(currentRoot->dad->left == currentRoot->left);
			currentRoot->dad->left = currentRoot;
		}
	}
	updateWeight(currentRoot->left, currentRoot);
}

template<typename T, class Compare>
void AVLTree<T, Compare>::rotateRL(AVLTree<T, Compare>::AVLNode* currentRoot) {
	rotateRight(currentRoot->right);
	updateHight(currentRoot->right->right, currentRoot->right);
	rotateLeft(currentRoot);
	if (currentRoot == root) {
		root = currentRoot->dad;
	}
}

template<typename T, class Compare>
void AVLTree<T, Compare>::rotateLR(AVLTree<T, Compare>::AVLNode* currentRoot) {
	rotateLeft(currentRoot->left);
	updateHight(currentRoot->left->left, currentRoot);
	rotateRight(currentRoot);
	if (currentRoot == root) {
		root = currentRoot->dad;
	}
}

template<typename T, class Compare>
void AVLTree<T, Compare>::rotateLL(AVLTree<T, Compare>::AVLNode* currentRoot) {
	rotateRight(currentRoot);
	if (currentRoot == root) {
		root = currentRoot->dad;
	}
}

template<typename T, class Compare>
void AVLTree<T, Compare>::rotateRR(AVLTree<T, Compare>::AVLNode* currentRoot) {
	rotateLeft(currentRoot);
	if (currentRoot == root) {
		root = currentRoot->dad;
	}
}

template<typename T, class Compare>
void AVLTree<T, Compare>::removeSingleChild(
		AVLTree<T, Compare>::AVLNode* currentRoot) {
	if (currentRoot->left != NULL && currentRoot->right == NULL) { //if current has only a left child
		if (currentRoot == root) { //if current is the root of the tree then let the current's left child become the root
			root = currentRoot->left;
			root->dad = NULL;
			currentRoot->dad = root; //this is just for the later heights update
		} else {	//if it isn't the root:
			if (compare(currentRoot->dad->left->data, currentRoot->data) == 0) { //if current is it's dads' left child
				currentRoot->dad->left = currentRoot->left;
				currentRoot->left->dad = currentRoot->dad;
			} else {					//else-current is it's dads right child
				currentRoot->dad->right = currentRoot->left;
				currentRoot->left->dad = currentRoot->dad;
			}
		}
	} else {	//else-current has only a right child (or no children at all)
		if (currentRoot == root) {	//if current is the rot of the tree
			root = currentRoot->right;
			root->dad = NULL;
			currentRoot->dad = root;//this is just for the later heights update
		} else {	//if it isn't the root
			if (compare(currentRoot->dad->left->data, currentRoot->data) == 0) {//if current is it's dads' left child
				currentRoot->dad->left = currentRoot->right;
				if (currentRoot->right != NULL) {
					currentRoot->right->dad = currentRoot->dad;
				}
			} else {					//else-current is it's dads right child
				currentRoot->dad->right = currentRoot->right;
				if (currentRoot->right != NULL) {
					currentRoot->right->dad = currentRoot->dad;
				}
			}
		}
	}
	updateHight(currentRoot->dad, currentRoot->dad);
	updateBFAfterRemove(currentRoot->dad);
	updateWeight(currentRoot->dad, root);
	delete (currentRoot);
}

template<typename T, class Compare>
bool AVLTree<T, Compare>::findIsIn(T& element) {
	try {
		find(element);
	} catch (DataDoesNotExist& noData) {
		return false;
	}
	return true;
}

template<typename T, class Compare>
void AVLTree<T, Compare>::remove(AVLTree<T, Compare>::AVLNode* currentRoot) {
	if (currentRoot == NULL) {
		throw DataDoesNotExist();
	}

	if (currentRoot->left == NULL && currentRoot->right == NULL) {//if current has no offsprings -leaf
		AVLNode* tempDad = currentRoot->dad;
		if (tempDad == NULL) {					//if wer'e at the root:
			delete (currentRoot);
			root = NULL;
			return;
		}
		if (tempDad->right == currentRoot) {//if current is it's dads right son.
			tempDad->right = NULL;
		} else {		//current is it's dads left son
			assert(tempDad->left == currentRoot);

			tempDad->left = NULL;
		}
		delete (currentRoot);
		updateHight(tempDad, root);
		updateBFAfterRemove(tempDad);
		return;
	}
	if ((currentRoot->left != NULL && currentRoot->right == NULL)
			|| (currentRoot->right != NULL && currentRoot->left == NULL)) {	//if current has only one child

		removeSingleChild(currentRoot);

	} else {								//current has both children

		assert(currentRoot->left != NULL && currentRoot->right != NULL);

		AVLNode* successor = currentRoot->right;
		while (successor->left != NULL) {		//find the successor
			successor = successor->left;
		}
		currentRoot->data = successor->data;	//swap data
		removeSingleChild(successor);
	}
}

template<typename T, class Compare>
void AVLTree<T, Compare>::remove(const T& element) {
	AVLNode* toRemove = find(root, element, 1);
	remove(toRemove);
	treeSize--;
	if (treeSize != 0) {
		assert(root != NULL);
		setMax(root);
	}
}

template<typename T, class Compare>
void AVLTree<T, Compare>::updateHight(AVLTree<T, Compare>::AVLNode* start,
		AVLTree<T, Compare>::AVLNode* end) {
	int lH = start->left == NULL ? -1 : start->left->hight, rH =//calc the subtrees heights
			start->right == NULL ? -1 : start->right->hight;

	if (start == end) {						//if we are at the root/stop point
		end->hight = 1 + (lH > rH ? lH : rH);
		return;
	}
	start->hight = 1 + (lH > rH ? lH : rH);	//take the max between both subs and add 1
	updateHight(start->dad, end);		//update the rest of the tree
}

template<typename T, class Compare>
typename AVLTree<T, Compare>::AVLNode* AVLTree<T, Compare>::updateBF(
		AVLTree<T, Compare>::AVLNode* start) {

	AVLNode* toFix = findBadBF(start);
	if (toFix == NULL) {
		return NULL;
	}

	int bf = calcBF(toFix);				//calc the BF
	if (bf > 1) {					//if the left side is heavier
		if (calcBF(toFix->left) >= 0) {	//if in the left subtree-the left side is heavier
			assert(bf >= 2);
			rotateLL(toFix);
		} else {	//if in the left subtree-the right side is heavier
			assert(bf >= 2);
			rotateLR(toFix);
		}
	}
	if (bf < -1) {						//if the right subtree is heavier
		if (calcBF(toFix->right) <= 0) {//if in the right subtree- the right side  is heavier
			assert(bf <= -2);
			rotateRR(toFix);
		} else {	//if in the right subtree- the left side  is heavier
			assert(bf <= -2);
			rotateRL(toFix);
		}
	}
	updateHight(toFix, root);			//fix the heights after the rolls
	return toFix;
}

template<typename T, class Compare>
typename AVLTree<T, Compare>::AVLNode* AVLTree<T, Compare>::findBadBF(
		AVLTree<T, Compare>::AVLNode* currentRoot) {

	int bf = calcBF(currentRoot);		//calc the BF

	if (compare(currentRoot->data, root->data) == 0) { //if you are the root
		if (bf < -1 || bf > 1) {			//check if the roots BF is broken
			return currentRoot;		//if it is, send the root as the node to fix
		}
		return NULL;		//else-there are no more nodes to fix-return null.
	}
	if (bf < -1 || bf > 1) {
		return currentRoot;
	}
	assert(bf >= -1 && bf <= 1);
	return findBadBF(currentRoot->dad);

}

template<typename T, class Compare>
int AVLTree<T, Compare>::calcBF(AVLTree<T, Compare>::AVLNode* node) {
	if (node == NULL) {
		throw InvalidInput();
	}
	int leftH = node->left == NULL ? -1 : node->left->hight, rightH =
			node->right == NULL ? -1 : node->right->hight;
	return leftH - rightH;
}

template<typename T, class Compare>
void AVLTree<T, Compare>::updateBFAfterRemove(
		AVLTree<T, Compare>::AVLNode* currentRoot) {
	while (currentRoot != NULL) {
		currentRoot = updateBF(currentRoot); //the new root will be the node that was recently fixed
	}
}

template<typename T, class Compare>
void AVLTree<T, Compare>::updateWeight(AVLTree<T, Compare>::AVLNode* start,
		AVLTree<T, Compare>::AVLNode* end) {
	int lW = start->left == NULL ? 0 : start->left->weight, rW = //calc the subtrees weights
			start->right == NULL ? 0 : start->right->weight;

	if (start == end) {						//if we are at the root/stop point
		end->weight = 1 + lW + rW;
		return;
	}
	start->weight = 1 + lW + rW;	//sum the weight of left and right and add 1
	updateWeight(start->dad, end);		//update the rest of the tree
}

template<typename T, class Compare>
T AVLTree<T, Compare>::select(int k) {
	if (k < 1 || k > treeSize) {
		throw DataDoesNotExist();
	}
	return select(root, k);
}

template<typename T, class Compare>
T AVLTree<T, Compare>::select(AVLTree<T, Compare>::AVLNode* currentRoot,
		int k) {
	int leftW = calcWeight(currentRoot->left);
	if (leftW == k - 1){ //if you're the k-th node
			//|| (currentRoot->left == NULL && currentRoot->right == NULL)) {
		return currentRoot->data;
	}
	if (leftW > k - 1) {//if the k-th node is in the left subtree
		return select(currentRoot->left, k);
	}
	return select(currentRoot->right, k - leftW - 1);
}

template<typename T, class Compare>
int AVLTree<T, Compare>::calcWeight(AVLTree<T, Compare>::AVLNode* currentRoot){
	if (currentRoot == NULL){
		return 0;
	}
	return currentRoot->weight;
}

template<typename T, class Compare>
int AVLTree<T, Compare>::getWeight(const T& element) {
	try {
		AVLNode* wanted = find(root, element, 0);
		return wanted->weight;
	} catch (DataDoesNotExist& e) {
		return -1;
	}
}

template<typename T, class Compare>
T AVLTree<T, Compare>::getMax() {
	return max->data;
}

template<typename T, class Compare>
T AVLTree<T, Compare>::getMax(AVLTree<T, Compare>::AVLNode* currentRoot) {
	if (currentRoot == NULL) {
		throw DataDoesNotExist();
	}
	if (currentRoot->right == NULL) {
		return currentRoot->data;
	}
	return getMax(currentRoot->right);
}

template<typename T, class Compare>
void AVLTree<T, Compare>::setMax(AVLTree<T, Compare>::AVLNode* currentRoot) {
	if (currentRoot == NULL) {
		throw DataDoesNotExist();
	}
	if (currentRoot->right == NULL) { //if you can't go right anymore-you're the rightmose therefor the max element!
		max = currentRoot;
		return;
	}
	setMax(currentRoot->right);
}

template<typename T, class Compare>
T AVLTree<T, Compare>::getMin() {
	return getMin(root);
}

template<typename T, class Compare>
T AVLTree<T, Compare>::getMin(AVLTree<T, Compare>::AVLNode* currentRoot) {
	if (currentRoot == NULL) {
		throw DataDoesNotExist();
	}
	if (currentRoot->left == NULL) {
		return currentRoot->data;
	}
	return getMin(currentRoot->left);
}
/*
 template<typename T, class Compare>
 class AVLTree<T, Compare>::CheckRoot {
 friend class AVLTree;
 public:
 void operator()(AVLNode* currentRoot) const {
 if (currentRoot == NULL) {
 return;
 }
 if (currentRoot->left != NULL) {		//if u have a left son
 if (currentRoot->left->dad != currentRoot) {//if your left sons' dad isn't you
 throw BadTreeElement < T > (currentRoot->data);
 }
 }
 if (currentRoot->right != NULL) { //if u have a right son
 if (currentRoot->right->dad != currentRoot) { //if your right sons' dad isn't you
 throw BadTreeElement < T > (currentRoot->data);
 }
 }
 }
 };
 */
template<typename T, class Compare>
class AVLTree<T, Compare>::PrintSubTree {
	friend class AVLTree;
public:
	void operator()(AVLNode* currentRoot) const {
		if (currentRoot == NULL) {
			return;
		}
		cout << "subs root is: " << currentRoot->data << "\n";
		if (currentRoot->left != NULL) {		//if u have a left son
			cout << "left son is: " << currentRoot->left->data << "\n";
		}
		if (currentRoot->right != NULL) { //if u have a right son
			cout << "right son is: " << currentRoot->right->data << "\n";
		}
	}
};
/*
 template<typename T, class Compare>
 bool AVLTree<T, Compare>::checkTree() {

 try {
 CheckRoot checker;
 preOrder(root, checker);
 } catch (BadTreeElement<T>& badElement) {
 return false;
 }
 return true;

 }
 */
template<typename T, class Compare>
template<typename Function>
void AVLTree<T, Compare>::preOrder(AVLTree<T, Compare>::AVLNode* currentRoot,
		Function func) const {
	if (currentRoot == NULL) {
		return;
	}
	func(currentRoot);	//do something on the root
	preOrder(currentRoot->left, func);
	preOrder(currentRoot->right, func);

}

template<typename T, class Compare>
void AVLTree<T, Compare>::printTree() const {
	if (root != NULL) {
		cout << "the root of the tree is: " << root->data << "\n";
	}
	PrintSubTree printer;
	preOrder(root, printer);
}

template<typename T, class Compare>
template<typename Function>
void AVLTree<T, Compare>::inOrder(AVLNode* currentRoot, Function &func) {
	if (currentRoot == NULL) {
		return;
	}
	inOrder(currentRoot->left, func);	//take care of left subtree
	func(currentRoot->data);			//do something on the roots' data
	inOrder(currentRoot->right, func);	//take care of the right subtree
}

template<typename T, class Compare>
template<typename Function>
void AVLTree<T, Compare>::postOrderNode(AVLNode* currentRoot, Function func) {
	if (currentRoot == NULL) {
		return;
	}
	postOrderNode(currentRoot->left, func);	//take care of left subtree
	postOrderNode(currentRoot->right, func);	//take care of the right subtree
	func(currentRoot);			//do something on the root
}

template<typename T, class Compare>
template<typename Function>
void AVLTree<T, Compare>::inOrder(Function &func) {
	inOrder(root, func);
}

#endif /* AVL_TREE_H_ */
