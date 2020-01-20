#include "dipHeader.h"
#include <bitset>

void histogramCountByChannel(unsigned char*** imageData, int* histcount ,  int width, int height, int BytesPerPixel , int channel) {
	memset(histcount, 0, 256 * sizeof(int)); 
	for (int row = 0; row < height; row++){
		for (int col = 0; col < width; col++) {
			histcount[imageData[row][col][channel]] += 1; 
		}
	}
}


void writeHistDataFile(char* filename, int histData[256]) {
	FILE* file;
	file = fopen(filename, "w");
	if (file != NULL){
		for (int i = 0; i < 256; i++){
			fprintf(file, "%d\t%u\n", i, histData[i]);
		}
		fclose(file);
		//cout << "File " << fileName << " written successfully !!!" << endl;
	}
	else{
		cout << "Cannot open file " << filename << endl;
	}
}

void transferFunctionBasedHistogramEqualization(unsigned char*** imageData, unsigned char ***equalizedData, int width, int height, int BytesPerPixel) {
	const int MAX_INTENSITY = 255; 
	int* histogramR = new int[256]; 
	int* sumHistogramR = new int[256]; 
	int* histogramG = new int[256];
	int* sumHistogramG = new int[256];
	int* histogramB = new int[256];
	int* sumHistogramB = new int[256];
	histogramCountByChannel(imageData, histogramR, width, height, BytesPerPixel, 0); 
	histogramCountByChannel(imageData, histogramG, width, height, BytesPerPixel, 1);
	histogramCountByChannel(imageData, histogramB, width, height, BytesPerPixel, 2);
	for (int i = 0; i < 256; i++) {
		sumHistogramR[i] += histogramR[i]; 
		sumHistogramG[i] += histogramG[i]; 
		sumHistogramB[i] += histogramB[i]; 
	}
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int pixelCount = row * width + col+1; 
			equalizedData[row][col][0] = sumHistogramR[imageData[row][col][0]] * MAX_INTENSITY / pixelCount; 
			equalizedData[row][col][1] = sumHistogramG[imageData[row][col][1]] * MAX_INTENSITY / pixelCount;
			equalizedData[row][col][2] = sumHistogramB[imageData[row][col][2]] * MAX_INTENSITY / pixelCount;
		}
	}
}

void pdfPixelCountByChannel(unsigned char*** imageData, double* pdf, int row, int col, int width, int height, int channel) {
	int pixelCount = row * width + col + 1; 
	for (int i = 0; i <= row; i++) {
		for (int j = 0; j <= col; j++) {
			pdf[imageData[i][j][channel]]+= 1/pixelCount ; 
		}
	}
}

double sumPdfByPixel(unsigned char*** imageData,int PixelValue,  double* pdf, double * cdf, int row, int col, int width, int height, int channel) {
	double result = 0; 
	for (int i = 0; i <= PixelValue; i++) {
		result += pdf[i]; 
	}
	return result;
}

void cumulativeProbabilityBasedHistogramEqualization(unsigned char*** imageData, unsigned char ***equalizedData, int width, int height, int BytesPerPixel) {
	const int MAX_INTENSITY = 255;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			double* tempPdfR = new double[256];
			double* tempPdfG = new double[256];
			double* tempPdfB = new double[256];
			pdfPixelCountByChannel(imageData, tempPdfR, row, col, width, height, 0); 
			pdfPixelCountByChannel(imageData, tempPdfG, row, col, width, height, 1);
			pdfPixelCountByChannel(imageData, tempPdfB, row, col, width, height, 2);

		}
	}


}


int main(int argc, char* argv[]) {
	// Define file pointer and variables
	FILE* file;
	int BytesPerPixel;
	int Size = 256;
	int rows = 256;
	int cols = 256;
	int width = 256;
	int height = 256;
	// method A is 0  method B is 1 
	int method = 0;  
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
			method = atoi(argv[6]); 
		}
	}
	unsigned char*** imageData; 
	unsigned char*** extendedImageData; 
	unsigned char*** equalizedImageData; 
	imageData = alloc3DImage(width, height, BytesPerPixel); 
	extendedImageData = alloc3DImage(width, height, BytesPerPixel); 
	equalizedImageData = alloc3DImage(width, height, BytesPerPixel);
	read3DImageFile(argv[1],imageData, width ,height, BytesPerPixel);


	write3DImageFile(argv[2], equalizedImageData,width,height, BytesPerPixel); 
	return 0;
}