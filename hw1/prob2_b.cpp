#include"dipHeader.h"

void testExtendEdgeFunction(unsigned char** imageData , unsigned char** extendedData, int width , int height) {
	extend2DImageEdge(imageData, extendedData, width ,height, 1 );

}

double computeGaussWeight(unsigned char **imageData, int row,int col,int i,int j) {
	double cigmaC = 1.0; 
	double cigmaS = 1.0; 
	double result ; 
	double indexl2 = (row - i) ^ 2 + (col - j) ^ 2; 
	double pixell2 = (imageData[row][col] - imageData[i][j]) ^ 2; 
	result = exp(0 - indexl2 / 2 / (cigmaC * cigmaC) - pixell2/2/(cigmaS*cigmaS)); 
	return result;
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
	unsigned char** imageData; 
	unsigned char** extendedData; 
	unsigned char** resultData; 


	return 0;
	
}