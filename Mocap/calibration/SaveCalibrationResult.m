%mat2xml(in.Pe, 'projectionmatrix.xml');
%load('F:/workspace/Qt/Mocap/matlab/calibration/TestDataZeng6/Pmatrices.dat');
fid = fopen('projectionmatrix.txt',  'w');
M = in.Pe;
[m, n] = size(M);
% output projection  matrix P
for i = 1 : m
       fprintf(fid, '%f %f %f %f\n', M(i, 1),  M(i, 2),  M(i, 3),  M(i, 4));
end
if exist('kc')
% output distortion kc
    fprintf(fid, 'DistortionExist\n');
    for i = 1 : m/3
        %fileName = ['calibration/TestDataZeng6/arctic', num2str(i)];
        fileName = ['./temp/arctic', num2str(i)];
        fileName = [fileName, '.rad'];
        [K, kc] = readradfile(fileName);
        %fprintf(fid, '%f %f %f\n %f %f %f\n %f %f %f\n', K(1,1), K(1,2), K(1,3), K(2,1), K(2,2), K(2,3), K(3,1), K(3,2), K(3,3));
        fprintf(fid, '%f %f %f %f\n', kc(1,1),  kc(1, 2),  kc(1, 3),  kc(1, 4));
    end
else
    fprintf(fid, 'DistortionNonExist');
end

%store center of cameras
fprintf(fid, 'CameraCenter\n');
C = in.Ce;
[m, n] = size(C);
for i = 1 : n
       fprintf(fid, '%f %f %f\n', C(1, i),  C(2, i),  C(3, i));
end



fclose(fid);