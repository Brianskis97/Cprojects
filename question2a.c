#include <stdio.h>
#include <math.h>
#include <time.h>

int isPrime(int x);

/* main runs through numbers 1-10000 and checks to see if they are prime using the isPrime fucntion */
 
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

	printf("You took: %f time.", total);


}

/* function 'isPrime' checks to see if a number is prime using the n/2 method 
 * b) you really only need to check the sqrt(n) numbers to see if a number is prime,
 * however the instructions require n/2
 * c) using the sqrt(n) method will be much faster because, for example, at 10000 
 * using the n/2 method you need to check at most 5000 numbers, while with the 
 * sqrt(n) method you only have to check 100.
*/

int isPrime(int x)
{
		
	for(int i = 2; i <= (x/2);i++ )
	{
		if(x%i==0)
		{
			return 0;
		}
		
	}
	return 1;

}
