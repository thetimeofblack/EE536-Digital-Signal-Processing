 #include "../dipHeader.h"

long int getPatternNumber(unsigned char** ImageData, int row, int col) {
	int result = 0 ;
	int index = 8; 
	int X_0 = (ImageData[row][col + 1] / 255); 
	int X_1 = (ImageData[row - 1][col + 1] / 255); 
	int X_2 = (ImageData[row - 1][col] / 255); 
	int X_3 = (ImageData[row - 1][col-1] / 255);
	int X_4 = ImageData[row ][col - 1] / 255;
	int X_5 = ImageData[row+1][col - 1] / 255;
	int X_6 = ImageData[row + 1][col] / 255;
	int X_7 = ImageData[row + 1][col+1] / 255;
	int compare =  X_0<<7 | X_1<<6 | X_2<<5 | X_3<<4 | X_4<<3 | X_5<<2 | X_6<<1 |X_7;
	
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			int value = ImageData[row + i][col + j]/255; 
			int tmp = 0; 
			if (value == 1) {
				tmp = 1 << index; 
			}
			else {
				
			}
			result = result | tmp;
			index--; 
		}
	}
	return compare;
}

bool checkImageDataModification(unsigned char** OriginImageData, unsigned char** ModifiedImageData, int width, int height, int BytesPerPixel) {
	bool flag = false; 
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (OriginImageData[row][col] != ModifiedImageData[row][col]) {
				flag = true; 
				break; 
			}
		}
	}
	return flag; 
}


bool thinImageDataIteration(unsigned char** OriginImageData, unsigned char** thinnedImageData, int width, int height, int BytesPerPixel, int itr) {
	unsigned char ** MaskImageData = alloc2DImage(width, height, BytesPerPixel); 
	bool isChanged = false; 

	int conditionalTable[46]={0b10100000,0b101000,0b1010,0b10000010,
							  0b11000001,0b1110000,0b11100,0b111,
							  0b10110000,0b10100001,0b1101000,0b11000010,
							  0b11100000,0b111000,  0b1110,0b10000011,
							  0b10110001,0b1101100,
							  0b11110000,0b11100001,0b1111000,0b111100,0b11110,0b1111,0b10000111,0b11000011,
							  0b11110001,0b1111100,0b11111,0b11000111,
							  0b11100011,0b11111000,0b111110,0b10001111,
							  0b11110011,0b11100111,0b11111100,0b11111001,0b1111110,0b111111,0b10011111,0b11001111,
							  0b11110111,0b11111101,0b1111111,0b11011111 };
	
	
	int unconditionalTable[364] = { 
		0b1000000,0b10000,0b10,0b10000000,
		0b11000000,0b1100000,0b110000,0b11000,0b1100,0b110,0b11,0b10000001,
		0b1101000,0b10110000,0b10100001,0b11000010,
		0b11000100,0b1100100,0b11100100,0b110001,0b11001,
		0b111001,0b1000110,0b1001100,0b1001110,0b10010001,0b10011,0b10010011,0b111000,
		0b111001,0b10111000,0b10111001,0b1111000,0b1111001,0b11111000,0b11111001,0b111010,0b111011,0b10111010,
		0b10111011,0b1111010,0b1111011,0b11111010,0b11111011,0b111100,0b111101,0b10111100,0b10111101,0b1111100,
		0b1111101,0b11111100,0b11111101,0b111110,0b111111,0b10111110,
		0b10111111,0b1111110,0b1111111,0b11111110,0b11111111,
		0b101010,0b1101010,0b111010,0b1111010,0b101010,0b101011,0b101110,0b101111,0b10100010,0b10100011,0b10100110,0b10100111,
		0b10100010,0b11100010,0b10110010,0b11110010,
		0b10101000,0b10101100,0b10111000,0b10111100,0b10101000,0b10101001,
		0b11101000,0b11101001,0b10001010,0b10001011,0b11001010,
		0b11001011,0b10001010,0b10001110,0b10011010,
		0b10011110,0b10101,0b10010100,0b10010101,0b1010100,
		0b1010101,0b11010100,0b11010101,0b10111,0b10010110,
		0b10010111,0b1010110,0b1010111,0b11010110,0b11010111,
		0b110101,0b10110100,0b10110101,0b1110100,
		0b1110101,0b11110100,0b11110101,0b110111,
		0b10110110,0b10110111,0b1110110,0b1110111,0b11110110,0b11110111,
		0b11101,0b10011100,0b10011101,0b1011100,0b1011101,0b11011100,0b11011101,
		0b11111,0b10011110,0b10011111,
		0b1011110,0b1011111,0b11011110,0b11011111,0b111101,0b10111100,0b10111101,0b1111100,0b1111101,
		0b11111100,0b11111101,0b111111,0b10111110,0b10111111,0b1111110,0b1111111,0b11111110,0b11111111,
		0b1010100,0b1010010,0b1010110,0b1010001,0b1010101,
		0b1010011,0b1010111,0b11010100,0b11010010,0b11010110,
		0b11010001,0b11010101,0b11010011,0b11010111,
		0b1110100,0b1110010,0b1110110,0b1110001,0b1110101,
		0b1110011,0b1110111,0b11110100,0b11110010,0b11110110,
		0b11110001,0b11110101,0b11110011,0b11110111,0b1011100,
		0b1011010,0b1011110,0b1011001,0b1011101,0b1011011,0b1011111,0b11011100,0b11011010,0b11011110,
		0b11011001,0b11011101,0b11011011,0b11011111,0b1111100,
		0b1111010,0b1111110,0b1111001,0b1111101,0b1111011,
		0b1111111,0b11111100,0b11111010,0b11111110,0b11111001,0b11111101,0b11111011,0b11111111,0b1000101,
		0b1001001,0b1001101,0b1010001,0b1010101,0b1011001,
		0b1011101,0b11000101,0b11001001,0b11001101,0b11010001,0b11010101,
		0b11011001,0b11011101,0b1000111,0b1001011,0b1001111,
		0b1010011,0b1010111,0b1011011,0b1011111,0b11000111,0b11001011,
		0b11001111,0b11010011,0b11010111,0b11011011,0b11011111,
		0b1100101,0b1101001,0b1101101,0b1110001,0b1110101,0b1111001,
		0b1111101,0b11100101,0b11101001,0b11101101,0b11110001,0b11110101,
		0b11111001,0b11111101,0b1100111,0b1101011,0b1101111,
		0b1110011,0b1110111,0b1111011,0b1111111,0b11100111,
		0b11101011,0b11101111,0b11110011,0b11110111,0b11111011,0b11111111,
		0b1000101,0b100101,0b1100101,0b10101,0b1010101,
		0b110101,0b1110101,0b11000101,0b10100101,0b11100101,0b10010101,
		0b11010101,0b10110101,0b11110101,0b1000111,0b100111,0b1100111,0b10111,0b1010111,
		0b110111,0b1110111,0b11000111,
		0b10100111,0b11100111,0b10010111,0b11010111,0b10110111,0b11110111,0b1001101,0b101101,0b1101101,0b11101,0b1011101,
		0b111101,0b1111101,0b11001101,0b10101101,0b11101101,
		0b10011101,0b11011101,0b10111101,0b11111101,0b1001111,0b101111,
		0b1101111,0b11111,0b1011111,0b111111,0b1111111,0b11001111,
		0b10101111,0b11101111,0b10011111,0b11011111,0b10111111,
		0b11111111,0b1001010,0b1001011,0b1011010,0b1011011,
		0b101001,0b1101001,0b101101,0b1101101,0b10100100,0b10100101,
		0b10110100,0b10110101,0b10010010,0b11010010,0b10010110,
		0b11010110,0b111000,0b111001,0b10111000,0b10111001,0b1111000,
		0b1111001,0b11111000,0b11111001,0b111010,0b111011,0b10111010,0b10111011,
		0b1111010,0b1111011,0b11111010,0b11111011,0b111100,0b111101,0b10111100,0b10111101,0b1111100,
		0b1111101,0b11111100,0b11111101,0b111110,0b111111,0b10111110,0b10111111,0b1111110,0b1111111,
		0b11111110,0b11111111};


	for (int row = 1; row < height-1; row++) {
		for (int col = 1; col < width-1; col++) {
			int PatternNumber = getPatternNumber(OriginImageData, row, col);
			// if hit change MaskImageData to 1
			//cout << PatternNumber;
			bool ishit = false; 
			MaskImageData[row][col] = 0; 
			for (int conitr = 0; conitr < 46; conitr++) {
				//hit 
				//cout << "hit" << endl;
				//cout << bitset<32>(PatternNumber) << "  " << bitset<32>(conditionalTable[conitr]) << endl; 
				if (OriginImageData[row][col] && !(PatternNumber ^ conditionalTable[conitr])) {
					MaskImageData[row][col] = (OriginImageData[row][col] & !(PatternNumber ^ conditionalTable[conitr])) * 255;
				}
				
					//cout << "Mask Data" << (int)MaskImageData[row][col] << endl;
				
				
			}

		}
	}

	string filenameMask = "maskData"+to_string(itr)+".raw"; 
	char fileNameMask[30] = ""; 
	std::strcpy(fileNameMask, filenameMask.c_str());
	write2DImageFile(fileNameMask,MaskImageData, width, height, BytesPerPixel);
	

	for (int row = 1; row < height-1; row++) {
		for (int col = 1; col < width-1; col++) {
			int PatternNumber = getPatternNumber(MaskImageData, row, col); 
			// if miss      
			int MaskValue = MaskImageData[row][col];
			//cout << MaskValue << endl;
			int MaskValueBinary = MaskValue / 255; 
			int OriginBinaryValue = OriginImageData[row][col] / 255; 
			bool isMiss = false;
			for (int unconitr = 0; unconitr < 364; unconitr++) {
			//cout << bitset<32>(PatternNumber) << "  " << bitset<32>(unconditionalTable[unconitr]) << endl;
				

			if (MaskImageData[row][col] && !(PatternNumber ^ unconditionalTable[unconitr])) {
				//cout << bitset<32>(PatternNumber) << "  " << bitset<32>(unconditionalTable[unconitr]) << endl;
				isMiss = true;
				break;

			}
			//cout << (OriginImageData[row][col] & (!MaskValueBinary | isMiss)) << endl;
				
			}
			
			thinnedImageData[row][col] = (OriginImageData[row][col] && (!MaskImageData[row][col]||isMiss)) * 255;
			if (thinnedImageData[row][col] != OriginImageData[row][col]) {
					isChanged = true;
			}
		
		}
	}
	
	string  filename = ""; 
	filename = "thinning_test" + to_string(itr)+".raw";
	char Filename[40]=""; 
	std::strcpy(Filename, filename.c_str()); 
	write2DImageFile(Filename, thinnedImageData, width, height, BytesPerPixel); 
	return isChanged; 
}

void copy2DImageData(unsigned char** OriginImageData, unsigned char** CopiedImageData, int width, int height, int BytesPerPixel) {
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			CopiedImageData[row][col] = OriginImageData[row][col]; 
		}
	}
}


void thinImageData(unsigned char** OriginImageData, unsigned char** thinnedImageData, int width ,int height, int BytesPerPixel ,int edgesize ) {
	unsigned char** preImageData;
	preImageData = alloc2DImage(width, height, BytesPerPixel); 
	copy2DImageData(OriginImageData, preImageData, width, height, BytesPerPixel); 
	bool flag = true; 
	int itr = 0; 
	while (flag) {
		itr++; 
		bool isChanged = true;
		isChanged = thinImageDataIteration(preImageData, thinnedImageData, width, height, BytesPerPixel,itr); 
		if (isChanged == false) {
			break; 
		}
		copy2DImageData(thinnedImageData, preImageData, width, height, BytesPerPixel);
	}
}



void skeletonizeImageData(unsigned char** OriginImageData, unsigned char** skeletonizedImageData, int width, int height, int BytesPerPixel) {

}




void shrinkImageData(unsigned char** OriginImageData, unsigned char** shrinkedImageData, int width, int height, int BytesPerPixel) {

}




void testBinaryOperation() {
	int bit8 = 2 << 29;
	int bit32 = 2 | 4 | 8;
	int binary4 = 0b10110;
	int binary8 = 0b10110;
	if (1 << 29) cout << "hello world sdfdfsd";
	bitset<64> x(bit8);
	cout << x << '\n';
	cout << bit8 << endl;
	cout << bitset<8>(bit32) << endl;
	cout << (binary4 & binary8) << endl;
	cout << (0 << 10);
	cout << bitset<32>(0b010 ^ 0b101) << endl;
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
	testBinaryOperation(); 
	char fanFileName[30] = "../data/fan.raw"; 
	char cupFileName[30] = "../data/cup.raw";
	char mazeFileName[30] = "../data/maze.raw";


	int fanwidth = 558;
	int fanheight = 558;
	BytesPerPixel = 1;

	int cupwidth = 315; 
	int cupheight = 356; 

	int mazewidth = 558; 
	int mazeheight = 558; 

	unsigned char** fanImageData = alloc2DImage(fanwidth, fanheight, BytesPerPixel);
	read2DImageFile(fanFileName, fanImageData, fanwidth, fanheight, BytesPerPixel);
	unsigned char** fanOutputImageData = alloc2DImage(fanwidth, fanheight, BytesPerPixel); 
	thinImageData(fanImageData, fanOutputImageData, fanwidth, fanheight, BytesPerPixel, 1);
	char FanOutputFilename[30] = "fan_thinned.raw"; 
	write2DImageFile(FanOutputFilename,fanOutputImageData, fanwidth, fanheight, BytesPerPixel); 

	unsigned char** cupImageData = alloc2DImage(cupwidth, cupheight, BytesPerPixel);
	read2DImageFile(cupFileName, cupImageData, cupwidth, cupheight, BytesPerPixel);
	unsigned char** cupOutputImageData = alloc2DImage(cupwidth, cupheight, BytesPerPixel);
	thinImageData(cupImageData, cupOutputImageData, cupwidth, cupheight, BytesPerPixel, 1);
	char CupOutputFilename[30] = "cup_thinned.raw";
	write2DImageFile(CupOutputFilename, cupOutputImageData, cupwidth, cupheight, BytesPerPixel);


	

}