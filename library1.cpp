#include "library1.h"
#include "Xmen.h"
#include <iostream>

#define DOESNT_EXIST -2

void *Init() {
	Xmen *DS = NULL;
	try {
		DS = new Xmen();
	} catch (std::bad_alloc &b) {
		DS = NULL;
	}
	return (void *) DS;
}

StatusType AddStudent(void *DS, int StudentID, int Grade, int Power) {
	if (!DS || StudentID <= 0 || Power <= 0 || Grade < 0) {
		return INVALID_INPUT;
	}
	try {
		bool inserted = ((Xmen*) DS)->addStudent(StudentID, Grade, Power);
		if(!inserted){
			return FAILURE;
		}
	} catch (std::bad_alloc &b) {
		return ALLOCATION_ERROR;
	} catch (...) {
		return FAILURE;
	}
	return SUCCESS;
}

StatusType AddTeam(void *DS, int TeamID) {
	if (!DS || TeamID <= 0) {
		return INVALID_INPUT;
	}
	try {
		bool inserted =((Xmen*) DS)->addTeam(TeamID);
		if(!inserted){
			return FAILURE;
		}
	} catch (std::bad_alloc &b) {
		return ALLOCATION_ERROR;
	} catch (...) {
		return FAILURE;
	}
	return SUCCESS;
}

StatusType MoveStudentToTeam(void *DS, int StudentID, int TeamID) {
	if (!DS || StudentID <= 0 || TeamID <= 0) {
		return INVALID_INPUT;
	}
	try {
		bool moved =((Xmen*) DS)->moveStudentToTeam(StudentID, TeamID);
		if(!moved){
			return FAILURE;
		}
	}
	catch (std::bad_alloc &b) { //added aloc error in the new PDF
		return ALLOCATION_ERROR;
	}
	catch (...) {
		return FAILURE;
	}
	return SUCCESS;
}

StatusType GetMostPowerful(void *DS, int TeamID, int *StudentID) {
	if (!DS || !StudentID || TeamID == 0) {
			return INVALID_INPUT;
	}try {
		if(TeamID<0){
			(*StudentID)=((Xmen*) DS)->getMostPowerful();
		}else{
			(*StudentID)=((Xmen*) DS)->getMostPowerful(TeamID);
			if((*StudentID) == DOESNT_EXIST){
				return FAILURE;
			}
		}
	} catch (std::bad_alloc &b) {
		return ALLOCATION_ERROR;
	} catch (...) {
		return FAILURE;
	}
	return SUCCESS;
}

StatusType RemoveStudent(void *DS, int StudentID) {
	if (!DS || StudentID <= 0) {
		return INVALID_INPUT;
	}
	try {
		bool removed =((Xmen*) DS)->removeStudent(StudentID);
		if(!removed){
			return FAILURE;
		}
	} catch (std::bad_alloc &b) {
		return ALLOCATION_ERROR;
	} catch (...) {
		return FAILURE;
	}
	return SUCCESS;
}

StatusType GetAllStudentsByPower(void *DS, int TeamID, int **Students, int *numOfStudents) {
	if( !DS || !Students || !numOfStudents || TeamID == 0){
		return INVALID_INPUT;
	}
	int exist=1;
	try {
		if(TeamID < 0){
			*Students=((Xmen*) DS)->
					getAllStudentsByPower(numOfStudents);
		}else{
			*Students= ((Xmen*) DS)->
					getAllStudentsByPower(TeamID,numOfStudents,&exist);
		}
		if(exist == DOESNT_EXIST){ //check if team doesn't exist
				return FAILURE;
		}
	}catch (std::bad_alloc &b) {
		return ALLOCATION_ERROR;
	} catch (...) {
		return FAILURE;
	}
	return SUCCESS;
}

StatusType IncreaseLevel(void *DS, int Grade, int PowerIncrease) {
	if (!DS || Grade < 0 || PowerIncrease <= 0) {
		return INVALID_INPUT;
	}
	try {
		((Xmen*) DS)->increaseLevel(Grade,PowerIncrease);
	} catch (std::bad_alloc &b) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

void Quit(void **DS) {
	delete (Xmen*) *DS;
	*DS = NULL;
}
