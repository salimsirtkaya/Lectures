
function [result]=DFS_main(puzzle,goalState, maxDepth)

global iter;
global Solution;
global solutionLevel;
Solution = cell(maxDepth,1);
iter=0;

Solution{1}=puzzle.nodenum;

currentNode=puzzle;

[Temp_puzzle, Temp_level]=DFS_limited(currentNode, maxDepth, goalState);

if all(all(Temp_puzzle.nodenum == goalState))
    result=1;
    solutionLevel = Temp_level;
    break;
else
    result=0;
end



