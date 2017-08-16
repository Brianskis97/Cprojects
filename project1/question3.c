#include <stdio.h>

//Declarations
void turtleWorld();
typedef struct turtle turtle;
int isMove(char command[]);
int getDistance(char command[]);
//Data for the turtle
struct turtle{
	int x; //X location
	int y; //Y location
	int pen; //******* 0 means the pen is up, 1 means the pen is down ***********
	int direction; //0 is up, 1 is right, 2 is down, and 3 is left
};

//Main
int main()
{
	turtleWorld();
}

//World turtle will live in
void turtleWorld()
{
	char array[20][20];
	int flag = 0;
	int size;
	char* commands[] = {"5,10","2","3","5,10","3","5,3","6"};	//distances must be two digits aka 3 would be 03
	printf("%s\n", commands[0]);

	for (int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			array[i][j] = ' ';
		}
	}

	turtle turtle1 = {.x=0, .y=0, .pen=0, .direction= 1};
	size = sizeof(commands)/sizeof(char*);
	printf("%d\n", size);
	printf("%d\n",isMove(commands[0]));
	int ree = getDistance(commands[0]);

	for(int i = 0; i<size; i++)
	{
		if (isMove(commands[i]) == 1)
		{	
			int dist = getDistance(commands[i]);
			if (turtle1.direction == 1)
			{	
				int distleft = 20 - turtle1.x;
				if (dist < distleft)
				{
					
					for (int j = turtle1.x; j<(dist + turtle1.x); j++)
					{
						if(turtle1.pen == 1)
						{
							array[j][turtle1.y] = '*';
						}
					}
					turtle1.x = turtle1.x + dist -1;
				}
			}
			if(turtle1.direction == 3)
			{
				int distleft = turtle1.x - dist;
				if (dist <= turtle1.x+1)
				{
					for (int j = turtle1.x; j>(turtle1.x-(dist)); j--)
					{
						if(turtle1.pen == 1)
						{
							array[j][turtle1.y] = '*';
						}
					}
					turtle1.x = turtle1.x - dist+1;
				}

			}
			if(turtle1.direction == 2)
			{
				
				int distleft = 20 - turtle1.y;
				if (dist < distleft)
				{
					for (int j = turtle1.y; j<(dist + turtle1.y); j++)
					{
						if(turtle1.pen == 1)
						{
							array[turtle1.x][j] = '*';
						}
					}
					turtle1.y = turtle1.y + dist-1;
				}

			}
			if(turtle1.direction == 0)
			{	
				int distleft = turtle1.y;
				if (dist <= turtle1.y+1)
				{
					for (int j = turtle1.y; j>(turtle1.y-dist); j--)
					{
						if(turtle1.pen == 1)
						{
							array[turtle1.x][j] = '*';
						}
					}
					turtle1.y = turtle1.y - dist+1;
				}

			}
		}
		else if (commands[i] == "1")
		{
			turtle1.pen = 0;
		}
		else if (commands[i] == "2")
		{
			turtle1.pen = 1;
		}
		else if (commands[i] == "3")
		{
			if (turtle1.direction == 3)
			{
				turtle1.direction = 0;
			}
			else
			{
				turtle1.direction = turtle1.direction + 1;
			}

		}
		else if (commands[i] == "4")
		{
			if (turtle1.direction == 0)
			{
				turtle1.direction = 3;
			}
			else
			{
				turtle1.direction = turtle1.direction - 1;
			}

		}
		else if (commands[i] == "6")
		{
			for (int p = 0; p < 20; p++)
			{
				for (int q = 0; q<20; q++)
				{
					printf("%c", array[q][p]);
				}
				printf("\n");
			}
		}
		else if (commands[i] == "9")
		{
			break;
		}

				
	
	
	}

}

int isMove(char command[])
{
	if(command[0] == '5' && command[1] == ',')
	{
		return 1;
	}
	return 0;

}
int getDistance(char command[])
{
	int num;
	char tempchars[2];
	tempchars[0] = command[2];
	tempchars[1] = command[3];
	sscanf(tempchars,"%d", &num);
	return num;
}

