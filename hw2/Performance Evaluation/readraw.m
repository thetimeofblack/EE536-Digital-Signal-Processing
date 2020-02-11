function G = readraw(filename,width,height,BytesPerPixel)
%readraw - read RAW format grey scale image of square size into matrix G
% Usage:	G = readraw(filename)

	disp(['	Retrieving Image ' filename ' ...']);

	% Get file ID for file
	fid=fopen(filename,'rb');

	% Check if file exists
	if (fid == -1)
	  	error('can not open input image file press CTRL-C to exit \n');
	  	pause
	end

	% Get all the pixels from the image
	pixels = fread(fid, inf, 'uchar');

	% Close file
	fclose(fid);

	%N=sqrt(Size);

	% Construct matrix
	G = zeros(height,width);

	% Write pixels into matrix
	for i = 1:length(pixels)
        row = round(i/width+1)
        col = round(mod(i,width))
        G(row,col) = pixels(i)
    end 
	% Transpose matrix, to orient it properly
	G = G';
end %function
