% --- Executes on button press in pb_randomize.
function pb_randomize_Callback(hObject, eventdata, handles)
% hObject    handle to pb_randomize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global puzzle;
global randomback;
randomback=0;
set(handles.text_randomback,'string',num2str(randomback));

%% create a source list that keeps the numbers of the puzzle
random_vect = linspace(0,puzzle.size^2-1, puzzle.size^2);

for i=1:puzzle.size
    for j=1:puzzle.size
        %%assign a random number to the current location from the source list
        puzzle.nodenum(i,j) = randsrc(1,1,random_vect);
        %%remove the assigned number from the source list
        random_vect(find(random_vect==puzzle.nodenum(i,j)))= [];
    end 
end

for i=1:puzzle.size
    for j=1:puzzle.size
        set(puzzle.squares(i,j),'string',num2str(puzzle.nodenum(i,j)));
    end
end

%%find the square which is not assigned to a number (assigned to zero)
[blank_x,blank_y] = find(puzzle.nodenum==0);

set(puzzle.squares(blank_x,blank_y),'string','');
%set(puzzle.squares(blank_x,blank_y),'BackgroundColor','blue');