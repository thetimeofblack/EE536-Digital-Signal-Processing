addEdgePath(); 
% Demo for Structured Edge Detector (please see readme.txt first).




%% 




%% set opts for training (see edgesTrain.m)
opts=edgesTrain();                % default options (good settings)
opts.modelDir='models/';          % model will be in models/forest
opts.modelFnm='modelBsds';        % model name
opts.nPos=5e5; opts.nNeg=5e5;     % decrease to speedup training
opts.useParfor=0;                 % parallelize if sufficient memory


%% train edge detector (~20m/8Gb per tree, proportional to nPos/nNeg)
tic, model=edgesTrain(opts); toc; % will load model if already trained


%% set detection parameters (can set after training)
model.opts.multiscale=3;          % for top accuracy set multiscale=1
model.opts.sharpen=2;             % for top speed set sharpen=0
model.opts.nTreesEval=5;          % for top speed set nTreesEval=1
model.opts.nThreads=6;            % max number threads for evaluation
model.opts.nms=1;                 % set to true to enable nms


%% evaluate edge detector on BSDS500 (see edgesEval.m)
if(0), edgesEval( model, 'show',1, '','' ); end



%% detect edge and visualize results
I = imread('../../Problem1/Dogs.jpg');
tic, E = edgesDetect(I,model); toc; 

figure(1); im(I);  
figure(2); im(E); 


% EdgeImageData = round((1-E)*255);
% writeraw(round(E*255),'DogEdge.raw');


%% evaluate edge and ground truth

prms1={ 'out','', 'thrs',10, 'maxDist',.0075, 'thin',1 } ; 
[thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg( E, 'Dogs_GT1.mat', prms1 )
recall = cntR./sumR
precision = cntP./sumP 
Fscore = 2*recall.*precision./(precision+recall)


