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
void 	AddTeamTest(){
	Xmen *xmen=new Xmen();
	assert(AddTeam(NULL,1)==INVALID_INPUT);
	assert(AddTeam(xmen,-1)==INVALID_INPUT);
	assert(AddTeam(xmen,1)==SUCCESS);
	assert(AddTeam(xmen,2)==SUCCESS);
	assert(AddTeam(xmen,1)==FAILURE);
	delete xmen;
	std::cout << "end of AddTeamTest" << std::endl;
}
void 	MoveStudentToTeamTest(){
	Xmen *xmen=new Xmen();
	assert(MoveStudentToTeam(NULL,1,1)==INVALID_INPUT);
	assert(MoveStudentToTeam(xmen,-1,1)==INVALID_INPUT);
	assert(MoveStudentToTeam(xmen,1,-1)==INVALID_INPUT);
	assert(AddStudent(xmen,1,1,1)==SUCCESS);
	assert(AddTeam(xmen,2)==SUCCESS);
	assert(MoveStudentToTeam(xmen,3,2)==FAILURE); //no such student
	assert(MoveStudentToTeam(xmen,1,3)==FAILURE); //no such team
	assert(MoveStudentToTeam(xmen,1,2)==SUCCESS);
	assert(MoveStudentToTeam(xmen,1,2)==FAILURE); //already there
	delete xmen;
	std::cout << "end of MoveStudentToTeamTest" << std::endl;
}
void 	GetMostPowerfulTest(){
	Xmen *xmen=new Xmen();
	int *studentID=0;
	assert(GetMostPowerful(NULL,1,studentID)==INVALID_INPUT);
	assert(GetMostPowerful(xmen,0,studentID)==INVALID_INPUT);
	assert(GetMostPowerful(xmen,1,NULL)==INVALID_INPUT);
	assert(GetMostPowerful(xmen,-1,studentID)==SUCCESS); //no students in the system
	assert(studentID==-1);
	assert(AddStudent(xmen,1,1,1)==SUCCESS);
	assert(AddStudent(xmen,2,2,2)==SUCCESS);
	assert(AddStudent(xmen,3,3,3)==SUCCESS);
	assert(GetMostPowerful(xmen,-1,studentID)==SUCCESS); //most powerful
	assert(studentID==3);
	assert(AddTeam(xmen,2)==SUCCESS);
	assert(AddTeam(xmen,3)==SUCCESS);
	assert(MoveStudentToTeam(xmen,1,2)==SUCCESS);
	assert(MoveStudentToTeam(xmen,2,2)==SUCCESS);
	assert(GetMostPowerful(xmen,2,studentID)==SUCCESS); //most powerful in team 2
	assert(studentID==2);
	assert(GetMostPowerful(xmen,3,studentID)==SUCCESS); //team 3 is empty
	assert(studentID==-1);
	assert(AddStudent(xmen,4,3,3)==SUCCESS);
	assert(GetMostPowerful(xmen,-1,studentID)==SUCCESS); //two with the same power, need to return the lower ID
	assert(studentID==3);
	delete xmen;
	std::cout << "end of MoveStudentToTeamTest" << std::endl;
}
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

