# MotionCapture
motion capture system using optitrack cameras.
1.calibration
using "calibration" dir. Input the sync captured points from all cameras, and output the intrinsic and extrinsic paras.

2.reconstruction
First, find point matching relationship using epipole constraint, and using  extra cameras to verify the mathing when confront ambiguity.
Second, using all projection matrixs to build a linear equation system. Solve it, you can  get the reconstructed 3d point.



