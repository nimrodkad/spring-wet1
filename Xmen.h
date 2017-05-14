#include "student.h"
#include "AVLtree.h"
#include "utils.h"
#include <iostream>

#define STUDENT_DOESNT_EXIST -1
#define TEAM_DOESNT_EXIST -2


//exception classes for catching errors
class studentDoesNotExist: public std::exception{};
class teamDoesNotExist: public std::exception{};


//main class for the Xmen of the students and teams.
//contains the most powerful ID and Power of the students in the whole school,
//also contains a teams AVL tree, a students AVL tree by ID and a students AVL tree by Level.
class Xmen {
public:
  int mostPowerfulID;
  int mostPowerfulPower;
  AVLtree<Team, Team, compByTeamID> *teams;
  AVLtree<Student, Student, compByStudentID> *students;
  AVLtree<Student, Student, compByStudentPower> *studentsPowers;
  Xmen();
  ~Xmen();

  //addStudent function: inserts a new student in both student trees(sorted by ID and Power)
  //returns true if SUCCESS and false otherwise.
  bool addStudent(int studentID, int grade, int power);

  //addTeam function: inserts a new team to the teams tree,
  //returns true if SUCCESS and false otherwise.
  bool addTeam(int teamID);

  //findTeam function: searches for a specific team in the tree by its ID,
  //returns true if the team was found and false otherwise.
  Team* findTeam(int teamID);

  //findStudent function: searches for a specific student by their ID,
  //returns a pointer to the student if found
  //and NULL otherwise.
  Student* findStudent(int studentID, Student** studentOut);

  //moveStudentToTeam function: moves a given student to a given team by their IDs.
  //returns true if the student was moved successfully and false otherwise.
  bool moveStudentToTeam(int studentID, int teamID);

  //getMostPowerful function: gets the most powerful student's ID in
  //the whole school
  int getMostPowerful();

  //getMostPowerful function: gets the most powerful student's ID in
  //a given team
  int getMostPowerful(int teamID);

  //removeStudent function: removes a given student from all trees.
  //returns true if SUCCESS and false otherwise.
  bool removeStudent(int studentID);

  //getAllStudentsByPower function: sorts all students in
  //the school by their power(or ID). returns a sorted students ID array,
  //and the number of them in the pointer.
  void getAllStudentsByPower(int *numOfStudents, int **Students);

  //getAllStudentsByPower function: sorts all students in
  //a given team by their power(or ID). returns a sorted students ID array,
  //and the number of them in the pointer.
  void getAllStudentsByPower(int teamID, int *numOfStudents, int **Students, int *exist);

  //increaseLevel function: increases the power of all students in a given grade
  //by a positive number. returns true if SUCCESS and false otherwise.
  void increaseLevel(int grade, int powerIncrease);

  //updateMostPowerful function: updates the most powerful student in
  //a given team
  void updateMostPowerful(Team* team);

  //updateMostPowerful function: updates the most powerful student in
  //the whole school
  void updateMostPowerful();

};

//Helper functions for IncreaseLevel
void inOrderUpdate(AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator, int grade, int powerInc);
void inOrderUpdate(AVLtree<Student, Student, compByStudentID>::AVLNode *iterator, int grade, int powerInc);
void inOrderCount(AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator, int grade, int *counter);
void inOrderSplit(AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator, int grade, Student **a, int *n, Student **b, int *m);
void mergeStudentsArrays(Student **a, int n, Student **b, int m, Student** c);
AVLtree<Student, Student, compByStudentPower>* arrayToTree(Student** treeArray,int size);
void updateTree(AVLtree<Student, Student, compByStudentPower> **tree, int grade, int powerIncrease);
void inOrderTeams(Xmen *xmen,AVLtree<Team, Team, compByTeamID>::AVLNode *root, int grade, int powerIncrease);
void inOrderUpdateStudent(AVLtree<Student, Student, compByStudentPower>::AVLNode *iterator);
