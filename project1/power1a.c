#include <stdio.h>

int integerPower( int base, int exponent);

int main(){
	int base, exponent = 0;
	int flag = 1;
	char response;

	while(flag == 1){
		printf( "Please enter the Base number: ");
		scanf("%d", &base);
		printf("Please enter the exponent: ");
		scanf("%d", &exponent);
		printf("Answer: %d\n", integerPower(base, exponent));
		printf("Would you like to run again?[y/n]: ");
		scanf(" %c", &response);
		if((response == 'n') || (response == 'N')){
			flag = 0;
		} 
	}
}

int integerPower( int base, int exponent) {
	int output = 1;
	for (int i = 0; i < exponent; i = i+1){
		output = output * base;
	}
	
	return output;
}
