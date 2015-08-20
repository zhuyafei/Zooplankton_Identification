function batch_phow()

TrainingSetInfo = importdata('Training_Set.txt');
TrainingSetNum = length(TrainingSetInfo.data);
imgSize = 64;
numWords = 100;

model.phowOpts = {'Verbose', 2, 'Sizes', 7, 'Step', 5};
model.numSpatialX = [2 4];
model.numSpatialY = [2 4];
model.quantizer = 'kdtree';
model.vocab = [] ;
model.w = [] ;
model.b = [] ;

%% For random dividing - cross validation
descrs = {} ;
for i = 1:TrainingSetNum
    img = im2single(imread(TrainingSetInfo.textdata{i, 1}));
    img = imresize(img, [imgSize imgSize]);
    [drop, descrs{i}] = vl_phow(img, model.phowOpts{:}) ;
end
descrs = cat(2, descrs{:});
descrs = single(descrs) ;
% Quantize the descriptors to get the visual words
vocab = vl_kmeans(descrs, numWords, 'verbose', 'algorithm', 'elkan', 'MaxNumIterations', 50) ;

model.vocab = vocab ;

if strcmp(model.quantizer, 'kdtree')
  model.kdtree = vl_kdtreebuild(vocab) ;
end

hists = {} ;
for i = 1:TrainingSetNum
    img = im2single(imread(TrainingSetInfo.textdata{i, 1}));
    img = imresize(img, [imgSize imgSize]);
    hists{i} = getImageDescriptor(model, img);
end

hists = cat(2, hists{:}) ;


% --------------------------------------------------------------------
%                                                  Compute feature map
% --------------------------------------------------------------------

psix = vl_homkermap(hists, 1, 'kchi2', 'gamma', .5) ;
psix = psix';
save Train-Features-SIFT.mat psix



% -------------------------------------------------------------------------
function hist = getImageDescriptor(model, im)
% -------------------------------------------------------------------------

width = size(im,2) ;
height = size(im,1) ;
numWords = size(model.vocab, 2) ;

% get PHOW features
[frames, descrs] = vl_phow(im, model.phowOpts{:}) ;

% quantize local descriptors into visual words
switch model.quantizer
  case 'vq'
    [drop, binsa] = min(vl_alldist(model.vocab, single(descrs)), [], 1) ;
  case 'kdtree'
    binsa = double(vl_kdtreequery(model.kdtree, model.vocab, ...
                                  single(descrs), ...
                                  'MaxComparisons', 50)) ;
end

for i = 1:length(model.numSpatialX)
  binsx = vl_binsearch(linspace(1,width,model.numSpatialX(i)+1), frames(1,:)) ;
  binsy = vl_binsearch(linspace(1,height,model.numSpatialY(i)+1), frames(2,:)) ;

  % combined quantization
  bins = sub2ind([model.numSpatialY(i), model.numSpatialX(i), numWords], ...
                 binsy,binsx,binsa) ;
  hist = zeros(model.numSpatialY(i) * model.numSpatialX(i) * numWords, 1) ;
  hist = vl_binsum(hist, ones(size(bins)), bins) ;
  hists{i} = single(hist / sum(hist)) ;
end
hist = cat(1,hists{:}) ;
hist = hist / sum(hist) ;

