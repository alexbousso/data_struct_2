#include "library2.h"

#include "planet.h"

void* Init(int n) {
	try {
		Planet* planet = new Planet(n);
		return (void*) planet;
	} catch (std::bad_alloc& e) {
		return NULL;
	}catch (InvalidInput& badInput) {
		return NULL;
	}
}

StatusType AddCitizen(void* DS, int citizenID) {
	if (DS == NULL || citizenID < 0) {
		return INVALID_INPUT;
	}
	try {
		(static_cast<Planet*>(DS))->AddCitizen(citizenID);
	} catch (InvalidInput& badInput) {
		return INVALID_INPUT;
	} catch (Failure& fail) {
		return FAILURE;
	} catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType MoveToCity(void* DS, int citizenID, int city) {
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	try {
		(static_cast<Planet*>(DS))->MoveToCity(citizenID, city);
	} catch (InvalidInput& badInput) {
		return INVALID_INPUT;
	} catch (Failure& fail) {
		return FAILURE;
	} catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType JoinKingdoms(void* DS, int city1, int city2) {
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	try {
		(static_cast<Planet*>(DS))->JoinKingdoms(city1, city2);
	} catch (InvalidInput& badinput) {
		return INVALID_INPUT;
	} catch (Failure& fail) {
		return FAILURE;
	} catch (std::bad_alloc& ba) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType GetCapital(void* DS, int citizenID, int* capital) {
	if (DS == NULL || !capital) {
		return INVALID_INPUT;
	}
	try {
		*capital = (static_cast<Planet*>(DS))->GetCapital(citizenID);
	} catch (InvalidInput& badInput) {
		return INVALID_INPUT;
	} catch (Failure& fail) {
		return FAILURE;
	}
	return SUCCESS;
}

StatusType SelectCity(void* DS, int k, int* city) {
	if (DS == NULL || city == NULL || k < 0) {
		return INVALID_INPUT;
	}
	try {
		*city = (static_cast<Planet*>(DS))->SelectCity(k);
	} catch (DataDoesNotExist& noData) {
		return FAILURE;
	} catch (Failure& fail) {
		return FAILURE;
	}
	return SUCCESS;
}

StatusType GetCitiesBySize(void* DS, int results[]) {
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	(static_cast<Planet*>(DS))->GetCitiesBySize(results);

	return SUCCESS;
}

void Quit(void** DS) {
	if (DS == NULL){
		return;
	}
	delete static_cast<Planet*>(*DS);
	*DS = NULL;
}
