addEdgePath()
ImageDataGalleries = imread('../Problem1/Gallery.jpg')
ImageDataDog = imread('../Problem1/Dogs.jpg')
ImageDataGalleriesGray = rgb2gray(ImageDataGalleries)
GalleryEdge = edge(ImageDataGalleriesGray,'canny',[0.2 0.6]) 
figure; 
imshow(GalleryEdge)

prms1={ 'out','', 'thrs',2, 'maxDist',.0075, 'thin',1 } ; 
[thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg( GalleryEdge, 'Dogs_GT1.mat', prms1 )
recall = cntR./sumR
precision = cntP./sumP 
Fscore = 2*recall.*precision./(precision+recall);

