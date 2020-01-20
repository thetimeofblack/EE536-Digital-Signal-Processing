#include"dipHeader.h"
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
	tempArray = new int[pow(starty-startx,2)]; 
	for (int i = starty; i <= endy; i++) {
		for (int j = startx; j <= endx; j++) {
			tempArray[tempCount++] = imageData[i][j]; 
		}
	}
	qsort(tempArray, tempCount, sizeof(int),compareMyInt); 
	result = (tempArray[tempCount/2]+tempArray[tempCount/2-1])/2; 
	delete[] tempArray; 
	return result; 
}


void linear_filter(unsigned char** imageData, unsigned char** targetImage, int width, int height, int BytesPerPixel , int widsize) {
	for (int row = widsize; row < height-widsize; row++) {
		for (int col = widsize; col < width-widsize; col++) {
			targetImage[row][col] = (unsigned char)aver2DImage(imageData, row+widsize , col+widsize ,1,  widsize);
		}
	}
	
}

int aver2DImage(unsigned char** imageData, int row, int col, int BytesPerPixel, int widsize) {
	double average;
	double sum = 0.0;
	int result;
	int startx = row - widsize / 2;
	int endx = row + widsize / 2;
	int starty = col - widsize / 2;
	int endy = col + widsize / 2;
	for (int i = startx; i <= endx; i++) {
		for (int j = starty; j <= endy; j++) {
			sum += imageData[i][j];
		}
	}
	int total = (endx - startx + 1) * (endx - startx + 1);
	average = sum / total;
	return (int)average;
}

void impulse_filter(unsigned char** imageData, unsigned char** filteredImage, int width, int height, int BytesPerPixel, int widsize) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			filteredImage[row][col] = (unsigned char)median2DImage(imageData, row + widsize, col + widsize, 1, widsize); 
		}
	}

}

int checkProperSyntax(int argc, char* argv[] , int &width , int &height , int &BytesPerPixel ) {
	if (argc < 3) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Width = 256] [Height = 256]" << endl;
		return 0;
	}

	// Check if image is grayscale or color
	if (argc < 4) {
		BytesPerPixel = 1; // default is grey image
	}
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if width and height is specified
		if (argc >= 5) {
			width = atoi(argv[4]);
			height = atoi(argv[5]);
		}
	}
	
}
int main(int argc, char* argv[]) {
	FILE* file; 
	int width; 
	int height; 
	int BytesPerPixel;
	if (argc < 3) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Width = 256] [Height = 256]" << endl;
		return 0;
	}

	// Check if image is grayscale or color
	if (argc < 4) {
		BytesPerPixel = 1; // default is grey image
	}
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if width and height is specified
		if (argc >= 5) {
			width = atoi(argv[4]);
			height = atoi(argv[5]);
		}
	}


	int edgesize = 3; 
	int widsize = 3;  
	unsigned char** imageData; 
	unsigned char** filteredData; 
	unsigned char** extendedImageData; 
	imageData = alloc2DImage(width,height , BytesPerPixel); 
	extendedImageData = alloc2DImage(width + 2 * edgesize, height + 2 * edgesize, BytesPerPixel); 
	filteredData = alloc2DImage(width, height , BytesPerPixel); 
	
	// Read image (filename specified by first argument) into image data matrix
	read2DImageFile(argv[1], imageData, width, height, BytesPerPixel);
	extend2DImageEdge(imageData, extendedImageData, width, height, BytesPerPixel, edgesize); 
	linear_filter(extendedImageData, filteredData, width, height, 1, widsize); 
	write2DImageFile(argv[2], filteredData, width, height, BytesPerPixel);
	return 0; 
}