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






void RandomPickBasedHistogramEqualizationByChannel(unsigned char*** imageData, unsigned char*** equalizedData, int width, int height, int BytesPerPixel,int channel) {
	unsigned int* RowIndex = new unsigned int[width * height]();
	unsigned int* ColIndex = new unsigned int[width * height]();
	unsigned char* PixelIntensityIndex = new unsigned char[width * height]();
	int bucketsize = ceil(width * height / 256); 
	unsigned int tempIndex = 0;
	for (int pixelValue = 0; pixelValue < 256; pixelValue++) {
		for (int row = 0; row < height; row++) {
			for (int col = 0; col < width; col++) {
				if (imageData[row][col][channel] == pixelValue) {
					RowIndex[tempIndex] = row;
					ColIndex[tempIndex] = col;
					PixelIntensityIndex[tempIndex] = pixelValue;
					tempIndex = tempIndex + 1;
				}
			}
		}
	}

	// Change the pixel array acccording to bucket size
	unsigned int tempCount = 0;
	unsigned char tempPixel = 0;
	unsigned int tempArrayIndex = 0;
	for (int i = 0; i < (width * height); i++) {
		if (tempCount != bucketsize) {
			PixelIntensityIndex[tempArrayIndex] = tempPixel;
			tempArrayIndex = tempArrayIndex + 1;
			tempCount = tempCount + 1;
		}
		else {
			tempPixel = tempPixel + 1;
			tempCount = 0;
		}
	}

	// Track back the changed pixel values to a 2D array
	unsigned int tempRowIndex;
	unsigned int tempColIndex;
	for (int i = 0; i < (width * height); i++) {
		tempRowIndex = RowIndex[i];
		tempColIndex = ColIndex[i];
		equalizedData[tempRowIndex][tempColIndex][channel] = PixelIntensityIndex[i];
	}

	delete[] RowIndex;
	delete[] ColIndex;
	delete[] PixelIntensityIndex;


}

void RandomPickHistogramEqualization(unsigned char*** imageData, unsigned char*** equalizedData, int width, int height, int BytesPerPixel) {
	for (int cor = 0; cor < 3; cor++) {
		RandomPickBasedHistogramEqualizationByChannel(imageData, equalizedData, width, height, BytesPerPixel, cor); 
	}

}
void TransferFunctionBasedHistogramEqualization(unsigned char*** imageData, unsigned char ***equalizedData, int width, int height, int BytesPerPixel) {
	const int MAX_INTENSITY = 255;
	int totalpixels = width * height; 
	int* histogramR = new int[256];
	int* histogramG = new int[256];
	int* histogramB = new int[256];
	int* transformArrayR = new int[256];
	int* transformArrayG = new int[256];
	int* transformArrayB = new int[256];
	histogramCountByChannel(imageData, histogramR, width, height, BytesPerPixel, 0); 
	histogramCountByChannel(imageData, histogramG, width, height, BytesPerPixel, 1);
	histogramCountByChannel(imageData, histogramB, width, height, BytesPerPixel, 2);
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
	if (method == 1) {
		TransferFunctionBasedHistogramEqualization(imageData, equalizedImageData, width, height, BytesPerPixel); 
	}
	else{
		RandomPickHistogramEqualization(imageData,equalizedImageData,width,height,BytesPerPixel);
	}

	write3DImageFile(argv[2], equalizedImageData,width,height, BytesPerPixel); 
	return 0;
}