#include <stdio.h>
#include <math.h>
#include <time.h>

int isPrime(int x);


int main(){
	double start, end, total;
	start = clock();	
	for(int i = 0; i < 10000; i++)
	{
		if (isPrime(i+1))
		{
			printf("%d\n", (i+1));
		}
	}		
	end = clock();
	total = end - start;
	printf("Execution time: %f clock ticks.", total);

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
