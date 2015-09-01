function [ cameraNum ] = CreateCalibrationData( calibrationPointsName)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here


%read calibration points

%calibrationPointsName = 'CalibrationPoints.txt';
points = [];
IdMat = [];
A = [1280,1024];
%read calibration points
M = dlmread(calibrationPointsName);
[rows, cols] = size(M);

% the first column is the frame index
cameraNum = (cols - 1) / 2;
M = M(:, 2:cols);
N = [];
[row, col] = size(M);
a = ones(row, 1);
for i = 1 : cameraNum
    N = [N, M(:,2 * i - 1: 2 * i), a];   
end

[row, col] = size(N);
for i = 1 : row
    for j = 1:col/3
        if N(i,j * 3 - 2) + 1 < 1e-6 && N(i,j * 3 - 1) + 1 < 1e-6
          IdMat(i,j) = 0;
          N(i,j * 3 - 2) = NaN;
          N(i,j * 3 - 1) = NaN;
          N(i,j * 3) = NaN;
        else
         IdMat(i,j) = 1;
        end
    end
end
N = transpose(N);
IdMat = transpose(IdMat);
Res = repmat(A,cameraNum,1);
save('./temp/points.dat', 'N', '-ascii');
save('./temp/IdMat.dat', 'IdMat', '-ascii');
save('./temp/Res.dat', 'Res', '-ascii');


end

