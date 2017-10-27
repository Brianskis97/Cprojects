#include <stdio.h>
#include <stdlib.h>

const int alphaSize = 26;
const char lower[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
const char upper[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

int getFileSize(FILE *fileIn);
void countLetters(char * charInputIn, int fileSizeIn, int *letterOccur);

int main()
{
    int *letterOccur;
    FILE *readFile;
    FILE *outFile;
    char *charInput;
    int fileSize;

    readFile = fopen("test", "r");
    fileSize = getFileSize(readFile);
    charInput = malloc(fileSize);
    letterOccur = malloc(fileSize);

    for (int i = 0; i <alphaSize; i++)
    {
        letterOccur[i] = 0;    
    }


    while(fgets(charInput,(fileSize+1),readFile) != NULL){}

    countLetters(charInput, fileSize, letterOccur);

    for (int i = 0; i < alphaSize; i++)
    {
        printf("%c: %d\n", upper[i], letterOccur[i]);
    }
    
        
}

void countLetters(char * charInputIn, int fileSizeIn, int *letterOccur)
{


    for (int i = 0; i < fileSizeIn; i++)
    {
        for (int j = 0; j < alphaSize; j++)
        {
            if (charInputIn[i] == lower[j] || charInputIn[i] == upper[j])
            {
                letterOccur[j] = letterOccur[j] + 1;
            }
        }
    }


}

int getFileSize( FILE *fileIn)
{
    int size = 0;
    char temp;

    while(getc(fileIn) != EOF)
    {
        size = size + 1;
    }

    fseek(fileIn, 0L, SEEK_SET);

    return size;
}
