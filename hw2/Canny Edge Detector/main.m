ImageDataGalleries = imread('../Problem1/Gallery.jpg');
ImageDataDogs = imread('../Problem1/Dogs.jpg');
ImageDataGalleriesGray = rgb2gray(ImageDataGalleries);
ImageDataDogsGray=rgb2gray(ImageDataDogs);
%subplot(2,2,1);
%imshow(ImageDataGalleriesGray);
GalleryEdge1 = edge(ImageDataGalleriesGray,'canny',[0.01 0.1]); 
%subplot(2,2,2);
%imshow(GalleryEdge1);
GalleryEdge2 = edge(ImageDataGalleriesGray,'canny',[0.09 0.1]); 
%subplot(2,2,3);
%imshow(GalleryEdge2);
GalleryEdge3 = edge(ImageDataGalleriesGray,'canny',[0.09 0.2]); 
%subplot(2,2,4);
%imshow(GalleryEdge3);

GalleryEdge4 =  edge(ImageDataGalleriesGray,'canny',[0.05 0.4]); 
imwrite(GalleryEdge4,'Gallery_0.1_0.4.jpg'); 

DogsEdge1 = edge(ImageDataDogsGray,'canny',[0.1 0.3]);
imwrite(DogsEdge1,'Dogs_0.1_0.3.jpg'); 
imshow(DogsEdge1)
%prms1={ 'out','', 'thrs',1, 'maxDist',.0075, 'thin',1 } ; 
%[thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg( GalleryEdge, 'Dogs_GT1.mat', prms1 )
%recall = cntR./sumR
%precision = cntP./sumP 
%Fscore = 2*recall.*precision./(precision+recall);

