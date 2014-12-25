/*
 * assert.h
 *
 *  Created on: Dec 25, 2014
 *      Author: alex
 */

#ifndef ASSERT_H_
#define ASSERT_H_

#include "test_utils.h"
#include "../exceptions.h"

#define ASSERT_LIST_IS_EMPTY(arg) \
	ASSERT_THROWS(ListIsEmpty, arg)

#define ASSERT_INDEX_OUT_OF_BOUNDS(arg) \
	ASSERT_THROWS(IndexOutOfBounds, arg)

#define ASSERT_INVALID_ITERATOR(arg) \
	ASSERT_THROWS(InvalidIterator, arg)

#define ASSERT_DATA_ALREADY_EXISTS(arg) \
	ASSERT_THROWS(DataAlreadyExsists, arg)

#define ASSERT_DATA_DOES_NOT_EXIST(arg) \
	ASSERT_THROWS(DataDoesNotExsist, arg)

#endif /* ASSERT_H_ */
