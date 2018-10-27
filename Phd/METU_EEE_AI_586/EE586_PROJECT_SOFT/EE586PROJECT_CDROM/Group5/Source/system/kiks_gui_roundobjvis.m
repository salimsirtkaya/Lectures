% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_roundobjvis(id)
global KIKS_ROUNDOBJ_HDL;

KIKS_ROUNDOBJ_HDL(id)=kiks_roundobjpatch(id);
