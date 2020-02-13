% groundTruth data seperation 
Dog_GT_Filename = '../Problem1/Dogs_GT.mat'; 
Dog_GT = load(Dog_GT_Filename);

Gallery_GT_Filename = '../Problem1/Gallery_GT.mat'; 
Gallery_GT = load(Gallery_GT_Filename) ; 

%% seperate Dog groundTruth data 

        

Dog_GT1 = struct() ; 
Dog_GT1.groundTruth{1,1}.Boundaries= Dog_GT.groundTruth{1,1}.Boundaries ; 
save('Dogs_GT1.mat', '-struct', 'Dog_GT1'); 

Dog_GT2 = struct() ; 
Dog_GT2.groundTruth{1,1}.Boundaries= Dog_GT.groundTruth{1,2}.Boundaries ; 
save('Dogs_GT2.mat', '-struct', 'Dog_GT2'); 

Dog_GT3 = struct() ; 
Dog_GT3.groundTruth{1,1}.Boundaries= Dog_GT.groundTruth{1,3}.Boundaries ; 
save('Dogs_GT3.mat', '-struct', 'Dog_GT2'); 

Dog_GT4 = struct() ; 
Dog_GT4.groundTruth{1,1}.Boundaries= Dog_GT.groundTruth{1,4}.Boundaries ; 
save('Dogs_GT4.mat', '-struct', 'Dog_GT2'); 
%imshow(Dog_GT4.groundTruth{1,1}.Boundaries)
Dog_GT5 = struct() ; 
Dog_GT5.groundTruth{1,1}.Boundaries= Dog_GT.groundTruth{1,5}.Boundaries ; 
save('Dogs_GT5.mat', '-struct', 'Dog_GT2'); 


Gallery_GT1 = struct() ; 
Gallery_GT1.groundTruth{1,1}.Boundaries= Gallery_GT.groundTruth{1,1}.Boundaries ; 
save('Gallery_GT1.mat', '-struct', 'Gallery_GT1'); 

Gallery_GT2 = struct() ; 
Gallery_GT2.groundTruth{1,1}.Boundaries= Gallery_GT.groundTruth{1,2}.Boundaries ; 
save('Gallery_GT2.mat', '-struct', 'Gallery_GT2'); 

Gallery_GT3 = struct() ; 
Gallery_GT3.groundTruth{1,1}.Boundaries= Gallery_GT.groundTruth{1,3}.Boundaries ; 
save('Gallery_GT3.mat', '-struct', 'Gallery_GT3'); 


Gallery_GT4 = struct() ; 
Gallery_GT4.groundTruth{1,1}.Boundaries= Gallery_GT.groundTruth{1,4}.Boundaries ; 
save('Gallery_GT4.mat', '-struct', 'Gallery_GT4'); 


Gallery_GT5 = struct() ; 
Gallery_GT5.groundTruth{1,1}.Boundaries= Gallery_GT.groundTruth{1,5}.Boundaries ; 
save('Gallery_GT5.mat', '-struct', 'Gallery_GT5'); 

