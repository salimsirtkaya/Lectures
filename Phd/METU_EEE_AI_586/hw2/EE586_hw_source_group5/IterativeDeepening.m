%%EE586 - Artificial Intelligence
%%METU - EE Spring 2006
%%Homework 2
%%Written by Salim SIRTKAYA, Barýþ TANRIVERDÝ and Bengi KOÇ

%%% Iterative deepening function %%%

function [result]=IterativeDeepening(puzzle,goalState, maxDepth)

depth=0;

global iter;
global Solution;
global solutionLevel;
global stop_sign;
global pause_sign;
Solution = cell(maxDepth,1);

iter=0;

Solution{1}=puzzle.nodenum;

currentNode=puzzle;

for depth=1:maxDepth
    if stop_sign==0
        iter=0;
        [Temp_puzzle, Temp_level]=DFS_limited(currentNode, depth, goalState);
       % fprintf('***************************************************\n');
       % fprintf('SEARCH DEPTH %d\n', depth);
        if all(all(Temp_puzzle.nodenum == goalState))
            result=1;
            solutionLevel = Temp_level;
            break;
        end
        
        if Temp_level==maxDepth
            result=0;
            break;
        end
        currentNode = puzzle;
        
    elseif stop_sign==1
        result=0;
        break
    end
end



