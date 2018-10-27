%%EE586 - Artificial Intelligence
%%METU - EE Spring 2006
%%Homework 2
%%Written by Salim SIRTKAYA, Barýþ TANRIVERDÝ and Bengi KOÇ

%%% Limited DFS function %%%

function [Temp_puzzle,Temp_level]=DFS_limited(currentNode, depth, goalState)
global iter;
global Solution;

iter=iter+1;
%fprintf('Current Node Level: %d\t\t\t', currentNode.level);
%fprintf('expanded node: %d\n', iter);

if currentNode.level >= depth
    Temp_level = currentNode.level;
    Temp_puzzle = currentNode;
    break;
end

if all(all(currentNode.nodenum == goalState))
    Temp_puzzle = currentNode;
    Temp_level = currentNode.level;
    break;
end

[Succ] = Successors(currentNode);

for i=1:Succ.size
    [Temp_puzzle, Temp_level] = DFS_limited(Succ.puzzle(i),depth,goalState);
    
    Solution{currentNode.level} = Succ.puzzle(i).nodenum;
    
    if all(all(Temp_puzzle.nodenum == goalState))
        %Temp_puzzle = goalState;
        break;
    end       
end