file = fopen('vs/sumHistogramR.txt','r');
sumhistR = fread(file, 256, 'int');
file = fopen('vs/sumHistogramG.txt','r');
sumhistG = fread(file, 256, 'int');
file = fopen('vs/sumHistogramB.txt','r');
sumhistB = fread(file, 256, 'int');
x = 0:1:255; 
x = int32(x);
subplot(3,1,1)
plot(x,sumhistR,'-'); 
title('Red');
subplot(3,1,2)
plot(x,sumhistG,'-'); 
title('Green');
subplot(3,1,3)
plot(x,sumhistB,'-'); 
title('Blue');