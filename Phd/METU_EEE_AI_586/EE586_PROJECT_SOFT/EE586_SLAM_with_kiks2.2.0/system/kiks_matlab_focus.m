function kiks_matlab_focus
global KIKS_GUI_HDL

figure(KIKS_GUI_HDL);
h=findobj(KIKS_GUI_HDL,'tag','kiks_matlab_command');
set(KIKS_GUI_HDL,'CurrentObject',h);
