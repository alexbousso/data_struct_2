/*
 * exceptions.h
 *
 *  Created on: Dec 25, 2014
 *      Author: alex
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

class DataAlreadyExists: public std::exception {
};

class DataDoesNotExist: public std::exception {
};

class ListIsEmpty: public std::exception {
};

class IndexOutOfBounds: public std::exception {
};

class InvalidIterator: public std::exception {
};
class InvalidInput: std::exception {
};

#endif /* EXCEPTIONS_H_ */
