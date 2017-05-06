#include "magizoologist.h"

std::ostream& operator<<(std::ostream& os, const Team& team)
{
    os << team.ID;
    return os;
}

Team::Team(int id): ID(id), mostPowerfulID(0),
		mostPowerfulPower(0){
	this->ownStudents=
			new AVLtree<OwnedStudent,OwnedStudent,compByStudentPower>();
}

Team::Team(Team& team){
	this->ID=team.ID;
	this->ownStudents=
			new AVLtree<OwnedStudent,OwnedStudent,compByStudentPower>();
	this->mostPowerfulID=team.mostPowerfulID;
	this->mostPowerfulPower=team.mostPowerfulPower;
}

Team::~Team(){
	delete this->ownStudents;
}

