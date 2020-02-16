
%% main input filename Dogs_20_tuned.raw Gallery_20_tuned.raw
filename = 'Gallery_20_tuned.raw';
width = 481; 
height = 321;  
BytesPerPixel = 1; 
graph = read2DImage(filename,width,height,BytesPerPixel); 

graph = imread('Gallery_TunedManitude_20.jpg');


%% evaluate edge and ground truth mean  

prms1={ 'out','', 'thrs',1, 'maxDist',.0075, 'thin',1 } ; 
[thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg( graph, 'Gallery_GT5.mat', prms1 ); 
recall = cntR./sumR; 
precision = cntP./sumP;  
Fscore = 2*recall.*precision./(precision+recall);
precision 
recall
Fscore
imshow(graph)