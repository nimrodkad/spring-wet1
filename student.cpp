#include "student.h"

Student::Student(int id, int grade, int power): ID(id), grade(grade), PWR(power), team(NULL){

}

Student::Student(Student& student): ID(student.ID), grade(student.grade), PWR(student.PWR), team(student.team){

}
