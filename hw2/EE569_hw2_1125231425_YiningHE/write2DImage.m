function count = writeraw(G, filename,width,height,BytesPerPixel)
%writeraw - write RAW format grey scale image file 
% Usage :	writeraw(G, filename)
% G:		input image matrix
% filename: file name of the file to write to disk
% count:	return value, the elements written to file

	disp([' Write image data to'  filename ' ...']);

	% Get file ID
	fid = fopen(filename,'w');
    imshow(G)
	% Check if file exists
	if (fid == -1)
		error('can not open output image filem press CTRL-C to exit \n');
		pause
	end

	% Transpose matrix to write file properly
	
    G(321,481)
	% Write and close fil
    fwrite(fid,G,'uchar'); 
    
	fclose(fid);

	% Transpose again to restore matrix
	
end %function