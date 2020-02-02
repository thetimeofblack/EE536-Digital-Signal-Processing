#include "..\dipHeader.h"

// Problem a 


/*
 Test code : 
	cout<<"Double Result: " << DoubleResult<< endl;
	cout<<"Final Result: "<<result << endl;
*/
unsigned char compXGradientPixel(unsigned char** ImageData , int row ,int col ,int BytesPerPixel) {
	double DoubleResult = 0; 
	DoubleResult = (1)*ImageData[row + 1][col + 1] + (1)* ImageData[row - 1][col + 1] +2* ImageData[row][col + 1] + (-1)*ImageData[row - 1][col - 1] + (-1)*ImageData[row + 1][col - 1] + (-2)*ImageData[row][col - 1]; 
	unsigned char result = 0; 
	result = round(0.125 * DoubleResult) + 127; 
	return result; 
}

unsigned char compYGradientPixel(unsigned char** ImageData, int row, int col, int BytesPerPixel) {
	double DoubleResult = 0;
	DoubleResult = (-1) * ImageData[row - 1][col - 1] + (-2) * ImageData[row - 1][col] + (-1) * ImageData[row - 1][col + 1] + ImageData[row + 1][col - 1] + 2 * ImageData[row + 1][col] + ImageData[row + 1][col + 1]; 
	unsigned char result = 0;
	result = round(0.125 * DoubleResult) + 127;
	return result;
}
void compXGradient(unsigned char** ImageData,unsigned char** XGrad2DArray,  int width, int height ,int BytesPerPixel ,int edgesize) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			XGrad2DArray[row][col] = compXGradientPixel(ImageData, row + edgesize, col + edgesize, BytesPerPixel); 
		}
	}

}

void compYGradient(unsigned char** ImageData,unsigned char** YGrad2DArray , int width, int height, int BytesPerPixel , int edgesize) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			YGrad2DArray[row][col] = compYGradientPixel(ImageData, row + edgesize, col + edgesize, BytesPerPixel);
		}
	}
}

void compMagnitudeGradient(unsigned char** XGrad2DArray, unsigned char** YGrad2DArray, unsigned char** MagntGrad2DArray, int width, int height, int BytesPerPixel) { 
	

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