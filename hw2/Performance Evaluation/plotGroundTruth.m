addpath('../');
load('../Problem1/Dogs_GT.mat');
im1 = groundTruth{1,5}.Boundaries;
imshow(im1);
imforsave = im1 *255 ;
writeraw(imforsave, 'Dogs_Boundaries_5.raw')