/*
 * citizen.h
 *
 *  Created on: Dec 28, 2014
 *      Author: alex
 */

#ifndef CITIZEN_H_
#define CITIZEN_H_

#include "exceptions.h"

class Citizen {
	int ID;
	int livingCity;

public:
	Citizen(int ID) :
			ID(ID), livingCity(-1) {
		if (ID < 0) {
			throw InvalidInput();
		}
	}

	int getID() {
		return ID;
	}

	void setLivingCity(int livingCity) {
		if (livingCity < 0 || this->livingCity >= 0) {
			throw InvalidInput();
		}
		this->livingCity = livingCity;
	}

	int getLivingCity() {
		return livingCity;
	}
};

#endif /* CITIZEN_H_ */
