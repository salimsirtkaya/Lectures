% --- Executes on button press in pb_start.
function pb_start_Callback(hObject, eventdata, handles)
% hObject    handle to pb_start (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global puzzle;
global goalState;
global Solution;
global solution_index;
global iter;

solution_index = 1;

val = get(handles.popup_searchmethod,'Value');

vect = linspace(1,puzzle.size^2-1, puzzle.size^2-1);
vect(puzzle.size^2)=0;

goalState = (reshape(vect,puzzle.size,puzzle.size))';

switch val
    case 4 % breadth first search
        set(handles.pb_showsolution,'visible','off');
        set(handles.pb_step,'visible','off');
        set(handles.text_nosolution,'visible','off');
        
        [solution,t,expended_node] = Breath_First;
        
        %% solution to Solution conversion
        [x,y,z] = size(solution);
        Solution = cell(z,1);
        for i=1:z
            Solution{z-i+1} = solution(:,:,i);
        end
        
        solution_level = z;
            
        set(handles.pb_showsolution,'visible','on');
        set(handles.pb_step,'visible','on');
        
        set(handles.text_processtime,'string',num2str(t));
        set(handles.text_total_iteration,'string',num2str(expended_node));
        
    case 3 % deep first search
        set(handles.text_wait,'visible','on');
        set(handles.pb_showsolution,'visible','off');
        set(handles.pb_step,'visible','off');
        set(handles.text_nosolution,'visible','off');
        maxDepth = str2num(get(handles.edit_maxDepth,'String'));
        
        tic;
        [result] = DFS_main(puzzle, goalState, maxDepth);
        toc;
        
        if result==1
            set(handles.pb_showsolution,'visible','on');
            set(handles.pb_step,'visible','on');
            t=toc;
            set(handles.text_processtime,'string',num2str(t));
            set(handles.text_total_iteration,'string',num2str(iter));

        elseif result==0
            set(handles.text_nosolution,'visible','on');
        end
        set(handles.text_wait,'visible','off');
        
    case 2 % iterative deepening
        set(handles.text_wait,'visible','on');
        set(handles.pb_showsolution,'visible','off');
        set(handles.pb_step,'visible','off');
        set(handles.text_nosolution,'visible','off');
        maxDepth = str2num(get(handles.edit_maxDepth,'String'));
        tic;
        [result]=IterativeDeepening(puzzle,goalState,maxDepth);
        toc;
        if result==1
            %enable the show solution button
            set(handles.pb_showsolution,'visible','on');
            set(handles.pb_step,'visible','on');
            t=toc;
            set(handles.text_processtime,'string',num2str(t));
            set(handles.text_total_iteration,'string',num2str(iter));
            
        elseif result==0
            set(handles.text_nosolution,'visible','on');            
        end
        set(handles.text_wait,'visible','off');
        
    case 5 % A* search - manhattan
        set(handles.text_wait,'visible','on');
        set(handles.pb_showsolution,'visible','off');
        set(handles.pb_step,'visible','off');
        set(handles.text_nosolution,'visible','off');
        
        [t,node] = Astar_manhattan;
        
        set(handles.pb_showsolution,'visible','on');
        set(handles.pb_step,'visible','on');
        set(handles.text_processtime,'string',num2str(t));
        set(handles.text_total_iteration,'string',num2str(node));
        set(handles.text_wait,'visible','off');

    case 6 % A* search - misplaced
        set(handles.text_wait,'visible','on');
        set(handles.pb_showsolution,'visible','off');
        set(handles.pb_step,'visible','off');
        set(handles.text_nosolution,'visible','off');
        
        [t,node] = Astar_misplaced;
        
        set(handles.pb_showsolution,'visible','on');
        set(handles.pb_step,'visible','on');
        set(handles.text_processtime,'string',num2str(t));
        set(handles.text_total_iteration,'string',num2str(node));
        set(handles.text_wait,'visible','off');       
end
