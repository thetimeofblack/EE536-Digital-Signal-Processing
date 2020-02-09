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
				int error = OriginImageData[row + EdgeSize][col + EdgeSize] - HalftonedImageData[row][col];
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						OriginImageData[row + EdgeSize + i][col + EdgeSize + j] += error * CoefficientMatrix[i + 1][j + 1]/16;
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
				int error = OriginImageData[row + EdgeSize][col + EdgeSize] - HalftonedImageData[row][col];

				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						OriginImageData[row + EdgeSize + i][col + EdgeSize + j] += error * MirrorCoefficientMatrix[i + 1][j + 1]/16;
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
				int error = OriginImageData[row + EdgeSize][col + EdgeSize] - HalftonedImageData[row][col];
				for (int i = -2; i <= 2; i++) {
					for (int j = -2; j <= 2; j++) {
						OriginImageData[row + EdgeSize + i][col + EdgeSize + j] += error * CoefficientMatrix[i + 2][j + 2]/48;
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
				int error = OriginImageData[row + EdgeSize][col + EdgeSize] - HalftonedImageData[row][col];

				for (int i = -2; i <= 2; i++) {
					for (int j = -2; j <= 2; j++) {
						OriginImageData[row + EdgeSize + i][col + EdgeSize + j] += error * MirrorCoefficientMatrix[i + 2][j + 2]/48;
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
		if (row % 2 == 0) {
			for (int col = 0; col < width; col++) {
				if (OriginImageData[row + EdgeSize][col + EdgeSize] > threshold) {
					HalftonedImageData[row][col] = 255;
				}
				else {
					HalftonedImageData[row][col] = 0;
				}
				int error = OriginImageData[row + EdgeSize][col + EdgeSize] - HalftonedImageData[row][col];
				for (int i = -2; i <= 2; i++) {
					for (int j = -2; j <= 2; j++) {
						OriginImageData[row + EdgeSize + i][col + EdgeSize + j] += error * CoefficientMatrix[i + 2][j + 2]/42;
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
				int error = OriginImageData[row + EdgeSize][col + EdgeSize] - HalftonedImageData[row][col];

				for (int i = -2; i <= 2; i++) {
					for (int j = -2; j <= 2; j++) {
						OriginImageData[row + EdgeSize + i][col + EdgeSize + j] += error * MirrorCoefficientMatrix[i + 2][j + 2]/42;
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



}