// denoising function 

#include "dipHeader.h"

//Median Filter 
int compareMyInt(const void* a, const void* b); 
int median2DImage(unsigned char** imageData, int row, int col, int BytesPerPixel, int widsize);


// Gaussian Filter 
double compGaussianWeight(int row, int col, int l, int k, double stdev);
unsigned char compGaussianPixel(unsigned char** imageData, unsigned char** targetImage, int row, int col, int widsize, double stdev); 
void GaussianFilter(unsigned char** imageData, unsigned char** targetImage, int width, int height, int BytesPerPixel, int edgesize, int widsize, double stdev); 

int compareMyInt(const void* a, const void* b)
{
	if (*(int*)a < *(int*)b) return -1;
	if (*(int*)a == *(int*)b) return 0;
	if (*(int*)a > * (int*)b) return 1;
}



int median2DImage(unsigned char** imageData, int row, int col, int BytesPerPixel, int widsize) {
	int result = 0;
	int startx = col - widsize / 2;
	int endx = col + widsize / 2;
	int starty = row - widsize / 2;
	int endy = row + widsize / 2;
	int* tempArray;
	int tempCount = 0;
	tempArray = new int[pow(starty - startx, 2)];
	for (int i = starty; i <= endy; i++) {
		for (int j = startx; j <= endx; j++) {
			tempArray[tempCount++] = imageData[i][j];
		}
	}
	qsort(tempArray, tempCount, sizeof(int), compareMyInt);
	result = (tempArray[tempCount / 2] + tempArray[tempCount / 2 - 1]) / 2;
	delete[] tempArray;
	return result;
}

double compGaussianWeight(int row, int col, int l, int k, double stdev) {
	double result;
	double pi = 3.14159265359;
	double sumdistance = pow(row - l, 2) + pow(col - k, 2);
	double coefficient = 1 / (2 * pi * pow(stdev, 2));
	result = coefficient * exp((-1) * sumdistance / 2 / pow(stdev, 2));
	return result;
}

unsigned char compGaussianPixel(unsigned char** imageData, unsigned char** targetImage, int row, int col, int widsize, double stdev) {
	unsigned char result;
	double weightPixelSum = 0;
	double weightSum = 0;
	double pi = 3.14159365;
	for (int i = row - widsize / 2; i <= row + widsize / 2; i++) {
		for (int j = col - widsize / 2; j <= col + widsize / 2; j++) {
			double GaussWeight = compGaussianWeight(row, col, i, j, stdev);
			weightPixelSum += imageData[i][j] * GaussWeight;
			weightSum += GaussWeight;
		}
	}
	result = weightPixelSum / weightSum;
	return result;
}

void GaussianFilter(unsigned char** imageData, unsigned char** targetImage, int width, int height, int BytesPerPixel, int edgesize, int widsize, double stdev) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			targetImage[row][col] = compGaussianPixel(imageData, targetImage, row + edgesize, col + edgesize, widsize, stdev);
		}
	}
}