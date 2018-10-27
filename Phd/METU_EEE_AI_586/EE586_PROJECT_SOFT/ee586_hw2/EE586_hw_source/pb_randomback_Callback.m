%%EE586 - Artificial Intelligence
%%METU - EE Spring 2006
%%Homework 2
%%Written by Salim SIRTKAYA, Barýþ TANRIVERDÝ and Bengi KOÇ

% --- Executes on button press in pb_randomback.
function pb_randomback_Callback(hObject, eventdata, handles)
% hObject    handle to pb_randomback (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global puzzle;
global randomback;
global randprev;

randomback = randomback+1;
set(handles.text_randomback,'string',num2str(randomback));


%find the empty box first
[blank_x,blank_y] = find(puzzle.nodenum==0);


%% generate random numbers between 1 and 4
%% 1 represents blank_x = blank_x+1
%% 2 represents blank_x = blank_x-1
%% 3 represents blank_y = blank_y+1
%% 4 represents blank_y = blank_y-1

random_source = [1 2 3 4];

if randprev==1
    random_source(randprev+1)=[];
elseif randprev==2
    random_source(randprev-1)=[];
elseif randprev==3
    random_source(randprev+1)=[];
elseif randprev==4
    random_source(randprev-1)=[];
end
        
randnum = randsrc(1,1,random_source);

% randprev = randnum;

switch randnum
    case 1
        blank_temp = blank_x+1;
        if blank_temp <= puzzle.size
            temp = puzzle.nodenum(blank_temp,blank_y);
            puzzle.nodenum(blank_temp,blank_y) = 0;
            puzzle.nodenum(blank_x,blank_y) = temp;
            randprev=1;
        else
            blank_temp = blank_x -1;
            temp = puzzle.nodenum(blank_temp,blank_y);
            puzzle.nodenum(blank_temp,blank_y) = 0;
            puzzle.nodenum(blank_x,blank_y) = temp;  
            randprev=2;
        end
    case 2
        blank_temp = blank_x-1;
        if blank_temp > 0
            temp = puzzle.nodenum(blank_temp,blank_y);
            puzzle.nodenum(blank_temp,blank_y) = 0;
            puzzle.nodenum(blank_x,blank_y) = temp;
            randprev=2;
        else
            blank_temp = blank_x +1;
            temp = puzzle.nodenum(blank_temp,blank_y);
            puzzle.nodenum(blank_temp,blank_y) = 0;
            puzzle.nodenum(blank_x,blank_y) = temp;  
            randprev=1;
        end 
        
    case 3
        blank_temp = blank_y+1;
        if blank_temp <= puzzle.size
            temp = puzzle.nodenum(blank_x,blank_temp);
            puzzle.nodenum(blank_x,blank_temp) = 0;
            puzzle.nodenum(blank_x,blank_y) = temp;
            randprev=3;
        else
            blank_temp = blank_y -1;
            temp = puzzle.nodenum(blank_x,blank_temp);
            puzzle.nodenum(blank_x,blank_temp) = 0;
            puzzle.nodenum(blank_x,blank_y) = temp;  
            randprev=4;
        end        
        
    case 4
        blank_temp = blank_y-1;
        if blank_temp > 0
            temp = puzzle.nodenum(blank_x,blank_temp);
            puzzle.nodenum(blank_x,blank_temp) = 0;
            puzzle.nodenum(blank_x,blank_y) = temp;
            randprev=4;
        else
            blank_temp = blank_y +1;
            temp = puzzle.nodenum(blank_x,blank_temp);
            puzzle.nodenum(blank_x,blank_temp) = 0;
            puzzle.nodenum(blank_x,blank_y) = temp; 
            randprev=3;
        end         
end


%%display the puzzle

for i=1:puzzle.size
    for j=1:puzzle.size
        set(puzzle.squares(i,j),'string',num2str(puzzle.nodenum(i,j)));
    end
end

%%find the square which is not assigned to a number (assigned to zero)
[blank_x,blank_y] = find(puzzle.nodenum==0);

set(puzzle.squares(blank_x,blank_y),'string','');
