% groundTruth data seperation 
Dog_GT = load('../Problem1/Dogs_GT.mat');
Dog_GT_Filename = '../Problem1/Dogs_GT.mat'; 
Dog_GT1 = struct() ; 
Dog_GT1.groundTruth{1,1}.Boundaries= Dog_GT.groundTruth{1,1}.Boundaries ; 
save('Dog_GT1.mat', '-struct', 'Dog_GT1'); 
Dog_GT1 = struct() ; 
Dog_GT1.groundTruth{1,1}.Boundaries= Dog_GT.groundTruth{1,1}.Boundaries ; 
save('Dog_GT1.mat', '-struct', 'Dog_GT1'); 