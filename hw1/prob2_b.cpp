#include"dipHeader.h"

void testExtendEdgeFunction(unsigned char** imageData , unsigned char** extendedData, int width , int height,int widsize) {
	extend2DImageEdge(imageData, extendedData, width ,height, 1 ,widsize);
}

double computeGaussWeight(unsigned char **imageData, int row,int col,int i,int j, double cigmaC, double cigmaS) {
	double result ; 
	double indexl2 = pow((row - i), 2) + pow((col - j) , 2); 
	double pixell2 = pow((imageData[row][col] - imageData[i][j]),2); 
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

void bilateral_filtering(unsigned char** imageData, unsigned char** filteredImageData, int width, int height,int BytesPerPixel, int edgesize ,int widsize , double cigmaC , double cigmaS) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			filteredImageData[row][col] = computeBilateralFilteredPixel(imageData, row + edgesize, col + edgesize, BytesPerPixel, widsize, cigmaC, cigmaS); 
		}
	}
}

int main(int argc, char* argv[]) {
	FILE* file;
	int width;
	int height;
	int BytesPerPixel;

	// configuration parameters
	double cigmaC = 0.1;
	double cigmaS = 30.0;
	int edgesize = 10;
	int widsize = 5;


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
		BytesPerPixel = atoi(argv[4]);
		// Check if width and height is specified
		if (argc >= 5) {
			width = atoi(argv[5]);
			height = atoi(argv[6]);
			widsize = atoi(argv[7]);
			cigmaC = atoi(argv[8]); 
			cigmaS = atoi(argv[9]);
		}
	}

	edgesize = 2 * widsize; 

	unsigned char** imageData; 
	unsigned char** extendedData; 
	unsigned char** filteredImageData;
	unsigned char** originalImageData; 
	originalImageData = alloc2DImage(width, height, BytesPerPixel); 
	imageData = alloc2DImage(width , height ,1);
	extendedData = alloc2DImage(width+2*edgesize,height+2*edgesize, 1); 
	filteredImageData = alloc2DImage(width, height, 1); 
	read2DImageFile(argv[1], imageData, width, height, 1); 
	read2DImageFile(argv[2], originalImageData, width, height, 1); 
	extend2DImageEdge(imageData, extendedData, width, height, 1,edgesize); 
	bilateral_filtering(extendedData, filteredImageData, width, height, 1,edgesize, widsize, cigmaC, cigmaS); 
	write2DImageFile(argv[3], filteredImageData, width, height, 1); 
	double psnr = eval2DImagePSNR(originalImageData, filteredImageData, width, height, BytesPerPixel);
	double psnrnoisy = eval2DImagePSNR(originalImageData, imageData, width, height, BytesPerPixel);
	cout << "PSNR for original image and filtered image: " << psnr << endl;
	cout << "PSNR for original image and noisy image" << psnrnoisy << endl;
	return 0;
	
}