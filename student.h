#ifndef STUDENT_H
#define STUDENT_H

#include "team.h"

class Team;


class Student {
public:
  int ID;
  int grade;
  int PWR;
  Team* team;
  void updateTeam(Team* team){
	  this->team=team;
   }
  Student(int id, int grade, int power,team);
  Student(Student& student);
  ~Student();
};

class compByStudentPower {
public:
  bool operator()(Student* a, Student* b) {
	  if(a->PWR>b->PWR){
		return false;
	  }else if(a->PWR<b->PWR){
		  return true;
	  }else{
		  if(a->ID>b->ID){
			  return true;
		  }else{
			  return false;
		  }
	  }
	}

};

class compByStudentID {
public:
  bool operator()(Student* a, Student* b) {
	  if(a->ID>=b->ID){
		return false;
	  }else{
		  return true;
	  }
	}
};

#endif /* STUDENT_H */
