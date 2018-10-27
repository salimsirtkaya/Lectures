% --- Executes on button press in pb_showsolution.
function pb_showsolution_Callback(hObject, eventdata, handles)
% hObject    handle to pb_showsolution (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global puzzle;
global iter;
global Solution;
global solutionLevel;

for ind=1:solutionLevel-1
    solve_onestep(ind);
end

