#include"dipHeader.h"

void testExtendEdgeFunction(unsigned char** imageData , unsigned char** extendedData, int width , int height,int widsize) {
	extend2DImageEdge(imageData, extendedData, width ,height, 1 ,widsize);
}

double computeGaussWeight(unsigned char **imageData, int row,int col,int i,int j, double cigmaC, double cigmaS) {
	double result ; 
	double indexl2 = (row - i) ^ 2 + (col - j) ^ 2; 
	double pixell2 = (imageData[row][col] - imageData[i][j]) ^ 2; 
	result = exp(0 - indexl2 / 2 / (cigmaC * cigmaC) - pixell2/2/(cigmaS*cigmaS)); 
	return result;
}

int computeBilateralFilteredPixel(unsigned char** imageData, int row, int col,int BytesPerPixel, int widsize , double cigmaC , double cigmaS ) {
	double weightednumerator =0 ; 
	double denominator= 0 ; 
	int result = 0; 
	for (int i = row - widsize / 2; i <= row + widsize / 2; i++) {
		for (int j = col - widsize / 2; j <= col + widsize / 2; j++) {
			double gaussWeight = computeGaussWeight(imageData, row, col, i, j, cigmaC, cigmaS);
			weightednumerator += gaussWeight*imageData[i][j]; 
			denominator += gaussWeight; 
		}
	}
	result =(int) weightednumerator / denominator; 
	return result; 
}

void bilateral_filtering(unsigned char** imageData, unsigned char** filteredImageData, int width, int height,int BytesPerPixel, int widsize , double cigmaC , double cigmaS) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			filteredImageData[row][col] = computeBilateralFilteredPixel(imageData, row + widsize, col + widsize, 1, widsize, cigmaC, cigmaS); 
		}
	}
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
	int widsize = 2; 
	double cigmaC = 1.0; 
	double cigmaS = 1.0; 
	unsigned char** imageData; 
	unsigned char** extendedData; 
	unsigned char** filteredImageData; 
	imageData = alloc2DImage(width , height ,1);
	extendedData = alloc2DImage(width+2*widsize,height+2*widsize, 1); 
	filteredImageData = alloc2DImage(width, height, 1); 
	read2DImageFile(argv[1], imageData, width, height, 1); 
	extend2DImageEdge(imageData, extendedData, width, height, 1,widsize); 
	bilateral_filtering(extendedData, filteredImageData, width, height, 1, widsize, cigmaC, cigmaS); 
	write2DImageFile(argv[2], filteredImageData, width, height, 1); 
	return 0;
	
}