#include"dipHeader.h"
#include<bitset>
int compBluePixelDelta(unsigned char **imageData, int row, int col) {
	int result = '0';
	//cout << imageData[row + 2][col] << endl << imageData[row - 2][col] << endl;
	result = imageData[row][col] - 0.25 * (imageData[row - 2][col] + imageData[row + 2][col] + imageData[row][col + 2] + imageData[row][col - 2]); 
	
	return result; 
}

int  compRedPixelDelta(unsigned char** imageData, int row, int col) {
	int result ='0';
	result = imageData[row][col] - 0.25 * (imageData[row - 2][col] + imageData[row + 2][col] + imageData[row][col + 2] + imageData[row][col - 2]); 
	return result; 

}


int compGreenPixelDelta(unsigned char** imageData, int row, int col) {
	int result = '0'; 
	result = imageData[row][col] - 0.25 * (imageData[row + 1][col-1] + imageData[row + 1][col+1] + imageData[row-1][col-1] + imageData[row-1][col+1]);
	return result; 
}

void MHC_Demosaicing(unsigned char **imageData,unsigned char ***imageRGBData, int width, int height) {
	for (int row = 2; row < height-4; row++) {
		for (int col = 2; col < width-4; col++) {
			//Red
			if (judgePixelColor(row, col) == 0) {
				imageRGBData[row][col][0] = imageData[row][col];
				imageRGBData[row][col][1] = compGreenforRedBL(imageData,row,col)+0.5*compRedPixelDelta(imageData,row,col);
				imageRGBData[row][col][2] = compBlueforRedBL(imageData, row, col) + 0.5 * compRedPixelDelta(imageData, row, col); 
			}
			//Green
			if (judgePixelColor(row, col) == 1) {
				imageRGBData[row][col][0] = compRedForGreenBL(imageData, row, col) + 5 / 8 * compGreenPixelDelta(imageData, row, col);
				imageRGBData[row][col][1] = imageData[row][col]; 
				imageRGBData[row][col][2] = compBlueforGreenBL(imageData, row, col) + 5 / 8 * compGreenPixelDelta(imageData, row, col); 
			}
			//Blue
			if (judgePixelColor(row, col) == 2) {
				imageRGBData[row][col][0] = compRedforBlueBL(imageData, row, col) + 0.75 * compBluePixelDelta(imageData, row, col);
					imageRGBData[row][col][1] = compGreenforBlueBL(imageData, row, col) + 0.75 * compBluePixelDelta(imageData, row, col);
				imageRGBData[row][col][2] = imageData[row][col];
			}
		}
	
	}
}


void testdelta() {

	unsigned char a = 255; 
	unsigned char b = 1; 
	int c = b - a; 
	cout << (int)c << endl; 
	
}




int main(int argc ,char *argv[]) {

	// Define file pointer and variables
	FILE* file;
	int BytesPerPixel;
	int Size = 256;
	int width; 
	int height; 
	int rows;
	int cols;


	// Check for proper syntax
	if (argc < 3) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}

	// Check if image is grayscale or color
	if (argc < 4) {
		BytesPerPixel = 1; // default is grey image
	}
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5) {
			width = atoi(argv[4]);
			height = atoi(argv[5]); 
		}
	}

	// Allocate image data array
	unsigned char** imageData = NULL; 
	imageData = alloc2DImage(width, height, BytesPerPixel);
	unsigned char*** imageRGBData = NULL; 
	imageRGBData = alloc3DImage(width, height, 3); 

	// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}
	read2DImage(file, imageData, width, height, BytesPerPixel);
	fclose(file);
	
	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
//	testdelta(); 
	MHC_Demosaicing(imageData, imageRGBData, width, height); 

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	write3DImage(file, imageRGBData, width, height, 3); 
	fclose(file);

	return 0;
}