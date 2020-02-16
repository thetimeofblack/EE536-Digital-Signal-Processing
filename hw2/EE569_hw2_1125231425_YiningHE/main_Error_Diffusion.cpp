#include "../dipHeader.h"

/*
				OriginImageData[row + EdgeSize][col + EdgeSize + 1] += 8 / 42 * error;
				OriginImageData[row + EdgeSize][col + EdgeSize + 2] += 4 / 42 * error;

				OriginImageData[row + EdgeSize + 1][col + EdgeSize - 2] += 2 / 42 * error;
				OriginImageData[row + EdgeSize + 1][col + EdgeSize - 1] += 4 / 42 * error;
				OriginImageData[row + EdgeSize + 1][col + EdgeSize] += 8 / 42 * error;
				OriginImageData[row + EdgeSize + 1][col + EdgeSize + 1] += 4 / 42 * error;
				OriginImageData[row + EdgeSize + 1][col + EdgeSize + 2] += 2 / 42 * error;


				OriginImageData[row + EdgeSize + 2][col + EdgeSize - 2] += 1 / 42 * error;
				OriginImageData[row + EdgeSize + 2][col + EdgeSize - 1] += 2 / 42 * error;
				OriginImageData[row + EdgeSize + 2][col + EdgeSize] += 4 / 42 * error;
				OriginImageData[row + EdgeSize + 2][col + EdgeSize + 1] += 2 / 42 * error;
				OriginImageData[row + EdgeSize + 2][col + EdgeSize + 2] += 1 / 42 * error;


*/


void ErrorDiffusionFloydSteinberg(unsigned char** OriginImageData,unsigned char** HalftonedImageData , int width, int height, int BytesPerPixel,int EdgeSize,int threshold) {
	double CoefficientMatrix[3][3] = { {0,0,0},{0,0,7.0},{3.0,5.0,1.0} };
	double MirrorCoefficientMatrix[3][3] = { {0,0,0},{7.0,0,0.0},{1.0,5.0,3.0} };
	for (int row = 0; row < height; row++) {
		if (row % 2 == 0) {
			for (int col = 0; col < width; col++) {
				if (OriginImageData[row + EdgeSize][col + EdgeSize] > threshold) {
					HalftonedImageData[row][col] = 255;
				}
				else {
					HalftonedImageData[row][col] = 0;
				}
				double error = OriginImageData[row + EdgeSize][col + EdgeSize] - HalftonedImageData[row][col];
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						OriginImageData[row + EdgeSize + i][col + EdgeSize + j] += error * CoefficientMatrix[i + 1][j + 1]/16.0;
					}
				}

			}
		}
		else {
			for (int col = width - 1; col >= 0; col--) {
				if (OriginImageData[row + EdgeSize][col + EdgeSize] > threshold) {
					HalftonedImageData[row][col] = 255;
				}
				else {
					HalftonedImageData[row][col] = 0;
				}
				double error = OriginImageData[row + EdgeSize][col + EdgeSize] - HalftonedImageData[row][col];

				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						OriginImageData[row + EdgeSize + i][col + EdgeSize + j] += error * MirrorCoefficientMatrix[i + 1][j + 1]/16.0;
					}
				}
			}
		}
	}


}

void ErrorDiffusionJJN(unsigned char** OriginImageData, unsigned char** HalftonedImageData, int width, int height, int BytesPerPixel, int EdgeSize, int threshold) {
	
	double CoefficientMatrix[5][5] = { {0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,7.0,5.0},{3.0,5.0,7.0,5.0,3.0},{1.0,3.0,5.0,3.0,1.0} };
	double MirrorCoefficientMatrix[5][5] = { {0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0},{5.0,7.0,0.0,0.0,0.0},{3.0,5.0,7.0,5.0,3.0},{1.0,3.0,5.0,3.0,1.0} };

	for (int row = 0; row < height; row++) {
		if (row % 2 == 0) {
			for (int col = 0; col < width; col++) {
				if (OriginImageData[row + EdgeSize][col + EdgeSize] > threshold) {
					HalftonedImageData[row][col] = 255;
				}
				else {
					HalftonedImageData[row][col] = 0;
				}
				double error = OriginImageData[row + EdgeSize][col + EdgeSize] - HalftonedImageData[row][col];
				for (int i = -2; i <= 2; i++) {
					for (int j = -2; j <= 2; j++) {
						OriginImageData[row + EdgeSize + i][col + EdgeSize + j] += error * CoefficientMatrix[i + 2][j + 2]/48.0;
					}
				}


			}
		}
		else {
			for (int col = width - 1; col >= 0; col--) {
				if (OriginImageData[row + EdgeSize][col + EdgeSize] > threshold) {
					HalftonedImageData[row][col] = 255;
				}
				else {
					HalftonedImageData[row][col] = 0;
				}
				double error = OriginImageData[row + EdgeSize][col + EdgeSize] - HalftonedImageData[row][col];

				for (int i = -2; i <= 2; i++) {
					for (int j = -2; j <= 2; j++) {
						OriginImageData[row + EdgeSize + i][col + EdgeSize + j] += error * MirrorCoefficientMatrix[i + 2][j + 2]/48.0;
					}
				}
			}
		}
	}

}

void ErrorDiffusionStucki(unsigned char** OriginImageData, unsigned char** HalftonedImageData, int width, int height, int BytesPerPixel, int EdgeSize, int threshold) {
	double CoefficientMatrix[5][5] = { {0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,8.0,4.0},{2.0,4.0,8.0,4.0,2.0},{1.0,2.0,4.0,2.0,1.0} };
	double MirrorCoefficientMatrix[5][5] = { {0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0},{4.0,8.0,0.0,0.0,0.0},{2.0,4.0,8.0,4.0,2.0},{1.0,2.0,4.0,2.0,1.0} };
	
	for (int row = 0; row < height; row++) {
		//double error = 0.0;
		if (row % 2 == 0) {
			for (int col = 0; col < width; col++) {
				if (OriginImageData[row + EdgeSize][col + EdgeSize] >= threshold) {
					HalftonedImageData[row][col] = 255;
				}
				else {
					HalftonedImageData[row][col] = 0;
				}
			
				double error = OriginImageData[row + EdgeSize][col + EdgeSize] - HalftonedImageData[row][col];
				//cout << error << " "; 
				for (int i = -2; i <= 2; i++) {
					for (int j = -2; j <= 2; j++) {
						OriginImageData[row + EdgeSize + i][col + EdgeSize + j] += error * CoefficientMatrix[i + 2][j + 2]/42.0;

					}
				}

			}
		}
		else {
			for (int col = width - 1; col >= 0; col--) {
				if (OriginImageData[row + EdgeSize][col + EdgeSize] >= threshold) {
					HalftonedImageData[row][col] = 255;
				}
				else {
					HalftonedImageData[row][col] = 0;
				}
				double error = OriginImageData[row + EdgeSize][col + EdgeSize] - HalftonedImageData[row][col];

				for (int i = -2; i <= 2; i++) {
					for (int j = -2; j <= 2; j++) {
						OriginImageData[row + EdgeSize + i][col + EdgeSize + j] += error * MirrorCoefficientMatrix[i + 2][j + 2]/42.0;
					}
				}
			}
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
	cout << "Hello world" << endl;
	char lighthousefilename[30] = "../Problem2/LightHouse.raw"; 
	int EdgeSize = 6; 
	int ltwidth = 750; 
	int ltheight = 500; 
	int ltBytesPerPixel = 1; 
	unsigned char** LightHouseImageData = alloc2DImage(ltwidth, ltheight, ltBytesPerPixel); 
	read2DImageFile(lighthousefilename, LightHouseImageData, ltwidth, ltheight, ltBytesPerPixel); 
	
	
	
	unsigned char** extendedltImageData = alloc2DImage(ltwidth + 2 * EdgeSize, ltheight + 2 * EdgeSize, ltBytesPerPixel); 
	//be careful about the pure image 
	
	extend2DImageEdge(LightHouseImageData,extendedltImageData,ltwidth,ltheight,ltBytesPerPixel,EdgeSize );
	unsigned char** FSDiffusedImageData = alloc2DImage(ltwidth, ltheight, ltBytesPerPixel); 
	ErrorDiffusionFloydSteinberg(extendedltImageData, FSDiffusedImageData, ltwidth, ltheight, ltBytesPerPixel, EdgeSize, 125); 
	
	extend2DImageEdge(LightHouseImageData, extendedltImageData, ltwidth, ltheight, ltBytesPerPixel, EdgeSize);
	unsigned char** JJNDiffusedImageData = alloc2DImage(ltwidth, ltheight, ltBytesPerPixel);
	ErrorDiffusionJJN(extendedltImageData, JJNDiffusedImageData, ltwidth, ltheight, ltBytesPerPixel, EdgeSize, 80);
	
	extend2DImageEdge(LightHouseImageData, extendedltImageData, ltwidth, ltheight, ltBytesPerPixel, EdgeSize);
	unsigned char** StuckiDiffusedImageData = alloc2DImage(ltwidth, ltheight, ltBytesPerPixel);
	ErrorDiffusionStucki(extendedltImageData, StuckiDiffusedImageData, ltwidth, ltheight, ltBytesPerPixel, EdgeSize, 200);
	
	char FloydSteinbergFilename[30] = "LightHouseFS.raw"; 
	char JJNFilename[30] = "LightHouseJJN.raw"; ; 
	char StuckiFilename[30] = "LightHouseStucki.raw"; 

	write2DImageFile(FloydSteinbergFilename, FSDiffusedImageData, ltwidth, ltheight, ltBytesPerPixel); 
	write2DImageFile(JJNFilename, JJNDiffusedImageData, ltwidth, ltheight, ltBytesPerPixel);
	write2DImageFile(StuckiFilename, StuckiDiffusedImageData, ltwidth, ltheight, ltBytesPerPixel);

}