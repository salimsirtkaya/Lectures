% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function kiks_gui_robotvis(id)
global KIKS_FIRE_HDL KIKS_GRIPPER_L_HDL KIKS_GRIPPER_R_HDL KIKS_GRIPPER_HDL KIKS_NR_HDL KIKS_LINVIS_GR_HDL KIKS_LINVIS_HDL KIKS_RBT_HDL KIKS_RBTSENS_HDL KIKS_RBTWHL_HDL KIKS_RBTLMP_HDL KIKS_RBTDIOD_HDL;
for j=1:8,
    KIKS_RBTSENS_HDL(id,j)=kiks_robotsenspatch(id,j);
end
KIKS_RBTDIOD_HDL(id,1)=kiks_robotdiodpatch(id,[.8 .9 .8]);
KIKS_RBTDIOD_HDL(id,2)=kiks_robotdiodpatch(id,[.8 .9 .8]);
KIKS_RBTWHL_HDL(id)=kiks_robotwheelpatch(id);
KIKS_GRIPPER_HDL(id)=patch('Facecolor',[.3 .3 .3],'EdgeColor','none','Erase','xor','tag',sprintf('@kheppatch %d',id));
KIKS_GRIPPER_L_HDL(id)=patch('Facecolor',[.3 .3 .3],'EdgeColor','none','Erase','xor','tag',sprintf('@kheppatch %d',id));
KIKS_GRIPPER_R_HDL(id)=patch('Facecolor',[.3 .3 .3],'EdgeColor','none','Erase','xor','tag',sprintf('@kheppatch %d',id));
KIKS_RBT_HDL(id)=kiks_robotpatch(id);
KIKS_RBTLMP_HDL(id)=kiks_robotlmppatch(id);
KIKS_LINVIS_HDL(id)=patch('Facecolor',[0.25 0.3 .35],'EdgeColor','none','Erase','xor','tag',sprintf('@kheppatch %d',id));
KIKS_LINVIS_GR_HDL(id)=patch('Facecolor',[.5 .65 .6],'EdgeColor','none','Erase','xor','tag',sprintf('@kheppatch %d',id));
KIKS_FIRE_HDL(id)=patch('Visible','off','Facecolor',[1  .4  .4],'EdgeColor','none','Erase','xor','tag',sprintf('@kheppatch %d',id));