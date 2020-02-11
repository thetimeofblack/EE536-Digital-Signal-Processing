Gallery_GT1 = load('Gallery_GT.mat'); 
Gallery_GT2 = load('Gallery_GT2.mat'); 
Gallery_GT5 = load('Gallery_GT5.mat'); 
subplot(3,1,1)
imshow(Gallery_GT1.groundTruth{1,1}.Boundaries)

subplot(3,1,2)
imshow(Gallery_GT2.groundTruth{1,1}.Boundaries)

subplot(3,1,3)
imshow(Gallery_GT5.groundTruth{1,1}.Boundaries)