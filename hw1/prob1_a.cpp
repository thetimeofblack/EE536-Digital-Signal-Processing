#include"dipHeader.h"
#include<bitset>
using namespace std; 

// dog.raw format 
// size:600*532 width 600 height 532
// 8-bit 
// gray 

// the source code from the class is useless !!!!


unsigned char ***  gray2RGB(unsigned char **imageData, unsigned char ***imageRGB , int width , int height,int pixelperByte); 


unsigned char *** gray2RGB(unsigned char **imageData, unsigned char ***imageRGB , int width , int height,int pixelperByte){
	unsigned char ***imageRGBData; 
	imageRGBData = new unsigned char**[height](); 
	for(int row = 0 ; row< height ; row++){
		imageRGBData[row] = new unsigned char*[width](); 
		for(int col = 0 ;col<width ;col++){
			imageRGBData[row][col] = new unsigned char[3]();
			//color is red  
			if(judgePixelColor(row,col)=='0'){
				
			}
		}
	}



}



int main(int argc, char *argv[])
{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 256;
	int rows =256; 
	int cols = 256; 
    int width ; 
    int height ; 
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Width = 256] [Height = 256]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if width and height is specified
		if (argc >= 6){
			width = atoi(argv[4]);
            height = atoi(argv[5]); 
        }
	}
	rows = height ;
    cols = width ; 
	// Allocate image data array   ?? when the width and height of image is not equal  ??
	unsigned char Imagedata[rows][cols];
	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
//  test the index of picture is or not swapped   	
//	cout<<"***********image info**************"<<endl; 
//	cout<<"  height: " << height<<"    width: "<<width<<endl; 
//	for(int row = 0 ;row<8;row++){
//		for(int col = 0 ; col<width ;col++){
//			Imagedata[row][col] = 0 ; 
//		}
//		cout<<endl; 
//	}
	


	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	return 0;
}
