#include"dipHeader.h"
int compareMyInt(const void* a, const void* b)
{
	if (*(int*)a < *(int*)b) return -1;
	if (*(int*)a == *(int*)b) return 0;
	if (*(int*)a > * (int*)b) return 1;
}


int median2DImage(unsigned char** imageData, int row, int col, int BytesPerPixel, int widsize) {
	int result = 0; 
	int startx = col - widsize / 2; 
	int endx = col + widsize / 2; 
	int starty = row - widsize / 2; 
	int endy = row + widsize / 2;
	int* tempArray;
	int tempCount = 0; 
	tempArray = new int[pow(starty-startx,2)]; 
	for (int i = starty; i <= endy; i++) {
		for (int j = startx; j <= endx; j++) {
			tempArray[tempCount++] = imageData[i][j]; 
		}
	}
	qsort(tempArray, tempCount, sizeof(int),compareMyInt); 
	result = (tempArray[tempCount/2]+tempArray[tempCount/2-1])/2; 
	delete[] tempArray; 
	return result; 
}

double compGaussianWeight(int row, int col, int l, int k,double stdev) {
	double result; 
	double pi = 3.14159265359; 
	double sumdistance = pow(row - l, 2) + pow(col - k, 2);  
	double coefficient = 1 / (2 * pi * pow(stdev, 2)); 
	result = coefficient * exp((-1) * sumdistance / 2 / pow(stdev, 2)); 
	return result; 
}

unsigned char compGaussianPixel(unsigned char** imageData, unsigned char** targetImage, int row, int col, int widsize,double stdev) {
	unsigned char result; 
	double weightPixelSum = 0;
	double weightSum = 0;
	double pi = 3.14159365; 
	for (int i = row - widsize / 2; i <= row + widsize / 2; i++) { 
		for (int j = col - widsize / 2; j <= col + widsize / 2; j++) {
			double GaussWeight = compGaussianWeight(row, col, i, j,stdev); 
			weightPixelSum += imageData[i][j]*GaussWeight; 
			weightSum += GaussWeight; 
		}
	}
	result = weightPixelSum / weightSum; 
	return result;
}

void GaussianFilter(unsigned char** imageData, unsigned char** targetImage, int width, int height, int BytesPerPixel, int edgesize, int widsize ,double stdev) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			targetImage[row][col] = compGaussianPixel(imageData, targetImage, row, col, widsize,stdev); 
		}
	}
}

void linear_filter(unsigned char** imageData, unsigned char** targetImage, int width, int height, int BytesPerPixel ,int edgesize, int widsize) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			targetImage[row][col] = (unsigned char)aver2DImage(imageData, row+edgesize , col+edgesize ,BytesPerPixel,  widsize);
		}
	}
	
}

int aver2DImage(unsigned char** imageData, int row, int col, int BytesPerPixel, int widsize) {
	double average;
	double sum = 0.0;
	int result;
	int startx = row - widsize / 2;
	int endx = row + widsize / 2;
	int starty = col - widsize / 2;
	int endy = col + widsize / 2;
	for (int i = startx; i <= endx; i++) {
		for (int j = starty; j <= endy; j++) {
			sum += imageData[i][j];
		}
	}
	int total = (endx - startx + 1) * (endx - startx + 1);
	average = sum / total;
	return (int)average;
}

void impulse_filter(unsigned char** imageData, unsigned char** filteredImage, int width, int height, int BytesPerPixel, int edgesize , int widsize ) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			filteredImage[row][col] = (unsigned char)median2DImage(imageData, row + edgesize, col + edgesize, BytesPerPixel, widsize); 
		}
	}

}

int checkProperSyntax(int argc, char* argv[] , int &width , int &height , int &BytesPerPixel ) {
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
	
}
int main(int argc, char* argv[]) {
	FILE* file; 
	int width; 
	int height; 
	int BytesPerPixel;
	int edgesize = 6;
	int widsize = 2;
	double stdev = 0; 
	int method = 0; 
	if (argc < 3) {
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw input_ori_image.raw output_image.raw [BytesPerPixel = 1] [Width = 256] [Height = 256]" << endl;
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
			stdev = atoi(argv[8]); 
			method = atoi(argv[9]); 

		}
	}
	

	edgesize = widsize * 2; 
	unsigned char** imageData; 
	unsigned char** filteredData; 
	unsigned char** extendedImageData; 
	unsigned char** originImageData; 

	imageData = alloc2DImage(width,height , BytesPerPixel); 
	extendedImageData = alloc2DImage(width + 2 * edgesize, height + 2 * edgesize, BytesPerPixel); 
	filteredData = alloc2DImage(width, height , BytesPerPixel); 
	originImageData = alloc2DImage(width, height, BytesPerPixel); 
	// Read image (filename specified by first argument) into image data matrix
	read2DImageFile(argv[1], imageData, width, height, BytesPerPixel);
	read2DImageFile(argv[2], originImageData, width, height, BytesPerPixel); 
	extend2DImageEdge(imageData, extendedImageData, width, height, BytesPerPixel, edgesize); 
	if (method == 0) {
		linear_filter(extendedImageData, filteredData, width, height, BytesPerPixel, edgesize, widsize);
	}
	else {
		GaussianFilter(extendedImageData, filteredData, width, height, BytesPerPixel, edgesize, widsize, stdev); 
	}
	write2DImageFile(argv[3], filteredData, width, height, BytesPerPixel);
	double psnr = eval2DImagePSNR(originImageData,filteredData , width ,height ,BytesPerPixel );
	double psnrnoisy = eval2DImagePSNR(originImageData, imageData, width, height, BytesPerPixel); 
	cout << "PSNR for original image and filtered image: " << psnr << endl;
	cout << "PSNR for original image and noisy image" << psnrnoisy << endl; 
	return 0; 
}