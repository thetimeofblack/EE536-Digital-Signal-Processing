#include "..\dipHeader.h"


void FixedThresholdingHalftoning(unsigned char** OriginImageData, unsigned char** ObtainedImageData, int width, int height, int BytesPerPixel,int threshold) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int tmp = 0; 
			if (OriginImageData[row][col] < threshold) {
				ObtainedImageData[row][col] = 0; 
			}
			else {
				ObtainedImageData[row][col] = 255; 
			}
		}
	}
}




void RandomThresholdingHalftoning(unsigned char** OriginImageData, unsigned char** ObtainedImageData, int width, int height, int BytesPerPixel) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int tmpThreshold = rand()%256;
			if (OriginImageData[row][col] < tmpThreshold) {
				ObtainedImageData[row][col] = 0;
			}
			else {
				ObtainedImageData[row][col] = 255;
			}
		}
	}
}




void DitheringMatrixHalftoning(unsigned char** OriginImageData, unsigned char** ObtainedImageData, int width, int height, int BytesPerPixel, int MatrixSize) {
	int DitherMatrix2[2][2] = { 1, 2,3,0 };
	int DitherMatrix8[8][8] = { {21,37,25,41,22,38,26,42},{53,5,57,9,54,6,58,10},{29,45,17,33,30,46,18,34},{61,13,49,1,62,14,50,2},{23,39,27,43,20,36,24,40},{55,7,59,11,52,4,56,8},{31,47,19,35,28,44,16,32},{63,15,51,3,60,12,48,0} };
	int DitherMatrix32[32][32] = { {341,597,405,661,357,613,421,677,345,601,409,665,361,617,425,681,342,598,406,662,358,614,422,678,346,602,410,666,362,618,426,682},{853,85,917,149,869,101,933,165,857,89,921,153,873,105,937,169,854,86,918,150,870,102,934,166,858,90,922,154,874,106,938,170},{469,725,277,533,485,741,293,549,473,729,281,537,489,745,297,553,470,726,278,534,486,742,294,550,474,730,282,538,490,746,298,554},{981,213,789,21,997,229,805,37,985,217,793,25,1001,233,809,41,982,214,790,22,998,230,806,38,986,218,794,26,1002,234,810,42},{373,629,437,693,325,581,389,645,377,633,441,697,329,585,393,649,374,630,438,694,326,582,390,646,378,634,442,698,330,586,394,650},{885,117,949,181,837,69,901,133,889,121,953,185,841,73,905,137,886,118,950,182,838,70,902,134,890,122,954,186,842,74,906,138},{501,757,309,565,453,709,261,517,505,761,313,569,457,713,265,521,502,758,310,566,454,710,262,518,506,762,314,570,458,714,266,522},{1013,245,821,53,965,197,773,5,1017,249,825,57,969,201,777,9,1014,246,822,54,966,198,774,6,1018,250,826,58,970,202,778,10},{349,605,413,669,365,621,429,685,337,593,401,657,353,609,417,673,350,606,414,670,366,622,430,686,338,594,402,658,354,610,418,674},{861,93,925,157,877,109,941,173,849,81,913,145,865,97,929,161,862,94,926,158,878,110,942,174,850,82,914,146,866,98,930,162},{477,733,285,541,493,749,301,557,465,721,273,529,481,737,289,545,478,734,286,542,494,750,302,558,466,722,274,530,482,738,290,546},{989,221,797,29,1005,237,813,45,977,209,785,17,993,225,801,33,990,222,798,30,1006,238,814,46,978,210,786,18,994,226,802,34},{381,637,445,701,333,589,397,653,369,625,433,689,321,577,385,641,382,638,446,702,334,590,398,654,370,626,434,690,322,578,386,642},{893,125,957,189,845,77,909,141,881,113,945,177,833,65,897,129,894,126,958,190,846,78,910,142,882,114,946,178,834,66,898,130},{509,765,317,573,461,717,269,525,497,753,305,561,449,705,257,513,510,766,318,574,462,718,270,526,498,754,306,562,450,706,258,514},{1021,253,829,61,973,205,781,13,1009,241,817,49,961,193,769,1,1022,254,830,62,974,206,782,14,1010,242,818,50,962,194,770,2},{343,599,407,663,359,615,423,679,347,603,411,667,363,619,427,683,340,596,404,660,356,612,420,676,344,600,408,664,360,616,424,680},{855,87,919,151,871,103,935,167,859,91,923,155,875,107,939,171,852,84,916,148,868,100,932,164,856,88,920,152,872,104,936,168},{471,727,279,535,487,743,295,551,475,731,283,539,491,747,299,555,468,724,276,532,484,740,292,548,472,728,280,536,488,744,296,552},{983,215,791,23,999,231,807,39,987,219,795,27,1003,235,811,43,980,212,788,20,996,228,804,36,984,216,792,24,1000,232,808,40},{375,631,439,695,327,583,391,647,379,635,443,699,331,587,395,651,372,628,436,692,324,580,388,644,376,632,440,696,328,584,392,648},{887,119,951,183,839,71,903,135,891,123,955,187,843,75,907,139,884,116,948,180,836,68,900,132,888,120,952,184,840,72,904,136},{503,759,311,567,455,711,263,519,507,763,315,571,459,715,267,523,500,756,308,564,452,708,260,516,504,760,312,568,456,712,264,520},{1015,247,823,55,967,199,775,7,1019,251,827,59,971,203,779,11,1012,244,820,52,964,196,772,4,1016,248,824,56,968,200,776,8},{351,607,415,671,367,623,431,687,339,595,403,659,355,611,419,675,348,604,412,668,364,620,428,684,336,592,400,656,352,608,416,672},{863,95,927,159,879,111,943,175,851,83,915,147,867,99,931,163,860,92,924,156,876,108,940,172,848,80,912,144,864,96,928,160},{479,735,287,543,495,751,303,559,467,723,275,531,483,739,291,547,476,732,284,540,492,748,300,556,464,720,272,528,480,736,288,544},{991,223,799,31,1007,239,815,47,979,211,787,19,995,227,803,35,988,220,796,28,1004,236,812,44,976,208,784,16,992,224,800,32},{383,639,447,703,335,591,399,655,371,627,435,691,323,579,387,643,380,636,444,700,332,588,396,652,368,624,432,688,320,576,384,640},{895,127,959,191,847,79,911,143,883,115,947,179,835,67,899,131,892,124,956,188,844,76,908,140,880,112,944,176,832,64,896,128},{511,767,319,575,463,719,271,527,499,755,307,563,451,707,259,515,508,764,316,572,460,716,268,524,496,752,304,560,448,704,256,512},{1023,255,831,63,975,207,783,15,1011,243,819,51,963,195,771,3,1020,252,828,60,972,204,780,12,1008,240,816,48,960,192,768,0} };
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int indexi = row % MatrixSize; 
			int indexj = col % MatrixSize; 
			double threshold = 0.0; 
			if (MatrixSize == 2) {
					threshold = (DitherMatrix2[indexi][indexj] + 0.5) / pow(MatrixSize,2) * 255;
			}
			else if (MatrixSize == 8) {
					threshold = (DitherMatrix8[indexi][indexj] + 0.5) / pow(MatrixSize, 2) * 255;
			}
			else if (MatrixSize == 32) {
					threshold = (DitherMatrix32[indexi][indexj] + 0.5) / pow(MatrixSize, 2) * 255;
			}
			else {
				
			}

			if (OriginImageData[row][col] < threshold) {
				ObtainedImageData[row][col] = 0; 
			}
			else {
				ObtainedImageData[row][col] = 255; 
			}
		}
	}
	

}



// if time is available, maybe I can try to solve the problem 
// dynamic allocate 2d array and iteratively use the algorithm to construct matrix 
int compThresholdForDithering( int row, int col, int MatrixSize) {
	int n = MatrixSize / 2; 
	int DitherMatrix2[2][2] = {1,2,3,0 };
	if (n == 1) {
		int result; 
		result = (DitherMatrix2[row % MatrixSize][col % MatrixSize] + 0.5) * 255 / pow(MatrixSize, 2); 
		return result; 
	}
	
	int** DitherIndexMatrix = new int* [MatrixSize];
	for (int i = 0; i < MatrixSize; i++) {
		DitherIndexMatrix[i] = new int[MatrixSize]; 
	}

	for (int k = 1; k <= MatrixSize/2; k++) {
		
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
	unsigned char** OriginImageData = alloc2DImage(width, height, BytesPerPixel); 
	read2DImageFile(argv[1], OriginImageData, width, height, BytesPerPixel); 

	unsigned char** DitheringHalftonedImageData = alloc2DImage(width, height, BytesPerPixel);
	DitheringMatrixHalftoning(OriginImageData, DitheringHalftonedImageData, width, height, BytesPerPixel, 128); 
	write2DImageFile(argv[2], DitheringHalftonedImageData, width, height, BytesPerPixel);

	unsigned char** FixedThresholdHalftonedImageData = alloc2DImage(width, height, BytesPerPixel);
	FixedThresholdingHalftoning(OriginImageData, FixedThresholdHalftonedImageData, width, height, BytesPerPixel,150);
	char FixedThresholdHalftoningfilename[30] = "HalfToned_FixedThreshold.raw";
	write2DImageFile(FixedThresholdHalftoningfilename, FixedThresholdHalftonedImageData, width, height, BytesPerPixel);
	
	unsigned char** RandomThresholdHalftonedImageData = alloc2DImage(width, height, BytesPerPixel);
	FixedThresholdingHalftoning(OriginImageData, RandomThresholdHalftonedImageData, width, height, BytesPerPixel,128);
	char RandomThresholdHalftoningfilename[30] = "HalfToned_RandomThreshold.raw";
	write2DImageFile(RandomThresholdHalftoningfilename, RandomThresholdHalftonedImageData, width, height, BytesPerPixel);


}