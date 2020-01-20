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
	int totalpixel = width * height; 
	int* histogramR = new int[256]; 
	int* sumHistogramR = new int[256]; 
	int* histogramG = new int[256];
	int* sumHistogramG = new int[256];
	int* histogramB = new int[256];
	int* sumHistogramB = new int[256];
	memset(sumHistogramR, 0, 256 * sizeof(int));
	memset(sumHistogramG, 0, 256 * sizeof(int));
	memset(sumHistogramB, 0, 256 * sizeof(int));
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
			equalizedData[row][col][0] = sumHistogramR[imageData[row][col][0]] * MAX_INTENSITY / totalpixel; 
			equalizedData[row][col][1] = sumHistogramG[imageData[row][col][1]] * MAX_INTENSITY / totalpixel;
			equalizedData[row][col][2] = sumHistogramB[imageData[row][col][2]] * MAX_INTENSITY / totalpixel;
		}
	}
}


void cumulativeProbabilityBasedHistogramEqualization(unsigned char*** imageData, unsigned char ***equalizedData, int width, int height, int BytesPerPixel) {
	const int MAX_INTENSITY = 255;
	int totalpixels = width * height; 
	int* histogramR = new int[256];
	int* histogramG = new int[256];
	int* histogramB = new int[256];
	int* transformArrayR = new int[256];
	int* transformArrayG = new int[256];
	int* transformArrayB = new int[256];
	histogramCountByChannel(imageData, histogramR, width, height, BytesPerPixel, 0); 
	histogramCountByChannel(imageData, histogramG, width, height, BytesPerPixel, 0);
	histogramCountByChannel(imageData, histogramB, width, height, BytesPerPixel, 0);
	int currR = 0;
	int currG = 0;
	int currB = 0;
	for (int i = 0; i < 256; i++) {
		currR += histogramR[i];
		currG += histogramG[i];
		currB += histogramB[i];
		transformArrayR[i] = round((((float)currR) * 255) / totalpixels);
		transformArrayG[i] = round((((float)currG) * 255) / totalpixels);
		transformArrayB[i] = round((((float)currB) * 255) / totalpixels);
	}
	
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			equalizedData[row][col][0] = transformArrayR[imageData[row][col][0]]; 
			equalizedData[row][col][1] = transformArrayG[imageData[row][col][1]];
			equalizedData[row][col][2] = transformArrayB[imageData[row][col][2]];
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
	// method A transfer function based  is 0  
	// method B cumulative probability distribution function based is 1 
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
	unsigned char*** equalizedImageData; 
	imageData = alloc3DImage(width, height, BytesPerPixel); 
	equalizedImageData = alloc3DImage(width, height, BytesPerPixel);
	read3DImageFile(argv[1],imageData, width ,height, BytesPerPixel);
	if (method == 0) {
		cumulativeProbabilityBasedHistogramEqualization(imageData, equalizedImageData, width, height, BytesPerPixel); 
	}
	else{
		transferFunctionBasedHistogramEqualization(imageData,equalizedImageData,width,height,BytesPerPixel);
	}

	write3DImageFile(argv[2], equalizedImageData,width,height, BytesPerPixel); 
	return 0;
}