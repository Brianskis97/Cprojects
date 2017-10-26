#include <stdio.h>

const int alphaSize = 26;
const char lower[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
const char upper[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

int main()
{
    int letterOccur[alphaSize];
    FILE *readFile;
    FILE *outFile;
    char test[100];

    readFile = fopen("test", "r");
    
    for (int i = 0; i <alphaSize; i++)
    {
        letterOccur[i] = 0;    
     }

    while(fgets(test,100,readFile) != NULL)
    {
        for (int i = 0; i < (sizeof(test)/sizeof(char)); i++)
        {
            for(int j = 0; j < alphaSize; j++)
            {
                if (test[i] == lower[j] || test[i] == upper[j])
                {
                    printf("%c: %d\n",test[i] ,letterOccur[4]);
                    letterOccur[j] = letterOccur[j] + 1;
                }
            } 
        }
    }

    printf("%c: %d\n",lower[4], letterOccur[4]);
}



int* countletters(int letarrin[])
{
    
}
