
std::ostream& operator<<(std::ostream& os, const Team& team)
{
    os << team.ID;
    return os;
}

Team::Team(int id): ID(id), mostPowerfulID(-1),
		mostPowerfulPower(-1){
	this->ownStudents = new AVLtree<Student,Student,compByStudentPower>();
}

Team::Team(Team& team){ //*********************
	this->ID=team.ID;
	this->ownStudents = new AVLtree<Student,Student,compByStudentPower>();
	this->mostPowerfulID=team.mostPowerfulID;
	this->mostPowerfulPower=team.mostPowerfulPower;
}

Team::~Team(){
	delete this->ownStudents;
}

