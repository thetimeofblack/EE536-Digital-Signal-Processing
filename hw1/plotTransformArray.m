file = fopen('vs/transformArrayR.txt','r');
arrR = fread(file, 256, 'int');
file = fopen('vs/transformArrayG.txt','r');
arrG = fread(file, 256, 'int');
file = fopen('vs/transformArrayB.txt','r');
arrB = fread(file, 256, 'int');
x = 0:1:255; 
x = int32(x);
subplot(3,1,1)
plot(x,arrR,'-'); 
title('Red');
subplot(3,1,2)
plot(x,arrG,'-'); 
title('Green');
subplot(3,1,3)
plot(x,arrB,'-'); 
title('Blue');