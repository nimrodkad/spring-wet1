#include "student.h"

Student::Student(int id, int grade, int power): ID(id), grade(grade), PWR(power), team(NULL){

}

Student::Student(Student& student): ID(student.ID), grade(student.grade), PWR(student.PWR), team(student.team){

}

OwnedStudent::OwnedStudent(int id, int grade, int power, Team* team, Student* byID, Student* byPWR):Student(id, grade, power, team), byID(byID), byPWR(byPWR){

}

OwnedStudent::OwnedStudent(OwnedStudent& student): Student(student), byID(student.byID), byPWR(student.byPWR){

}

OwnedStudent::~OwnedStudent(){

}
