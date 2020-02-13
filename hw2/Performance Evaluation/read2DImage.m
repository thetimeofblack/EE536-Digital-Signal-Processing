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

	% Construct matrix
	G = zeros(height,width);
    
	% Read pixels into matrix
	for row = 1: height
        for col = 1: width 
        G(row,col) = pixels((row-1)*width + col); 
        end
    end
end %function
