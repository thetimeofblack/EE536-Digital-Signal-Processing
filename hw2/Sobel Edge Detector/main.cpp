#include "..\dipHeader.h"



unsigned char compXgradientPixel(unsigned char** ImageData) {

}


void compXGradient(unsigned char** ImageData, int width, int height ,int BytesPerPixel) {
	int widsize = 3; 

}

void compYGradient(unsigned char** ImageData, int width, int height, int BytesPerPixel) {

}


/*
    Y=0.2989∗R+0.5870∗G+0.1140∗B
*/
void convertRGB2GrayImage(unsigned char*** ImageRGBData, unsigned char** ImageData, int width, int height, int BytesPerPixel) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			double grayValue = 0.2989*ImageRGBData[row][col][0] + 0.5870*ImageRGBData[row][col][1] + 0.1140*ImageRGBData[row][col][2];
			
			ImageData[row][col] = round(grayValue); 
		}
	
	}
}

int main(int *argc, char* argv[]) {
	cout << "Hello world" << endl ; 


	double result = 0.2989 * 255 + 0.5870 * 255 + 0.1140 * 255; 
	cout << result << endl;
}