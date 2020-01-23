G = readraw('../HW1_images/Corn_noisy.raw'); 
Y = readraw('../HW1_images/Corn_gray.raw')
x = im2double(G); 
[NA, y_est] = BM3D(Y, x, 100); 
final_result = y_est*255; 
writeraw(final_result,'Corn_bm3d.raw');




