/*
 * DynamicArray.h
 *
 *  Created on: Dec 24, 2014
 *      Author: alex
 */

#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

#include "Array.h"

template<typename T>
class DynamicArray: public Array<T> {
public:
	DynamicArray(int size, T defaultValue) :
			Array(size, defaultValue), initializedBlocks(0) {
	}

private:
	int initializedBlocks;
};

#endif /* DYNAMICARRAY_H_ */
