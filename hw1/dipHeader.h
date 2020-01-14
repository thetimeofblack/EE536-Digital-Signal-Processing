/*
dipHeader.h

Created by Yining HE on 1/19/18.
Copyright © 2020 Yining HE. All rights reserved.
*/
#ifndef dipHeader_h
#define dipHeader_h 
#endif
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std; 



void readImage(char *imagepath, unsigned char*imageData, int width , int height ); 

/*

*/
void extend2DImageEdge(unsigned char **imageData, int width , int height, int pixelperByte); 
void extend3DImageEdge(unsigned char **imageData, int width , int height, int pixelperByte); 



void testHeaderIncluded(){
    cout<<"Hello World"<<endl;     
}
void writeGrayImage(char *imagepath , unsigned char **imageData, int width , int height); 

void extend2DImageEdge(unsigned char **imageData,  int width , int height , int pixelperByte){
    unsigned char **extendedImage ;
    extendedImage = new unsigned char *[height+2](); 
    for (int i=0 ;i<height;i++){
        extendedImage[i]  = new unsigned char [width+2](); 
        for(int j = 0 ;j <width ;j++){
            if(i==0){
                extendedImage[0][j] = imageData[1][j]; 
            }
            if(i==height+1){
                extendedImage[height+1][j]= extendedImage[i][j]; 
            }
        }
    }
}

