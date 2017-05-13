/*
 * libraryTEST.cpp
 *
 *  Created on: 13 ???? 2017
 *      Author: Alex
 */
#include "library1.h"
#include "Xmen.h"
#include <iostream>


void InitTest(){
	assert(Init()!=NULL);
	std::cout << "end of InitTest" << std::endl;
}
void 	AddStudentTest(){
		Xmen *xmen=new Xmen();
		assert(AddStudent(NULL,1,1,1)==INVALID_INPUT);
		assert(AddStudent(xmen,-1,1,1)==INVALID_INPUT);
		assert(AddStudent(xmen,1,-1,1)==INVALID_INPUT);
		assert(AddStudent(xmen,1,1,0)==INVALID_INPUT);
		assert(AddStudent(xmen,1,1,1)==SUCCESS);
		assert(AddStudent(xmen,1,1,1)==FAILURE);
		assert(AddStudent(xmen,2,1,1)==SUCCESS);
		delete xmen;
		std::cout << "end of AddStudentTest" << std::endl;
}
void 	AddTeamTest();
void 	MoveStudentToTeam();
void 	GetMostPowerfulTest();
void 	RemoveStudentTest();
void 	GetAllStudentsByPowerTest();
void 	IncreaseLevelTest();



int main(){
	InitTest();
	AddStudentTest();
	AddTeamTest();
	MoveStudentToTeam();
	GetMostPowerfulTest();
	RemoveStudentTest();
	GetAllStudentsByPowerTest();
	IncreaseLevelTest();
	return 0;
}

