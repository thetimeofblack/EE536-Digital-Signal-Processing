function [histogram] = im_histogram(input_img,channel)

% for each pixel in the input image 
% compute the count array for the pixelvalue 0- 255 
height = size(input_img, 1) ;
width = size(input_img,2); 
% initialize the array for histogram
histogram = zeros(256,1); 
for row = 1:height 
    for col=1:width 
        histogram(inpute_img(row,col,channel)+1)= ...
            histogram(input_img(row,col,channel)+1) +1 ;
    end
end


end 

