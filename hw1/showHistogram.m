% show histogram
x_size = 400 ; 
y_size = 560; 
height = 560; 
width = 400 ; 
file = fopen('Toy_b.raw','r');
Image = fread(file, (x_size * y_size * 3), '*uint8');
redChannel = reshape(Image(1:3:end), [y_size, x_size]);
greenChannel = reshape(Image(2:3:end), [y_size, x_size]);
blueChannel = reshape(Image(3:3:end), [y_size, x_size]);
rgbImage = cat(3, redChannel, greenChannel, blueChannel);
;
% Requires R2019b or later
% Top plot
subplot(3,1,1)
histogram(redChannel,256); 
title('Red')
subplot(3,1,2)
histogram(blueChannel,256); 
title('Green')
subplot(3,1,3)
histogram(greenChannel,256); 
title('Blue')