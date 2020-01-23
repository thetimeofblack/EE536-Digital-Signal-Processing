% EE569 Homework Assignment #1
% Date: January 13, 2020
% Name: Yining HE
% ID: 1125231425
% email: heyining@usc.edu
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Description 
% All .exe file is generated and complied by the 
% corresponding .cpp file. you can just open the cmd to run 
% the program for the specific problem. 
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Problem 1_a: Bilinear Demosaicing
% C++-file name: prob1_a.cpp
% Execuable file: prob1_a.exe 
% Command template : prob1_a [input filepath] [output filepath] [byte per pixel] [width] [height] 
% Command: prob1_a imagepath/dog.raw   outputpath/dog_BD.raw 1 600 532
% Output image: dog_BD1.raw
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Problem 1_b: Malvar-He-Cutler (MHC) Demosaicing
% C++-file name: prob1_b.cpp
% Command template : prob1_b [input filepath] [output filepath] [byte per pixel of input file] [width] [height]
% Command: prob1_a imagepath/dog.raw outputpath/dog_MHC1.raw 1 600 532
% Output image: dog_MHC1.raw 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Problem 1_c:  Histogram Manipulation
% C++-file name: prob1_c.cpp
% Command template : prob1_c [input filepath] [output filepath] [byte per pixel of input file] [width] [height] [method]
% Command: prob1_c imagepath/toy.raw outputpath/toy_a(b).raw 1 400 560 [you can choose method to solve this image]
% Output image: toy_a1.raw toy_b1.raw
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Problem 2_a: Linear Denoising
% C++-file name: prob2_a.cpp
% Command template :  prob2_a [input filepath] [output filepath] [byte per pixel of input file] [width] [height] [edgesize] [window size] [standard deviation C] [standard deviation S]
% Command: prob2_b ..\HW1_images\Corn_noisy.raw corn_bf1.raw 1 320 320 10 9 2 2 
% Output image: corn_bf1.raw
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
% Problem 2_b: Bilateral Denoising
% C++-file name: prob2_b.cpp
% Command template : prob2_b [inputfile path] [the compared image path] [output image path] [BytesPerPixel] [width] [height] [variance]  
% Command: prob2_b imagepath/dog.raw outputpath/dog_BD.raw 1 
% Output image: linear_amp_lena.256
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
% Problem 2_c: Non-Local mean Denoising
% M-file name: prob2_c.cpp
% Command template : 
% Command: prob2_c ..\HW1_images\Corn_noisy.raw ..\HW1_images\Corn_gray.raw corn_nlm1.raw 1 320 320 5 5 1 100  
% Output image: corn_nlm1.raw
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   