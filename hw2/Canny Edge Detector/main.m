addEdgePath()
ImageDataGalleries = imread('../Problem1/Gallery.jpg')
ImageDataDog = imread('../Problem1/Dogs.jpg')
ImageDataGalleriesGray = rgb2gray(ImageDataGalleries)
GalleryEdge = edge(ImageDataGalleriesGray,'canny',[0.2 0.6]) 
figure; 
imshow(GalleryEdge)
