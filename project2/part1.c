#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//---------------------------------------------------------Constant Variables---------------------------------------------------------------start
const int alphaSize = 26;
const char lower[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const char upper[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
const char numbers[] = {'0','1','2','3','4','5','6','7','8','9'};
const char symbols[] = {'~', '!', '@', '#', '$', '%', '^', '&', '*', '(', '_', '+', '-', '=', ')', '\\', '[', ']', '{', '}', ':', ';', '<', '>', ',', '.', '/', '?', '"', '\n', '\t', '\r'};
//---------------------------------------------------------Constant Variables---------------------------------------------------------------end

//---------------------------------------------------------Non Struct-Dependent Function Declarationss---------------------------------------------------------------start
int getFileSize(FILE *fileIn);
int getNumWords(char *charInputIn, int fileSizeIn);
void countLetters(char *charInputIn, int fileSizeIn, int *letterOccur);
void createWordsList(char **wordsListIn, int numWords, int fileSizeIn, char *charInputIn);
int isSymbol(char input);
int isNumber(char input);
int getWordLength(char *word);
//---------------------------------------------------------Non Struct-Dependent Function Declarations---------------------------------------------------------------end

//---------------------------------------------------------Struct Declarations---------------------------------------------------------------start
struct wordLengthElement
{
    int numLetters;
    int occurences;
};

struct wordElement
{
    char *word;
    int occurences;
};
//---------------------------------------------------------Struct Declarations---------------------------------------------------------------end

//---------------------------------------------------------Struct Dependent Function Declarations---------------------------------------------------------------start
int doesWordLengthExist(int num, struct wordLengthElement *elementIn, int numWords);
void fillWordLengthList(struct wordLengthElement *elementsIn, int numWords, char **wordsList);
void sortWordLengthList(struct wordLengthElement *elementsIn, int numWords);
int doesWordElementExist(char *word, struct wordElement *elementsIn, int numWords);
void fillWordElementList(struct wordElement *elementsIn, int numWords, char **wordsList);
void sortWordElementListByWord(struct wordElement *elementsIn, int numWords);
void sortWordElementListByWordOccur(struct wordElement *elementsIn, int numWords);
//---------------------------------------------------------Struct Dependent Function Declarations---------------------------------------------------------------end

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("You must enter a file name!\nFormat: ./program inputFile outputFile\nOutput File is optional!\n");
    }
    else
    {

        int *letterOccur;
        FILE *readFile;
        FILE *outFile;
        char *charInput;
        char *buffer;
        int fileSize;
        int numWords;
        char **wordsList;
        struct wordLengthElement *wordLengthList;
        struct wordElement *wordElementList;

        readFile = fopen(argv[1], "r");
        if (readFile)
        {
            fileSize = getFileSize(readFile);
            charInput = malloc(fileSize * sizeof(char));
            buffer = malloc(fileSize * sizeof(char));
            letterOccur = malloc(fileSize * sizeof(char));

            for (int i = 0; i < alphaSize; i++)
            {
                letterOccur[i] = 0;
            }

            while (fgets(buffer, (fileSize + 1), readFile) != NULL)
            {
                charInput = strcat(charInput, buffer);
            }
            free(buffer);

            numWords = getNumWords(charInput, fileSize);
            countLetters(charInput, fileSize, letterOccur);
            wordsList = (char **)malloc(numWords * sizeof(char *));
            wordLengthList = (struct wordLengthElement *)malloc(numWords * sizeof(struct wordLengthElement));
            wordElementList = (struct wordElement *)malloc(numWords * sizeof(struct wordElement));

            for (int i = 0; i < numWords; i++)
            {
                wordsList[i] = (char *)malloc(100 * sizeof(char));
            }

            for (int i = 0; i < numWords; i++)
            {
                wordElementList[i].word = (char *)malloc(100 * sizeof(char));
                wordElementList[i].word[0] = '\0';
            }

            createWordsList(wordsList, numWords, fileSize, charInput);

            fillWordLengthList(wordLengthList, numWords, wordsList);
            fillWordElementList(wordElementList, numWords, wordsList);

            
            if (argc == 2)
            {
                printf("Letter  Occurence\n");
                for (int i = 0; i < alphaSize; i++)
                {
                    printf("%c:      %d\n", upper[i], letterOccur[i]);
                }

                printf("----------------------\n");
                printf("WordLength   Occurence\n");

                for (int i = 0; i < numWords && wordLengthList[i].numLetters != 0; i++)
                {
                    printf("%d:           %d\n", wordLengthList[i].numLetters, wordLengthList[i].occurences);
                }

                printf("----------------------\n");
                printf("Words vs Occurence (Unsorted)\n");
                printf("%21s    %s\n", "Word", "Occurence");

                for (int i = 0; i < numWords && wordElementList[i].word[0] != '\0'; i++)
                {
                    printf("%20s: %4d\n", wordElementList[i].word, wordElementList[i].occurences);
                }

                sortWordElementListByWord(wordElementList, numWords);
                printf("----------------------\n");
                printf("Words vs Occurence (Sorted by Word)\n");
                printf("%21s    %s\n", "Word", "Occurence");

                for (int i = 0; i < numWords && wordElementList[i].word[0] != '\0'; i++)
                {
                    printf("%20s: %4d\n", wordElementList[i].word, wordElementList[i].occurences);
                }

                sortWordElementListByWordOccur(wordElementList, numWords);
                printf("----------------------\n");
                printf("Words vs Occurence (Sorted by Occurence)\n");
                printf("%21s    %s\n", "Word", "Occurence");

                for (int i = 0; i < numWords && wordElementList[i].word[0] != '\0'; i++)
                {
                    printf("%20s: %4d\n", wordElementList[i].word, wordElementList[i].occurences);
                }
            }

            else if (argc == 3)
            {
                outFile = fopen(argv[2], "w");
                fprintf(outFile, "Letter  Occurence\n");
                for (int i = 0; i < alphaSize; i++)
                {
                    fprintf(outFile, "%c:      %d\n", upper[i], letterOccur[i]);
                }

                fprintf(outFile, "----------------------\n");
                fprintf(outFile, "WordLength   Occurence\n");

                for (int i = 0; i < numWords && wordLengthList[i].numLetters != 0; i++)
                {
                    fprintf(outFile, "%d:           %d\n", wordLengthList[i].numLetters, wordLengthList[i].occurences);
                }

                fprintf(outFile, "----------------------\n");
                fprintf(outFile, "Words vs Occurence (Unsorted)\n");
                fprintf(outFile, "%21s    %s\n", "Word", "Occurence");

                for (int i = 0; i < numWords && wordElementList[i].word[0] != '\0'; i++)
                {
                    fprintf(outFile, "%20s: %4d\n", wordElementList[i].word, wordElementList[i].occurences);
                }

                sortWordElementListByWord(wordElementList, numWords);
                fprintf(outFile, "----------------------\n");
                fprintf(outFile, "Words vs Occurence (Sorted by Word)\n");
                fprintf(outFile, "%21s    %s\n", "Word", "Occurence");

                for (int i = 0; i < numWords && wordElementList[i].word[0] != '\0'; i++)
                {
                    fprintf(outFile, "%20s: %4d\n", wordElementList[i].word, wordElementList[i].occurences);
                }

                sortWordElementListByWordOccur(wordElementList, numWords);
                fprintf(outFile, "----------------------\n");
                fprintf(outFile, "Words vs Occurence (Sorted by Occurence)\n");
                fprintf(outFile, "%21s    %s\n", "Word", "Occurence");

                for (int i = 0; i < numWords && wordElementList[i].word[0] != '\0'; i++)
                {
                   fprintf(outFile, "%20s: %4d\n", wordElementList[i].word, wordElementList[i].occurences);
                }

            }



            free(wordsList);
            free(wordLengthList);
            free(charInput);
            free(letterOccur);
            return 0;

        }
        else
        {
            printf("File not found/ Incorrect Permissions!\n");
        }
    }
}

void countLetters(char *charInputIn, int fileSizeIn, int *letterOccur)
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

int getFileSize(FILE *fileIn)
{
    int size = 0;
    char temp;

    while (getc(fileIn) != EOF)
    {
        size = size + 1;
    }

    fseek(fileIn, 0L, SEEK_SET);

    return size;
}

int getNumWords(char *charInputIn, int fileSizeIn)
{
    int counter = 0;

    for (int i = 0; charInputIn[i] != '\0'; i++)
    {
        if (charInputIn[i] == ' ')
        {
            counter = counter + 1;
        }
    }

    return counter + 1;
}

void createWordsList(char **wordsList, int numWords, int fileSizeIn, char *charInputIn)
{
    int counter = 0;
    int wordCounter = 0;
    int locFlag = 0;
    char temp;

    for (int i = 0; i < fileSizeIn; i++)
    {
        temp = charInputIn[i];
        if (isSymbol(temp) == 1 || isNumber(temp) == 1)
        {
        }

        else if (temp == ' ')
        {
            wordsList[counter][wordCounter] = '\0';
            counter = counter + 1;
            wordCounter = 0;
        }

        else
        {
            wordsList[counter][wordCounter] = temp;
            wordCounter = wordCounter + 1;
        }
    }
}

int isSymbol(char input)
{
    int flag = 0;
    int sizeSymbols = (sizeof(symbols) / sizeof(char));
    for (int i = 0; i < sizeSymbols; i++)
    {
        if (input == symbols[i])
        {
            flag = 1;
        }
    }

    return flag;
}

int isNumber(char input)
{
    int flag = 0;
    int sizeNumbers = (sizeof(numbers) / sizeof(char));
    for (int i = 0; i < sizeNumbers; i++)
    {
        if (input == symbols[i])
        {
            flag = 1;
        }
    }

    return flag;
}

int getWordLength(char *word)
{
    int counter = 0;
    char temp = word[0];
    while (temp != '\0')
    {
        counter = counter + 1;
        temp = word[counter];
    }

    return counter;
}

int doesWordLengthExist(int num, struct wordLengthElement *elementsIn, int numWords)
{

    for (int i = 0; i < numWords; i++)
    {
        if (num == elementsIn[i].numLetters)
        {
            elementsIn[i].occurences = elementsIn[i].occurences + 1;
            return 1;
        }
        else if (elementsIn[i].numLetters == 0)
        {
            elementsIn[i].numLetters = num;
            elementsIn[i].occurences = elementsIn[i].occurences + 1;
            return 1;
        }
    }
    return 0;
}

void fillWordLengthList(struct wordLengthElement *elementsIn, int numWords, char **wordsList)
{

    for (int i = 0; i < numWords; i++)
    {
        if (wordsList[i][0] == '\0')
        {
        }
        else
        {
            int tempNum = getWordLength(wordsList[i]);

            doesWordLengthExist(tempNum, elementsIn, numWords);
        }
    }

    sortWordLengthList(elementsIn,numWords);   
    
}

void sortWordLengthList(struct wordLengthElement *elementsIn, int numWords)
{
    struct wordLengthElement tempElement;

    for (int i = 0; i < numWords && elementsIn[i].numLetters != 0; i++)
    {
        int j;
        for (j = i; j < numWords && elementsIn[j].numLetters != 0; j++)
        {
            if (elementsIn[j].numLetters < elementsIn[i].numLetters)
            {
                tempElement = elementsIn[j];
                elementsIn[j] = elementsIn[i];
                elementsIn[i] = tempElement;
            }
        }
    }
}

void fillWordElementList(struct wordElement *elementsIn, int numWords, char **wordsList)
{

    for (int i = 0; i < numWords; i++)
    {
        if (wordsList[i][0] == '\0')
        {
        }
        else
        {
            char *word = wordsList[i];
            doesWordElementExist(word, elementsIn, numWords);
        }
    }

    

    
}

int doesWordElementExist(char *word, struct wordElement *elementsIn, int numWords)
{

    for (int i = 0; i < numWords; i++)
    {
        if (strcasecmp(word, elementsIn[i].word) == 0)
        {
            elementsIn[i].occurences = elementsIn[i].occurences + 1;
            return 1;
        }
        else if (elementsIn[i].word[0] == '\0')
        {
            elementsIn[i].word = word;
            elementsIn[i].occurences = elementsIn[i].occurences + 1;
            return 1;
        }
    }
    return 0;
}

void sortWordElementListByWord(struct wordElement *elementsIn, int numWords)
{
    struct wordElement tempElement;

    for (int i = 0; i < numWords && elementsIn[i].word[0] != '\0'; i++)
    {
        int j;
        for (j = i; j < numWords && elementsIn[j].word[0] != '\0'; j++)
        {
            if (strcasecmp(elementsIn[j].word, elementsIn[i].word) < 0)
            {
                tempElement = elementsIn[j];
                elementsIn[j] = elementsIn[i];
                elementsIn[i] = tempElement;
            }
        }
    }
}

void sortWordElementListByWordOccur(struct wordElement *elementsIn, int numWords)
{
    struct wordElement tempElement;

    for (int i = 0; i < numWords && elementsIn[i].word[0] != '\0'; i++)
    {
        int j;
        for (j = i; j < numWords && elementsIn[j].word[0] != '\0'; j++)
        {
            if (elementsIn[j].occurences < elementsIn[i].occurences)
            {
                tempElement = elementsIn[j];
                elementsIn[j] = elementsIn[i];
                elementsIn[i] = tempElement;
            }
        }
    }
}
