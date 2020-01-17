#include"dipHeader.h"
#include<bitset>
unsigned char compBluePixelDelta(unsigned char **imageData, int row, int col ,int height , int width) {
	unsigned char result = '0';
	//cout << imageData[row + 2][col] << endl << imageData[row - 2][col] << endl;
	result = imageData[row][col] - 0.25 * (imageData[row - 2][col] + imageData[row + 2][col] + imageData[row][col + 2] + imageData[row][col - 2]); 
	
	return result; 
}

unsigned char compRedPixelDelta(unsigned char** imageData, int row, int col) {
	unsigned char result ='0';
	result = imageData[row][col] - 0.25 * (imageData[row - 2][col] + imageData[row + 2][col] + imageData[row][col + 2] + imageData[row][col - 2]); 
	return result; 

}


unsigned char compGreenPixelDelta(unsigned char** imageData, int row, int col) {
	unsigned char result = '0'; 
	result = imageData[row][col] - 0.25 * (imageData[row + 1][col-1] + imageData[row + 1][col+1] + imageData[row-1][col-1] + imageData[row-1][col+1]);
	return result; 
}

void MHC_Demosaicing(unsigned char **imageData,unsigned char ***imageRGBData, int width, int height) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (judgePixelColor(row, col) == 0) {
				imageRGBData[row][col][0] = imageData[row+2][col+2];
				imageRGBData[row][col][1] = imageData[row + 2][col + 2];
			}
			if (judgePixelColor(row, col) == 1) {
				imageRGBData[row][col][1] = imageData[row + 2][col + 2];
			}
			if (judgePixelColor(row, col) == 2) {
				imageRGBData[row][col][2] = imageData[row + 2][col + 2];
			}
		}
	
	}
}

unsigned char aces2dArray(unsigned char** imageData, int row, int col, int rows ,int cols) {
	unsigned char temp =(unsigned char ) *((unsigned char*)imageData + row*cols + col+1);
	cout <<bitset<8> (temp) << endl;
	cout << imageData[row][col] << endl;
	imageData[row][col] = '3'; 
	//cout << "hello" << endl;
	return temp; 
}


int main() {

	unsigned char** imageData; 
	int width = 6; 
	int height = 6; 
	imageData =  (unsigned char **) malloc(height*sizeof(unsigned char *)); 
	for (int row = 0; row < height; row++) {
		imageData[row] = (unsigned char *)malloc(width*sizeof(unsigned char)); 
	}
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			imageData[row][col] = row + col + '0'; 
			cout << imageData[row][col];
		}
	}

	unsigned char number2 = '0'+1+1; 
	cout << endl<< bitset<8>(imageData[1][1]) << endl;
	cout << endl << "return value for fuction" << endl; 
	cout << bitset<8>(aces2dArray(imageData, 1, 1,height,width)) << endl;
	cout << imageData[3][3] << endl;   
	imageData[1][3] =255;
	cout <<bitset<8>( compBluePixelDelta(imageData, 3, 3, height, width));   
}