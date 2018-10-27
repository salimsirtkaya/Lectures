% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_staticbtn
global KIKS_GUI_HDL KIKS_TIMESCALE KIKS_updatelmp;

KIKS_updatelmp=-1;

KIKS_TIMESCALE=-1;
H=findobj(KIKS_GUI_HDL,'Tag','update_frame');
set(H,'BackgroundColor',[ 0.3 0.3 0.3 ]); 
H=findobj(KIKS_GUI_HDL,'Tag','update_text');
set(H,'BackgroundColor',[ 0.3 0.3 0.3 ]); 

H=findobj(KIKS_GUI_HDL,'Tag','button_dynamic');
set(H,'Value',0); 
H=findobj(KIKS_GUI_HDL,'Tag','button_real');
set(H,'Value',0); 
H=findobj(KIKS_GUI_HDL,'Tag','button_static');
set(H,'Value',1); 

H=findobj(KIKS_GUI_HDL,'Tag','step_popup');
set(H,'Enable','on');
H=findobj(KIKS_GUI_HDL,'Tag','stat_popup');
set(H,'Enable','on');

H=findobj(KIKS_GUI_HDL,'Tag','acc_popup');
set(H,'Enable','off');
H=findobj(KIKS_GUI_HDL,'Tag','limit_popup');
set(H,'Enable','on');
H=findobj(KIKS_GUI_HDL,'Tag','int_check');
set(H,'Enable','on');

kiks_gui_getstatlistbox;