#include"dipHeader.h"
#include<bitset>
using namespace std; 

// dog.raw format 
// size:600*532 width 600 height 532
// 8-bit 
// gray 

// the source code from the class is useless !!!!


void test2Darray(unsigned char **input, int rows, int cols ){
	cout<<*( (unsigned char*)(input+10)+9)<<endl;
	unsigned char temp =  *( (unsigned char*)(input+34)+9); 
	unsigned char **temparray ; 
	temparray = new unsigned char *[3];
	temparray[0] = new unsigned char[3];  
	temparray[0][0]=  *( (unsigned char*)(input+34)+9); 
	temparray[0][1]=  *( (unsigned char*)(input+34)+10); 
	temparray[0][2]=  *( (unsigned char*)(input+35)+11); 
	unsigned char sum = 0.5*(temparray[0][0]+temparray[0][2]); 
	cout<<bitset<8>(temp)<<endl; 
	cout<<bitset<8>(temparray[0][0])<<endl;
	cout<<bitset<8>(temparray[0][1])<<endl;
	cout<<bitset<8>(temparray[0][2])<<endl;
	cout<<bitset<8>(sum)<<endl;
}

void testUnsignedCharOverflow() {
	unsigned char a = 255; 
	unsigned char b = 255; 
	//unsigned char c = a + b; 
	int d = a + b; 
//	cout << c << endl; 
	cout << d << endl; 
//	unsigned char* arr;  
//	arr = new unsigned char[10]; 
//	arr[0] = a + b; 
//	cout << arr[1] << endl;
//	cout << arr[0] << endl; 



}


void gray2RGB(unsigned char **imageData ,unsigned char ***imageRGBData,  int width , int height,int pixelperByte ,int edgesize){
//	cout<<"***********image info**************"<<endl; 
//	cout<<"  height: " << height<<"    width: "<<width<<endl;
	// we need to prevent overflow for the unsigned char 
	for(int row = 0 ; row< height ; row++){
		for(int col = 0 ;col<width ;col++){ 
			//color is red
			if(judgePixelColor(row,col) == 0){
				//cout<<"test command 2"<<endl; 
				imageRGBData[row][col][0] = imageData[row + edgesize][col + edgesize]; 
				imageRGBData[row][col][1] = compGreenforRedBL(imageData, row + edgesize, col + edgesize);
				imageRGBData[row][col][2] = compBlueforRedBL(imageData, row + edgesize, col + edgesize);

				
			}
			//color is green 
			if(judgePixelColor(row,col) == 1){
				imageRGBData[row][col][0] = compRedforGreenBL(imageData, row + edgesize, col + edgesize);
				imageRGBData[row][col][1] = imageData[row + edgesize][col + edgesize];
				imageRGBData[row][col][2] = compBlueforGreenBL(imageData, row + edgesize, col + edgesize);
			}
			//color is blue 
			if(judgePixelColor(row,col)==2){
				imageRGBData[row][col][0] = compRedforBlueBL(imageData, row + edgesize, col + edgesize);
				imageRGBData[row][col][1] = compGreenforBlueBL(imageData, row + edgesize, col + edgesize);
				imageRGBData[row][col][2] = imageData[row + edgesize][col + edgesize];
			}
			//cout<<"test command 3"<<endl; 
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
    int width =256; 
    int height =256; 
	//testHeaderIncluded();
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
		if (argc >= 5){
			width = atoi(argv[4]);
            height = atoi(argv[5]); 
        }
	}
	rows = height ;
    cols = width ; 
	int edgesize=4; 
	// Allocate image data array   ?? when the width and height of image is not equal  ??
	
	unsigned char ** imageData;
	imageData = alloc2DImage(width, height, BytesPerPixel); 
	read2DImageFile(argv[1], imageData, width, height, BytesPerPixel); 

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////


	unsigned char ***imageRGBData = NULL; 
	imageRGBData= alloc3DImage( width, height, 3); 
	unsigned char** extendedImageData; 
	extendedImageData = alloc2DImage(width + 2 * edgesize, height + 2 * edgesize,BytesPerPixel);
	extend2DImageEdge(imageData, extendedImageData, width, height, BytesPerPixel, edgesize); 
	gray2RGB(extendedImageData,imageRGBData, width,height,BytesPerPixel,edgesize);
//	 Write image data (filename specified by second argument) from image data matrix
//	testUnsignedCharOverflow(); 

	write3DImageFile(argv[2], imageRGBData, width, height, 3); 
	

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
