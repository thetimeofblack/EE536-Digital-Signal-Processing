class Image
{
public:
	Image();
	~Image();
	void getImageData(unsigned char ** image2dData, unsigned char ***image3dData); 
	void setImageData(); 

private:
	unsigned char** image2dData; 
	unsigned char*** image3dData; 
	
};


