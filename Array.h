/*
 * Array.h
 *
 *  Created on: Dec 24, 2014
 *      Author: alex
 */

#ifndef ARRAY_H_
#define ARRAY_H_

#include <exception>

template<typename T>
class Array {
public:
	class InvalidInput: public std::exception {
	};

	class IndexOutOfBounds: public std::exception {
	};

	class SizesDoNotMatch: public std::exception {
	};

	Array(int size, T defaultValue);
	~Array();

	void set(int index, T data);
	T& get(int index) const;
	T& operator[](int index) const;

protected:
	T *dataArray;
	T defaultValue;
	int *definedBlocks;
	int *stack;
	int top;
	int size;

	bool isGarbage(int index) const;

private:
	// TODO: Don't know if needed
	Array(Array&);
	Array& operator=(const Array&);
};

template<typename T>
Array<T>::Array(int size, T defaultValue) :
		dataArray(new T[size]), defaultValue(defaultValue), definedBlocks(
				new int[size]), stack(new int[size]), top(0), size(size) {
	if (size <= 0) {
		// Question: Does this throw call ~Array()?
		throw InvalidInput();
	}
}

// TODO: Don't know if needed
//template<typename T>
//Array<T>::Array(Array& copy) :
//		dataArray(new T[copy.size]), defaultValue(copy.defaultValue), definedBlocks(
//				new int[copy.size]), stack(new int[copy.size]), top(copy.top), size(copy.size) {
//	// TODO
//}

template<typename T>
Array<T>::~Array() {
	delete[] dataArray;
	delete[] definedBlocks;
	delete[] stack;
}

template<typename T>
void Array<T>::set(int index, T data) {
	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}

	if (isGarbage(index)) {
		stack[top] = index;
		definedBlocks[index] = top;
		top++;
	}
	dataArray[index] = data;
}

template<typename T>
T& Array<T>::get(int index) const {
	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}

	return (*this)[index];
}

template<typename T>
T& Array<T>::operator[](int index) const {
	if (isGarbage(index)) {
		// FIXME: This may be a bug!
		set(index, defaultValue);
	}
	return dataArray[index];
}

// TODO: Don't know if needed
//template<typename T>
//Array& Array<T>::operator=(const Array& toCopy) {
//	if (size != toCopy.size) {
//		throw SizesDoNotMatch();
//	}
//
//	T *tempDataArray(new T[size]);
//	int *tempDefinedBlocks(new int[size]);
//	int *tempStack(new int[size]);
//
//	for (int i = 0; i < size; i++) {
//		tempDataArray[i] = toCopy.dataArray[i];
//		tempDefinedBlocks[i] = toCopy.definedBlocks[i];
//		tempStack[i] = toCopy.stack[i];
//	}
//
//	delete[] dataArray;
//	delete[] definedBlocks;
//	delete[] stack;
//
//	for (int i = 0; i < size; i++) {
//		dataArray[i] = tempDataArray[i];
//		definedBlocks[i] = tempDefinedBlocks[i];
//		stack[i] = tempStack[i];
//	}
//
//	defaultValue = toCopy.defaultValue;
//	top = toCopy.top;
//
//	return *this;
//}

template<typename T>
bool Array<T>::isGarbage(int index) const {
	return !(definedBlocks[index] < top && definedBlocks[index] >= 0
			&& stack[definedBlocks[index]] == index);
}

#endif /* ARRAY_H_ */

