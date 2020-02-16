#include "../dipHeader.h"


void determineMBVQ(char* result, int R, int G, int B) {
	if ((R + G) > 255) {
		if ((G + B) > 255) {
			if ((R + G + B) > 510) {
				strcpy(result, "CMYW");
			}
			else {
				strcpy(result, "MYGC");
			}
		}
		else {
			strcpy(result, "RGMY");
		}
	}
	else {
		if (!((G + B) > 255)) {
			if (!((R + G + B) > 255)) {
				strcpy(result, "KRGB");
			}
			else {
				strcpy(result, "RGBM");
			}
		}
		else {
			strcpy(result, "CMGB");
		}
	}



}


void determineVertex(char* vertex,char* MBVQ, double R, double G, double B) {
	if (strcmp(MBVQ, "CMYW") == 0) {
		strcpy(vertex, "white");
		if (B < 0.5 && B <= R && B <= G) {
			strcpy(vertex, "yellow");
		}
		else if (G < 0.5 && G <= B && G <= R) {
			strcpy(vertex, "magenta");
		}
		else if (R < 0.5 && R <= B && R <= G) {
			strcpy(vertex, "cyan");
		}
	}

	else if (strcmp(MBVQ, "MYGC") == 0) {
		strcpy(vertex, "magenta");
		if (R >= B && G >= B) {
			if (R >= 0.5) {
				strcpy(vertex, "yellow");
			}
			else {
				strcpy(vertex, "green");
			}
		}
		if (G >= R && B >= R) {
			if (B >= 0.5) {
				strcpy(vertex, "cyan");
			}
			else {
				strcpy(vertex, "green");
			}
		}
	}

	else if (strcmp(MBVQ, "RGMY") == 0) {
		if (B > 0.5) {
			if (R > 0.5) {
				if (B >= G) {
					strcpy(vertex, "magenta");
				}
				else {
					strcpy(vertex, "yellow");
				}
			}
			else {
				if (G > (B + R)) {
					strcpy(vertex, "green");
				}
				else {
					strcpy(vertex, "magenta");
				}
			}
		}
		else {
			if (R >= 0.5) {
				if (G >= 0.5) {
					strcpy(vertex, "yellow");
				}
				else {
					strcpy(vertex, "red");
				}
			}
			else {
				if (R >= G) {
					strcpy(vertex, "red");
				}
				else {
					strcpy(vertex, "green");
				}
			}
		}

	}

	else if (strcmp(MBVQ, "KRGB") == 0) {
		strcpy(vertex, "black");
		if (B > 0.5 && B >= R && B >= G) {
			strcpy(vertex, "blue");
		}
		else if (G > 0.5 && G >= B && G >= R) {
			strcpy(vertex, "green");
		}
		else if (R > 0.5 && R >= B && R >= G) {
			strcpy(vertex, "red");
		}
	}
	else if (strcmp(MBVQ, "RGBM") == 0) {
		strcpy(vertex, "green");
		if (R > G&& R >= B) {
			if (B < 0.5) {
				strcpy(vertex, "red");
			}
			else {
				strcpy(vertex, "magenta");
			}
		}
		if (B > G&& B >= R) {
			if (R < 0.5) {
				strcpy(vertex, "blue");
			}
			else {
				strcpy(vertex, "magenta");
			}
		}

	}
	else if (strcmp(MBVQ, "CMGB") == 0) {
		if (B > 0.5) {
			if (R > 0.5) {
				if (G >= R) {
					strcpy(vertex, "cyan");
				}
				else {
					strcpy(vertex, "magenta");
				}
			}
			else {
				if (G > 0.5) {
					strcpy(vertex, "cyan");
				}
				else {
					strcpy(vertex, "blue");
				}
			}
		}
		else {
			if (R > 0.5) {
				if ((R - G + B) >= 0.5) {
					strcpy(vertex, "magenta");
				}
				else {
					strcpy(vertex, "green");
				}
			}
			else {
				if (G >= B) {
					strcpy(vertex, "green");
				}
				else {
					strcpy(vertex, "blue");
				}
			}
		}

	}

}

void setVertexValue(unsigned char*** ImageData, char* vertex, int row, int col) {
	if (strcmp(vertex, "white") == 0) {
		ImageData[row][col][0] = 255;
		ImageData[row][col][1] = 255;
		ImageData[row][col][2] = 255;
	}
	else if (strcmp(vertex, "black") == 0) {
		ImageData[row][col][0] = 0;
		ImageData[row][col][1] = 0;
		ImageData[row][col][2] = 0;
	}
	else if (strcmp(vertex, "red") == 0) {
		ImageData[row][col][0] = 255;
		ImageData[row][col][1] = 0;
		ImageData[row][col][2] = 0;
	}
	else if (strcmp(vertex, "green") == 0) {
		ImageData[row][col][0] = 0;
		ImageData[row][col][1] = 255;
		ImageData[row][col][2] = 0;
	}
	else if (strcmp(vertex, "blue") == 0) {
		ImageData[row][col][0] = 0;
		ImageData[row][col][1] = 0;
		ImageData[row][col][2] = 255;
	}
	else if (strcmp(vertex, "magenta") == 0) {
		ImageData[row][col][0] = 255;
		ImageData[row][col][1] = 0;
		ImageData[row][col][2] = 255;
	}
	else if (strcmp(vertex, "cyan") == 0) {
		ImageData[row][col][0] = 0;
		ImageData[row][col][1] = 255;
		ImageData[row][col][2] = 255;
	}
	else if (strcmp(vertex, "yellow") == 0) {
		ImageData[row][col][0] = 255;
		ImageData[row][col][1] = 255;
		ImageData[row][col][2] = 0;
	}
	else {
	
	}

}


void convertRGBtoCMY(unsigned char*** OriginImageData,  int width, int height, int BytesPerPixel) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			for (int cor = 0; cor < BytesPerPixel; cor++) {
				double tmp = 0.0; 
				tmp = (1 - OriginImageData[row][col][cor] / 255.0) * 255; 
				OriginImageData[row][col][cor] = tmp; 
			}
		}
	}


}

void convertCMYtoRGB(unsigned char*** OriginImageData, int width, int height, int BytesPerPixel) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			for (int cor = 0; cor < BytesPerPixel; cor++) {
				double tmp = 0.0;
				tmp = (1 - OriginImageData[row][col][cor] / 255.0) * 255;
				OriginImageData[row][col][cor] = tmp;
			}
		}
	}
}
// useless function 
void makeErrorDiffusion(unsigned char*** OriginImageData, unsigned char*** HalftonedImageData, double** ErrorCoefficientMatrix, int row, int col, int cor,int EdgeSize, int WidSize) {
	int error = OriginImageData[row+EdgeSize][col+EdgeSize][cor] - HalftonedImageData[row][col][cor]; 
	for (int i = -WidSize / 2; i <= WidSize / 2; i++) {
		for (int j = -WidSize / 2; j <= WidSize / 2; j++) {
			OriginImageData[row + EdgeSize+i][col + EdgeSize+j][cor] += error * ErrorCoefficientMatrix[i + WidSize / 2][j + WidSize / 2]; 
		}

	}

}

void ColorErrorDiffusionJJN(unsigned char*** OriginImageData, unsigned char*** HalftonedImageData, int width, int height, int BytesPerPixel, int EdgeSize, int threshold) {
	double CoefficientMatrix[5][5] = { {0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,7.0,5.0},{3.0,5.0,7.0,5.0,3.0},{1.0,3.0,5.0,3.0,1.0} };
	double MirrorCoefficientMatrix[5][5] = { {0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0},{5.0,7.0,0.0,0.0,0.0},{3.0,5.0,7.0,5.0,3.0},{1.0,3.0,5.0,3.0,1.0} };
	//double** CoefficientMatrixPointer; 
	//CoefficientMatrixPointer = new double*[5]; 
	//for (int i = 0; i < 5; i++) {
	//	CoefficientMatrixPointer[i] = new double[5]; 
	//}
	//CoefficientMatrixPointer = CoefficientMatrix; 
	//int WidSize = 5;
	for (int row = 0; row < height; row++){
		if (row % 2 == 0) {
			for (int col = 0; col < width; col++) {
				for (int cor = 0; cor < BytesPerPixel; cor++) {
					if (OriginImageData[row+EdgeSize][col+EdgeSize][cor] > threshold) {
						HalftonedImageData[row][col][cor] = 255; 
					}
					else {
						HalftonedImageData[row][col][cor] = 0; 
					}
					//makeErrorDiffusion(OriginImageData, HalftonedImageData, CoefficientMatrixPointer, row, col, cor, EdgeSize, WidSize); 
					int error = OriginImageData[row + EdgeSize][col + EdgeSize][cor] - HalftonedImageData[row][col][cor];
					for (int i = -2; i <= 2; i++) {
						for (int j = -2; j <= 2; j++) {
							OriginImageData[row + EdgeSize + i][col + EdgeSize + j][cor] += error * CoefficientMatrix[i + 2][j + 2] / 48;
						}
					}
				}
			}
		}
		else {
			for (int col = width - 1; col >= 0; col--) {
				for (int cor = 0; cor < BytesPerPixel; cor++) {
					if (OriginImageData[row + EdgeSize][col + EdgeSize][cor] > threshold) {
						HalftonedImageData[row][col][cor] = 255;
					}
					else {
						HalftonedImageData[row][col][cor] = 0;
					}
					int error = OriginImageData[row + EdgeSize][col + EdgeSize][cor] - HalftonedImageData[row][col][cor];
					for (int i = -2; i <= 2; i++) {
						for (int j = -2; j <= 2; j++) {
							OriginImageData[row + EdgeSize + i][col + EdgeSize + j][cor] += error * MirrorCoefficientMatrix[i + 2][j + 2] / 48;
						}
					}
				}
			}
		}
	}
}


void ColorErrorDiffusionFloydSteinberg(unsigned char*** OriginImageData, unsigned char*** HalftonedImageData, int width, int height, int BytesPerPixel,int EdgeSize, int threshold) {
	double CoefficientMatrix[3][3] = { {0,0,0},{0,0,7.0},{3.0,5.0,1.0} };
	double MirrorCoefficientMatrix[3][3] = { {0,0,0},{7.0,0,0.0},{1.0,5.0,3.0} };
	for (int row = 0; row < height; row++) {
		if (row % 2 == 0) {
			for (int col = 0; col < width; col++) {
				for (int cor = 0; cor < BytesPerPixel; cor++) {
					if (OriginImageData[row + EdgeSize][col + EdgeSize][cor] > threshold) {
						HalftonedImageData[row][col][cor] = 255;
					}
					else {
						HalftonedImageData[row][col][cor] = 0;
					}
					int error = OriginImageData[row + EdgeSize][col + EdgeSize][cor] - HalftonedImageData[row][col][cor];
					for (int i = -1; i <= 1; i++) {
						for (int j = -1; j <= 1; j++) {
							OriginImageData[row + EdgeSize+i][col + EdgeSize+j][cor] += error * CoefficientMatrix[i + 1][j + 1] / 16;
						}
					}
				}
			}
		}
		else {
			for (int col = width - 1; col >= 0; col--) {
				for (int cor = 0; cor < BytesPerPixel; cor++) {
					if (OriginImageData[row + EdgeSize][col + EdgeSize][cor] > threshold) {
						HalftonedImageData[row][col][cor] = 255;
					}
					else {
						HalftonedImageData[row][col][cor] = 0;
					}
					int error = OriginImageData[row + EdgeSize][col + EdgeSize][cor] - HalftonedImageData[row][col][cor];
					for (int i = -1; i <= 1; i++) {
						for (int j = -1; j <= 1; j++) {
							OriginImageData[row + EdgeSize + i][col + EdgeSize + j][cor] += error * MirrorCoefficientMatrix[i + 1][j + 1] / 16;
						}
					}

				}

			}
		}
	}
}


void ColorErrorDiffusionStucki(unsigned char*** OriginImageData, unsigned char*** HalftonedImageData, int width, int height, int BytesPerPixel, int EdgeSize, int threshold) {
	double CoefficientMatrix[5][5] = { {0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,8.0,4.0},{2.0,4.0,8.0,4.0,2.0},{1.0,2.0,4.0,2.0,1.0} };
	double MirrorCoefficientMatrix[5][5] = { {0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0},{4.0,8.0,0.0,0.0,0.0},{2.0,4.0,8.0,4.0,2.0},{1.0,2.0,4.0,2.0,1.0} };

	for (int row = 0; row < height; row++) {
		if (row % 2 == 0) {
			for (int col = 0; col < width; col++) {
				for (int cor = 0; cor < BytesPerPixel; cor++) {
					if (OriginImageData[row + EdgeSize][col + EdgeSize][cor] > threshold) {
						HalftonedImageData[row][col][cor] = 255;
					}
					else {
						HalftonedImageData[row][col][cor] = 0;
					}
					int error = OriginImageData[row + EdgeSize][col + EdgeSize][cor] - HalftonedImageData[row][col][cor];
					for (int i = -2; i <= 2; i++) {
						for (int j = -2; j <= 2; j++) {
							OriginImageData[row + EdgeSize + i][col + EdgeSize + j][cor] += error * CoefficientMatrix[i + 2][j + 2] / 42;
						}
					}

				}
			}
		}
		else {
			for (int col = width - 1; col >= 0; col--) {
				for (int cor = 0; cor < BytesPerPixel; cor++) {
					if (OriginImageData[row + EdgeSize][col + EdgeSize][cor] > threshold) {
						HalftonedImageData[row][col][cor] = 255;
					}
					else {
						HalftonedImageData[row][col][cor] = 0;
					}
					int error = OriginImageData[row + EdgeSize][col + EdgeSize][cor] - HalftonedImageData[row][col][cor];

					for (int i = -2; i <= 2; i++) {
						for (int j = -2; j <= 2; j++) {
							OriginImageData[row + EdgeSize + i][col + EdgeSize + j][cor] += error * MirrorCoefficientMatrix[i + 2][j + 2] / 42;
						}
					}
				}
			}
		}
	}

}

void ColorErrorDiffusionFloydSteinbergMBVQ(unsigned char*** OriginImageData, unsigned char*** HalftonedImageData, int width, int height, int BytesPerPixel, int EdgeSize, int threshold) {
	double CoefficientMatrix[3][3] = { {0,0,0},{0,0,7.0},{3.0,5.0,1.0} };
	double MirrorCoefficientMatrix[3][3] = { {0,0,0},{7.0,0,0.0},{1.0,5.0,3.0} };
	for (int row = 0; row < height; row++) {
		if (row % 2 == 0) {
			for (int col = 0; col < width; col++) {
				int red = OriginImageData[row+EdgeSize][col+EdgeSize][0]; 
				int green = OriginImageData[row+EdgeSize][col+EdgeSize][1]; 
				int blue = OriginImageData[row+EdgeSize][col+EdgeSize][2];
				char* MBVQ = new char[30]; 

				determineMBVQ(MBVQ, red, green, blue); 

				double normalizedRed = OriginImageData[row+EdgeSize][col+EdgeSize][0] / 255.0;
				double normalizedGreen = OriginImageData[row+EdgeSize][col+EdgeSize][1] / 255.0;
				double normalizedBlue = OriginImageData[row+EdgeSize][col+EdgeSize][2] / 255.0; 

				char* vertex = new char[10]; 
				
				determineVertex(vertex, MBVQ, normalizedRed, normalizedGreen, normalizedBlue); 
				setVertexValue(HalftonedImageData, vertex, row, col); 
				
				//double* error = alloc1DArrayDouble(BytesPerPixel); 
				for (int cor = 0; cor < BytesPerPixel; cor++) {
					double error = OriginImageData[row + EdgeSize][col + EdgeSize][cor] - HalftonedImageData[row][col][cor]; 
					for (int i = -1; i <= 1; i++) {
						for (int j = -1; j <= 1; j++) {
							OriginImageData[row + EdgeSize+i][col + EdgeSize+j][cor] += error * CoefficientMatrix[i + 1][j + 1]/16; 
						}
					}
				}
				

			}
		}
		else {
			for (int col = width - 1; col >= 0; col--) {
				int red = OriginImageData[row + EdgeSize][col + EdgeSize][0];
				int green = OriginImageData[row + EdgeSize][col + EdgeSize][1];
				int blue = OriginImageData[row + EdgeSize][col + EdgeSize][2];
				char* MBVQ = new char[30];

				determineMBVQ(MBVQ, red, green, blue);

				double normalizedRed = OriginImageData[row + EdgeSize][col + EdgeSize][0] / 255.0;
				double normalizedGreen = OriginImageData[row + EdgeSize][col + EdgeSize][1] / 255.0;
				double normalizedBlue = OriginImageData[row + EdgeSize][col + EdgeSize][2] / 255.0;

				char* vertex = new char[30];

				determineVertex(vertex, MBVQ, normalizedRed, normalizedGreen, normalizedBlue);
				setVertexValue(HalftonedImageData, vertex, row, col);

				//double* error = alloc1DArrayDouble(BytesPerPixel);
				for (int cor = 0; cor < BytesPerPixel; cor++) {
					double error = OriginImageData[row + EdgeSize][col + EdgeSize][cor] - HalftonedImageData[row][col][cor];
					for (int i = -1; i <= 1; i++) {
						for (int j = -1; j <= 1; j++) {
							OriginImageData[row + EdgeSize+i][col + EdgeSize+j][cor] += error * MirrorCoefficientMatrix[i + 1][j + 1] / 16;
						}
					}
				}

			}
		}
	}
	

}

void ColorErrorDiffusionJJNMBVQ(unsigned char*** OriginImageData, unsigned char*** HalftonedImageData, int width, int height, int BytesPerPixel, int EdgeSize, int threshold) {
	double CoefficientMatrix[5][5] = { {0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,7.0,5.0},{3.0,5.0,7.0,5.0,3.0},{1.0,3.0,5.0,3.0,1.0} };
	double MirrorCoefficientMatrix[5][5] = { {0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0},{5.0,7.0,0.0,0.0,0.0},{3.0,5.0,7.0,5.0,3.0},{1.0,3.0,5.0,3.0,1.0} };
	for (int row = 0; row < height; row++) {
		if (row % 2 == 0) {
			for (int col = 0; col < width; col++) {
				int red = OriginImageData[row + EdgeSize][col + EdgeSize][0];
				int green = OriginImageData[row + EdgeSize][col + EdgeSize][1];
				int blue = OriginImageData[row + EdgeSize][col + EdgeSize][2];
				char* MBVQ = new char[30];

				determineMBVQ(MBVQ, red, green, blue);

				double normalizedRed = OriginImageData[row + EdgeSize][col + EdgeSize][0] / 255.0;
				double normalizedGreen = OriginImageData[row + EdgeSize][col + EdgeSize][1] / 255.0;
				double normalizedBlue = OriginImageData[row + EdgeSize][col + EdgeSize][2] / 255.0;

				char* vertex = new char[30];

				determineVertex(vertex, MBVQ, normalizedRed, normalizedGreen, normalizedBlue);
				setVertexValue(HalftonedImageData, vertex, row, col);

				double* error = alloc1DArrayDouble(BytesPerPixel);
				for (int cor = 0; cor < BytesPerPixel; cor++) {
					error[cor] = OriginImageData[row + EdgeSize][col + EdgeSize][cor] - HalftonedImageData[row][col][cor];
					for (int i = -2; i <= 2; i++) {
						for (int j = -2; j <= 2; j++) {
							OriginImageData[row + EdgeSize+i][col + EdgeSize+j][cor] += error[cor] * CoefficientMatrix[i + 2][j + 2] / 48;
						}
					}
				}


			}
		}
		else {
			for (int col = width - 1; col >= 0; col--) {
				int red = OriginImageData[row + EdgeSize][col + EdgeSize][0];
				int green = OriginImageData[row + EdgeSize][col + EdgeSize][1];
				int blue = OriginImageData[row + EdgeSize][col + EdgeSize][2];
				char* MBVQ = new char[30];

				determineMBVQ(MBVQ, red, green, blue);

				double normalizedRed = OriginImageData[row + EdgeSize][col + EdgeSize][0] / 255.0;
				double normalizedGreen = OriginImageData[row + EdgeSize][col + EdgeSize][1] / 255.0;
				double normalizedBlue = OriginImageData[row + EdgeSize][col + EdgeSize][2] / 255.0;

				char* vertex = new char[30];

				determineVertex(vertex, MBVQ, normalizedRed, normalizedGreen, normalizedBlue);
				setVertexValue(HalftonedImageData, vertex, row, col);

				double* error = alloc1DArrayDouble(BytesPerPixel);
				for (int cor = 0; cor < BytesPerPixel; cor++) {
					error[cor] = OriginImageData[row + EdgeSize][col + EdgeSize][cor] - HalftonedImageData[row][col][cor];
					for (int i = -2; i <= 2; i++) {
						for (int j = -2; j <= 2; j++) {
							OriginImageData[row + EdgeSize+i][col + EdgeSize+j][cor] += error[cor] * MirrorCoefficientMatrix[i + 2][j + 2] / 48;
						}
					}
				}

			}
		}
	}
}

void ColorErrorDiffusionStuckiMBVQ(unsigned char*** OriginImageData, unsigned char*** HalftonedImageData, int width, int height, int BytesPerPixel, int EdgeSize, int threshold) {
	double CoefficientMatrix[5][5] = { {0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,8.0,4.0},{2.0,4.0,8.0,4.0,2.0},{1.0,2.0,4.0,2.0,1.0} };
	double MirrorCoefficientMatrix[5][5] = { {0.0,0.0,0.0,0.0,0.0},{0.0,0.0,0.0,0.0,0.0},{4.0,8.0,0.0,0.0,0.0},{2.0,4.0,8.0,4.0,2.0},{1.0,2.0,4.0,2.0,1.0} };

	for (int row = 0; row < height; row++) {
		if (row % 2 == 0) {
			for (int col = 0; col < width; col++) {
				int red = OriginImageData[row + EdgeSize][col + EdgeSize][0];
				int green = OriginImageData[row + EdgeSize][col + EdgeSize][1];
				int blue = OriginImageData[row + EdgeSize][col + EdgeSize][2];
				char* MBVQ = new char[30];

				determineMBVQ(MBVQ, red, green, blue);

				double normalizedRed = OriginImageData[row + EdgeSize][col + EdgeSize][0] / 255.0;
				double normalizedGreen = OriginImageData[row + EdgeSize][col + EdgeSize][1] / 255.0;
				double normalizedBlue = OriginImageData[row + EdgeSize][col + EdgeSize][2] / 255.0;

				char* vertex = new char[30];

				determineVertex(vertex, MBVQ, normalizedRed, normalizedGreen, normalizedBlue);
				setVertexValue(HalftonedImageData, vertex, row, col);

				double* error = alloc1DArrayDouble(BytesPerPixel);
				for (int cor = 0; cor < BytesPerPixel; cor++) {
					error[cor] = OriginImageData[row + EdgeSize][col + EdgeSize][cor] - HalftonedImageData[row][col][cor];
					for (int i = -2; i <= 2; i++) {
						for (int j = -2; j <= 2; j++) {
							OriginImageData[row + EdgeSize+i][col + EdgeSize+j][cor] += error[cor] * CoefficientMatrix[i + 2][j + 2] / 42;
						}
					}
				}


			}
		}
		else {
			for (int col = width - 1; col >= 0; col--) {
				int red = OriginImageData[row + EdgeSize][col + EdgeSize][0];
				int green = OriginImageData[row + EdgeSize][col + EdgeSize][1];
				int blue = OriginImageData[row + EdgeSize][col + EdgeSize][2];
				char* MBVQ = new char[30];

				determineMBVQ(MBVQ, red, green, blue);
				//cout << MBVQ << endl;
				double normalizedRed = OriginImageData[row + EdgeSize][col + EdgeSize][0] / 255.0;
				double normalizedGreen = OriginImageData[row + EdgeSize][col + EdgeSize][1] / 255.0;
				double normalizedBlue = OriginImageData[row + EdgeSize][col + EdgeSize][2] / 255.0;

				char* vertex = new char[30];

				determineVertex(vertex, MBVQ, normalizedRed, normalizedGreen, normalizedBlue);
				//cout << vertex << endl;
				
				setVertexValue(HalftonedImageData, vertex, row, col);
			
				double* error = alloc1DArrayDouble(BytesPerPixel);
				for (int cor = 0; cor < BytesPerPixel; cor++) {
					error[cor] = OriginImageData[row + EdgeSize][col + EdgeSize][cor] - HalftonedImageData[row][col][cor];
					for (int i = -2; i <= 2; i++) {
						for (int j = -2; j <= 2; j++) {
							OriginImageData[row + EdgeSize+i][col + EdgeSize+j][cor] += error[cor] * MirrorCoefficientMatrix[i + 2][j + 2] / 42;
						}
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
	width = 640; 
	height = 480; 
	BytesPerPixel = 3; 
	int EdgeSize = 5; 
	int threshold = 128; 
	char originFilename[30] = "../Problem2/Rose.raw"; 
	unsigned char*** OriginImageData = alloc3DImage(width, height, BytesPerPixel); 
	read3DImageFile(originFilename, OriginImageData,width, height, BytesPerPixel); 
	unsigned char*** extendedImageData = alloc3DImage(width + 2 * EdgeSize, height + 2 * EdgeSize, BytesPerPixel); 


	unsigned char*** EFFSHalftonedImageData = alloc3DImage(width, height, BytesPerPixel); 
	extend3DImageEdge(OriginImageData, extendedImageData, width, height, BytesPerPixel,EdgeSize); 
	convertRGBtoCMY(extendedImageData, width + 2 * EdgeSize, height + 2 * EdgeSize, BytesPerPixel); 
	ColorErrorDiffusionFloydSteinberg(extendedImageData, EFFSHalftonedImageData, width, height, BytesPerPixel, EdgeSize, 140);
	convertRGBtoCMY(EFFSHalftonedImageData, width, height, BytesPerPixel);
	char ColorEFFloydSteinbergFilename[40] = "ColorErrorDiffusionFloydSteinberg.raw"; 
	write3DImageFile(ColorEFFloydSteinbergFilename, EFFSHalftonedImageData, width, height, BytesPerPixel); 

	unsigned char*** EFJJNHalftonedImageData = alloc3DImage(width, height, BytesPerPixel); 
	extend3DImageEdge(OriginImageData, extendedImageData, width, height, BytesPerPixel, EdgeSize);
	convertRGBtoCMY(extendedImageData, width + 2 * EdgeSize, height + 2 * EdgeSize, BytesPerPixel);
	ColorErrorDiffusionJJN(extendedImageData, EFJJNHalftonedImageData, width, height, BytesPerPixel, EdgeSize, 150); 
	convertRGBtoCMY(EFJJNHalftonedImageData, width, height, BytesPerPixel);
	char ColorEFJJNFilename[40] = "ColorErrorDiffusionJJN.raw"; 
	write3DImageFile(ColorEFJJNFilename, EFJJNHalftonedImageData, width, height, BytesPerPixel); 

	unsigned char*** EFStuckiHalftonedImageData = alloc3DImage(width, height, BytesPerPixel); 
	extend3DImageEdge(OriginImageData, extendedImageData, width, height, BytesPerPixel, EdgeSize);
	convertRGBtoCMY(extendedImageData, width + 2 * EdgeSize, height + 2 * EdgeSize, BytesPerPixel);
	ColorErrorDiffusionStucki(extendedImageData, EFStuckiHalftonedImageData, width, height, BytesPerPixel, EdgeSize,175); 
	convertRGBtoCMY(EFStuckiHalftonedImageData, width, height, BytesPerPixel); 
	char ColorEFStuckiFilename[40] = "ColorErrorDiffusionStucki.raw"; 
	write3DImageFile(ColorEFStuckiFilename, EFStuckiHalftonedImageData, width, height, BytesPerPixel); 


	unsigned char*** MBVQFSHalftonedImageData = alloc3DImage(width, height, BytesPerPixel);
	extend3DImageEdge(OriginImageData, extendedImageData, width, height, BytesPerPixel, EdgeSize);
	ColorErrorDiffusionFloydSteinbergMBVQ(extendedImageData, MBVQFSHalftonedImageData, width, height, BytesPerPixel, EdgeSize, 150);
	char MBVQEFFloydSteinbergFilename[40] = "MBVQErrorDiffusionFloydSteinberg.raw";
	write3DImageFile(MBVQEFFloydSteinbergFilename, MBVQFSHalftonedImageData, width, height, BytesPerPixel);

	unsigned char*** MBVQJJNHalftonedImageData = alloc3DImage(width, height, BytesPerPixel);
	extend3DImageEdge(OriginImageData, extendedImageData, width, height, BytesPerPixel, EdgeSize);
	ColorErrorDiffusionJJNMBVQ(extendedImageData, MBVQJJNHalftonedImageData, width, height, BytesPerPixel, EdgeSize, 130);
	char MBVQEFJJNFilename[40] = "MBVQErrorDiffusionJJN.raw";
	write3DImageFile(MBVQEFJJNFilename, MBVQJJNHalftonedImageData, width, height, BytesPerPixel);

	unsigned char*** MBVQStuckiHalftonedImageData = alloc3DImage(width, height, BytesPerPixel);
	extend3DImageEdge(OriginImageData, extendedImageData, width, height, BytesPerPixel, EdgeSize);
	ColorErrorDiffusionStuckiMBVQ(extendedImageData, MBVQStuckiHalftonedImageData, width, height, BytesPerPixel, EdgeSize,80 );
	char MBVQEFStuckiFilename[40] = "MBVQErrorDiffusionStucki.raw";
	write3DImageFile(MBVQEFStuckiFilename, MBVQStuckiHalftonedImageData, width, height, BytesPerPixel);

}
