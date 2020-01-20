#include"dipHeader.h"

int main(int argc , char* argv[]){
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
	imageData = alloc2DImage(width, height, BytesPerPixel);
	filteredData = alloc2DImage(width, height, BytesPerPixel);
	extendedImageData = alloc2DImage(width, height, BytesPerPixel); 
	// Read image (filename specified by first argument) into image data matrix

	read2DImageFile(argv[1], imageData, width, height, BytesPerPixel); 


	
	write2DImageFile(argv[2], filteredData, width, height, BytesPerPixel); 
	return 0;
}


