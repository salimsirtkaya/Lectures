%%EE586 - Artificial Intelligence
%%METU - EE Spring 2006
%%Homework 2
%%Written by Salim SIRTKAYA, Barýþ TANRIVERDÝ and Bengi KOÇ

% --- Executes on button press in pb_loadGoal.
function pb_loadGoal_Callback(hObject, eventdata, handles)
% hObject    handle to pb_loadGoal (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global puzzle;
global randomback;
global goalState;
randomback=0;
set(handles.text_randomback,'string',num2str(randomback));
set(handles.pb_showsolution,'visible','off');
set(handles.text_nosolution,'visible','off');
        
vect = linspace(1,puzzle.size^2-1, puzzle.size^2-1);
vect(puzzle.size^2)=0;

puzzle.nodenum = (reshape(vect,puzzle.size,puzzle.size))';

%%generate the goalstate
goalState = puzzle.nodenum;

for i=1:puzzle.size
    for j=1:puzzle.size
        set(puzzle.squares(i,j),'string',num2str(puzzle.nodenum(i,j)));
    end
end
%%find the square which is not assigned to a number (assigned to zero)
[blank_x,blank_y] = find(puzzle.nodenum==0);

set(puzzle.squares(blank_x,blank_y),'string','');


