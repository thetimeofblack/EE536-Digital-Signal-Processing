#include "../dipHeader.h"

void warpImageDataBy45DegreeUpperLeft(unsigned char*** OriginImageData, unsigned char*** ScaledImageData, int width, int height, int BytesPerPixel) {
	double pi = 3.14159265;
	for (int row = 0; row <= height / 2; row++) {
		for (int col = 0; col <= width / 2; col++) {
			for (int cor = 0; cor < BytesPerPixel; cor++) {
				double x = width / 2 - col + 0.5;
				double y = height / 2 + 0.5 - row;
				double dist = sqrt(pow(x, 2) + pow(y, 2));
				double theta = atan(y / x);
				double u;
				double v;
				if (theta >= pi / 4) {
					u = dist + x - y;
					v = dist;
				}
				else {
					u = dist;
					v = dist +y-x;
				}
				int warpedRow = height / 2 + 0.5 - v;
				int warpedCol = width / 2 + 0.5 - u;
				if (u > 256 || u < 0 || v>256 || v < 0) continue;
				ScaledImageData[row][col][cor] = OriginImageData[warpedRow][warpedCol][cor];
			}
		}
	}

}

void warpImageDataBy45DegreeUpperRight(unsigned char*** OriginImageData, unsigned char*** ScaledImageData, int width, int height, int BytesPerPixel) {
	double pi = 3.14159265;
	for (int row = 0; row <= height / 2; row++) {
		for (int col = width/2; col < width ; col++) {
			for (int cor = 0; cor < BytesPerPixel; cor++) {
				double x = col - width/2 +0.5;
				double y = height/2-row+0.5;
				double dist = sqrt(pow(x, 2) + pow(y, 2));
				double theta = atan(y / x);
				double u;
				double v;
				if (theta >= pi / 4) {
					u = x; 
					v = dist;
				}
				else {
					u = x;
					v = dist;
				}
				int warpedRow = u + 255.5;
				int warpedCol = 256.5 - v;
				if (u > 256 || u < 0 || v>256 || v < 0) continue;
				ScaledImageData[row][col][cor] = OriginImageData[warpedRow][warpedCol][cor];
			}
		}
	}

}


void warpImageDataBy45DegreeDownLeft(unsigned char*** OriginImageData, unsigned char*** ScaledImageData, int width, int height, int BytesPerPixel) {
	double pi = 3.14159265;
	for (int row = height/2; row < height; row++) {
		for (int col = 0; col <= width / 2; col++) {
			for (int cor = 0; cor < BytesPerPixel; cor++) {
				double x = width / 2 - col + 0.5;
				double y = height / 2 + 0.5 - row;
				double dist = sqrt(pow(x, 2) + pow(y, 2));
				double theta = atan(y / x);
				double u;
				double v;
				if (theta >= pi / 4) {
					u = dist + x - y;
					v = dist;
				}
				else {
					u = dist;
					v = dist + y - x;
				}
				int warpedRow = height / 2 + 0.5 - v;
				int warpedCol = width / 2 + 0.5 - u;
				if (u > 256 || u < 0 || v>256 || v < 0) continue;
				ScaledImageData[row][col][cor] = OriginImageData[warpedRow][warpedCol][cor];
			}
		}
	}

}

void warpImageDataBy45DegreeDownRight(unsigned char*** OriginImageData, unsigned char*** ScaledImageData, int width, int height, int BytesPerPixel) {
	double pi = 3.14159265;
	for (int row = 0; row <= height / 2; row++) {
		for (int col = 0; col <= width / 2; col++) {
			for (int cor = 0; cor < BytesPerPixel; cor++) {
				double x = width / 2 - col + 0.5;
				double y = height / 2 + 0.5 - row;
				double dist = sqrt(pow(x, 2) + pow(y, 2));
				double theta = atan(y / x);
				double u;
				double v;
				if (theta >= pi / 4) {
					u = dist + x - y;
					v = dist;
				}
				else {
					u = dist;
					v = dist + y - x;
				}
				int warpedRow = height / 2 + 0.5 - v;
				int warpedCol = width / 2 + 0.5 - u;
				if (u > 256 || u < 0 || v>256 || v < 0) continue;
				ScaledImageData[row][col][cor] = OriginImageData[warpedRow][warpedCol][cor];
			}
		}
	}

}

void warpImageDataByPolar(unsigned char*** OriginImageData, unsigned char*** ScaledImageData, int width, int height, int BytesPerPixel) {
	double pi = 3.14159265; 
	for (int row = 0; row <= height / 2; row++) {
		for (int col = 0; col <= width / 2; col++) {
			for (int cor = 0; cor < BytesPerPixel; cor++) {
				double x = width/2 - col + 0.5;
				double y = height/2 + 0.5 - row;
				double dist = sqrt(pow(x, 2) + pow(y, 2));
				double theta = atan(y / x);
				double u; 
				double v; 
				if (theta >= pi / 4) {
					u = dist * tan(pi/2-theta);
					v = dist; 
				}
				else {
					u = dist; 
					v = dist * tan(theta);
				}
				int warpedRow = height/2 + 0.5 - v;
				int warpedCol = width/2 + 0.5 - u ;
				if (u > 256 || u < 0 || v>256 || v < 0) continue;
				ScaledImageData[row][col][cor] = OriginImageData[warpedRow][warpedCol][cor]; 
			}
		}
	}

}
void warpImageDataBy45Degree(unsigned char*** OriginImageData, unsigned char*** WarpedImageData, int width, int height, int BytesPerPixel) {
	warpImageDataBy45DegreeUpperLeft(OriginImageData, WarpedImageData, width, height, BytesPerPixel); 
	warpImageDataBy45DegreeUpperRight(OriginImageData, WarpedImageData, width, height, BytesPerPixel); 
	warpImageDataBy45DegreeDownLeft(OriginImageData, WarpedImageData, width, height, BytesPerPixel);
	warpImageDataBy45DegreeDownRight(OriginImageData, WarpedImageData, width, height, BytesPerPixel);
}

void warpImageData(unsigned char*** OriginImageData, unsigned char*** ScaledImageData, int width, int height, int BytesPerPixel) {
	double inverseMatrixA[2][6] = { {
	 -74.2902,
	1.2902,
	0.2902,
	0.0000,
   - 0.0011,
		 0},
	{ 

   75.2941,
   - 0.2941,
	0.7059,
   - 0.0000,
	0.0011,
		 0
}};

	for (int row = 0; row < height; row++) {
		for(int col = 0 ;col<width ;col++){
			for (int cor = 0; cor < BytesPerPixel; cor++) {
				//compute col 
				double x = col - 0.5; 
				double y = height + 0.5 -row; 
				double u = 0; 
				double v = 0;
				u = inverseMatrixA[0][0] + inverseMatrixA[0][1] * x + inverseMatrixA[0][2] * y + inverseMatrixA[0][3] * pow(x, 2) + inverseMatrixA[0][5] * x * y + inverseMatrixA[0][5] * pow(y, 2); 
				v = inverseMatrixA[1][0] + inverseMatrixA[1][1] * x + inverseMatrixA[1][2] * y + inverseMatrixA[1][3] * pow(x, 2) + inverseMatrixA[1][5] * x * y + inverseMatrixA[1][5] * pow(y, 2);
				int warpedRow=height + 0.5 - v; 
				int warpedCol = u - 0.5; 
				//cout << warpedRow << endl;
				if (warpedCol > 255 || warpedCol < 0 || warpedRow>255 || warpedRow < 0) continue; 
				ScaledImageData[row][col][cor] = OriginImageData[warpedRow][warpedCol][cor]; 
			}
		}
	}
}




int main(int argc, char* argv[])
{
	cout << "hello world" << endl;
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
	
	char HedwigFilename[30] = "../data/hedwig.raw";
	char RaccoonFilename[30] = "../data/Raccoon.raw"; 
	char bb8Filename[30] = "../data/bb8.raw"; 
	width = 512; 
	height = 512;
	BytesPerPixel = 3; 
	
	unsigned char*** OriginImageData = alloc3DImage(width, height, BytesPerPixel); 
	read3DImageFile(HedwigFilename, OriginImageData, width, height, BytesPerPixel); 
	cout << "hello world" << endl; 
	unsigned char*** WarpedImageData = alloc3DImage(width , height , BytesPerPixel); 
	warpImageDataBy45Degree(OriginImageData, WarpedImageData, width, height, BytesPerPixel);
	char HedwigOutputFilename[30] = "WarpedHedwig.raw";
	write3DImageFile(HedwigOutputFilename, WarpedImageData, width , height , BytesPerPixel); 

	read3DImageFile(RaccoonFilename, OriginImageData, width, height, BytesPerPixel);
	warpImageDataBy45Degree(OriginImageData, WarpedImageData, width, height, BytesPerPixel);
	char RacoonOutputFilename[30] = "WarpedRacoon.raw";
	write3DImageFile(RacoonOutputFilename, WarpedImageData, width, height, BytesPerPixel);

	read3DImageFile(bb8Filename, OriginImageData, width, height, BytesPerPixel);
	warpImageDataBy45Degree(OriginImageData, WarpedImageData, width, height, BytesPerPixel);
	char Bb8OutputFilename[30] = "Warpedbb8.raw";
	write3DImageFile(Bb8OutputFilename, WarpedImageData, width, height, BytesPerPixel);
}