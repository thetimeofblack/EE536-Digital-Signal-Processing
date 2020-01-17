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


void gray2RGB(unsigned char **ImageData ,unsigned char ***&imageRGBData,  int width , int height,int pixelperByte =1){
//	cout<<"***********image info**************"<<endl; 
//	cout<<"  height: " << height<<"    width: "<<width<<endl;
	unsigned char** tempImageData; 
	tempImageData =  new unsigned char *[height]; 
	for(int row = 0 ;row<height;row++){
		tempImageData[row] = new unsigned char [width]; 
	}
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			tempImageData[row][col] = *((unsigned char*)(ImageData + row) + col);
		}
	}

	for(int row = 2 ; row< height-2 ; row++){
		
		for(int col = 2 ;col<width-2 ;col++){
			//cout<<"test command 1"<<endl;   
			//color is red
			int color = judgePixelColor(row ,col); 
			//cout<<color<<endl;
			//cout<<"height: "<<height<<endl;
			//cout<<tempImageData[row][col]<<endl;
			//cout<<"width  "<<width<<endl; 
			if(judgePixelColor(row,col) == 0){
				//cout<<"test command 2"<<endl; 
				imageRGBData[row][col][0] = (unsigned char)tempImageData[row][col];
				imageRGBData[row][col][1] =(unsigned char)  0.25*((double)tempImageData[row-1][col]+ (double)tempImageData[row+1][col]+ (double)tempImageData[row][col-1]+ (double)tempImageData[row][col+1]);
				imageRGBData[row][col][2] = (unsigned char)0.25*((double)tempImageData[row-1][col-1]+ (double)tempImageData[row+1][col+1]+ (double)tempImageData[row+1][col-1]+ (double)tempImageData[row-1][col+1]) ;
			}
			//color is green 
			if(judgePixelColor(row,col) == 1){
				//cout<<"test command 4"<<endl; 
				if(row%2==0){
					imageRGBData[row][col][0] = (unsigned char)0.5*((double)tempImageData[row][col+1]+ (double)tempImageData[row][col-1]);
					//cout<<"test command 6"<<endl; 
					imageRGBData[row][col][1] = (unsigned char)(double)tempImageData[row][col];
					imageRGBData[row][col][2] = (unsigned char)0.5*((double)tempImageData[row-1][col]+ (double)tempImageData[row+1][col]);
				}else{
					imageRGBData[row][col][0] = (unsigned char)0.25*((double)tempImageData[row-1][col-1]+ (double)tempImageData[row+1][col+1]+ (double)tempImageData[row+1][col-1]+ (double)tempImageData[row-1][col+1]);
					imageRGBData[row][col][1] = (unsigned char)0.25*((double)tempImageData[row-1][col]+ (double)tempImageData[row+1][col]+ (double)tempImageData[row][col-1]+ (double)tempImageData[row][col+1]);
					imageRGBData[row][col][2] = (unsigned char)tempImageData[row][col];
				}
			}
			//color is blue 
			if(judgePixelColor(row,col)==2){
				imageRGBData[row][col][0] = (unsigned char)0.25*((double)tempImageData[row - 1][col - 1] + (double)tempImageData[row + 1][col + 1] + (double)tempImageData[row + 1][col - 1] + (double)tempImageData[row - 1][col + 1]);
				imageRGBData[row][col][1] = (unsigned char)0.25*((double)tempImageData[row-1][col]+ (double)tempImageData[row+1][col]+ (double)tempImageData[row][col-1]+ (double)tempImageData[row][col+1]);
				imageRGBData[row][col][2] =  tempImageData[row][col]; 
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
	unsigned char** imageData;
	imageData = new unsigned char* [height];
	for (int row = 0; row < height; row++) {
		imageData[row] = new unsigned char[width];

	}
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
	
	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(imageData, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
//  test the index of picture is or not swapped   	
//	cout<<"***********image info**************"<<endl; 
//	cout<<"  height: " << height<<"    width: "<<width<<endl; 
//	for(int row = 0 ;row<8;row++){
//		for(int col = 0 ; col<width ;col++){
//			cout<<bitset<8>(imageData[row][col]); 
//		}
//		cout<<endl; 
//	}
	
	unsigned char ***imageRGBData; 
	imageRGBData = new unsigned char**[height]; 
	for(int row=0 ; row<height ; row++){
		imageRGBData[row] = new unsigned char *[width];
		for(int col=0; col<width; col++){
			imageRGBData[row][col] = new unsigned char[3]; 
		}
	}

//	test2Darray(imageData,height, width); 
//	imageRGBData[0][0][0] =(unsigned char)10;  
//	cout<<imageRGBData[0][0][0]; 
	gray2RGB(imageData,imageRGBData, width,height,1);
	// Write image data (filename specified by second argument) from image data matrix
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	cout << "***********image info**************" << endl;
	cout << "  height: " << height << "    width: " << width << endl;
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < width; col++) {
			cout << bitset<8>(imageRGBData[row][col][2]);
		}
		cout << endl;
	}
	fwrite(imageRGBData, sizeof(unsigned char), height*width*3, file);
	fclose(file);
    cout<<"writing image successfully"; 
	delete imageRGBData; 
	delete imageData; 
	return 0;
}
