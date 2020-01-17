#include"dipHeader.h"
#include<bitset>
unsigned char compBluePixelDelta(unsigned char **imageData, int row, int col ,int height , int width) {
	unsigned char result = '0';
	//cout << imageData[row + 2][col] << endl << imageData[row - 2][col] << endl;
	result = imageData[row][col] - 0.25 * (imageData[row - 2][col] + imageData[row + 2][col] + imageData[row][col + 2] + imageData[row][col - 2]); 
	
	return result; 
}

unsigned char compRedPixelDelta(unsigned char** imageData, int row, int col) {
	unsigned char result ='0';
	result = imageData[row][col] - 0.25 * (imageData[row - 2][col] + imageData[row + 2][col] + imageData[row][col + 2] + imageData[row][col - 2]); 
	return result; 

}


unsigned char compGreenPixelDelta(unsigned char** imageData, int row, int col) {
	unsigned char result = '0'; 
	result = imageData[row][col] - 0.25 * (imageData[row + 1][col-1] + imageData[row + 1][col+1] + imageData[row-1][col-1] + imageData[row-1][col+1]);
	return result; 
}

void MHC_Demosaicing(unsigned char **imageData,unsigned char ***imageRGBData, int width, int height) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			//Red
			if (judgePixelColor(row, col) == 0) {
				imageRGBData[row][col][0] = imageData[row][col];
				imageRGBData[row][col][1] = compGreenforRedBL(imageData,row,col)+0.5*compRedPixelDelta(imageData,row,col);
				imageRGBData[row][col][2] = compBlueforRedBL(imageData, row, col) + 0.5 * compRedPixelDelta(imageData, row, col); 
			}
			//Green
			if (judgePixelColor(row, col) == 1) {
				imageRGBData[row][col][0] = compRedForGreenBL(imageData, row, col) + 5 / 8 * compGreenPixelDelta(imageData, row, col);
				imageRGBData[row][col][1] = imageData[row][col]; 
				imageRGBData[row][col][2] = compBlueforGreenBL(imageData, row, col) + 5 / 8 * compGreenPixelDelta(imageData, row, col); 
			}
			//Blue
			if (judgePixelColor(row, col) == 2) {
				imageRGBData[row][col][0] = compRedforBlueBL(imageData, row, col) + 0.75 * compBluePixelDelta(imageData, row, col);
					imageRGBData[row][col][1] = compGreenforBlueBL(imageData, row, col) + 0.75 * compBluePixelDelta(imageData, row, col);
				imageRGBData[row][col][2] = imageData[row][col];
			}
		}
	
	}
}






int main() {

	   
}