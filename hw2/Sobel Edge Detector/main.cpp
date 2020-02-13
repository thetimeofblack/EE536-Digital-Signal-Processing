#include "..\dipHeader.h"

// Problem a 


/*
 Test code : 
	cout<<"Double Result: " << DoubleResult<< endl;
	cout<<"Final Result: "<<result << endl;
*/
unsigned char compXGradientPixel(unsigned char** ImageData , int row ,int col ,int BytesPerPixel) {
	double DoubleResult = 0; 
	DoubleResult = (1)*ImageData[row + 1][col + 1] + (1)* ImageData[row - 1][col + 1] +2* ImageData[row][col + 1] + (-1)*ImageData[row - 1][col - 1] + (-1)*ImageData[row + 1][col - 1] + (-2)*ImageData[row][col - 1]; 
	unsigned char result = 0; 
	result = round(0.125 * DoubleResult) + 127; 
	return result; 
}


unsigned char compYGradientPixel(unsigned char** ImageData, int row, int col, int BytesPerPixel) {
	double DoubleResult = 0;
	DoubleResult = (-1) * ImageData[row - 1][col - 1] + (-2) * ImageData[row - 1][col] + (-1) * ImageData[row - 1][col + 1] + ImageData[row + 1][col - 1] + 2 * ImageData[row + 1][col] + ImageData[row + 1][col + 1]; 
	unsigned char result = 0;
	result = round(0.125 * DoubleResult) + 127;
	return result;
}

double compXGradientPixelDouble(unsigned char** ImageData, int row, int col, int BytesPerPixel) {
	double DoubleResult = 0;
	DoubleResult = (-1) * ImageData[row-1][col - 1] + (-2) * ImageData[row ][col-1] + (-1) * ImageData[row + 1][col - 1] + ImageData[row -1][col + 1] + 2 * ImageData[row ][col+1] + ImageData[row + 1][col + 1];
	return DoubleResult;
}

double compYGradientPixelDouble(unsigned char** ImageData, int row, int col, int BytesPerPixel) {
	double DoubleResult = 0;
	DoubleResult = (-1) * ImageData[row - 1][col - 1] + (-2) * ImageData[row - 1][col] + (-1) * ImageData[row - 1][col + 1] + ImageData[row + 1][col - 1] + 2 * ImageData[row + 1][col] + ImageData[row + 1][col + 1];
	return DoubleResult;
}

void compXGradient(unsigned char** ImageData,unsigned char** XGrad2DArray,  int width, int height ,int BytesPerPixel ,int edgesize) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			XGrad2DArray[row][col] = compXGradientPixel(ImageData, row + edgesize, col + edgesize, BytesPerPixel); 
		}
	}

}


void compYGradient(unsigned char** ImageData,unsigned char** YGrad2DArray , int width, int height, int BytesPerPixel , int edgesize) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			YGrad2DArray[row][col] = compYGradientPixel(ImageData, row + edgesize, col + edgesize, BytesPerPixel);
		}
	}
}

void compMagnitudeGradient(unsigned char** XGrad2DArray, unsigned char** YGrad2DArray, unsigned char** MagntGrad2DArray, int width, int height, int BytesPerPixel) { 
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width;  col++) {
			double tmp = 0; 
			tmp = sqrt(pow(XGrad2DArray[row][col], 2) + pow(YGrad2DArray[row][col], 2));
			int normalizedtmp = round(tmp / sqrt(pow(255, 2) + pow(255, 2)) * 255); 
			MagntGrad2DArray[row][col] = normalizedtmp  ; 

		}
	}

}

void cmpMagnitudeGradientByDouble(unsigned char** OriginImageData, unsigned char** ObtainedImageData, int width, int height, int BytesPerPixel ,int edgesize) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			double xgrad; 
			double ygrad; 
			double tmp; 
			xgrad = compXGradientPixelDouble(OriginImageData, row + edgesize, col + edgesize, BytesPerPixel); 
			ygrad = compYGradientPixelDouble(OriginImageData, row + edgesize, col + edgesize, BytesPerPixel); 
			tmp = sqrt(pow(xgrad, 2) + pow(ygrad, 2));
			int normalizedtmp  = round(tmp * 0.25/sqrt(2));
			ObtainedImageData[row][col] = normalizedtmp; 
		} 
	}
}

void tuneMagnitudeGrad(unsigned char** OriginImageData, unsigned char** ObtainedImageData, int width, int height, int BytesPerPixel , int threshold) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (OriginImageData[row][col] <= threshold) {
				ObtainedImageData[row][col] = 0; 
			}
			else {
				ObtainedImageData[row][col] = 255;
			}
		}
	}

}

void normalize2DImageData(unsigned char** OriginImageData, int width, int height, int BytesPerPixel) {

}
/*
    Y=0.2989∗R+0.5870∗G+0.1140∗B
*/
void convertRGB2GrayImage(unsigned char*** ImageRGBData, unsigned char** ImageData, int width, int height, int BytesPerPixel) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			double grayValue = 0.2989*ImageRGBData[row][col][0] + 0.5870*ImageRGBData[row][col][1] + 0.1140*ImageRGBData[row][col][2];
			ImageData[row][col] = round(grayValue); 
		}
	}
}

int main(int argc, char* argv[]) {
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
	width = 481; 
	height = 321; 
	BytesPerPixel = 3; 
	char DogsImagefilename[30] = "../Problem1/Dogs.raw"; 
	char detectedDogsImagefilename[30] = "../Problem1/Dogs_Sobel.raw"; 
	char GalleryImagefilename[30] = "../Problem1/Gallery.raw";
	char detectedGalleryImagefilename[30] = "../Problem1/Gallery_Sobel.raw";
	// get gray-scaled image
	int edgesize = 3; 
	unsigned char*** ImageOriginData = alloc3DImage(width, height, BytesPerPixel); 
	read3DImageFile(GalleryImagefilename, ImageOriginData, width, height, BytesPerPixel); 
	unsigned char** GrayImageData = alloc2DImage(width, height, BytesPerPixel); 
	convertRGB2GrayImage(ImageOriginData, GrayImageData, width, height, BytesPerPixel); 
	write2DImageFile(detectedGalleryImagefilename, GrayImageData, width, height, BytesPerPixel); 


	// extend image
	unsigned char** extendedImageData = alloc2DImage(width + 2 * edgesize, height + 2 * edgesize, BytesPerPixel);
	extend2DImageEdge(GrayImageData, extendedImageData, width, height, BytesPerPixel, edgesize); 

	// compute X Gradient
	unsigned char** XGradientImageData = alloc2DImage(width, height, BytesPerPixel);
	compXGradient(extendedImageData,XGradientImageData,width,height,BytesPerPixel,edgesize);
	char XGradfilename[20] = "XGrad.raw"; 
	write2DImageFile(XGradfilename,XGradientImageData,width,height,BytesPerPixel);
	
	// compute Y Gradient 
	unsigned char** YGradientImageData = alloc2DImage(width, height, BytesPerPixel); 
	compYGradient(extendedImageData, YGradientImageData, width, height, BytesPerPixel,edgesize); 
	char YGradfilename[20] = "YGrad.raw"; 
	write2DImageFile(YGradfilename, YGradientImageData, width, height, BytesPerPixel); 

	// magnitude of the x gradient and y gradient 
	unsigned char** MagnitudeGradImageData = alloc2DImage(width, height, BytesPerPixel); 
	cmpMagnitudeGradientByDouble(extendedImageData, MagnitudeGradImageData, width, height, BytesPerPixel,edgesize);
	char Magnitudefilename[20] = "Magnitude.raw" ; 
	write2DImageFile(Magnitudefilename, MagnitudeGradImageData, width, height, BytesPerPixel);
	
	// thresholding the edge map
	int threshold = 20; 
	unsigned char** TunedMagnitudeGradImageData = alloc2DImage(width, height, BytesPerPixel); 
	tuneMagnitudeGrad(MagnitudeGradImageData, TunedMagnitudeGradImageData, width, height, BytesPerPixel, threshold); 
	char TunedMagnitudefilename[20] = "TunedManitude.raw"; 
	write2DImageFile(TunedMagnitudefilename, TunedMagnitudeGradImageData, width, height, BytesPerPixel); 
	

}