#include "Xmen.h"
#include "utils.h"
#include <cassert>
#include <cstdlib>

#define DOESNT_EXIST -2

void inOrderUpdate(AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator, int grade, int powerInc);
void inOrderUpdate(AVLtree<Student, Student, compByStudentID>::AVLNode *iterator, int grade, int powerInc);
void inOrderCount(AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator, int grade, int *counter);
void inOrderSplit(AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator, int grade, Student **a, int n, Student **b, int m);
void mergeStudentsArrays(Student **a, int n, Student **b, int m, Student** c);
AVLtree<Student, Student, compByStudentPower>* arrayToTree(Student** treeArray,int size);
void updateTree(AVLtree<Student, Student, compByStudentPower> *tree, int grade, int powerIncrease);
void inOrderTeams(AVLtree<Team, Team, compByTeamID>::AVLNode *root, int grade, int powerIncrease);

Xmen::Xmen() :
		mostPowerfulID(-1), mostPowerfulPower(-1) {
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

//adds the student to both of the trees,updates the MostPowerful if needed
bool Xmen::addStudent(int studentID, int grade, int power) {
	Student* newStud = new Student(studentID, grade, power);
	if (!this->students->insert(newStud, NULL)
			|| this->studentsPowers->insert(newStud, NULL)) {
		delete newStud;
		return false;
	}
	delete newStud;
	this->updateMostPowerful();
	return true;
}
//return pointers to the student in the id tree and in the power tree(2th param)
Student *Xmen::findStudent(int studentID, Student **studentOut) {
	Student *dummyStudent1 = new Student(studentID, 0, 0);
	AVLtree<Student, Student, compByStudentID>::AVLNode *lastNode1;
	AVLtree<Student, Student, compByStudentID>::AVLNode *studentById =
			this->students->find(this->students->root, dummyStudent1,
					&lastNode1);
	delete dummyStudent1;
	if (!studentById) {
		return NULL;
	}
	Student *dummyStudent2 = new Student(studentID, studentById->keyValue->PWR,
			0);
	AVLtree<Student, Student, compByStudentPower>::AVLNode *lastNode2;
	AVLtree<Student, Student, compByStudentPower>::AVLNode *studentByPwr =
			this->studentsPowers->find(this->studentsPowers->root,
					dummyStudent2, &lastNode2);
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
	AVLtree<Team, Team, compByTeamID>::AVLNode *teamNode = this->teams->find(
			this->teams->root, newTeam, &lastNode);
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
	if (dummy2->team) { //has a team
		Team *team = dummy2->team;
		Student *ownedDummy = new Student(studentID, dummy2->PWR, 0);
		team->ownStudents->remove(ownedDummy);
		if (studentID == team->mostPowerfulID) {
			this->updateMostPowerful(team);
		}
		delete ownedDummy;
	}
	this->studentsPowers->remove(dummy);
	this->students->remove(dummy2);
	if (studentID == this->mostPowerfulID) {
		this->updateMostPowerful();
	}
	return true;
}

bool Xmen::moveStudentToTeam(int studentID, int teamID) {
	Student *dummy = NULL;
	Student *dummy2 = this->findStudent(studentID, &dummy);
	if (!dummy2) {
		return false;
	}
	if (dummy2->team) { //if already has a team - remove him from it
		dummy2->team->ownStudents->remove(dummy2);
		this->updateMostPowerful(dummy2->team);
	}
	Team* team = this->findTeam(teamID);
	if (!team) {
		return false;
	}
	Student* newStud = new Student(studentID, dummy2->grade, dummy2->PWR, team);
	if (!team->ownStudents->insert(newStud, NULL)) {
		delete newStud;
		return false;
	}
	delete newStud;
	dummy2->team = team;
	dummy->team = team;
	this->updateMostPowerful(team);
	return true;
}
//////////////////////////////////////////////-------------------------------------------
void Xmen::increaseLevel(int grade, int powerIncrease) { // changed from bool to void
    inOrderUpdate(students->root, grade, powerIncrease);
    updateTree(studentsPowers, grade, powerIncrease);
    inOrderTeams(teams->root, grade, powerIncrease);
}
//////////////////////////////////////////////-------------------------------------------
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
		*numOfStudents = 0;
		return NULL;
	}
	Student **studentsArray = this->studentsPowers->inorder(numOfStudents);
	int *sortedIDArray = (int *) malloc(sizeof(int) * ((*numOfStudents)));
	for (int i = *numOfStudents - 1, j = 0; i >= 0; i--, j++) {
		sortedIDArray[i] = (studentsArray[j]->ID);
	}
	delete[] studentsArray;
	return sortedIDArray;
}

int *Xmen::getAllStudentsByPower(int teamID, int *numOfStudents, int *exist) {
	Team *team = this->findTeam(teamID);
	if (!team) {
		*exist = DOESNT_EXIST;
		return NULL;
	}
	if (team->ownStudents->numOfElements == 0) {
		*numOfStudents = 0;
		return NULL;
	}
	Student **studentsArray = team->ownStudents->inorder(numOfStudents);
	int *sortedIDArray = (int *) malloc(sizeof(int) * ((*numOfStudents)));
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

//-------------------------------------------------------------------------------

//function for counting the amount of students in a given grade
void inOrderCount(
		AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator,
		int grade, int *counter) {
	if (!iterator) {
		return;
	}
	inOrderCount(iterator->left, grade, counter);
	if (iterator->keyValue->grade == grade) {
		(*counter)++;
	}
	inOrderCount(iterator->right, grade, counter);
}

//function for updating the new power of students in a given grade
void inOrderUpdate(
		AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator,
		int grade, int powerInc) {
	if (!iterator) {
		return;
	}
	inOrderUpdate(iterator->left, grade, powerInc);
	if (iterator->keyValue->grade == grade) {
		iterator->keyValue->grade += powerInc;
	}
	inOrderUpdate(iterator->right, grade, powerInc);
}

void inOrderUpdate(
		AVLtree<Student, Student, compByStudentID>::AVLNode *iterator,
		int grade, int powerInc) {
	if (!iterator) {
		return;
	}
	inOrderUpdate(iterator->left, grade, powerInc);
	if (iterator->keyValue->grade == grade) {
		iterator->keyValue->grade += powerInc;
	}
	inOrderUpdate(iterator->right, grade, powerInc);
}

//function that puts the studens in given grade in A array, others in B array.
void inOrderSplit(
		AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator,
		int grade, Student **a, int n, Student **b, int m) {//first call to func(n=m=0)
	if (!iterator) {
		return;
	}
	inOrderSplit(iterator->left, grade, a, n, b, m);
	if (iterator->keyValue->grade == grade) { // students in grade go to A array
		a[n++] = iterator->keyValue;
	} else {	// students not in grade go to B array
		b[m++] = iterator->keyValue;
	}
	inOrderSplit(iterator->right, grade, a, n, b, m);
}	//dont forget to inc the A array by given INC

//function for merging two students arrays(already sorted) into one sorted array.
void mergeStudentsArrays(Student **a, int n, Student **b, int m, Student** c) {
	int i = 0, j = 0, k = 0;
	while (i < n && j < m) {
		if (a[i]->PWR > b[i]->PWR) {
			c[k++] = b[j++];
		} else {
			c[k++] = a[i++];
		}
	}
	if (i < m) {
		for (int p = i; p < n; p++) {
			c[k++] = a[p];
		}
	} else {
		for (int p = j; p < m; p++) {
			c[k++] = b[p];
		}
	}
}

//________________________________________________________________________
//  makes a new tree with a given array of nodes
//________________________________________________________________________
//  This function operates on array of nodes. It returns a new AVLtree with
//  the elements from array.
//________________________________________________________________________
AVLtree<Student, Student, compByStudentPower>* arrayToTree(Student** treeArray,int size){
	  AVLtree<Student, Student, compByStudentPower>* newTree = new AVLtree<Student, Student, compByStudentPower>(size); //makes a new empty tree
      AVLtree<Student, Student, compByStudentPower>::AVLNode** newTreeArray = newTree->inorderNodes(NULL);//get empty nodes from the new tree.
      for(int i=0;i<size;++i){//update all the nodes.
        newTreeArray[i]->keyValue=treeArray[i];
        treeArray[i]=NULL;
      }
      return newTree;
  }

void updateTree(AVLtree<Student, Student, compByStudentPower> *tree, int grade, int powerIncrease)
{
    if(!tree) return;
    int counter = 0;
    inOrderCount(tree->root, grade, &counter);
    if(!counter) return;
    int numElements = tree->numOfElements;
    if(counter == numElements)
    {
        inOrderUpdate(tree->root, grade, powerIncrease);
        return;
    }
    Student** A = new Student*[counter];
    Student** B = new Student*[numElements-counter];
    Student** C = new Student*[numElements];
    inOrderSplit(tree->root, grade, A, 0, B, 0);
    for(int i=0; i<counter; i++) A[i]->PWR += powerIncrease;
    mergeStudentsArrays(A, counter, B, numElements-counter, C);
    tree = arrayToTree(C, numElements);
    delete[] A;
    delete[] B;
    delete[] C;
}

void inOrderTeams(AVLtree<Team, Team, compByTeamID>::AVLNode *root, int grade, int powerIncrease)
{
    if(!root) return;
    inOrderTeams(root->left, grade, powerIncrease);
    updateTree(root->keyValue->ownStudents, grade, powerIncrease);
    inOrderTeams(root->right, grade, powerIncrease);
}
