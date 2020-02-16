%% main input filename Dogs_20_tuned.raw Gallery_20_tuned.raw
filename = 'Gallery_0.09_0.2.jpg';
width = 481; 
height = 321; 
BytesPerPixel = 1; 
graph = imread('../Problem1/Gallery.jpg');
CannyGrayGraph = rgb2gray(graph); 
CannyEdgeDetector = edge(CannyGrayGraph,'canny',[0.09 0.2], 3); 


%% evaluate edge and ground truth mean  
imshow(1-CannyEdgeDetector)
imwrite(1-CannyEdgeDetector,'Gallery_Canny_tuned.jpg'); 
prms1={ 'out','', 'thrs',1, 'maxDist',.0075, 'thin',1 } ; 
[thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg( CannyEdgeDetector, 'Gallery_GT5.mat', prms1 ); 
recall = cntR./sumR; 
precision = cntP./sumP;  
Fscore = 2*recall.*precision./(precision+recall); 
Fscore
recall 
precision
