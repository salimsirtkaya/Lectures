% This is code for solving L-puzzle by Breadth-First Search algorithm.
% Takes an input matrix as starting state, gives 3 output as "solution",
% "t",and "expended_node".
% "solution" is the matrix including all the states from starting to goal.
% "t" is the amount of time needed for the program to reach the goal.
% "expended_node" is the number of nodes expended to reach the goal.

function [solution,t,expended_node]= Breath_First;

global puzzle;
global goalState;

input = puzzle.nodenum;
output = goalState;
input_size = puzzle.size;

% input=[3,4,6;1,0,8;7,2,5]; [solution,t,expended_node]=Breath_First(input);

t=cputime; % t keeps the starting time to measure the time needed for this algorithm to solve the puzzle.

%  defining goal for the L-puzzle:
% input_size=size(input);
% for n=1:input_size(1);
%     output(n,:)=[((n-1)*input_size(2)+1):(n*input_size(2))];
% end
% output(input_size(1),input_size(2))=0;
% end of defining goal for the L-puzzle.

%succesor hesaplama:

states(:,:,1)=input; % "states" is the matrix in which all the states are stored. First state is the input matrix.

back_pointer(1)=1; % "back_pointer" is the matrix recording the predecessor states.
% First entry of "back_pointer" matrix is "1" meaning that
% the predecessor of the first entry of "states" matrix is the first entry of "states" matrix.

goal=0; % Variable "goal" is initiated as "0". It shall be "1" when the goal is reached.

p=1; % "p" is the number of matrices stored in the states matrix.

for expended_node=1:100000; % "expended_node" is used to point the state in "states" matrix which shall be expended.
    %When the goal is reached the value of "expended_node" shows the number of expended nodes to reach the goal.

    suc=succesors(states(:,:,expended_node)); % "suc" keeps the succesors of the node expended.

    suc_size=size(suc); % "suc_size" keeps the number of succesors of the expended node.

    for i=1:suc_size(3); % This "for" loop has three main tasks: Firstly it checks for each succesor if the goal is reached or not.
        % Secondy if the goal is reached it generates the "solution" from "states" and "back_pointer" matrices.
        % And lastly if the goal is not reached it stores the succesor to "states" matrix
        % if the succesor is a state which did not exist previously in "state" matrix"

        if suc(:,:,i)==output; % Checking if the succesor is the goal state or not

            solution(:,:,1)=suc(:,:,i); % If the succesor is the goal state the first entry of the solution matrix is defined as goal.
            bp=expended_node; % If the succesor is the goal state back pointer of the goal is node being expended.

            % Generating "solution" matrix from "states" and "back_pointer" matrices.
            c=2;
            while bp~=1;
                solution(:,:,c)=states(:,:,bp);
                bp=back_pointer(bp);
                c=c+1;
            end
            solution(:,:,c)=states(:,:,1);
            % The end of generating "solution" matrix.

            t=cputime-t; % Time needed for this algorithm to solve the puzzle is calculated.

            goal=1; %Goal is reached.
        
        else
            % If the goal is not reached, checking whether the succesor is a
            % new state or not:
            k=0;
            for j=1:p;
                if suc(:,:,i) == states(:,:,j);
                    k=1;
                end
            end
        end
        
        if k==0;
            states(:,:,p+1)=suc(:,:,i); %If the succesor is a new state, it is added into "states" matrix.
            back_pointer(p+1)=expended_node; % Expended node which is the back pointer of the succesor is stored.
            p=p+1; % Numner of states stored in "states matrix is increades by 1.
        end
        
    end
    
    if goal ==1;
        break %If the goal is reached terminates the execution of the for loop.
    end
    
end



