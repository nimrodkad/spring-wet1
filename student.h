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
  virtual void updateTeam(Team* team){
	  this->team=team;
  }
	Student(int id, int grade, int power, Team* team);
	Student(Student& student);
	virtual ~Student();
};

class OwnedStudent : public Student {
public:
  Student* byID;
  Student* byPWR;
  void updateTeam(Team* team){
  	  this->team=team;
  	  byID->team=team;
      byPWR->team=team;
    }
	OwnedStudent(int id, int grade, int power, Team* team, Student* byID,
			Student* byPWR);
	OwnedStudent(OwnedStudent& student);
	~OwnedStudent();
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
