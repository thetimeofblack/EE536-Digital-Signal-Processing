#include"dipHeader.h"
#include<bitset>
using namespace std; 

// dog.raw format 
// size:600*532 width 600 height 532
// 8-bit 
// gray 

// the source code from the class is useless !!!!





void gray2RGB(unsigned char **imageExtendedData ,unsigned char ***&imageRGBData,  int width , int height,int pixelperByte =1){
//	cout<<"***********image info**************"<<endl; 
//	cout<<"  height: " << height<<"    width: "<<width<<endl; 
//	for(int row = 0 ;row<8;row++){
//		for(int col = 0 ; col<width ;col++){
//			cout<<bitset<8>(imageExtendedData[row][col]); 
//		}
//		cout<<endl; 
//	}

	
	for(int row = 2 ; row< height-2 ; row++){
		
		for(int col = 2 ;col<width-2 ;col++){
			cout<<"test command 1"<<endl; 
			//color is red  
			int color = judgePixelColor(row ,col); 
			cout<<color<<endl;
			if(judgePixelColor(row,col) == 0){
				cout<<"test command 2"<<endl; 
				cout<<"This is red "<<imageExtendedData[row][col]<<endl; 
				imageRGBData[row][col][0] =  imageExtendedData[row][col];
				imageRGBData[row][col][1] =  0.25*(imageExtendedData[row-1][col]+imageExtendedData[row+1][col]+imageExtendedData[row][col-1]+imageExtendedData[row][col+1]);
				imageRGBData[row][col][2] =  0.25*(imageExtendedData[row-1][col-1]+imageExtendedData[row+1][col+1]+imageExtendedData[row+1][col-1]+imageExtendedData[row-1][col+1]);
			}
			//color is green 
			if(judgePixelColor(row,col) == 1){
				if(row%2==0){
					imageRGBData[row][col][0] =  0.5*(imageExtendedData[row][col+1]+imageExtendedData[row][col-1]);
					imageRGBData[row][col][1] =  imageExtendedData[row][col]; 
					imageRGBData[row][col][2] =  0.5*(imageExtendedData[row-1][col]+imageExtendedData[row+1][col]);	
				}else{
					imageRGBData[row][col][0] =  0.25*(imageExtendedData[row-1][col-1]+imageExtendedData[row+1][col+1]+imageExtendedData[row+1][col-1]+imageExtendedData[row-1][col+1]);
					imageRGBData[row][col][1] =  0.25*(imageExtendedData[row-1][col]+imageExtendedData[row+1][col]+imageExtendedData[row][col-1]+imageExtendedData[row][col+1]);
					imageRGBData[row][col][2] =  imageExtendedData[row][col]; 
				}
			}
			//color is blue 
			if(judgePixelColor(row,col)==2){
				imageRGBData[row][col][0] =  imageExtendedData[row][col];
				imageRGBData[row][col][1] =  0.25*(imageExtendedData[row-1][col]+imageExtendedData[row+1][col]+imageExtendedData[row][col-1]+imageExtendedData[row][col+1]);
				imageRGBData[row][col][2] =  imageExtendedData[row][col];
			}
			cout<<"test command 3"<<endl; 
		}
	}
	cout<<"***********image info**************"<<endl; 
	cout<<"  height: " << height<<"    width: "<<width<<endl; 
	for(int row = 0 ;row<8;row++){
		for(int col = 0 ; col<width ;col++){
			cout<<bitset<8>(imageRGBData[row][col][0]); 
		}
		cout<<endl; 
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
	testHeaderIncluded();
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
	unsigned char **imageData;
	imageData = new unsigned char*[height]; 
	for(int row ; row<height ; row++){
		imageData[row] = new unsigned char [width]; 
	}
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
//	
	unsigned char ***imageRGBData; 
	imageRGBData = new unsigned char**[height]; 
	for(int row ; row<height ; row++){
		imageRGBData[row] = new unsigned char *[width];
		for(int col; col<width; col++){
			imageRGBData[row][width] = new unsigned char[3]; 
		}
	}

	imageRGBData[0][0][0] =1;  
	gray2RGB(imageData,imageRGBData, width,height,1);

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageRGBData, sizeof(unsigned char), height*width*3, file);
	fclose(file);
    cout<<"writing"; 
	return 0;
}
