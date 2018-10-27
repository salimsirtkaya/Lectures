% --- Executes on button press in pb_step.
function pb_step_Callback(hObject, eventdata, handles)
% hObject    handle to pb_step (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global puzzle;
global iter;
global Solution;
global solutionLevel;
global solution_index;

temp = Solution{solution_index};

solution_index = solution_index + 1;

for i=1:puzzle.size
    for j=1:puzzle.size
        set(puzzle.squares(i,j),'string',num2str(temp(i,j)));
    end
end

%%find the square which is not assigned to a number (assigned to zero)
[blank_x,blank_y] = find(temp==0);

set(puzzle.squares(blank_x,blank_y),'string','');

    