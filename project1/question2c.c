#include <stdio.h>
#include <math.h>
#include <time.h>

int isPrime(int x);
int buildArray(int array[],int size);

int main(){
	int size;	
	size = 10000; /*default size of 10000 */
	int array[size];
	*array = buildArray(array, size);
	int start, end, total;
	start = clock();
	for(int i = 0; i < size; i++)
	{
		if(array[i] != 0 && (isPrime(array[i]) == 1))
		{
			printf("%d is a prime number.\n", array[i]);
		}
	}
	end = clock();
	total = end - start;
	printf("This took: %d clock ticks\n", total);

}

int buildArray(int array[], int size){

	for (int i = 0; i <size; i++)
	{
		if((i+1)%2==0)
		{
			array[i] = 0;
		}
		else
		{
			array[i] = i + 1;
		}
	}
	return *array;
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
