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
	ASSERT_THROWS(DataAlreadyExists, arg)

#define ASSERT_DATA_DOES_NOT_EXIST(arg) \
	ASSERT_THROWS(DataDoesNotExist, arg)

#define ASSERT_INVALID_INPUT(arg) \
	ASSERT_THROWS(InvalidInput, arg)

#define ASSERT_FAILURE(arg) \
	ASSERT_THROWS(Failure, arg)

#endif /* ASSERT_H_ */
