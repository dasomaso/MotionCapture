% Config configuration file for self-calibration experiments
% 
% config = configdata(experiment)
%
% experiment ... string with an experiment name

% $Author: svoboda $
% $Revision: 2.9 $
% $Id: configdata.m,v 2.9 2005/05/23 16:23:35 svoboda Exp $
% $State: Exp $

function config = configdata(experiment, cameraNum)

if nargin<1,
  display('No name of the experiment specified: >>basic<< used as default')
  experiment = 'TestData';
end
if strcmp(experiment,'TestData')
  %config.paths.data		= ['F:/workspace/Qt/Mocap/matlab/calibration/TestDataZeng6/'];
  config.paths.data		= ['./temp/'];
  config.files.basename = 'arctic';
  config.paths.img      = [config.paths.data,config.files.basename,'%d/'];
  config.files.imnames	= [config.files.basename,'%d.pvi.*.'];
%  config.files.idxcams	= [2,4,6,10,11,13,15];
%  config.files.idxcams	= [1,2,3,4,5,6,7,8];
  config.files.idxcams = 1:cameraNum;
  config.imgs.LEDsize	= 20; % avg diameter of a LED in pixels 
%  config.imgs.LEDsize	= 7; % avg diameter of a LED in pixels 
  config.imgs.LEDcolor	= 'green'; % color of the laser pointer
  config.imgs.subpix	= 1/3;
  config.cal.nonlinpar	= [70,0,1,0,0,0];
  config.cal.NL_UPDATE	= [1,0,1,0,0,0];
  config.cal.DO_GLOBAL_ITER = 1;
  config.cal.GLOBAL_ITER_THR = 0.5;
  config.cal.GLOBAL_ITER_MAX = 5;
  config.cal.INL_TOL	= 10; % if UNDO_RADIAL than it may be relatively small <1 
  config.cal.NUM_CAMS_FILL = 10;
  config.cal.DO_BA		= 1;
  config.cal.UNDO_RADIAL= 0; % CalTech (BlueC compatible)
 % config.cal.UNDO_RADIAL= 1;   %  do radical 
  config.cal.MIN_PTS_VAL = 30;
  config.cal.NTUPLES	= 3;
else
  error('Configdata: wrong identifier of the data set');
end

% camera indexes handling
try, config.cal.cams2use; catch, config.cal.cams2use = config.files.idxcams; end

% Default initial settings for the estiamtion of the nonlinear distortion
% (1) ... camera view angle
% (2) ... estimate principal point?
% (3:4) ... parameters of the radial distortion
% (5:6) ... parameters of the tangential distortion
try, config.cal.nonlinpar; catch, config.cal.nonlinpar = [50,0,1,0,0,0]; end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% adding more and more non-linear paramaters might be tricky
% in case of bad data. You may fall in the trap of overfitting
% You may want to disable this
% update all possible parameters by default
try, config.cal.NL_UPDATE; catch, config.cal.NL_UPDATE = [1,1,1,1,1,1]; end



% configuration of the for the calibration process
try, config.cal.SQUARE_PIX;	      catch,  config.cal.SQUARE_PIX = 1;end	% most of the cameras have square pixels
try, config.cal.START_BA;		  catch,	config.cal.START_BA = 0; end
try, config.cal.DO_GLOBAL_ITER;	  catch,  config.cal.DO_GLOBAL_ITER = 1; end
try, config.cal.GLOBAL_ITER_THR;  catch,	config.cal.GLOBAL_ITER_THR = 1; end
try, config.cal.GLOBAL_ITER_MAX;  catch,	config.cal.GLOBAL_ITER_MAX = 10; end
try, config.cal.INL_TOL;		  catch,  config.cal.INL_TOL = 5; end;
try, config.cal.NUM_CAMS_FILL;	  catch,	config.cal.NUM_CAMS_FILL = 12; end;
try, config.cal.DO_BA;			  catch,	config.cal.DO_BA = 0; end;
try, config.cal.UNDO_RADIAL;	  catch,	config.cal.UNDO_RADIAL = 0; end;
try, config.cal.UNDO_HEIKK;		  catch,	config.cal.UNDO_HEIKK = 0; end; % only for testing, not a part of standard package
try, config.cal.NTUPLES;		  catch,  config.cal.NTUPLES	= 3; end;	% size of the camera tuples, 2-5 implemented
try, config.cal.MIN_PTS_VAL;	  catch,  config.cal.MIN_PTS_VAL = 30; end; % minimal number of correnspondences in the sample

% image extensions
try, config.files.imgext;  catch,  config.files.imgext	= 'jpg'; end;

% image resolution
try, config.imgs.res; catch, config.imgs.res		  = [1280,1024];	end;

% scale for the subpixel accuracy
% 1/3 is a good compromise between speed and accuracy
% for high-resolution images or bigger LEDs you may try, 1/1 or 1/2
try, config.imgs.subpix; catch, config.imgs.subpix = 1/3; end;

% data names
try, config.files.Pmats;     catch, config.files.Pmats	    = [config.paths.data,'Pmatrices.dat'];		end;
try, config.files.points;	 catch, config.files.points		= [config.paths.data,'points.dat'];		end;
try, config.files.IdPoints;	 catch,	config.files.IdPoints	= [config.paths.data,'IdPoints.dat'];		end;
try, config.files.Res;		 catch,	config.files.Res		= [config.paths.data,'Res.dat'];		end;
try, config.files.IdMat;	 catch, config.files.IdMat		= [config.paths.data,'IdMat.dat'];			end;
try, config.files.inidx;	 catch, config.files.inidx		= [config.paths.data,'idxin.dat'];			end;
try, config.files.avIM;		 catch, config.files.avIM		= [config.paths.data,'camera%d.average.tiff'];		end;
try, config.files.stdIM;	 catch, config.files.stdIM		= [config.paths.data,'camera%d.std.tiff'];		end;
try, config.files.CalPar;	 catch, config.files.CalPar		= [config.paths.data,'camera%d.cal'];			end;
try, config.files.CalPmat;	 catch, config.files.CalPmat	= [config.paths.data,'camera%d.Pmat.cal'];			end;
try, config.files.StCalPar;	 catch,	config.files.StCalPar	= [config.paths.data,config.files.basename,'%d.cal'];	end;
try, config.files.rad;		 catch, config.files.rad		= [config.paths.data,config.files.basename,'%d.rad'];	end;
try, config.files.heikkrad;	 catch, config.files.heikkrad	= [config.paths.data,config.files.basename,'%d.heikk'];	end;
try, config.files.Pst;		 catch,	config.files.Pst		= [config.paths.data,'Pst.dat']; end;
try, config.files.Cst;		 catch,	config.files.Cst		= [config.paths.data,'Cst.dat']; end;
try, config.files.points4cal; catch,	config.files.points4cal = [config.paths.data,'cam%d.points4cal.dat']; end;
