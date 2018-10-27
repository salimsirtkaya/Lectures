% --- Executes on button press in pb_montecarlo.
function pb_montecarlo_Callback(hObject, eventdata, handles)
% hObject    handle to pb_montecarlo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global puzzle;
global goalState;
global Solution;
global solutionLevel;
global solution_index;
global stop_sign;
global pause_sign;
global iter;

simNo = str2num(get(handles.edit_simNo,'String'));

randomBackNo = str2num(get(handles.edit_backNo,'String'));

val = get(handles.popup_searchmethod,'Value');

averageTime=0;
averageIteration=0;

switch val
    
    case 2 % iterative deepening
        maxDepth = str2num(get(handles.edit_maxDepth,'String'));

        for i=1:simNo
            pb_loadGoal_Callback(hObject, eventdata, handles);
            for j=1:randomBackNo
                pb_randomback_Callback(hObject, eventdata, handles);
            end
            
            tic;
            [result]=IterativeDeepening(puzzle,goalState,maxDepth);
            toc;
            t=toc;
            
            averageTime=averageTime+t;
            
            averageIteration = averageIteration+iter;
        end
        
        averageTime = averageTime / simNo;
        
        averageIteration = averageIteration / simNo;
        
        set(handles.text_processtime,'string',num2str(averageTime));
        set(handles.text_total_iteration,'string',num2str(averageIteration));

        
    case 3 % deep first
        maxDepth = str2num(get(handles.edit_maxDepth,'String'));    
        for i=1:simNo
            pb_loadGoal_Callback(hObject, eventdata, handles);
            for j=1:randomBackNo
                pb_randomback_Callback(hObject, eventdata, handles);
            end
            
            tic;
            [result]=DFS_main(puzzle,goalState,maxDepth);
            toc;
            t=toc;
            
            averageTime=averageTime+t;
            
            averageIteration = averageIteration+iter;
        end
        
        averageTime = averageTime / simNo;
        averageIteration = averageIteration / simNo;        
        set(handles.text_processtime,'string',num2str(averageTime));
        set(handles.text_total_iteration,'string',num2str(averageIteration));
        
    case 4 % breadth first
        for i=1:simNo
            pb_loadGoal_Callback(hObject, eventdata, handles);
            for j=1:randomBackNo
                pb_randomback_Callback(hObject, eventdata, handles);
            end
            
            [solution,t,expended_node]=Breath_First;       
            
            averageTime=averageTime+t;
            
            averageIteration = averageIteration+expended_node;
        end
        
        averageTime = averageTime / simNo;
        averageIteration = averageIteration / simNo;        
        set(handles.text_processtime,'string',num2str(averageTime));
        set(handles.text_total_iteration,'string',num2str(averageIteration));
        
    case 5 % a*
end

