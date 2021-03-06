#include "Xmen.h"
#include "utils.h"
#include <cassert>
#include <cstdlib>

Xmen::Xmen() : mostPowerfulID(STUDENT_DOESNT_EXIST), mostPowerfulPower(STUDENT_DOESNT_EXIST) {
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
			|| !this->studentsPowers->insert(newStud, NULL)) {
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
			this->students->find(this->students->root, dummyStudent1, &lastNode1);
	delete dummyStudent1;
	if (!studentById) {
		return NULL;
	}
	Student *dummyStudent2 = new Student(studentID, studentById->keyValue->grade, studentById->keyValue->PWR);
	AVLtree<Student, Student, compByStudentPower>::AVLNode *lastNode2;
	AVLtree<Student, Student, compByStudentPower>::AVLNode *studentByPwr =
			this->studentsPowers->find(this->studentsPowers->root, dummyStudent2, &lastNode2);
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
	AVLtree<Team, Team, compByTeamID>::AVLNode *teamNode = this->teams->find(this->teams->root, newTeam, &lastNode);
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
		Student *ownedDummy = new Student(studentID,dummy2->grade, dummy2->PWR);
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
        if(dummy2->team->ID == teamID){
            return true;
        }
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

void Xmen::increaseLevel(int grade, int powerIncrease) { // changed from bool to void
    inOrderUpdate(students->root, grade, powerIncrease); //increases the power in the StudentsByID tree
    updateTree(&studentsPowers, grade, powerIncrease);//increases the power in the StudentsByPWR tree
    this->updateMostPowerful();
    inOrderTeams(this,teams->root, grade, powerIncrease); // for each available team so the same
}

int Xmen::getMostPowerful() {
	if (this->students->numOfElements == 0) {
		return STUDENT_DOESNT_EXIST;
	} else {
		return this->mostPowerfulID;
	}
}

int Xmen::getMostPowerful(int teamID) {
	Team *team = this->findTeam(teamID);
	if (!team) {
		return TEAM_DOESNT_EXIST;
	}
	if (team->ownStudents->numOfElements == 0) {
		return STUDENT_DOESNT_EXIST;
	} else {
		return team->mostPowerfulID;
	}
}

void Xmen::getAllStudentsByPower(int *numOfStudents, int** Students) {
    *numOfStudents = this->studentsPowers->numOfElements;
	if (*numOfStudents == 0) {
        *Students=NULL;
		return;
	}
	Student **studentsArray = this->studentsPowers->inorder(numOfStudents);
	*Students = (int*)malloc(sizeof(int)*(*numOfStudents));
	for (int i = *numOfStudents - 1, j = 0; i >= 0; i--, j++) {
		(*Students)[i] = (studentsArray[j]->ID);
	}
	delete[] studentsArray;
}

void Xmen::getAllStudentsByPower(int teamID, int *numOfStudents, int **Students, int *exist) {
	Team *team = this->findTeam(teamID);
	if (!team) {
		*exist = TEAM_DOESNT_EXIST;
		return;
	}
	*numOfStudents = team->ownStudents->numOfElements;
	if (team->ownStudents->numOfElements == 0) {
        *Students=NULL;
		return;
	}
	Student **studentsArray = team->ownStudents->inorder(numOfStudents);
	*Students = (int *) malloc(sizeof(int) * ((*numOfStudents)));
	for (int i = *numOfStudents - 1, j = 0; i >= 0; i--, j++) {
		(*Students)[i] = (studentsArray[j]->ID);
	}
	delete[] studentsArray;
}

void Xmen::updateMostPowerful(Team *team) {
	if (team->ownStudents->numOfElements == 0) {
		team->mostPowerfulID = team->mostPowerfulPower = STUDENT_DOESNT_EXIST;
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
		this->mostPowerfulID = this->mostPowerfulPower = STUDENT_DOESNT_EXIST;
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
	if (!iterator || !iterator->keyValue) {
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
	if (!iterator || !iterator->keyValue) {
		return;
	}
	inOrderUpdate(iterator->left, grade, powerInc);
	if (iterator->keyValue->grade == grade) {
		iterator->keyValue->PWR += powerInc;
	}
	inOrderUpdate(iterator->right, grade, powerInc);
}

void inOrderUpdate(
		AVLtree<Student, Student, compByStudentID>::AVLNode *iterator,
		int grade, int powerInc) {
	if (!iterator || !iterator->keyValue) {
		return;
	}
	inOrderUpdate(iterator->left, grade, powerInc);
	if (iterator->keyValue->grade == grade) {
		iterator->keyValue->PWR += powerInc;
	}
	inOrderUpdate(iterator->right, grade, powerInc);
}

//the function puts NULL in the old tree pointers to student
void inOrderUpdateStudent(AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator){
		if (!iterator || !iterator->keyValue){
			return;
		}
		inOrderUpdateStudent(iterator->left);
		iterator->keyValue=NULL;
		inOrderUpdateStudent(iterator->right);
}

void inOrderSplit(
		AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator,
		int grade, Student **a, int *n, Student **b, int *m) {//first call to func(n=m=0)
	if (!iterator || !iterator->keyValue) {
		return;
	}
	inOrderSplit(iterator->left, grade, a, n, b, m);
	if (iterator->keyValue->grade == grade) { // students in grade go to A array
		a[*n] = iterator->keyValue;
		(*n)++;
	} else {	// students not in grade go to B array
		b[*m] = iterator->keyValue;
		(*m)++;
	}
	inOrderSplit(iterator->right, grade, a, n, b, m);
}	//dont forget to inc the A array by given INC

//function for merging two students arrays(already sorted) into one sorted array.
void mergeStudentsArrays(Student **a, int n, Student **b, int m, Student** c) {
	int i = 0, j = 0, k = 0;

    while (i < n && j < m)
    {
       //c[k++] = a[i]->PWR < b[j]->PWR ? a[i++] : b[j++];
       compByStudentPower comp;
       c[k++] = comp(a[i], b[j]) ? a[i++] : b[j++];
    }

    while (i < n)
        c[k++] = a[i++];


    while (j < m)
        c[k++] = b[j++];
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
      }
      delete []newTreeArray;
      return newTree;
  }

void updateTree(AVLtree<Student, Student, compByStudentPower> **tree, int grade, int powerIncrease)
{
    if(!tree) return;
    int counter = 0;
    inOrderCount((*tree)->root, grade, &counter); //count the number of student in the given grade
    if(!counter) return; //no students in this grade - finish
    int numElements = (*tree)->numOfElements;
    if(counter == numElements) //if all the students are from this grade
    {
        inOrderUpdate((*tree)->root, grade, powerIncrease);
        return;
    }
    AVLtree<Student, Student, compByStudentPower> *newTree;
    Student** A = new Student*[counter]; //students in given grade array
    Student** B = new Student*[numElements-counter]; //other students array
    Student** C = new Student*[numElements]; //array for the merged arrays.
    assert(A && B && C); //check if there is no alloc errors
    int n=0,m=0;
    inOrderSplit((*tree)->root, grade, A, &n, B, &m); //fills the A and B array
    for(int i=0; i<counter; i++) A[i]->PWR += powerIncrease;
    mergeStudentsArrays(A, counter, B, numElements-counter, C); //merge array into C array
    newTree = arrayToTree(C, numElements);
    inOrderUpdateStudent((*tree)->root); //puts null in the nodes of the tree before destruction
    delete *tree;
    *tree=newTree; 										//not sure if we can do this - or we need to return it from the function out
    delete[] A;
    delete[] B;
    delete[] C;
}//where do we delete the old tree? (before we do so we need to use inOrderUpdateStudent function)

void inOrderTeams(Xmen *xmen,AVLtree<Team, Team, compByTeamID>::AVLNode *root, int grade, int powerIncrease)
{
    if(!root || !root->keyValue) return;
    inOrderTeams(xmen,root->left, grade, powerIncrease);
    updateTree(&root->keyValue->ownStudents, grade, powerIncrease);
    xmen->updateMostPowerful(root->keyValue); //updates the most dangerous of the current tree
    inOrderTeams(xmen,root->right, grade, powerIncrease);
}
