% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_setinterpolate
global KIKS_INTERPOLATE KIKS_GUI_HDL;
h=findobj(KIKS_GUI_HDL,'Tag','int_check');
set(h,'Value',KIKS_INTERPOLATE);
