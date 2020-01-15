// dipHeader.h
// Created by Yining HE on 1/19/18.
// Copyright © 2020 Yining HE. All rights reserved.

#ifndef dipHeader_h
#define dipHeader_h 
#endif

// these definition may cause confusion for the compiler 
// #define R 0  
// #define G 1
// #define B 2 

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std; 




// IO function for image input and output 
void readImage(char *imagepath, unsigned char*imageData, int width , int height ); 
void writeGrayImage(char *imagepath , unsigned char **imageData, int width , int height); 

// extend image edges to avoid the different solution for edge pixels 
unsigned char ** extend2DImageEdge(unsigned char **imageData, int width , int height, int pixelperByte); 
unsigned char *** extend3DImageEdge(unsigned char ***imageData, int width , int height, int pixelperByte); 
unsigned char ** cut2DImageEdge(unsigned char **imageData); 


// return a number that indicates color of current pixels 
// RGB  R 0 G 1 B 2  
// input the position of current pixel
// the row and col indicates the position of the pixel, the start pixel is at position (0,0)   
int judgePixelColor(int row, int col); 




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
unsigned char ** extend2DImageEdge(unsigned char **imageData,  int width , int height , int pixelperByte){
    unsigned char **extendedImage ;
    int extendedWidth = width +4 ; 
    int extednedHeight = height+4; 
    extendedImage = new unsigned char *[extednedHeight](); 
    for (int row=0 ;row<height;row++){
        
        //assign space for columns 
        extendedImage[row]  = new unsigned char [extendedWidth](); 
        
        if(row==0){
            extendedImage[0][0] = imageData[1][1] ; 
            extendedImage[0][1] = imageData[0][1] ; 
            extendedImage[0][width+2] = imageData[0][width-2];
            extendedImage[0][width+3] = imageData[0][width-1];
            for(int col=2 ; col<extendedWidth-2;col++){
                extendedImage[0][col] = imageData[1][col-2]; 
            }  
        }

        if(row==1){
            extendedImage[1][0] = imageData[1][1] ; 
            extendedImage[1][1] = imageData[0][1] ; 
            extendedImage[1][width+2] = imageData[0][width-2];
            extendedImage[1][width+3] = imageData[0][width-1];
            for(int col=2 ; col<extendedWidth-2;col++){
                extendedImage[1][col] = imageData[0][col-2]; 
            }  
        }

        if(row==extednedHeight-1){

        }

        if(row==extednedHeight-2){

        }

        if(row>=2||row<=extednedHeight-3){
            for(int col = 0 ;col<width ;col++){
                    if(col==0){
                        extendedImage[0][0] = imageData[0][0];
                        extendedImage[height+1][0]= extendedImage[0][0]; 
                    }
            }
        }
    }
    return extendedImage ;

}


