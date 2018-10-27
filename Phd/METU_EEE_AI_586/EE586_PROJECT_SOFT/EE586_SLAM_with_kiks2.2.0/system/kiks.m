% kiks (ARENA,COLORMASK)
% initializes KiKS.
%
% System requirements:
%  * Matlab r11.1 or later
%  * Neural network toolbox is optional
%  * KiKS will not work with the student edition of Matlab thanks
%    to the 128x128 restriction in matrix size (there are two kinds of
%    Matlab student products - see http://www.mathworks.com/products/studentversion/comparison.shtml)
%
% ARENA should be a matrix describing the arena or a string containing the
% filename of a TIF file.
%
% If ARENA is empty, a default arena is created and a robot is spawned.
% If ARENA is a m*n matrix, an arena corresponding to the matrix is created 
% and one (or more, if start positions are defined) robot(s) will be spawned.
% Each matrix element must be one of the following:
% <0=robot start position (absolute value defines the start angle)
% 	0=no obstacle
%	1=wall
%	2=light source
%	3=ball
%   4=cylinder
%
% One matrix element corresponds to 1 square millimeter. 
% The environment may be of any size.
%
% You may also provide a COLORMASK matrix. This matrix tells KiKS what 
% color the walls defined by the ARENA matrix are.
% The COLORMASK matrix must be the same size as the arena matrix.
% For each '1' element in the ARENA matrix at position [x,y],
% set [x,y] in the COLORMASK matrix to the color you want the wall to
% have.
%
% The easiest way to create an arena with a colormask is to draw
% a _grayscale_ (256 colors) picture using e.g. Photoshop, save
% the picture as .tif, and use the command
% [arena,colormask]=kiks_tif2arena('filename')
% where filename is the name of the .tif file.
% All completely black areas (RGB=#000000) will be regarded as floor by
% this function, and the rest of the colors should be used to draw
% the walls. So if you want a black wall, draw it using RGB #010101.
% There are a few sample pictures in the demos\football\ directory,
% and the m-file demos\football\field.m demonstrates how to use kiks_tif2arena.
%
%
% For example, 
% >> kiks(zeros(500,500));
% will start up KiKS and create an empty arena of 500x500mm size.
%
% The sequence
% >> ARENA=zeros(400,600);
% >> ARENA(1:100,1:100)=1;
% >> kiks(ARENA);
% will start up KiKS and create a 400mm high and 600mm wide arena with a 
% 100x100mm obstacle in the top left corner.
%
% and the sequence
% >> [ARENA,COLORMASK]=kiks_tif2arena('myfile.tif');
% >> kiks(ARENA,COLORMASK);
% Will convert the picture myfile.tif into an arena and a colormask and
% start up KiKS.
%
% Note: 
% If you use this simulator, never name your variables or functions 
% kiks_* or KIKS_*. If you do, you may completely screw up the simulation.
%
% Never interrupt a program running a behaviour on a KiKS simulated robot
% using ctrl-C. Instead, use the "halt simulation" button to stop the program
% in a more KiKS-friendly manner.
%
% Also, the CLEAR ALL command should not be used during a simulation.
%
% -------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -------------------------------------------------

function kiks(arena, colormask)
global KIKS_SESSIONACTIVE;
res=0;
if isempty(KIKS_SESSIONACTIVE) KIKS_SESSIONACTIVE=0; end;
if KIKS_SESSIONACTIVE==1
    fprintf('<KiKS> Error: A KiKS session is already active.\n<KiKS> Error: Use kiks_quit if you want quit the active session.\n');
    res = -1;
    return;
end;
if nargin<1 arena=[]; end
if nargin<2 colormask=[]; end
res=kiks_init(arena,colormask);
if res==-1
    kiks_quit;
end;
