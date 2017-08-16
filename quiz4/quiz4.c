#include <stdio.h>

typedef struct student
{
	int idnum = 0;
	int firstname;
	int lastname;
	char* major;	
	float gpa;
}student; 

student* addStudent(student stuin[], int size);
student createStudent();

int main()
{
	int size = 5;
	student studentlist[size];

}
:
student createStudent()
{
	student tempstudent;
	printf("Please enter the student's ID number: ");
	scanf("%d", &tempstudent.idnum);
	printf("\nPlease enter the student's first name: ");
	scanf("%s", &tempstudent.firstname);
	printf("\nPlease enter the student's last name: ");
	scanf("%s", &tempstudent.lastname);
	printf("\nPlease enter the student's major name: ");
	scanf("%s", &tempstudent.major);
	printf("\nPlease enter the student's first GPA: ");
	scanf("%f", &tempstudent.firstname);
	return tempstudent;
}

student* addStudent(student stuin[], int size)
{
	student tempstudent;
	for (int i = 0; i < size; i++){
		tempstudent = createStudent();
		if (stuin[i].idnum == 0)
		{
			stuin[i] = tempstudent;
		}
	}
}


