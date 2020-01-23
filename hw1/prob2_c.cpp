#include"dipHeader.h"


void testGaussOutput() {
	double result1;
	const double pi = 3.1415926535897;
	result1 = (1 / (2 * sqrt(2 * pi))) * exp(-0.01);
	double exp2 = exp(0); 
	cout << result1 << endl;
	cout << exp2 << endl;
}






double GaussianKernel(int n1, int n2 , double stdev ) {
	double result;
	const double pi = 3.1415926535897;
	double sumsquare = pow(n1,2) + pow(n2,2); 
	result = (1 / ((sqrt(2 * pi)) * stdev)) * exp((-1) * (sumsquare/2/pow(stdev,2) )); 
	return result; 
}

double compEuclidianDistanceArea2Area(unsigned char** imageData, int row, int col, int i, int j, int widwidth, int widheight , double stdev) {
	const double pi = 3.1415926535897;
	double distance = 0;
	double sum = 0; 
	for (int k = -widheight/2; k <= widheight/2; k++) {
		for (int l = widwidth / 2; l <= widwidth / 2; l++) {
			sum += GaussianKernel(abs(k),abs(l),stdev)*pow(imageData[row + k][col + l] - imageData[i + k][j + l], 2);
		}
	}
	return sum;
}


double compEuclidianDistanceWeight(unsigned char** imageData, int row, int col, int i, int j, int widwidth, int widheight, double hparm , double stdev) {
	
	double result = 0 ;
	double distance = compEuclidianDistanceArea2Area(imageData, row, col, i, j, widwidth, widheight, stdev); 
	result = exp(- distance / pow(hparm, 2)); 
	return result; 
}



double computeNLMPixel(unsigned char** imageData,  int row, int col, int BytesPerPixel,int widsize,   int widwidth, int widheight ,double hparm, double stdev) {
	double totalweightedPixel = 0 ;
	double totalweight = 0 ; 
	double result = 0;
	for (int i = row-widsize/2; i <= row+widsize/2; i++) {
		for (int j = col-widsize/2; j <= col+widsize/2; j++) {
			totalweightedPixel += compEuclidianDistanceWeight( imageData,row,col,i,j,BytesPerPixel,widwidth,widheight, stdev)*imageData[i][j]; 
			totalweight += compEuclidianDistanceWeight(imageData,row,col,i,j,BytesPerPixel,widwidth,widheight, stdev) ; 
		}
	}
	result = totalweightedPixel / totalweight; 
	return result;
}

void NLM_filtering(unsigned char** imageData, unsigned char** filteredData, int width, int height, int BytesPerPixel,int edgesize ,int widsize , int widwidth, int widheight , double hparm , double stdev) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			filteredData[row][col] = computeNLMPixel(imageData, row + edgesize, col + edgesize, BytesPerPixel,widsize, widwidth, widheight , hparm ,stdev );
		}
	}
}

int main(int argc , char *argv[]) {
	FILE* file;
	int width;
	int height;
	int BytesPerPixel;
	int edgesize = 10;
	int widsize = 3;
	int widwidth = 5;
	int widheight = 5;
	double hparm = 10.0;
	double stdev = 10.0; 
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
		BytesPerPixel = atoi(argv[4]);
		// Check if width and height is specified
		if (argc >= 5) {
			width = atoi(argv[5]);
			height = atoi(argv[6]);
			widsize = atoi(argv[7]); 
			widwidth = widheight = atoi(argv[8]);  
			hparm = atoi(argv[9]); 
			stdev = atoi(argv[10]); 
		}
	}

	unsigned char** imageData; 
	unsigned char** filteredImageData; 
	unsigned char** extendedImageData;
	unsigned char** desiredImageData; 
	edgesize = widsize + widwidth + 10; 
	imageData = alloc2DImage(width, height, BytesPerPixel);
	desiredImageData = alloc2DImage(width, height, BytesPerPixel);
	extendedImageData = alloc2DImage(width + 2 * edgesize, height + 2 * edgesize, 1);
	filteredImageData = alloc2DImage(width, height, BytesPerPixel);
	read2DImageFile(argv[1], imageData, width, height, BytesPerPixel ); 
	read2DImageFile(argv[2], desiredImageData, width, height, BytesPerPixel);
	extend2DImageEdge(imageData, extendedImageData, width, height, BytesPerPixel, edgesize);
	NLM_filtering(extendedImageData, filteredImageData, width, height, BytesPerPixel,edgesize,  widsize, widwidth, widheight, hparm , stdev);
	write2DImageFile(argv[3], filteredImageData, width, height, BytesPerPixel); 
	double psnr = eval2DImagePSNR(desiredImageData, filteredImageData, width, height, BytesPerPixel);
	double psnrnoisy = eval2DImagePSNR(desiredImageData, imageData, width, height, BytesPerPixel);
	cout << "PSNR for original image and filtered image: " << psnr << endl;
	cout << "PSNR for original image and noisy image" << psnrnoisy << endl;
	return 0; 
}