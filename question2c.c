#include <stdio.h>
#include <math.h>

int isPrime(int x);
int buildArray(int size);

int main(){
	
	for(int i = 0; i < 10000; i++)
	{
		if (isPrime(i+1))
		{
			printf("%d\n", (i+1));
		}
	}		

}

int * buildArray(int size){
	int[] array;

	for (int i = 0; i <size; i++)
	{
		
	}
}

int isPrime(int x)
{
		
	for(int i = 2; i <= sqrt(x);i++ )
	{
		if(x%i==0)
		{
			return 0;
		}
		
	}
	return 1;

}
