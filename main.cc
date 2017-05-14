
#include "Xmen.h"
#include "test_utils.h"
#include "library1.h"


static bool schooAddStudentTest(){

	Xmen* technion = (Xmen*)Init();
	ASSERT_TEST(technion != NULL);

	//checking errors of AddStudent:
	//invalid input:
	ASSERT_TEST(AddStudent(NULL,100,100,100) == INVALID_INPUT);
	ASSERT_TEST(AddStudent(technion,-1,100,100) == INVALID_INPUT);
	ASSERT_TEST(AddStudent(technion,0,100,100) == INVALID_INPUT);
	ASSERT_TEST(AddStudent(technion,100,-1,100) == INVALID_INPUT);
	ASSERT_TEST(AddStudent(technion,100,100,-1) == INVALID_INPUT);
	ASSERT_TEST(AddStudent(technion,100,100,0) == INVALID_INPUT);

	ASSERT_TEST(AddStudent(technion,1,0,1) == SUCCESS);
	//failure:
	ASSERT_TEST(AddStudent(technion,1,0,1) == FAILURE);


	Quit((void**)&technion);

	return true;
}

static bool schoolAddTeamTest(){

Xmen* technion = (Xmen*)Init();
	ASSERT_TEST(technion != NULL);

	//checking errors of AddTeam:
	//invalid input:
	ASSERT_TEST(AddTeam(NULL,1) ==  INVALID_INPUT);
	ASSERT_TEST(AddTeam(technion,-1) ==  INVALID_INPUT);
	ASSERT_TEST(AddTeam(technion, 0) ==  INVALID_INPUT);

	ASSERT_TEST(AddTeam(technion,1) ==  SUCCESS);
	//failure:
	ASSERT_TEST(AddTeam(technion,1) ==  FAILURE);

	Quit((void**)&technion);

	return true;
}


static bool schoolMoveStudentToTeamTest(){

Xmen* technion = (Xmen*)Init();
	ASSERT_TEST(technion != NULL);

	//checking errors of MoveStudentToTeam:
	//invalid input:
	ASSERT_TEST(MoveStudentToTeam(NULL,1,1) == INVALID_INPUT);
	ASSERT_TEST(MoveStudentToTeam(technion,-1,1) == INVALID_INPUT);
	ASSERT_TEST(MoveStudentToTeam(technion,0,1) == INVALID_INPUT);
	ASSERT_TEST(MoveStudentToTeam(technion,1,-1) == INVALID_INPUT);
	ASSERT_TEST(MoveStudentToTeam(technion,1,0) == INVALID_INPUT);

	//failure:
	ASSERT_TEST(MoveStudentToTeam(technion,1,1) == FAILURE);
	ASSERT_TEST(AddStudent(technion,1,1,1) == SUCCESS);
	ASSERT_TEST(MoveStudentToTeam(technion,1,1) == FAILURE);
	ASSERT_TEST(AddTeam(technion,1) == SUCCESS);
	ASSERT_TEST(MoveStudentToTeam(technion,1,1) == SUCCESS);
	ASSERT_TEST(MoveStudentToTeam(technion,1,1) == SUCCESS);


	ASSERT_TEST(AddTeam(technion,2) == SUCCESS);
	ASSERT_TEST(MoveStudentToTeam(technion,1,2) == SUCCESS);

	Quit((void**)&technion);

	return true;
}

static bool schoolGetMostPowerful(){


Xmen* technion = (Xmen*)Init();
	ASSERT_TEST(technion != NULL);

	int most_powerful_id;

	//checking errors of MoveStudentToTeam:
	//invalid input:
	ASSERT_TEST(GetMostPowerful(NULL,1,&most_powerful_id) == INVALID_INPUT);
	ASSERT_TEST(GetMostPowerful(technion,0,&most_powerful_id) == INVALID_INPUT);
	ASSERT_TEST(GetMostPowerful(technion,1,NULL) == INVALID_INPUT);

	//Failure:
	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_id) == FAILURE);

	ASSERT_TEST(AddTeam(technion,1) == SUCCESS);

	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == -1);

	ASSERT_TEST(AddStudent(technion,1,1,1) == SUCCESS);
	ASSERT_TEST(AddStudent(technion,2,1,1) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == -1);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 1);
	ASSERT_TEST(MoveStudentToTeam(technion,1,1) == SUCCESS);

	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 1);
	ASSERT_TEST(MoveStudentToTeam(technion,2,1) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 1);

	ASSERT_TEST(AddTeam(technion,2) == SUCCESS);
	ASSERT_TEST(MoveStudentToTeam(technion,1,2) == SUCCESS);

	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 2);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 1);



	Quit((void**)&technion);

	return true;
}



static bool schoolRemoveStudentTest(){

Xmen* technion = (Xmen*)Init();
	ASSERT_TEST(technion != NULL);
	int most_powerful_student;

	//checking errors of RemoveStudent:
	//invalid input:
	ASSERT_TEST(RemoveStudent(NULL,1) == INVALID_INPUT);
	ASSERT_TEST(RemoveStudent(technion,-1) == INVALID_INPUT);
	ASSERT_TEST(RemoveStudent(technion,0) == INVALID_INPUT);

	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_student) == -1);

	//Failure:
	ASSERT_TEST(RemoveStudent(technion, 1) == FAILURE);

	ASSERT_TEST(AddStudent(technion,1,1,1) == SUCCESS);
	ASSERT_TEST(AddStudent(technion,2,1,1) == SUCCESS);
	ASSERT_TEST(AddStudent(technion,3,1,1) == SUCCESS);

	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == 1);

	ASSERT_TEST(AddTeam(technion,1) == SUCCESS);
	ASSERT_TEST(AddTeam(technion,2) == SUCCESS);
	ASSERT_TEST(AddTeam(technion,3) == SUCCESS);

	ASSERT_TEST(MoveStudentToTeam(technion,1,1) == SUCCESS);//all students in team1
	ASSERT_TEST(MoveStudentToTeam(technion,2,1) == SUCCESS);
	ASSERT_TEST(MoveStudentToTeam(technion,3,1) == SUCCESS);

	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == 1);

	ASSERT_TEST(MoveStudentToTeam(technion,1,2) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == 2);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == 1);

	ASSERT_TEST(MoveStudentToTeam(technion,3,3) == SUCCESS);//st 1 in team 2
	                                                        //   2 in team 1
                                                            //   3 in team 3
	ASSERT_TEST(GetMostPowerful(technion,-1, &most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == 1);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == 1);

	ASSERT_TEST(RemoveStudent(technion,1) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == 2);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == -1);
	ASSERT_TEST(RemoveStudent(technion,2) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == 3);
	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == -1);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == 3);
	ASSERT_TEST(RemoveStudent(technion,3) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == -1);
	ASSERT_TEST(GetMostPowerful(technion,1, &most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == -1);
	ASSERT_TEST(GetMostPowerful(technion,2, &most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == -1);
	ASSERT_TEST(GetMostPowerful(technion,3, &most_powerful_student) == SUCCESS);
	ASSERT_TEST(most_powerful_student == -1);

	Quit((void**)&technion);

	return true;
}


static bool SchooGetAllStudentsByPowerTest(){

Xmen* technion = (Xmen*)Init();
	ASSERT_TEST(technion != NULL);
	int* students_by_power_array;
	int num_of_students;
	int most_powerful_id;

	//checking errors of GetAllStudentsByPower:
	//invalid input:
	ASSERT_TEST(GetAllStudentsByPower(NULL,1,&students_by_power_array,
			&num_of_students) == INVALID_INPUT);
	ASSERT_TEST(GetAllStudentsByPower(technion,0,&students_by_power_array,
				&num_of_students) == INVALID_INPUT);
	ASSERT_TEST(GetAllStudentsByPower(technion,1,NULL,
				&num_of_students) == INVALID_INPUT);
	ASSERT_TEST(GetAllStudentsByPower(technion,1,&students_by_power_array,
				NULL) == INVALID_INPUT);

	//Failure:
	ASSERT_TEST(GetAllStudentsByPower(technion,1,&students_by_power_array,
			&num_of_students) == FAILURE);

	ASSERT_TEST(GetAllStudentsByPower(technion,-1,&students_by_power_array,
			&num_of_students) == SUCCESS);
	ASSERT_TEST(students_by_power_array == NULL);
	ASSERT_TEST(num_of_students == 0);

	for(int i = 1; i<=10; i++){
		ASSERT_TEST(AddStudent(technion,i,i,1) == SUCCESS);
	}
	ASSERT_TEST(GetAllStudentsByPower(technion,-1,&students_by_power_array,
			&num_of_students) == SUCCESS);
	ASSERT_TEST(num_of_students == 10);
	for(int j=0; j<10; j++){
		ASSERT_TEST(students_by_power_array[j] == j+1);
	}
	delete []students_by_power_array;
		ASSERT_TEST(AddTeam(technion,1) == SUCCESS);
	ASSERT_TEST(AddTeam(technion,2) == SUCCESS);

	for(int i = 1; i<=10 ;i++){
		ASSERT_TEST(MoveStudentToTeam(technion,i,(i%2) + 1) == SUCCESS);
	}


	ASSERT_TEST(GetAllStudentsByPower(technion,1,&students_by_power_array,
			&num_of_students) == SUCCESS);
	for(int i=0; i<num_of_students; i++){
		ASSERT_TEST(students_by_power_array[i] == i*2+2);
	}
	if (students_by_power_array != NULL){
	delete []students_by_power_array;
	}

	ASSERT_TEST(GetAllStudentsByPower(technion,2,&students_by_power_array,
			&num_of_students) == SUCCESS);
	for(int i=0; i<num_of_students; i++){
		ASSERT_TEST(students_by_power_array[i] == i*2+1);
	}
	if (students_by_power_array != NULL){
	delete []students_by_power_array;
	}

	for(int i=1; i<=9; i=i+2){
		ASSERT_TEST(MoveStudentToTeam(technion,i,2) == SUCCESS);
	}
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 1);

	ASSERT_TEST(GetAllStudentsByPower(technion,2,&students_by_power_array,
			&num_of_students) == SUCCESS);
	for(int i = 0; i<num_of_students; i++){
		ASSERT_TEST(students_by_power_array[i] == i*2+1);
	}
	if (students_by_power_array != NULL){
	delete []students_by_power_array;
	}


	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 2);

	for(int i=1; i<=9; i=i+2){
		ASSERT_TEST(MoveStudentToTeam(technion,i,1) == SUCCESS);
	}
	ASSERT_TEST(GetAllStudentsByPower(technion,1,&students_by_power_array,
			&num_of_students) == SUCCESS);
	for(int i=0; i<num_of_students; i++){
		ASSERT_TEST(students_by_power_array[i] == i+1);
	}
	if (students_by_power_array != NULL){
	delete []students_by_power_array;
	}


	ASSERT_TEST(GetAllStudentsByPower(technion,2,&students_by_power_array,
			&num_of_students) == SUCCESS);
	ASSERT_TEST(num_of_students==0);
	ASSERT_TEST(students_by_power_array == NULL);
	if (students_by_power_array != NULL){
	delete []students_by_power_array;
	}

	Quit((void**)&technion);

	return true;
}


static bool schooIncreaseLevelTest(){

Xmen* technion = (Xmen*)Init();
	ASSERT_TEST(technion != NULL);
	int* students_by_power_array;
	int num_of_students;
	int most_powerful_id;


	//checking errors of IncreaseLevel:
		//invalid input:
	ASSERT_TEST(IncreaseLevel(technion,-1,1) == INVALID_INPUT);
	ASSERT_TEST(IncreaseLevel(technion,1,-1) == INVALID_INPUT);
	ASSERT_TEST(IncreaseLevel(technion,1,0) == INVALID_INPUT);
	ASSERT_TEST(IncreaseLevel(technion,1,1) == SUCCESS);

	ASSERT_TEST(AddTeam(technion,1) == SUCCESS);
	ASSERT_TEST(AddTeam(technion,2) == SUCCESS);

	for(int i = 1; i<=10; i++){
		ASSERT_TEST(AddStudent(technion,i,(i%2)+1,1) == SUCCESS);
	}

	for(int i = 1; i<=10; i++){
		ASSERT_TEST(MoveStudentToTeam(technion,i,(i%2)+1) == SUCCESS);
	}
	//10 students:
	//  id    |   grade   |   power   |   team
	//  1     |     2     |     1     |     2
	//  2     |     1     |     1     |     1
	//  3     |     2     |     1     |     2
	//  4     |     1     |     1     |     1
	//  5     |     2     |     1     |     2
	//  6     |     1     |     1     |     1
	//  7     |     2     |     1     |     2
	//  8     |     1     |     1     |     1
	//  9     |     2     |     1     |     2
	//  10    |     1     |     1     |     1

	ASSERT_TEST(GetAllStudentsByPower(technion,-1,&students_by_power_array,
			&num_of_students) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 1);
	for(int i = 0; i<num_of_students; i++){
		ASSERT_TEST(students_by_power_array[i] == i+1);
	}
	delete []students_by_power_array;


	ASSERT_TEST(IncreaseLevel(technion,1,1) == SUCCESS);//increase power by 1
	                                                    //to grade 1.
	ASSERT_TEST(GetAllStudentsByPower(technion,-1,&students_by_power_array,
			&num_of_students) == SUCCESS);
	for(int i = 0; i< num_of_students; i++){
		if(i <= 4){
			ASSERT_TEST(students_by_power_array[i] == (i*2)+2);
		} else{
			ASSERT_TEST(students_by_power_array[i] == ((i-5)*2) + 1);
		}
	}
	delete []students_by_power_array;


	ASSERT_TEST(GetAllStudentsByPower(technion,1,&students_by_power_array,
			&num_of_students) == SUCCESS);

	for(int i = 0 ; i < num_of_students; i++){
		ASSERT_TEST(students_by_power_array[i] == (i*2)+2);
	}
	delete []students_by_power_array;


	for(int i =1; i <=10; i++){
		ASSERT_TEST(MoveStudentToTeam(technion,i,1) == SUCCESS);
	}

	ASSERT_TEST(GetAllStudentsByPower(technion,1,&students_by_power_array,
			&num_of_students) == SUCCESS);
	for(int i = 0; i< num_of_students; i++){
		if(i <= 4){
			ASSERT_TEST(students_by_power_array[i] == (i*2)+2);
		} else{
			ASSERT_TEST(students_by_power_array[i] == ((i-5)*2) + 1);
		}
	}
	delete []students_by_power_array;


	for(int i = 9; i >=1; i=i-2){//
		ASSERT_TEST(RemoveStudent(technion,i) == SUCCESS);
		ASSERT_TEST(GetAllStudentsByPower(technion,1,&students_by_power_array,
				&num_of_students) == SUCCESS);

	for(int j = 0; j<num_of_students; j++){
			if(j<=4){
				ASSERT_TEST(students_by_power_array[j] == (j*2) +2);
			}else{
				ASSERT_TEST(students_by_power_array[j] == ((j-5)*2) +1);
			}
		}
	delete []students_by_power_array;
	}

	Quit((void**)&technion);

	return true;
}


static bool schoolBigTest(){

Xmen* technion = (Xmen*)Init();
	ASSERT_TEST(technion != NULL);
	int* students_by_power_array;
	int num_of_students;


	ASSERT_TEST(AddTeam(technion,1) == SUCCESS);
	ASSERT_TEST(AddTeam(technion,2) == SUCCESS);
	ASSERT_TEST(AddTeam(technion,3) == SUCCESS);

	int j = 1;
	for(int i = 3; i != 0 ; i = (i+3)%10){
		ASSERT_TEST(AddStudent(technion, j, j, i) == SUCCESS);
		if(j%3 == 0){
			ASSERT_TEST(MoveStudentToTeam(technion,j,1) == SUCCESS);
		} else if(j%3 == 1){
			ASSERT_TEST(MoveStudentToTeam(technion,j,2) == SUCCESS);
		} else{
			ASSERT_TEST(MoveStudentToTeam(technion,j,3) == SUCCESS);
		}
		j++;

	}

	for(int i = 3; i != 0 ; i = (i+3)%10){
		ASSERT_TEST(AddStudent(technion, j, j, i) == SUCCESS);
		if(j%3 == 0){
			ASSERT_TEST(MoveStudentToTeam(technion,j,1) == SUCCESS);
		} else if(j%3 == 1){
			ASSERT_TEST(MoveStudentToTeam(technion,j,2) == SUCCESS);
		} else{
			ASSERT_TEST(MoveStudentToTeam(technion,j,3) == SUCCESS);
		}
		j++;
	}

		//18 students:
		//  id    |   grade   |   power   |   team
		//  1     |     1     |     3     |     2
		//  2     |     2     |     6     |     3
		//  3     |     3     |     9     |     1
		//  4     |     4     |     2     |     2
		//  5     |     5     |     5     |     3
		//  6     |     6     |     8     |     1
		//  7     |     7     |     1     |     2
		//  8     |     8     |     4     |     3
		//  9     |     9     |     7     |     1
		//  10    |    10     |     3     |     2
		//  11    |    11     |     6     |     3
		//  12    |    12     |     9     |     1
		//  13    |    13     |     2     |     2
		//  14    |    14     |     5     |     3
		//  15    |    15     |     8     |     1
		//  16    |    16     |     1     |     2
		//  17    |    17     |     4     |     3
		//  18    |    18     |     7     |     1
	int most_powerful_id;

	ASSERT_TEST(IncreaseLevel(technion,16,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 16);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 16);

	ASSERT_TEST(IncreaseLevel(technion,7,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 7);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 7);

	ASSERT_TEST(IncreaseLevel(technion,13,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 13);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 13);

	ASSERT_TEST(IncreaseLevel(technion,4,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 4);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 4);

	ASSERT_TEST(IncreaseLevel(technion,10,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 10);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 10);

	ASSERT_TEST(IncreaseLevel(technion,1,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 1);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 1);

	ASSERT_TEST(IncreaseLevel(technion,17,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,3,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 17);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 17);

	ASSERT_TEST(IncreaseLevel(technion,8,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,3,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 8);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 8);

	ASSERT_TEST(IncreaseLevel(technion,14,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,3,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 14);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 14);

	ASSERT_TEST(IncreaseLevel(technion,5,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,3,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 5);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 5);

	ASSERT_TEST(IncreaseLevel(technion,11,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,3,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 11);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 11);

	ASSERT_TEST(IncreaseLevel(technion,2,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,3,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 2);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 2);

	ASSERT_TEST(IncreaseLevel(technion,18,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 18);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 18);

	ASSERT_TEST(IncreaseLevel(technion,9,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 9);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 9);

	ASSERT_TEST(IncreaseLevel(technion,15,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 15);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 15);

	ASSERT_TEST(IncreaseLevel(technion,6,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 6);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 6);

	ASSERT_TEST(IncreaseLevel(technion,12,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 12);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 12);

	ASSERT_TEST(IncreaseLevel(technion,3,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 3);
	ASSERT_TEST(GetMostPowerful(technion,-1,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 3);

	ASSERT_TEST(GetAllStudentsByPower(technion,1,&students_by_power_array,
			&num_of_students) == SUCCESS);
	ASSERT_TEST(students_by_power_array[0] == 3);
	ASSERT_TEST(students_by_power_array[1] == 12);
	ASSERT_TEST(students_by_power_array[2] == 6);
	ASSERT_TEST(students_by_power_array[3] == 15);
	ASSERT_TEST(students_by_power_array[4] == 9);
	ASSERT_TEST(students_by_power_array[5] == 18);
	delete []students_by_power_array;

	ASSERT_TEST(GetAllStudentsByPower(technion,2,&students_by_power_array,
			&num_of_students) == SUCCESS);
	ASSERT_TEST(students_by_power_array[0] == 1);
	ASSERT_TEST(students_by_power_array[1] == 10);
	ASSERT_TEST(students_by_power_array[2] == 4);
	ASSERT_TEST(students_by_power_array[3] == 13);
	ASSERT_TEST(students_by_power_array[4] == 7);
	ASSERT_TEST(students_by_power_array[5] == 16);
	delete []students_by_power_array;


	ASSERT_TEST(MoveStudentToTeam(technion,18,2) == SUCCESS);
	ASSERT_TEST(MoveStudentToTeam(technion,9,2) == SUCCESS);
	ASSERT_TEST(MoveStudentToTeam(technion,15,2) == SUCCESS);
	ASSERT_TEST(MoveStudentToTeam(technion,6,2) == SUCCESS);
	ASSERT_TEST(MoveStudentToTeam(technion,12,2) == SUCCESS);
	ASSERT_TEST(MoveStudentToTeam(technion,3,2) == SUCCESS);

	ASSERT_TEST(GetAllStudentsByPower(technion,2,&students_by_power_array,
			&num_of_students) == SUCCESS);
	ASSERT_TEST(students_by_power_array[0] == 3);
	ASSERT_TEST(students_by_power_array[1] == 12);
	ASSERT_TEST(students_by_power_array[2] == 6);
	ASSERT_TEST(students_by_power_array[3] == 15);
	ASSERT_TEST(students_by_power_array[4] == 9);
	ASSERT_TEST(students_by_power_array[5] == 18);


	ASSERT_TEST(students_by_power_array[6] == 1);
	ASSERT_TEST(students_by_power_array[7] == 10);
	ASSERT_TEST(students_by_power_array[8] == 4);
	ASSERT_TEST(students_by_power_array[9] == 13);
	ASSERT_TEST(students_by_power_array[10] == 7);
	ASSERT_TEST(students_by_power_array[11] == 16);

	delete []students_by_power_array;


	ASSERT_TEST(RemoveStudent(technion,3) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 12);


	ASSERT_TEST(RemoveStudent(technion,12) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 6);

	ASSERT_TEST(RemoveStudent(technion,6) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 15);

	ASSERT_TEST(RemoveStudent(technion,15) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 9);

	ASSERT_TEST(RemoveStudent(technion,9) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 18);

	ASSERT_TEST(RemoveStudent(technion,18) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 1);

	ASSERT_TEST(RemoveStudent(technion,1) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 10);

	ASSERT_TEST(RemoveStudent(technion,10) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 4);

	ASSERT_TEST(RemoveStudent(technion,4) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 13);

	ASSERT_TEST(RemoveStudent(technion,13) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 7);

	ASSERT_TEST(RemoveStudent(technion,7) == SUCCESS);
	ASSERT_TEST(GetMostPowerful(technion,2,&most_powerful_id) == SUCCESS);
	ASSERT_TEST(most_powerful_id == 16);


		Quit((void**)&technion);

return true;
}


int main(){

	RUN_TEST(schooAddStudentTest);
	RUN_TEST(schoolAddTeamTest);
	RUN_TEST(schoolMoveStudentToTeamTest);
	RUN_TEST(schoolGetMostPowerful);
	RUN_TEST(schoolRemoveStudentTest);
	RUN_TEST(SchooGetAllStudentsByPowerTest);
	RUN_TEST(schooIncreaseLevelTest);
	RUN_TEST(schoolBigTest);

	return 0;
}
