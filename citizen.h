/*
 * citizen.h
 *
 *  Created on: Dec 28, 2014
 *      Author: alex
 */

#ifndef CITIZEN_H_
#define CITIZEN_H_

#include "exceptions.h"
#include <iostream>

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

	int getID() const {
		return ID;
	}

	void setLivingCity(int livingCity) {
		if (livingCity < 0 || this->livingCity >= 0) {
			throw InvalidInput();
		}
		this->livingCity = livingCity;
	}

	int getLivingCity() const {
		return livingCity;
	}

	bool operator==(Citizen other) const {
		return ID == other.ID;
	}

	bool operator==(int ID) const {
		return this->ID == ID;
	}

	friend std::ostream& operator<<(std::ostream& os, const Citizen& citizen) {
		os << "ID: ";
		os.width(4);
		os << citizen.ID << ", lives in: ";
		os.width(3);
		os << citizen.livingCity;

		return os;
	}
};

#endif /* CITIZEN_H_ */
