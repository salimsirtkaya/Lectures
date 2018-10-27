function kiks_gui_kiksnet_scroll(val)
global KIKS_GUI_HDL KIKS_GUI_KIKSNET_CLIENTS_CNT

KIKS_GUI_KIKSNET_CLIENTS_CNT=max(0,KIKS_GUI_KIKSNET_CLIENTS_CNT+val);
set(findobj(KIKS_GUI_HDL,'Tag','t_kiksnetserver_scrollup'),'Enable','off');
set(findobj(KIKS_GUI_HDL,'Tag','t_kiksnetserver_scrolldown'),'Enable','off');