#include "../dipHeader.h"

long int compEdgeTruePositive(unsigned char** ImageGroundTruthData, unsigned char** ImageEdgeData , int width ,int height, int BytesPerPixel) {
	long int countIdentifiedEdgePixels = 0; 
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (ImageEdgeData[row][col] == 255 && ImageGroundTruthData[row][col]==ImageEdgeData[row][col]) {
				countIdentifiedEdgePixels += 1;
			}
		}
	}
	return countIdentifiedEdgePixels;
}

int main(int argc , char* argv[]) {

}