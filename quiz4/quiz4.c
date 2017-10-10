#include <stdio.h>
#include <string.h>
//------------------Constants---------------------
const int size = 2;
//------------------Constants--------------------
//------------------Structures---------------------
typedef struct student {
	int ID;
	char firstname[100];
	char lastname[100];
	char major[100];
	float gpa;
}student;
//------------------Structures---------------------
//------------------Function Declarations---------------------
student createStudent();
student findStudent(student studarray[], char firstname[100], char lastname[100]);
void printStudent(student studin);
//------------------Function Declarations---------------------

int main()
{
	int flag = 1;
	char ans;
	student studentList[size];
	for (int i = 0; i < size; i++)
	{
		studentList[i] = createStudent();
	}

	while (flag == 1)
	{
		printf("Would you like to find a user [y/n]");
		scanf(" %c", &ans);
		if(ans == 'N' || ans =='n')
		{
			flag = 0;
		}
		else
		{
			char firstname [100];
			char lastname [100];
			printf("Please input the student's first name: ");
			scanf("%s", firstname);
			printf("\nPlease input the student's last name: ");
			scanf("%s", lastname);
			printf("\n");
			student tempstud = findStudent(studentList, firstname, lastname);
			if ((strcmp(tempstud.firstname, "-null-")==0))
			{
			}
			else
			{
				printStudent(tempstud);
			}
		}



	}

}

student createStudent()
{
	student tempstudent;
	
	printf("\nPlease enter the Student's ID number: ");
	scanf("%d", &tempstudent.ID);

	printf("\nPlease enter the Student's first name: ");
	scanf("%s", tempstudent.firstname);

	printf("\nPlease enter the Student's last name: ");
	scanf("%s", tempstudent.lastname);

	printf("\nPlease enter the Student's major: ");
	scanf("%s", tempstudent.major);

	printf("\nPlease enter the Student's GPA: ");
	scanf("%f", &tempstudent.gpa);
	

	return tempstudent;

}

student findStudent(student studarray[], char firstname[100], char lastname[100])
{
	for(int i = 0; i < size; i++)
	{

		if((strcmp(firstname, studarray[i].firstname) == 0) && (strcmp(lastname,studarray[i].lastname)==0))
		{
			return studarray[i];
		}
					
	}

	student temp;
	char words[100] = "-null-";
	strcpy(temp.firstname, words);
	return temp;

}

void printStudent(student studin){
	printf("ID Number: %d\n", studin.ID);
	printf("First Name: %s\n", studin.firstname);
	printf("Last Name: %s\n", studin.lastname);
	printf("Major: %s\n", studin.major);
	printf("GPA: %f\n", studin.gpa);
}
