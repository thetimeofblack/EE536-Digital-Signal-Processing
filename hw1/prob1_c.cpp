#include "dipHeader.h"
#include <bitset>

int main(int argc, char* argv[]) {
	// Define file pointer and variables
	FILE* file;
	int BytesPerPixel;
	int Size = 256;
	int rows = 256;
	int cols = 256;
	int width = 256;
	int height = 256;

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
	rows = height;
	cols = width;

// allocate memory for arrays 
	unsigned char** imageData;
	imageData = new unsigned char* [height];
	for (int row = 0; row < height; row++) {
		imageData[row] = new unsigned char [width];
//		for (int col = 0; col < width; col++) {
//			imageData[row][col] = new unsigned char[BytesPerPixel+1];
//		}
	}
//	cout <<bitset<8>( imageData[height - 1][width - 1][0]) << endl;
	unsigned char*** imageRGBData;
	imageRGBData = new unsigned char** [height];
	for (int row = 0; row < height; row++) {
		imageRGBData[row] = new unsigned char* [width];
		for (int col = 0; col < width; col++) {
			imageRGBData[row][col] = new unsigned char[3];
		}
	}

	//	imageData[height][width]; 
		// Read image (filename specified by first argument) into image data matrix
	if (!(file = fopen(argv[1], "rb"))) {
		cout << "Cannot open file: " << argv[1] << endl;
		exit(1);
	}


	fread(imageData, sizeof(unsigned char), height * width * BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
//  test the i0x771BF94D (ntdll.dll) (hm1.exe 中)处有未经处理的异常: 0xC0000374: 堆已损坏。 (参数: 0x771FB960ndex of picture is or not swapped   	
	cout<<"***********image info**************"<<endl; 
	cout<<"  height: " << height<<"    width: "<<width<<endl; 
	for(int row = 0 ;row<8;row++){
		for(int col = 0 ; col<width ;col++){
			cout<<bitset<8>(imageData[row][col])<<" "; 
		}
		cout<<endl; 
	}




	if (!(file = fopen(argv[2], "wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	cout << "***********image info**************" << endl;
	cout << "  height: " << height << "    width: " << width << endl;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			imageRGBData[row][col][1] = 231; 
			//cout << bitset<8>(imageRGBData[row][col][1]) << " ";
		}
	}
	fwrite(imageData, sizeof(unsigned char), height * width * 3, file);
	fclose(file);
	cout << "writing image successfully";

	//	for (int row = 0; row < height; row++) {
	//		delete[] imageData[row]; 
	//	}
	//	delete[] imageData;  


	//	for (int row = 0; row < height; row++) {
	//		for (int col = 0; col < width; col++) {
	//			delete[] imageRGBData[row][col];
	//		}
	//		delete[] imageRGBData[row];
	//	}
	//	delete[] imageRGBData;
	return 0;
}