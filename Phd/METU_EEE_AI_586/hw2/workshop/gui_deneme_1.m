function varargout = gui_deneme_1(varargin)

% GUI_DENEME_1 M-file for gui_deneme_1.fig
%      GUI_DENEME_1, by itself, creates a new GUI_DENEME_1 or raises the existing
%      singleton*.
%
%      H = GUI_DENEME_1 returns the handle to a new GUI_DENEME_1 or the handle to
%      the existing singleton*.
%
%      GUI_DENEME_1('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUI_DENEME_1.M with the given input arguments.
%
%      GUI_DENEME_1('Property','Value',...) creates a new GUI_DENEME_1 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before gui_deneme_1_OpeningFunction gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to gui_deneme_1_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help gui_deneme_1

% Last Modified by GUIDE v2.5 11-Apr-2006 20:32:52

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @gui_deneme_1_OpeningFcn, ...
                   'gui_OutputFcn',  @gui_deneme_1_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin & isstr(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before gui_deneme_1 is made visible.
function gui_deneme_1_OpeningFcn(hObject, eventdata, handles, varargin)

% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to gui_deneme_1 (see VARARGIN)

% Choose default command line output for gui_deneme_1
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

%%Assign square handles to puzzle
global puzzle;
global randomback; randomback=0;
global randprev; randprev=NaN;
global goalState;
global Solution;
global solutionLevel;
global solution_index;
global stop_sign;
global pause_sign;

stop_sign=0;
pause_sign=0;
solution_index = 1;
puzzle.level = 1;

puzzle.squares(1,1)=handles.sq_11;
puzzle.squares(1,2)=handles.sq_12;
puzzle.squares(1,3)=handles.sq_13;
puzzle.squares(1,4)=handles.sq_14;
puzzle.squares(1,5)=handles.sq_15;
puzzle.squares(1,6)=handles.sq_16;
puzzle.squares(1,7)=handles.sq_17;
puzzle.squares(1,8)=handles.sq_18;

puzzle.squares(2,1)=handles.sq_21;
puzzle.squares(2,2)=handles.sq_22;
puzzle.squares(2,3)=handles.sq_23;
puzzle.squares(2,4)=handles.sq_24;
puzzle.squares(2,5)=handles.sq_25;
puzzle.squares(2,6)=handles.sq_26;
puzzle.squares(2,7)=handles.sq_27;
puzzle.squares(2,8)=handles.sq_28;

puzzle.squares(3,1)=handles.sq_31;
puzzle.squares(3,2)=handles.sq_32;
puzzle.squares(3,3)=handles.sq_33;
puzzle.squares(3,4)=handles.sq_34;
puzzle.squares(3,5)=handles.sq_35;
puzzle.squares(3,6)=handles.sq_36;
puzzle.squares(3,7)=handles.sq_37;
puzzle.squares(3,8)=handles.sq_38;

puzzle.squares(4,1)=handles.sq_41;
puzzle.squares(4,2)=handles.sq_42;
puzzle.squares(4,3)=handles.sq_43;
puzzle.squares(4,4)=handles.sq_44;
puzzle.squares(4,5)=handles.sq_45;
puzzle.squares(4,6)=handles.sq_46;
puzzle.squares(4,7)=handles.sq_47;
puzzle.squares(4,8)=handles.sq_48;

puzzle.squares(5,1)=handles.sq_51;
puzzle.squares(5,2)=handles.sq_52;
puzzle.squares(5,3)=handles.sq_53;
puzzle.squares(5,4)=handles.sq_54;
puzzle.squares(5,5)=handles.sq_55;
puzzle.squares(5,6)=handles.sq_56;
puzzle.squares(5,7)=handles.sq_57;
puzzle.squares(5,8)=handles.sq_58;

puzzle.squares(6,1)=handles.sq_61;
puzzle.squares(6,2)=handles.sq_62;
puzzle.squares(6,3)=handles.sq_63;
puzzle.squares(6,4)=handles.sq_64;
puzzle.squares(6,5)=handles.sq_65;
puzzle.squares(6,6)=handles.sq_66;
puzzle.squares(6,7)=handles.sq_67;
puzzle.squares(6,8)=handles.sq_68;

puzzle.squares(7,1)=handles.sq_71;
puzzle.squares(7,2)=handles.sq_72;
puzzle.squares(7,3)=handles.sq_73;
puzzle.squares(7,4)=handles.sq_74;
puzzle.squares(7,5)=handles.sq_75;
puzzle.squares(7,6)=handles.sq_76;
puzzle.squares(7,7)=handles.sq_77;
puzzle.squares(7,8)=handles.sq_78;

puzzle.squares(8,1)=handles.sq_81;
puzzle.squares(8,2)=handles.sq_82;
puzzle.squares(8,3)=handles.sq_83;
puzzle.squares(8,4)=handles.sq_84;
puzzle.squares(8,5)=handles.sq_85;
puzzle.squares(8,6)=handles.sq_86;
puzzle.squares(8,7)=handles.sq_87;
puzzle.squares(8,8)=handles.sq_88;
% UIWAIT makes gui_deneme_1 wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% --- Outputs from this function are returned to the command line.
function varargout = gui_deneme_1_OutputFcn(hObject, eventdata, handles)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

% --- Executes on button press in sq_11.
function sq_11_Callback(hObject, eventdata, handles)
% hObject    handle to sq_12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% --- Executes on button press in sq_12.
function sq_12_Callback(hObject, eventdata, handles)
% hObject    handle to sq_12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_13.
function sq_13_Callback(hObject, eventdata, handles)
% hObject    handle to sq_13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_14.
function sq_14_Callback(hObject, eventdata, handles)
% hObject    handle to sq_14 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_21.
function sq_21_Callback(hObject, eventdata, handles)
% hObject    handle to sq_21 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_22.
function sq_22_Callback(hObject, eventdata, handles)
% hObject    handle to sq_22 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_23.
function sq_23_Callback(hObject, eventdata, handles)
% hObject    handle to sq_23 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_24.
function sq_24_Callback(hObject, eventdata, handles)
% hObject    handle to sq_24 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_31.
function sq_31_Callback(hObject, eventdata, handles)
% hObject    handle to sq_31 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_33.
function sq_33_Callback(hObject, eventdata, handles)
% hObject    handle to sq_33 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_32.
function sq_32_Callback(hObject, eventdata, handles)
% hObject    handle to sq_32 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_34.
function sq_34_Callback(hObject, eventdata, handles)
% hObject    handle to sq_34 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_41.
function sq_41_Callback(hObject, eventdata, handles)
% hObject    handle to sq_41 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_42.
function sq_42_Callback(hObject, eventdata, handles)
% hObject    handle to sq_42 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_43.
function sq_43_Callback(hObject, eventdata, handles)
% hObject    handle to sq_43 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_44.
function sq_44_Callback(hObject, eventdata, handles)
% hObject    handle to sq_44 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_15.
function sq_15_Callback(hObject, eventdata, handles)
% hObject    handle to sq_15 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_16.
function sq_16_Callback(hObject, eventdata, handles)
% hObject    handle to sq_16 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_17.
function sq_17_Callback(hObject, eventdata, handles)
% hObject    handle to sq_17 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_18.
function sq_18_Callback(hObject, eventdata, handles)
% hObject    handle to sq_18 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_25.
function sq_25_Callback(hObject, eventdata, handles)
% hObject    handle to sq_25 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_27.
function sq_27_Callback(hObject, eventdata, handles)
% hObject    handle to sq_27 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_28.
function sq_28_Callback(hObject, eventdata, handles)
% hObject    handle to sq_28 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_28.
function pushbutton23_Callback(hObject, eventdata, handles)
% hObject    handle to sq_28 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_35.
function sq_35_Callback(hObject, eventdata, handles)
% hObject    handle to sq_35 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_36.
function sq_36_Callback(hObject, eventdata, handles)
% hObject    handle to sq_36 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_37.
function sq_37_Callback(hObject, eventdata, handles)
% hObject    handle to sq_37 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_38.
function sq_38_Callback(hObject, eventdata, handles)
% hObject    handle to sq_38 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_45.
function sq_45_Callback(hObject, eventdata, handles)
% hObject    handle to sq_45 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_46.
function sq_46_Callback(hObject, eventdata, handles)
% hObject    handle to sq_46 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_47.
function sq_47_Callback(hObject, eventdata, handles)
% hObject    handle to sq_47 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_48.
function sq_48_Callback(hObject, eventdata, handles)
% hObject    handle to sq_48 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton32.
function pushbutton32_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton32 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton33.
function pushbutton33_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton33 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton34.
function pushbutton34_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton34 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% % --- Executes on button press in pb_randomize.
% function pb_randomize_Callback(hObject, eventdata, handles)
% % hObject    handle to pb_randomize (see GCBO)
% % eventdata  reserved - to be defined in a future version of MATLAB
% % handles    structure with handles and user data (see GUIDATA)
% set(handles.sq_11,'string','9');
% set(handles.sq_12,'string','4');
% set(handles.sq_13,'string','1');
% set(handles.sq_21,'string','5');
% set(handles.sq_22,'string','3');
% set(handles.sq_23,'string','6');
% set(handles.sq_31,'string','7');
% set(handles.sq_32,'string','2');


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes on button press in tb_pause.
function tb_pause_Callback(hObject, eventdata, handles)
% hObject    handle to tb_pause (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- ?Executes on button press in tb_stop.
function tb_stop_Callback(hObject, eventdata, handles)
% hObject    handle to tb_stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
temp = get(handles.tb_stop,'SelectionHighLight');

if all(temp=='on')
    stop_sign=1;
elseif all(temp=='off')
    stop_sign=0;
end

% --- Executes during object creation, after setting all properties.
function edit_simNo_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_simNo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function edit_simNo_Callback(hObject, eventdata, handles)
% hObject    handle to edit_simNo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_simNo as text
%        str2double(get(hObject,'String')) returns contents of edit_simNo as a double


% --- Executes on button press in pb_loadfromfile.
function pb_loadfromfile_Callback(hObject, eventdata, handles)
% hObject    handle to pb_loadfromfile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global puzzle;
for i=1:8
    for j=1:8
        set(puzzle.squares(i,j),'visible','off');
        set(puzzle.squares(i,j),'string','');
        puzzle.nodenum(i,j)=NaN;
    end
end

fid = fopen('example_puzzle.txt','r');

temp = fscanf(fid,'%d\n');

puzzle.size = temp(1);
puzzle.nodenum = (reshape(temp(2:size(temp)),puzzle.size,puzzle.size))';
puzzle.level=1;

fclose(fid);

for i=1:puzzle.size
    for j=1:puzzle.size
        set(puzzle.squares(i,j),'visible','on');
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

% --- Executes on button press in sq_26.
function sq_26_Callback(hObject, eventdata, handles)
% hObject    handle to sq_26 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --------------------------------------------------------------------
function menu_1_Callback(hObject, eventdata, handles)
% hObject    handle to menu_1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on mouse press over figure background.
function figure1_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_51.
function sq_51_Callback(hObject, eventdata, handles)
% hObject    handle to sq_51 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_52.
function sq_52_Callback(hObject, eventdata, handles)
% hObject    handle to sq_52 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_53.
function sq_53_Callback(hObject, eventdata, handles)
% hObject    handle to sq_53 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_54.
function sq_54_Callback(hObject, eventdata, handles)
% hObject    handle to sq_54 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_55.
function sq_55_Callback(hObject, eventdata, handles)
% hObject    handle to sq_55 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_56.
function sq_56_Callback(hObject, eventdata, handles)
% hObject    handle to sq_56 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_57.
function sq_57_Callback(hObject, eventdata, handles)
% hObject    handle to sq_57 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_58.
function sq_58_Callback(hObject, eventdata, handles)
% hObject    handle to sq_58 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_61.
function sq_61_Callback(hObject, eventdata, handles)
% hObject    handle to sq_61 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_62.
function sq_62_Callback(hObject, eventdata, handles)
% hObject    handle to sq_62 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_63.
function sq_63_Callback(hObject, eventdata, handles)
% hObject    handle to sq_63 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_64.
function sq_64_Callback(hObject, eventdata, handles)
% hObject    handle to sq_64 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_65.
function sq_65_Callback(hObject, eventdata, handles)
% hObject    handle to sq_65 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_66.
function sq_66_Callback(hObject, eventdata, handles)
% hObject    handle to sq_66 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_67.
function sq_67_Callback(hObject, eventdata, handles)
% hObject    handle to sq_67 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_68.
function sq_68_Callback(hObject, eventdata, handles)
% hObject    handle to sq_68 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_71.
function sq_71_Callback(hObject, eventdata, handles)
% hObject    handle to sq_71 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_72.
function sq_72_Callback(hObject, eventdata, handles)
% hObject    handle to sq_72 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_73.
function sq_73_Callback(hObject, eventdata, handles)
% hObject    handle to sq_73 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_74.
function sq_74_Callback(hObject, eventdata, handles)
% hObject    handle to sq_74 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_75.
function sq_75_Callback(hObject, eventdata, handles)
% hObject    handle to sq_75 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_76.
function sq_76_Callback(hObject, eventdata, handles)
% hObject    handle to sq_76 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_77.
function sq_77_Callback(hObject, eventdata, handles)
% hObject    handle to sq_77 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_78.
function sq_78_Callback(hObject, eventdata, handles)
% hObject    handle to sq_78 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_81.
function sq_81_Callback(hObject, eventdata, handles)
% hObject    handle to sq_81 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_82.
function sq_82_Callback(hObject, eventdata, handles)
% hObject    handle to sq_82 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_83.
function sq_83_Callback(hObject, eventdata, handles)
% hObject    handle to sq_83 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_84.
function sq_84_Callback(hObject, eventdata, handles)
% hObject    handle to sq_84 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_85.
function sq_85_Callback(hObject, eventdata, handles)
% hObject    handle to sq_85 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_86.
function sq_86_Callback(hObject, eventdata, handles)
% hObject    handle to sq_86 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_87.
function sq_87_Callback(hObject, eventdata, handles)
% hObject    handle to sq_87 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in sq_88.
function sq_88_Callback(hObject, eventdata, handles)
% hObject    handle to sq_88 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- If Enable == 'on', executes on mouse press in 5 pixel border.
% --- Otherwise, executes on mouse press in 5 pixel border or over pb_randomize.
function pb_randomize_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to pb_randomize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function popup_puzzlesize_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popup_puzzlesize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end


% --- Executes during object creation, after setting all properties.
function popup_searchmethod_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popup_searchmethod (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



% --- If Enable == 'on', executes on mouse press in 5 pixel border.
% --- Otherwise, executes on mouse press in 5 pixel border or over popup_puzzlesize.
function popup_puzzlesize_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to popup_puzzlesize (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in rb_manhattan.
function rb_manhattan_Callback(hObject, eventdata, handles)
% hObject    handle to rb_manhattan (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_manhattan


% --- Executes on button press in rb_misplaced.
function rb_misplaced_Callback(hObject, eventdata, handles)
% hObject    handle to rb_misplaced (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of rb_misplaced


% --- Executes during object creation, after setting all properties.
function edit_maxDepth_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_maxDepth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function edit_maxDepth_Callback(hObject, eventdata, handles)
% hObject    handle to edit_maxDepth (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_maxDepth as text
%        str2double(get(hObject,'String')) returns contents of edit_maxDepth as a double


% --- Executes during object creation, after setting all properties.
function text_wait_CreateFcn(hObject, eventdata, handles)
% hObject    handle to text_wait (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called


% --- Executes during object creation, after setting all properties.
function edit_backNo_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit_backNo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc
    set(hObject,'BackgroundColor','white');
else
    set(hObject,'BackgroundColor',get(0,'defaultUicontrolBackgroundColor'));
end



function edit_backNo_Callback(hObject, eventdata, handles)
% hObject    handle to edit_backNo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit_backNo as text
%        str2double(get(hObject,'String')) returns contents of edit_backNo as a double


