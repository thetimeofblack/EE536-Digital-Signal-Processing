function [ thrs fscore] = compFscore(E,groundtruthpath)
prms1={ 'out','', 'thrs',40, 'maxDist',.0075, 'thin',1 } ; 
[thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg( E, 'Gallery_GT.mat', prms1 ); 
recall = cntR./sumR; 
precision = cntP./sumP;  
fscore = 2*recall.*precision./(precision+recall); 

end
