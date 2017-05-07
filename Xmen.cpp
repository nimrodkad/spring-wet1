#include "Xmen.h"
#include "utils.h"
#include <cassert>
#include <cstdlib>

#define DOESNT_EXIST -2

Xmen::Xmen() : mostPowerfulID(-1), mostPowerfulPower(-1) {
  teams = new AVLtree<Team, Team, compByTeamID>();
  students = new AVLtree<Student, Student, compByStudentID>;
  studentsPowers = new AVLtree<Student, Student, compByStudentPower>;
}

Xmen::~Xmen() {
  delete teams;
  delete students;
  delete studentsPowers;
}

bool Xmen::addTeam(int teamID) {
  Team *newTeam = new Team(teamID);
  bool result = this->teams->insert(newTeam, NULL);
  delete newTeam;
  return result;
}
//need to find the students team and then add him to that team's tree*********************
bool Xmen::addStudent(int studentID, int grade, int power) {
  Student* newStud = new Student(studentID, grade, power);
  if (!this->students->insert(newStud, NULL)) {
    delete newStud;
    return false;
  }
  this->studentsPowers->insert(newStud, NULL);
  delete newStud;
  Student* studByPwr = NULL;
  Student* studByID = this->findStudent(teamID, &studByPwr);
  OwnedStudent* studentInTeam =
      new Student(studentID, grade, power, team, studByID, studByPwr);
  team->ownStudents->insert(ownedStudent, NULL);
  this->updateMostPowerful();
  delete ownedStudent;
  return true;
}

Student *Xmen::findStudent(int studentID, Student **studentOut) { //////////////
  Student *dummyStudent1 = new Student(studentID, 0, 0);
  AVLtree<Student, Student, compByStudentID>::AVLNode *lastNode1;
  AVLtree<Student, Student, compByStudentID>::AVLNode *studentById =
      this->students->find(this->students->root, dummyStudent1, &lastNode1);
  delete dummyStudent1;
  if (!studentById) {
    return NULL;
  }
  Student *dummyStudent2 =
      new Student(studentID, studentById->keyValue->PWR, NULL);
  AVLtree<Student, Student, compByStudentPower>::AVLNode *lastNode2;
  AVLtree<Student, Student, compByStudentPower>::AVLNode *studentByPwr =
      this->studentsPowers->find(this->studentsPowers->root, dummyStudent2,
                                  &lastNode2);
  delete dummyStudent2;
  if (!studentByPwr) {
    return NULL;
  }
  (*studentOut) = studentByPwr->keyValue;
  return studentById->keyValue;
}

Team *Xmen::findTeam(int teamID) {
  Team *newTeam = new Team(teamID);
  AVLtree<Team, Team, compByTeamID>::AVLNode *lastNode;
  AVLtree<Team, Team, compByTeamID>::AVLNode *teamNode =
      this->teams->find(this->teams->root, newTeam,
                                 &lastNode);
  delete newTeam;
  if (!teamNode) {
    return NULL;
  } else {
    return teamNode->keyValue;
  }
  return NULL;
}

bool Xmen::removeStudent(int studentID) {
  Student *dummy = NULL;
  Student *dummy2 = this->findStudent(studentID, &dummy);
  if (!dummy2) {
    return false;
  }
  Team *team = dummy2->team;
  OwnedStudent *ownedDummy =
      new OwnedStudent(studentID, dummy2->PWR, NULL, NULL, NULL);
  team->ownStudents->remove(ownedDummy);
  this->studentsPowers->remove(dummy);
  this->students->remove(dummy2);
  if (studentID ==
      this->mostPowerfulID) {
    this->updateMostPowerful();
  }
  if (studentID == team->mostPowerfulID) {
    this->updateMostPowerful(team);
  }
  delete ownedDummy;
  return true;
}

int Xmen::replaceMagizoologist(int teamID, int replacementID) {
  Team *magiOld = this->findMagi(teamID);
  Team *magiReplacement = this->findMagi(replacementID);
  if (!magiOld || !magiReplacement) { //no such magis
    return DOESNT_EXIST;
  }
  AVLtree<OwnedCreature, OwnedCreature, compByStudentPower> *newTree =
      magiReplacement->ownCreatures->merge(&magiOld->ownCreatures);
  magiReplacement->ownCreatures=newTree;
  int numOfCreatures=0;
  OwnedCreature **creaturesArray = magiReplacement->ownCreatures->
		  inorder(&numOfCreatures);
  for(int i=0;i<numOfCreatures;++i){
    creaturesArray[i]->magi=magiReplacement;
    creaturesArray[i]->byLVL->magi=magiReplacement;
    creaturesArray[i]->byID->magi=magiReplacement;
  }
  this->updateMostDangerous(magiReplacement);
  magiOld->ownCreatures=NULL;
  this->teams->remove(magiOld);
  return 0;
}


void Xmen::increaseLevel(int studentID, int levelIncrease) { // changed from bool to void
  Student *dummy = NULL;
  Student *creature = this->findCreature(studentID, &dummy);
  if (!creature) { //no such creature
    return false;
  }
  int newLevel = (creature->LVL + levelIncrease);
  Team *magi = creature->magi;
  this->releaseCreature(studentID);
  this->insertCreature(studentID, (magi->ID), newLevel);
  return true;
}

int Xmen::getMostPowerful() {
  if (this->students->numOfElements == 0) {
    return -1;
  } else {
    return this->mostPowerfulID;
  }
}

int Xmen::getMostPowerful(int teamID) {
  Team *team = this->findTeam(teamID);
  if (!team) {
    return DOESNT_EXIST;
  }
  if (team->ownStudents->numOfElements == 0) {
    return -1;
  } else {
    return team->mostPowerfulID;
  }
}

int *Xmen::getAllStudentsByPower(int *numOfStudents) {
  if (this->studentsPowers->numOfElements == 0) {
    *numOfCreatures = 0;
    return NULL;
  }
  Student **studentsArray = this->studentsPowers->inorder(numOfStudents);
  int *sortedIDArray = (int *)malloc(sizeof(int) * ((*numOfStudents)));
  for (int i = *numOfCreatures - 1, j = 0; i >= 0; i--, j++) {
    sortedIDArray[i] = (studentsArray[j]->ID);
  }
  delete[] studentsArray;
  return sortedIDArray;
}

int *Xmen::getAllStudentsByPower(int *numOfStudents, int teamID, int *exist) {
  Team *team = this->findTeam(teamID);
  if (!team) {
    *exist = DOESNT_EXIST;
    return NULL;
  }
  if (team->ownStudents->numOfElements == 0) {
    *numOfCreatures = 0;
    return NULL;
  }
  OwnedStudent **studentsArray = team->ownStudents->inorder(numOfCreatures);
  int *sortedIDArray = (int *)malloc(sizeof(int) * ((*numOfStudents)));
  for (int i = *numOfStudents - 1, j = 0; i >= 0; i--, j++) {
    sortedIDArray[i] = (studentsArray[j]->ID);
  }
  return sortedIDArray;
}

void Xmen::updateMostPowerful(Team *team) {
  if (team->ownStudents->numOfElements == 0) {
    team->mostPowerfulID = team->mostPowerfulPower = -1;
    return;
  }
  AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator =
      team->ownStudents->root;
  while (iterator->right) {
    iterator = iterator->right;
  }
  team->mostPowerfulID = iterator->keyValue->ID;
  team->mostPowerfulPower = iterator->keyValue->PWR;
}

void Xmen::updateMostPowerful() {
  if (this->studentsPowers->numOfElements == 0) {
    this->mostPowerfulID = this->mostPowerfulPower = -1;
    return;
  }
  AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator =
      this->studentsPowers->root;
  while (iterator->right) {
    iterator = iterator->right;
  }
  this->mostPowerfulID = iterator->keyValue->ID;
  this->mostPowerfulPower = iterator->keyValue->PWR;
}
