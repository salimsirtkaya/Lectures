% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function res=kiks_delete_object(id,objtype)
global KIKS_BALLARRAY KIKS_BALL_HDL KIKS_BALLDATA KIKS_LIGHTARRAY KIKS_LIGHT_HDL KIKS_LIGHTDATA KIKS_ROUNDOBJDATA KIKS_ROUNDOBJARRAY KIKS_GUI_HDL KIKS_2DVISUALIZE;
if objtype==1
    [rows,cols]=size(KIKS_LIGHTARRAY);
    if(cols==0) return; end;
    newarray=[];
    
    j=0;
    for i=1:cols,
        j=j+1;
        if(KIKS_LIGHTARRAY(i)~=id)
            newarray(j)=KIKS_LIGHTARRAY(i);
        else
            j=j-1;
        end
    end;
    
    KIKS_LIGHTARRAY=newarray;
    if(KIKS_2DVISUALIZE>0)
        o=findobj(KIKS_GUI_HDL,'tag',sprintf('@lightobj %d',id));
        delete(o);
    end;
    
    [rows,cols]=size(KIKS_LIGHTARRAY);
    if cols>0
        o=findobj(KIKS_GUI_HDL,'tag',sprintf('@lightobj %d',KIKS_LIGHTARRAY(1)));
        set(o,'Selected','on');
        h=findobj(KIKS_GUI_HDL,'Tag','deleteobj');
        set(h,'Callback',sprintf('kiks_delete_object(%d,%d)',KIKS_LIGHTARRAY(1),2));
        set(h,'Enable','on');
    else
        h=findobj('Name','KiKS');
        o=findobj(h,'tag','deleteobj');
        set(o,'Enable','off');
    end;
else % ball
    [rows,cols]=size(KIKS_BALLARRAY);
    if(cols==0) return; end;
    newarray=[];
    xp = floor(KIKS_BALLDATA(id,1));
    yp = floor(KIKS_BALLDATA(id,2));
    kiks_arena_subball(id,xp,yp);
    
    j=0;
    for i=1:cols,
        j=j+1;
        if(KIKS_BALLARRAY(i)~=id)
            newarray(j)=KIKS_BALLARRAY(i);
        else
            j=j-1;
            KIKS_BALLDATA(KIKS_BALLARRAY(i),:)=[0 0 0 0 0];
        end
    end;
    
    KIKS_BALLARRAY=newarray;
    
    if(KIKS_2DVISUALIZE>0)
        o=findobj(KIKS_GUI_HDL,'tag',sprintf('@ballobj %d',id));
        delete(o);
    end;
    
    [rows,cols]=size(KIKS_BALLARRAY);
    if cols>0
        o=findobj(KIKS_GUI_HDL,'tag',sprintf('@ballobj %d',KIKS_BALLARRAY(1)));
        set(o,'Selected','on');
        h=findobj(KIKS_GUI_HDL,'Tag','deleteobj');
        set(h,'Callback',sprintf('kiks_delete_object(%d,%d)',KIKS_BALLARRAY(1),2+KIKS_BALLDATA(KIKS_BALLARRAY(1),5)));
        set(h,'Enable','on');
    else
        h=findobj('Name','KiKS');
        o=findobj(h,'tag','deleteobj');
        set(o,'Enable','off');
    end;
end;
