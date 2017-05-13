/*
 * libraryTEST.cpp
 *
 *  Created on: 13 ???? 2017
 *      Author: Alex
 */
#include "library1.h"
#include "Xmen.h"
#include <iostream>

void InitTest() {
	assert(Init()!=NULL);
	std::cout << "end of InitTest" << std::endl;
}
void AddStudentTest() {
	Xmen *xmen = new Xmen();
	assert(AddStudent(NULL,1,1,1)==INVALID_INPUT);
	assert(AddStudent(xmen, -1, 1, 1) == INVALID_INPUT);
	assert(AddStudent(xmen, 1, -1, 1) == INVALID_INPUT);
	assert(AddStudent(xmen, 1, 1, 0) == INVALID_INPUT);
	assert(AddStudent(xmen, 1, 1, 1) == SUCCESS);
	assert(AddStudent(xmen, 1, 1, 1) == FAILURE);
	assert(AddStudent(xmen, 2, 1, 1) == SUCCESS);
	delete xmen;
	std::cout << "end of AddStudentTest" << std::endl;
}
void AddTeamTest() {
	Xmen *xmen = new Xmen();
	assert(AddTeam(NULL,1)==INVALID_INPUT);
	assert(AddTeam(xmen, -1) == INVALID_INPUT);
	assert(AddTeam(xmen, 1) == SUCCESS);
	assert(AddTeam(xmen, 2) == SUCCESS);
	assert(AddTeam(xmen, 1) == FAILURE);
	delete xmen;
	std::cout << "end of AddTeamTest" << std::endl;
}
void MoveStudentToTeamTest() {
	Xmen *xmen = new Xmen();
	assert(MoveStudentToTeam(NULL,1,1)==INVALID_INPUT);
	assert(MoveStudentToTeam(xmen, -1, 1) == INVALID_INPUT);
	assert(MoveStudentToTeam(xmen, 1, -1) == INVALID_INPUT);
	assert(AddStudent(xmen, 1, 1, 1) == SUCCESS);
	assert(AddTeam(xmen, 2) == SUCCESS);
	assert(MoveStudentToTeam(xmen, 3, 2) == FAILURE); //no such student
	assert(MoveStudentToTeam(xmen, 1, 3) == FAILURE); //no such team
	assert(MoveStudentToTeam(xmen, 1, 2) == SUCCESS);
	assert(MoveStudentToTeam(xmen, 1, 2) == FAILURE); //already there
	delete xmen;
	std::cout << "end of MoveStudentToTeamTest" << std::endl;
}
void GetMostPowerfulTest() {
	Xmen *xmen = new Xmen();
	int *studentID = 0;
	assert(GetMostPowerful(NULL,1,studentID)==INVALID_INPUT);
	assert(GetMostPowerful(xmen, 0, studentID) == INVALID_INPUT);
	assert(GetMostPowerful(xmen,1,NULL)==INVALID_INPUT);
	assert(GetMostPowerful(xmen, -1, studentID) == SUCCESS); //no students in the system
	assert(studentID == -1);
	assert(GetMostPowerful(xmen, 1, studentID) == FAILURE); //no such team
	assert(AddStudent(xmen, 1, 1, 1) == SUCCESS);
	assert(AddStudent(xmen, 2, 2, 2) == SUCCESS);
	assert(AddStudent(xmen, 3, 3, 3) == SUCCESS);
	assert(GetMostPowerful(xmen, -1, studentID) == SUCCESS); //most powerful
	assert(studentID == 3);
	assert(AddTeam(xmen, 2) == SUCCESS);
	assert(AddTeam(xmen, 3) == SUCCESS);
	assert(MoveStudentToTeam(xmen, 1, 2) == SUCCESS);
	assert(MoveStudentToTeam(xmen, 2, 2) == SUCCESS);
	assert(GetMostPowerful(xmen, 2, studentID) == SUCCESS); //most powerful in team 2
	assert(studentID == 2);
	assert(GetMostPowerful(xmen, 3, studentID) == SUCCESS); //team 3 is empty
	assert(studentID == -1);
	assert(AddStudent(xmen, 4, 3, 3) == SUCCESS);
	assert(GetMostPowerful(xmen, -1, studentID) == SUCCESS); //two with the same power, need to return the lower ID
	assert(studentID == 3);
	delete xmen;
	std::cout << "end of MoveStudentToTeamTest" << std::endl;
}
void RemoveStudentTest() {
	Xmen *xmen = new Xmen();
	assert(RemoveStudent(NULL,1)==INVALID_INPUT);
	assert(RemoveStudent(xmen, -1) == INVALID_INPUT);
	assert(RemoveStudent(xmen, 1) == FAILURE); //no such student
	assert(AddStudent(xmen, 1, 1, 1) == SUCCESS);
	assert(AddStudent(xmen, 3, 3, 3) == SUCCESS);
	assert(AddStudent(xmen, 4, 4, 4) == SUCCESS);
	assert(RemoveStudent(xmen, 2) == FAILURE); //no such student
	assert(RemoveStudent(xmen, 1) == SUCCESS);
	assert(RemoveStudent(xmen, 1) == FAILURE); //no such student
	assert(RemoveStudent(xmen, 4) == SUCCESS);
	assert(RemoveStudent(xmen, 4) == FAILURE); //no such student
	delete xmen;
	std::cout << "end of MoveStudentToTeamTest" << std::endl;
}
void GetAllStudentsByPowerTest() {
	Xmen *xmen = new Xmen();
	int num;
	int **students;
	assert(GetAllStudentsByPower(NULL,1,students,&num)==INVALID_INPUT);
	assert(GetAllStudentsByPower(xmen, 0, students, &num) == INVALID_INPUT);
	assert(GetAllStudentsByPower(xmen,1,NULL,&num)==INVALID_INPUT);
	assert(GetAllStudentsByPower(xmen,1,students,NULL)==INVALID_INPUT);
	assert(AddStudent(xmen, 1, 1, 1) == SUCCESS);
	assert(AddStudent(xmen, 2, 2, 2) == SUCCESS);
	assert(AddStudent(xmen, 3, 3, 3) == SUCCESS);
	assert(AddStudent(xmen, 4, 4, 4) == SUCCESS);
	assert(GetAllStudentsByPower(xmen,-1,students,&num)==SUCCESS); //get all powers
	for(int i=0;i<num;i++){
		std::cout << (*students[i]) + " " <<std::endl;
	}
	assert(AddTeam(xmen,1)==SUCCESS);
	assert(AddTeam(xmen,2)==SUCCESS);
	assert(MoveStudentToTeam(xmen, 1, 1) == SUCCESS);
	assert(MoveStudentToTeam(xmen, 3, 1) == SUCCESS);
	assert(MoveStudentToTeam(xmen, 4, 1) == SUCCESS);
	assert(MoveStudentToTeam(xmen, 2, 2) == SUCCESS);
	assert(GetAllStudentsByPower(xmen,1,students,&num)==SUCCESS); //get all powers team 1
	for(int i=0;i<num;i++){
			std::cout << (*students[i]) + " " <<std::endl;
	}
	assert(GetAllStudentsByPower(xmen,3,students,&num)==FAILURE); //team doesnt exist
	delete xmen;
	delete[] students;
	std::cout << "end of GetAllStudentsByPowerTest" << std::endl;
}
void IncreaseLevelTest(){
	Xmen *xmen = new Xmen();
	int *studentID;
		assert(AddStudent(xmen, 1, 1, 1) == SUCCESS);
		assert(AddStudent(xmen, 2, 1, 0) == SUCCESS);
		assert(AddStudent(xmen, 3, 3, 3) == SUCCESS);
		assert(AddStudent(xmen, 4, 4, 4) == SUCCESS);
		assert(IncreaseLevel(NULL,1,1)==INVALID_INPUT);
		assert(IncreaseLevel(xmen,0,1)==INVALID_INPUT);
		assert(IncreaseLevel(xmen,1,-1)==INVALID_INPUT);
		assert(IncreaseLevel(xmen,3,2)==SUCCESS);
		assert(GetMostPowerful(xmen, -1, studentID) == SUCCESS); //most powerful now is 3 with 5 power
		assert(studentID == 3);
		assert(IncreaseLevel(xmen,1,6)==SUCCESS);
		assert(GetMostPowerful(xmen, -1, studentID) == SUCCESS); //most powerful now is 1 with 7 power
		assert(studentID == 1);
		assert(RemoveStudent(xmen,1)==SUCCESS);
		assert(GetMostPowerful(xmen, -1, studentID) == SUCCESS); //most powerful now is 2 with 6 power
		assert(studentID == 2);
		delete xmen;
		std::cout << "end of MoveStudentToTeamTest" << std::endl;
}

int main() {
	InitTest();
	AddStudentTest();
	AddTeamTest();
	MoveStudentToTeamTest();
	GetMostPowerfulTest();
	RemoveStudentTest();
	GetAllStudentsByPowerTest();
	IncreaseLevelTest();
	return 0;
}

