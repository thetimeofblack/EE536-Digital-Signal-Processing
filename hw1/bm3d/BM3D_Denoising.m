G = readraw('../HW1_images/Corn_noisy.raw'); 
Y = readraw('../HW1_images/Corn_gray.raw');
x = im2double(G); 
y = im2double(Y); 
[psnr, y_est] = BM3D(y, x, 40,1); 
final_result = y_est*255; 
writeraw(final_result,'Corn_bm3d.raw');




