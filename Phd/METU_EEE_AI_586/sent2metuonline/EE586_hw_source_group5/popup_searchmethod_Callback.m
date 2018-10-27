% --- Executes on selection change in popup_searchmethod.
function popup_searchmethod_Callback(hObject, eventdata, handles)
% hObject    handle to popup_searchmethod (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = get(hObject,'String') returns popup_searchmethod contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popup_searchmethod

global puzzle;

set(handles.pb_showsolution,'visible','off');
set(handles.text_nosolution,'visible','off');

val = get(hObject,'Value');
switch val
    case 4
        % The user selected breadth first search method
        set(handles.pb_step,'visible','off');
        set(handles.edit_maxDepth,'visible','off');
        set(handles.text_maxDepth,'visible','off');        
        
    case 3
        % The user selected deep first search method
        set(handles.pb_step,'visible','off');
        set(handles.edit_maxDepth,'visible','on');
        set(handles.text_maxDepth,'visible','on');        
        
    case 2
        % The user selected iterative deepening method
        set(handles.pb_step,'visible','off');
        set(handles.edit_maxDepth,'visible','on');
        set(handles.text_maxDepth,'visible','on');
        
    case 5
        % The user selected A* search method - manhattan
        set(handles.pb_step,'visible','off');
        set(handles.edit_maxDepth,'visible','off');
        set(handles.text_maxDepth,'visible','off');
        
    case 6
        % The user selected A* search method - misplaced
        set(handles.pb_step,'visible','off');
        set(handles.edit_maxDepth,'visible','off');
        set(handles.text_maxDepth,'visible','off'); 
end
