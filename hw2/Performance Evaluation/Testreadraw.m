%readraw('../Problem1/Dogs.raw',481,321)
filename = 'Gallery1.raw'; 
fid = fopen(filename, 'rb'); 


if (fid == -1)
	  	error('can not open input image file press CTRL-C to exit \n');
	  	pause
	end
pixels = fread(fid, inf, 'uchar');
fclose(fid);

width = 481; 
height = 321; 
graph = zeros(height,width);

for row = 1: height
    for col = 1: width 
        graph(row,col) = pixels((row-1)*width+col); 
    end
end 
G = readraw('Gallery1.raw',width, height,1)
imshow(G/255)
