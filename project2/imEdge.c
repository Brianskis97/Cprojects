#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "iplib2New.c"

image_ptr read_pnm(char *filename, int *rows, int *cols, int *type);
int getnum(FILE *fp);
void write_pnm(image_ptr ptr, char *filename, int rows, int cols, int type);

void calculateERHeight(image_ptr imageERHeight, image_ptr imageInput, int rows, int cols);
void calculateERWidth(image_ptr imageERWidth, image_ptr imageInput, int rows, int cols);
void combineERImages(image_ptr imageERHeight, image_ptr imageERWidth, image_ptr imageERComb, int rows, int cols);
void makeBinaryImage(image_ptr binary, image_ptr edgeResponseIn, int rows, int cols);

int main(int argc, char **argv)
{
    image_ptr imageIn;
    image_ptr outputImage;
    image_ptr imageERHeight;
    image_ptr imageERWidth;
    image_ptr imageERComb;
    image_ptr binaryHeight;
    image_ptr binaryWidth;
    image_ptr binaryComb;
    
    

    int rows, cols, type;
    
    if (argc != 8)
    {
      printf("wrong inputs: use %s imageIn.ppm outEh.ppm outEv.ppm outE.ppm outBh.ppm outBv.ppm outB.ppm \n", argv[0]);  
      return 0;
    }

    imageIn = read_pnm(argv[1], &rows, &cols, &type);
    printf("rows=%d, cols=%d, type=%d \n", rows, cols, type);
    outputImage = malloc(rows * cols *sizeof(unsigned char*));
    imageERHeight = malloc(rows * cols *sizeof(unsigned char*));
    imageERWidth = malloc(rows * cols *sizeof(unsigned char*));
    imageERComb = malloc(rows * cols *sizeof(unsigned char*));
    binaryHeight = malloc(rows * cols *sizeof(unsigned char*));
    binaryWidth= malloc(rows * cols *sizeof(unsigned char*));
    binaryComb = malloc(rows * cols *sizeof(unsigned char*));
    
    
    calculateERHeight(imageERHeight, imageIn, rows, cols);
    calculateERWidth(imageERWidth, imageIn, rows, cols);
    combineERImages(imageERHeight, imageERWidth, imageERComb, rows, cols);
    makeBinaryImage(binaryHeight, imageERHeight, rows, cols);
    makeBinaryImage(binaryWidth, imageERWidth, rows, cols);
    makeBinaryImage(binaryComb, imageERComb, rows, cols);

    write_pnm(imageERHeight, argv[2], rows, cols, type);
    write_pnm(imageERWidth, argv[3], rows, cols, type);
    write_pnm(imageERComb, argv[4], rows, cols, type);
    write_pnm(binaryHeight, argv[5], rows, cols, type);
    write_pnm(binaryWidth, argv[6], rows, cols, type);
    write_pnm(binaryComb, argv[7], rows, cols, type);

    free(outputImage);
    free(imageERHeight);
    free(imageERWidth);
    free(imageERComb);

    return 0;
}

void calculateERHeight(image_ptr imageERHeight, image_ptr imageInput, int rows, int cols)
{
    
    int total;
    int mask[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    
    
    for (int i = 1; i < rows-1; i++)
    {
        for(int j = 1; j < cols-1; j++)
        {
            
            total = 0;
            total = total + ((unsigned int)imageInput[(i-1)*cols + (j-1)]) * mask[0][0];
            total = total + ((unsigned int)imageInput[(i)*cols + (j-1)]) * mask[0][1];
            total = total + ((unsigned int)imageInput[(i+1)*cols + (j-1)]) * mask[0][2];
            total = total + ((unsigned int)imageInput[(i-1)*cols + (j)]) * mask[1][0];
            total = total + ((unsigned int)imageInput[(i)*cols + (j)]) * mask[1][1];
            total = total + ((unsigned int)imageInput[(i+1)*cols + (j)]) * mask[1][2];
            total = total + ((unsigned int)imageInput[(i-1)*cols + (j+1)]) * mask[2][0];
            total = total + ((unsigned int)imageInput[(i)*cols + (j+1)]) * mask[2][1];
            total = total + ((unsigned int)imageInput[(i+1)*cols + (j+1)]) * mask[2][2];
            imageERHeight[i*cols + j] = (unsigned char) abs(total);
            
        }
    }
    
    
}

void calculateERWidth(image_ptr imageERWidth, image_ptr imageInput, int rows, int cols)
{
    int total;
    int mask[3][3] = {{-1,0,1},{-2,0,2,},{-1,0,1}};
    
    for (int i = 1; i < rows-1; i++)
    {
        for(int j = 1; j < cols-1; j++)
        {
            
            total = 0;
            total = total + ((unsigned int)imageInput[(i-1)*cols + (j-1)]) * mask[0][0];
            total = total + ((unsigned int)imageInput[(i-1)*cols + (j)]) * mask[0][1];
            total = total + ((unsigned int)imageInput[(i-1)*cols + (j+1)]) * mask[0][2];
            total = total + ((unsigned int)imageInput[(i)*cols + (j-1)]) * mask[1][0];
            total = total + ((unsigned int)imageInput[(i)*cols + (j)]) * mask[1][1];
            total = total + ((unsigned int)imageInput[(i)*cols + (j+1)]) * mask[1][2];
            total = total + ((unsigned int)imageInput[(i+1)*cols + (j-1)]) * mask[2][0];
            total = total + ((unsigned int)imageInput[(i+1)*cols + (j)]) * mask[2][1];
            total = total + ((unsigned int)imageInput[(i+1)*cols + (j+1)]) * mask[2][2];
            imageERWidth[i*cols + j] = (unsigned char) abs(total);
            

        }
    }

}

void combineERImages(image_ptr imageERHeight, image_ptr imageERWidth, image_ptr imageERComb, int rows, int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            imageERComb[i*cols + j] = imageERHeight[i*cols + j] + imageERWidth[i*cols + j];
        }
    }
}




void makeBinaryImage(image_ptr binary, image_ptr edgeResponseIn, int rows, int cols)
{
    float total;
    float temp;
    float threshold;
    float average;
    float stdDev;
    float K=.65;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            total = edgeResponseIn[i*cols + j] + total; 
        }
    }

    average = total / ((cols-2)*(rows-1));

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            temp = pow((edgeResponseIn[i*cols + j] - total),2); 
        }
    }
    stdDev = sqrt((1/((rows-2)*(cols-2))*temp));
    threshold = average + (K * stdDev);

    for(int i = 0; i < rows-2; i++)
    {
        for(int j = 0; j < cols-2; j++)
        {
            if (edgeResponseIn[i*cols + j] >= threshold)
            {
                binary[i*cols + j] = 255;
            }
            else
            {
                binary[i*cols + j] = 0;
            }      
          }
    }
}
