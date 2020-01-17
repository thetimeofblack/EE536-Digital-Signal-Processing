// dipHeader.h
// Created by Yining HE on 1/19/18.
// Copyright © 2020 Yining HE. All rights reserved.

#ifndef dipHeader_h
#define dipHeader_h 
#endif
#define _CRT_SECURE_NO_WARNINGS
// these definition may cause confusion for the compiler 
// #define R 0  
// #define G 1
// #define B 2 

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std; 

// Allocate memory for image
void alloc2DImage(unsigned char** imageData, int width , int height, int BytePerPixel);
void alloc3DImage(unsigned char** imageData, int width, int height, int BytePerPixel); 


// IO function for image input and output 
void read2DImage(FILE *file, unsigned char**imageData, int width , int height , int BytePerPixel  ); 
void read3DImage(FILE *file, unsigned char*** imageData, int width, int height , int channels); 
void write2DImage(FILE *file , unsigned char **imageData, int width , int height); 
void write3DImage(FILE* file, unsigned char*** imageData, int width, int height , int channels);



// extend image edges to avoid the different solution for edge pixels 
void extend2DImageEdge(unsigned char **imageData, unsigned char **extendedImage , int width , int height, int BytePerPixel); 
void  extend3DImageEdge(unsigned char ***imageData, unsigned char **extendedImage , int width , int height, int BytePerPixel); 





// return a number that indicates color of current pixels 
// RGB  R 0 G 1 B 2  
// input the position of current pixel
// the row and col indicates the position of the pixel, the start pixel is at position (0,0)   
int judgePixelColor(int row , int col);



int judgePixelColor(int row , int col){
    if(row%2==1 &&col%2==1||row%2==0&&col%2==0){
        return 1 ; 
    }else if(row%2==0&&col%2==1){
        return 0 ; 
    }else{
        return 2 ; 
    }
}


// test library inclusion 
void testHeaderIncluded(){
    cout<<"Hello World"<<endl;     
}


// if the input image only contains one pixel, this will return null ;  
// the copied image obeys the reflection rule
void extend2DImageEdge(unsigned char **imageData, unsigned char **extendedImage,  int width , int height , int BytePerPixel){
    unsigned char **extendedImage ;
    int extendedWidth = width +4 ; 
    int extendedHeight = height+4; 
    for (int row=0 ;row<extendedHeight;row++){
        for (int col = 0; col < extendedWidth; col++) {
            //assign space for columns 

            if (row == 0) {
                extendedImage[0][0] = imageData[1][1];
                extendedImage[0][1] = imageData[0][1];
                extendedImage[0][width + 2] = imageData[0][width - 2];
                extendedImage[0][width + 3] = imageData[0][width - 1];
                for (int col = 2; col < extendedWidth - 2; col++) {
                    extendedImage[0][col] = imageData[1][col - 2];
                }
            }

            if (row == 1) {
                extendedImage[1][0] = imageData[1][1];
                extendedImage[1][1] = imageData[0][1];
                extendedImage[1][width + 2] = imageData[0][width - 2];
                extendedImage[1][width + 3] = imageData[0][width - 1];
                for (int col = 2; col < extendedWidth - 2; col++) {
                    extendedImage[1][col] = imageData[0][col - 2];
                }
            }

            if (row == extendedHeight - 1) {
                extendedImage[extendedHeight - 1][0] = imageData[height - 1][1];
                extendedImage[extendedHeight - 1][1] = imageData[height - 1][0];
            }

            if (row == extendedHeight - 2) {

            }
            if (row>=2&&col == 0&&row<extendedHeight-2) {

            }
            if (col == 1&& row>=2&&row<extendedHeight-2) {

            }



        }
       
    }


}


unsigned char compRedForGreenBL(unsigned char **imageData, int row, int col) {
    unsigned char result; 
    result = 0.5 * (imageData[row+1][col]+imageData[row-1][col]); 
    return result; 
}


unsigned char compRedforBlueBL(unsigned char** imageData, int row, int col) {
    unsigned char result; 
    result = 0.25 * (imageData[row + 1][col + 1] +imageData[row+1][col-1] +imageData[row-1][col+1]+imageData[row-1][col-1]);
    return result; 
}

unsigned char compGreenforRedBL(unsigned char** imageData, int row, int col) {
    unsigned char result; 
    result = 0.25 * (imageData[row + 1][col + 1] + imageData[row + 1][col - 1] + imageData[row - 1][col + 1] + imageData[row - 1][col - 1]);

    return result; 
}

unsigned char compGreenforBlueBL(unsigned char** imageData, int row, int col) {
    unsigned char result;
    result = 0.25 * (imageData[row + 1][col + 1] + imageData[row + 1][col - 1] + imageData[row - 1][col + 1] + imageData[row - 1][col - 1]);

    return result; 
}   

unsigned char compBlueforRedBL(unsigned char** imageData, int row, int col) {
    unsigned char result; 
    result = 0.25 * (imageData[row + 1][col + 1] + imageData[row + 1][col - 1] + imageData[row - 1][col + 1] + imageData[row - 1][col - 1]);

    return result;
}

unsigned char compBlueforGreenBL(unsigned char** imageData, int row, int col) {
    unsigned char result;
    result = 0.25 * (imageData[row + 1][col + 1] + imageData[row + 1][col - 1] + imageData[row - 1][col + 1] + imageData[row - 1][col - 1]);

    return result; 
}

void read2DImage(FILE *file, unsigned char** imageData, int width, int height ,int BytesPerPixel) {
    for (int row = 0; row < height; row++) {
       fread(imageData[row], sizeof(unsigned char),  width * BytesPerPixel, file);
    }
}

void read3DImage(FILE* file, unsigned char*** imageData, int width, int height, int channels) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            fread(imageData[row][col], sizeof(unsigned char), channels, file); 
        }
    }
}

void write2DImage(FILE* file, unsigned char** imageData, int width, int height, int BytesPerPixel) {
    for (int row = 0; row < height; row++) {
        fwrite(imageData[row], sizeof(unsigned char), width * BytesPerPixel, file); 
    }

}

void write3DImage(FILE* file, unsigned char*** imageData, int width, int height, int channels) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            fwrite(imageData[row][col], sizeof(unsigned char), channels, file); 
        }
    }
}


void extend2DImageEdge(unsigned char** imageData, unsigned char** extendedImage, int width, int height, int BytePerPixel,int widsize) {
    for (int row = 0; row < height+2*widsize; row++) {
        for (int col = 0; col < width + 2 * widsize; col++) {
            if (row < widsize && col < widsize) {
            
            }
            if (row<widsize && col>=width + widsize&& col<width+widsize) {
            
            }
            if (row < widsize && col >= widsize + width) {
            
            }
            if (row >= widsize && row < widsize + height && col < widsize) {
            
            }
            if (row >= widsize + height && row < widsize * 2 + height && col < widsize) {
            
            }

        }
    
    }

}