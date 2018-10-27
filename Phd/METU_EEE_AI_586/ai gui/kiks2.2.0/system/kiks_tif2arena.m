% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function [arena,colormap]=kiks_tif2arena(filename);

try
    colormap=imread(filename,'tif');
    arena=~(colormap==0);
catch
    arena=[];
    colormap=[];
    kiks_status(sprintf('Warning: %s is not a valid TIF image file.\n',filename));
end;