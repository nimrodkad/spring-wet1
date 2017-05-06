#ifndef TEAM_H
#define TEAM_H

#include "AVLtree.h"
#include "student.h"
#include <iostream>

class Student;
class OwnedStudent;
class compByStudentPower;


class Team{
public:
	int ID;
	int mostPowerfulID;
	int mostPowerfulPower;
	AVLtree<OwnedStudent, OwnedStudent, compByStudentPower>* ownStudents;
	Team(int id);
	Team(Team& team);
	~Team();
	friend std::ostream& operator<<(std::ostream& os,const Team& team);
};

class compByTeamID {
public:
  bool operator()(Team* a, Team* b) {
	  if(a->ID >= b->ID){
		return false;
	  }else{
		  return true;
	  }
	}
};

#endif /* TEAM_H */
