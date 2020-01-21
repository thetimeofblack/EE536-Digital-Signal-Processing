#include"dipHeader.h"
#include<bitset>
int compBluePixelDelta(unsigned char** imageData, int row, int col) {
	int result = 0;
	//cout << imageData[row + 2][col] << endl << imageData[row - 2][col] << endl;
	result = (int)imageData[row][col] - 0.25 * ((int)imageData[row - 2][col] + (int)imageData[row + 2][col] +(int) imageData[row][col + 2] + (int)imageData[row][col - 2]);
	return result; 
}

int  compRedPixelDelta(unsigned char** imageData, int row, int col) {
	int result =0;
	result = (int)imageData[row][col] - 0.25 * ((int)imageData[row - 2][col] + (int)imageData[row + 2][col] + (int)imageData[row][col + 2] + (int)imageData[row][col - 2]);
	return result; 

}


int compGreenPixelDelta(unsigned char** imageData, int row, int col) {
	int result =0; 
	result = (int)imageData[row][col] - 0.25 * ((int)imageData[row + 1][col-1] + (int)imageData[row + 1][col+1] + (int)imageData[row-1][col-1] + (int)imageData[row-1][col+1]);
	return result; 
}

void MHC_Demosaicing(unsigned char **imageData,unsigned char ***imageRGBData, int width, int height , int edgesize) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			//Red
			if (judgePixelColor(row, col) == 0) {
				imageRGBData[row][col][0] = imageData[row+edgesize][col+edgesize];
				imageRGBData[row][col][1] =round( compGreenforRedBL(imageData,row+edgesize,col+edgesize)+0.5*compRedPixelDelta(imageData,row + edgesize,col + edgesize));
				imageRGBData[row][col][2] =round( compBlueforRedBL(imageData, row+edgesize, col+edgesize) + 0.5 * compRedPixelDelta(imageData, row + edgesize, col + edgesize));
			}
			//Green
			if (judgePixelColor(row , col) == 1) {
				imageRGBData[row][col][0] =round( compRedforGreenBL(imageData, row+edgesize, col+edgesize) + 5 / 8 * compGreenPixelDelta(imageData, row + edgesize, col + edgesize));
				imageRGBData[row][col][1] = imageData[row+edgesize][col+edgesize]; 
				imageRGBData[row][col][2] = round( compBlueforGreenBL(imageData, row + edgesize, col + edgesize) + 5 / 8 * compGreenPixelDelta(imageData, row + edgesize, col + edgesize));
			}
			//Blue
			if (judgePixelColor(row , col ) == 2) {
				imageRGBData[row][col][0] =round( compRedforBlueBL(imageData, row + edgesize, col + edgesize) + 0.75 * compBluePixelDelta(imageData, row + edgesize, col + edgesize));
				imageRGBData[row][col][1] =round( compGreenforBlueBL(imageData, row + edgesize, col + edgesize) + 0.75 * compBluePixelDelta(imageData, row + edgesize, col + edgesize));
				imageRGBData[row][col][2] = imageData[row + edgesize][col + edgesize];
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
	int edgesize = 2; 
	// Allocate image data array
	unsigned char** imageData = NULL; 
	imageData = alloc2DImage(width, height, BytesPerPixel);
	unsigned char*** imageRGBData = NULL; 
	imageRGBData = alloc3DImage(width, height, 3); 
	unsigned char** extendedImageData; 
	extendedImageData = alloc2DImage(width+2*edgesize, height+2*edgesize, BytesPerPixel); 
	// Read image (filename specified by first argument) into image data matrix
	read2DImageFile(argv[1],imageData, width, height, BytesPerPixel);
	
	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
	extend2DImageEdge(imageData, extendedImageData, width, height, BytesPerPixel, edgesize);
	MHC_Demosaicing(extendedImageData, imageRGBData, width, height,edgesize);
	cout << width << endl; 
	cout << height << endl;
	// Write image data (filename specified by second argument) from image data matrix
	cout << bitset<8>('0') << endl;
	cout << bitset<8>(imageRGBData[500][0][0]) << endl;
	cout << (int)imageRGBData[531][594][1] << endl;
	write3DImageFile(argv[2], imageRGBData, width, height, 3); 

	return 0;
}