% --- Executes on selection change in popup_puzzlesize.
function popup_puzzlesize_Callback(hObject, eventdata, handles)
% hObject    handle to popup_puzzlesize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popup_puzzlesize contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popup_puzzlesize
%%ss-begin

global puzzle;

val = get(hObject,'Value');
switch val
    case 2
        % The user selected 8 puzzle
        puzzle.size = 3;
        
    case 3
        % The user selected 15 puzzle
        puzzle.size = 4;  
        
    case 4
        % The user selected 24 puzzle
        puzzle.size = 5;     
        
    case 5
        % The user selected 35 puzzle
        puzzle.size = 6;
        
    case 6
        % The user selected 48 puzzle
        puzzle.size = 7;
        
    case 7
        % The user selected 63 puzzle
        puzzle.size = 8;
end

for i=1:8
    for j=1:8
        set(puzzle.squares(i,j),'visible','off');
        set(puzzle.squares(i,j),'string','');
        puzzle.nodenum(i,j)=NaN;
    end
end

for i=1:puzzle.size
    for j=1:puzzle.size
        set(puzzle.squares(i,j),'visible','on');
    end
end


%%ss-end
