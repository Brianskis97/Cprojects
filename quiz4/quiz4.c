#include <stdio.h>
#include <string.h>

const int size = 5;

typedef struct student {
	int ID;
	char *firstname;
	char *lastname;
	char *major;
	float gpa;
}student;

student createStudent();

int main()
{
	student studentList[size];
	studentList[0] = createStudent();
	printf("%s", studentList[0].firstname);
	printf("%s", studentList[0].lastname);
}

student createStudent()
{
	student tempstudent;
	char *firstname, *lastname, *major;
	tempstudent.firstname = firstname;
	tempstudent.lastname = lastname;
	tempstudent.major =  major;
	printf("\nPlease enter the Student's ID number: ");
	scanf(" %d", &tempstudent.ID);
	printf("\nPlease enter the Student's first name: ");
	scanf(" %s", firstname);
	getchar();
	scanf("%*[^\n]%*1[\n]");
	printf("\nPlease enter the Student's last name: ");
	scanf(" %s", lastname);
	printf("\nPlease enter the Student's major: ");
	scanf(" %s", major);
	printf("\nPlease enter the Student's GPA: ");
	scanf(" %f", &tempstudent.gpa);

	return tempstudent;

}
