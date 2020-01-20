#include"dipHeader.h"

void GaussWeightedPixel(unsigned char** imageData, int row, int col, int i, int j, int BytesPerPixel){
		
}


double GaussCoefficients(int n1, int n2 , double stanDevia) {
	double result;
	const double pi = 3.1415926535897;
	double sumsquare = n1 ^ 2 + n2 ^ 2; 
	result = 1 / ((sqrt(2 * pi)) * stanDevia) * exp((-1) * (sumsquare / (2*stanDevia^2))); 
	return result; 
}


double GaussWeightedEuclidianDistance(unsigned char** imageData, int row, int col, int i, int j) {
	const double pi = 3.1415926535897;
	int rpx = row - i;
	int rpy = col-j;
	double result; 
	double squaresum = rpx ^ 2 + rpy ^ 2; 
	result = 1 / sqrt(2 * pi)*exp(-(squaresum)); 
	
}



void NLM_filtering(unsigned char** ImageData, unsigned char** filteredData , int width, int height, int BytesPerPixel) {
	for (int row = 0; row < height; row++) {
		for(int col = 0; col<width ; col++){
						
		}
	}
}

double compPixelByWindow(unsigned char** imageData,  int row, int col, int i, int j, int BytesPerPixel, int widwidth, int widheight) {

}

double computeNLMPixel(unsigned char** imageData, unsigned char** filteredImageData, int row, int col, int BytesPerPixel, int widwidth, int widheight) {
	double result;
	for (int i = row-widheight/2; i <= row+widheight/2; i++) {
		for (int j = col-widwidth/2; j <= col+widwidth/2; j++) {
			result = compPixelByWindow( imageData,row,col ,i , j , BytesPerPixel,  widwidth ,widheight); 
		}
	}

	return result;
}

int main(int argc , char *argv[]) {
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
	unsigned char** filteredImageData; 
	unsigned char** extendedData;
	extend2DImageEdge(imageData, extendedData, width, height, BytesPerPixel, edgesize); 
	imageData = alloc2DImage(width, height, BytesPerPixel); 
	extendedData = alloc2DImage(width + 2 * widsize, height + 2 * widsize, 1); 
	filteredImageData = alloc2DImage(width, height, BytesPerPixel); 

	read2DImageFile(argv[1], imageData, width, height, BytesPerPixel ); 

	write2DImageFile(argv[2], filteredImageData, width, height, BytesPerPixel); 
	

}