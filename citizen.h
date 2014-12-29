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
	const int ID;
	int livingCity;

public:
	Citizen() :
			ID(-1), livingCity(-1) {
	}
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

	bool operator==(Citizen other) {
		return ID == other.ID;
	}

	bool operator==(int ID) {
		return this->ID == ID;
	}
};

#endif /* CITIZEN_H_ */
