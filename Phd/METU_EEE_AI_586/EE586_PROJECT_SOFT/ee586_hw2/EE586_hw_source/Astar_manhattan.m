
function [t, node] = Astar_manhattan();

global puzzle;
global goalState;
global Solution;
global solutionLevel;

goal = goalState;
start = puzzle.nodenum;

tic;
%
%goal=[1 2 3 4; 5 6 7 8;9 10 11 12; 13 14 15 0];
%start=[7 2 8 3; 1 5 0 4;9 6 10 12; 13 14 11 15];
[dim, dim2]=size(start);
%}


%init
warning off all;
i=1; %indice of st structure, holds closed states. points to next empty st.
st(i).state=start;
st(i).pred=zeros(dim,dim);
A=st(i).state;

%Find the distance to goal.
mh=manh_dist_f(A,goal);
%mh=misp_dist_f(A,goal);

st(i).h=mh;
st(i).g=0;
st(i).f=st(i).h+st(i).g;
i=i+1;

r=1; %indice of opened states. points to the next empty state.
%opened(r)=st(r);

jj=1; 


%end init
node=0;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
test=0;
for x=1:10000,   %<<<<<<<<--------------------<<<<<<<<<----------------LOOP

test=test+1;
%will loop

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Here we form an array, which stores the f values of the closed states. 
 
F=[];


for j=1:length(st),
    F=[F st(j).f];
end;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%Here we find the state that has min. f value and then we pop it.

[fmin,fmin_ptr]=min(F,[],2); 

pop=st(fmin_ptr); %the state that will be popped.


%if the goal is reached, stop and return the solution.
if all(all(pop.state==goal)),   %<<<<<---------------------<<<<<----------|
    solution=[];
    S=pop;
    step_num=0;
    while ~all(all(S.state == start)),
        solution=[solution, S.state]; 
        dummy=S.pred;
        for j=1:length(opened),
            if all(all(opened(j).state==dummy)),
                step_num=step_num+1; %shows the number of movements. 
                break;
            end;
        end;
        
        if ~all(all(opened(j).state == 0)),
            S=opened(j);
            opened(j)=[];
        end;
    end;
    solution=[solution, start];
        
    Solution = cell(step_num,1);
    solution_level = step_num;
    
    for i=1:solution_level
        Solution{solution_level-i+1} = solution(:,(i-1)*dim+1:i*dim);
    end
    
    break;
end;



                
    
%remove the popped state from closed

st(fmin_ptr)=[];
i=i-1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%store the popped state in opened states set.
opened(r)=pop;
r=r+1;



[a1, a2, a3, a4]=successor_f(pop.state);



%
a=10;
b=10;
if ~isempty(a1),
    node=node+1;
    %check if state a1 is visited before ?????
    for k=1:(length(st)),
        a=all(all((st(k).state==a1)));
        if a==1,
            kk=k; %kk points to the state in closed which is equal to a1.
            break;
        end;
    end;
    if a~=1,
        for k=1:length(opened),
            b=all(all(opened(k).state==a1));
            if b==1,
                kb=k; %kb points to the state in opened which is equal to a1
                break;
            end;
        end;
    end;
    
    if (a~=1) & (b~=1), %the a1 state is encountered for the first time
        
        st(i).state=a1;
        st(i).pred=pop.state;
        st(i).h=manh_dist_f(st(i).state,goal);
        
        st(i).g=pop.g+1;
        
        st(i).f=st(i).h+st(i).g;
        i=i+1;
        
    elseif a==1 & (st(kk).f > (manh_dist_f(a1,goal)+pop.g+1)), %a1 is already in closed and f of a1 is less.
        st(kk).g=pop.g+1;
        st(kk).f=(st(kk).h+st(kk).g);
        st(kk).pred=pop.state;
    elseif ((b==1) & (opened(kb).f > (manh_dist_f(a1,goal)+pop.g+1))), %a1 is already in opened and f of a1 is less.
        opened(kb)=[]; %remove previous from opened.
        r=r-1;
        st(i).state=a1;%add to closed with new heuristic and cost.
        st(i).pred=pop.state;
        st(i).h=manh_dist_f(st(i).state,goal);
        
        st(i).g=pop.g+1;
        
        st(i).f=st(i).h+st(i).g;
        i=i+1;
    end;

end;



a=10;
b=10;

%%%%
if ~isempty(a2),
    node=node+1;
    %check if state a1 is visited before ?????
    for k=1:(length(st)),
        a=all(all((st(k).state==a2)));
        if a==1,
            kk=k; %kk points to the state which is equal to a1.
            break;
        end;
    end;
    if (a~=1),
        for k=1:length(opened),
            b=all(all(opened(k).state==a2));
            if b==1,
                kb=k;
                break;
            end;
        end;
    end;
    
    if (a~=1) & (b~=1), %the a2 state is encountered for the first time
        
        st(i).state=a2;
        st(i).pred=pop.state;
        st(i).h=manh_dist_f(st(i).state,goal);
        
        st(i).g=pop.g+1;
        
        st(i).f=st(i).h+st(i).g;
        i=i+1;
        
    elseif a==1 & (st(kk).f > (manh_dist_f(a2,goal)+pop.g+1)), %a2 is already in closed and f of a2 is less.
        st(kk).g=pop.g+1;
        st(kk).f=(st(kk).h+st(kk).g);
        st(kk).pred=pop.state;
        
    elseif ((b==1) & (opened(kb).f > (manh_dist_f(a2,goal)+pop.g+1))), %a2 is already in opened and f of a2 is less.,
        opened(kb)=[]; %remove previous from opened.
        r=r-1;
        st(i).state=a2;%add to closed with new heuristic and cost.
        st(i).pred=pop.state;
        st(i).h=manh_dist_f(st(i).state,goal);
        
        st(i).g=pop.g+1;
        
        st(i).f=st(i).h+st(i).g;
        
        i=i+1
    end;
end;




%%%%

a=10;
b=10;
if ~isempty(a3),
    node=node+1;
    %check if state a1 is visited before ?????
    for k=1:(length(st)),
        a=all(all((st(k).state==a3)));
        if a==1,
            kk=k; %kk points to the state which is equal to a3.
            break;
        end;
    end;
    if (a~=1),
        for k=1:length(opened),
            b=all(all(opened(k).state==a3));
            if b==1,
                kb=k;
                break;
            end;
        end;
    end;
    
    if (a~=1) & (b~=1), %the a3 state is encountered for the first time
        
        st(i).state=a3;
        st(i).pred=pop.state;
        st(i).h=manh_dist_f(st(i).state,goal);
        
        st(i).g=pop.g+1;
        
        st(i).f=st(i).h+st(i).g;
        
        i=i+1;
        
    elseif a==1 & (st(kk).f > (manh_dist_f(a3,goal)+pop.g+1)), %a3 is already in closed and f of a3 is less.
        st(kk).g=pop.g+1;
        st(kk).f=(st(kk).h+st(kk).g);
        st(kk).pred=pop.state;
    elseif ((b==1) & (opened(kb).f > (manh_dist_f(a3,goal)+pop.g+1))), %a3 is already in opened and f of a3 is less.,
        opened(kb)=[]; %remove previous from opened.
        r=r-1;
        st(i).state=a3;%add to closed with new heuristic and cost.
        st(i).pred=pop.state;
        st(i).h=manh_dist_f(st(i).state,goal);
        
        st(i).g=pop.g+1;
        
        st(i).f=st(i).h+st(i).g;
        
        i=i+1;
    end;

end;



%%%%

a=10;
b=10;
if ~isempty(a4),
    node=node+1;
    %check if state a1 is visited before ?????
    for k=1:(length(st)),
        a=all(all((st(k).state==a4)));
        if a==1,
            kk=k; %kk points to the state which is equal to a4.
            break;
        end;
    end;
    if (a~=1),
        for k=1:length(opened),
            b=all(all(opened(k).state==a4));
            if b==1,
                kb=k;
                break;
            end;
        end;
    end;
    
    if (a~=1) & (b~=1), %the a4 state is encountered for the first time
        
        st(i).state=a4;
        st(i).pred=pop.state;
        st(i).h=manh_dist_f(st(i).state,goal);
        
        st(i).g=pop.g+1;
        
        st(i).f=st(i).h+st(i).g;
        
        i=i+1;
           
    elseif a==1 & (st(kk).f > (manh_dist_f(a4,goal)+pop.g+1)), %a4 is already in closed and f of a4 is less.
        st(kk).g=pop.g+1;
        st(kk).f=(st(kk).h+st(kk).g);
        st(kk).pred=pop.state;
        
    elseif ((b==1) & (opened(kb).f > (manh_dist_f(a4,goal)+pop.g+1))), %a4 is already in opened and f of a4 is less.
        opened(kb)=[]; %remove previous from opened.
        r=r-1;
        st(i).state=a4;%add to closed with new heuristic and cost.
        st(i).pred=pop.state;
        st(i).h=manh_dist_f(st(i).state,goal);
        
        st(i).g=pop.g+1;
        
        st(i).f=st(i).h+st(i).g;
        
        i=i+1;
        
    end;

end;





%}

end;
toc;


t=toc;

mem=length(st)+length(opened);
