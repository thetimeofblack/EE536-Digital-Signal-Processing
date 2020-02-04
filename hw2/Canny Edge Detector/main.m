ImageDataGalleries = imread('../Problem1/Gallery.jpg')
ImageDataDog = imread('../Problem1/Dogs.jpg')
ImageDataGalleriesGray = rgb2gray(ImageDataGalleries)
GalleryEdge = edge(ImageDataGalleriesGray,'canny') 
figure; 
imshow(GalleryEdge)
