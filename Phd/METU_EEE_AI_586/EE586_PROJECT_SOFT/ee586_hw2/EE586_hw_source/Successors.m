%%EE586 - Artificial Intelligence
%%METU - EE Spring 2006
%%Homework 2
%%Written by Salim SIRTKAYA, Barýþ TANRIVERDÝ and Bengi KOÇ

%%% Successors function returns the next step puzzle %%%

function [Succ]=Successors(puzzle)

%find the location of the empty box
[empty_x,empty_y]=find(puzzle.nodenum==0);

% determine the successors and number of successors
    
Succ.size=0;

tempPuzzle = puzzle;

%level of the successor is one more than the origin

if (empty_x > 1 && empty_x < puzzle.size)
    Succ.size = Succ.size + 2;
    %%create two successors
    tempPuzzle.nodenum(empty_x,empty_y) = puzzle.nodenum(empty_x+1,empty_y);
    tempPuzzle.nodenum(empty_x+1,empty_y) = puzzle.nodenum(empty_x,empty_y);
    Succ.puzzle(1)=tempPuzzle;
    
    tempPuzzle = puzzle;
   
    tempPuzzle.nodenum(empty_x,empty_y) = puzzle.nodenum(empty_x-1,empty_y);
    tempPuzzle.nodenum(empty_x-1,empty_y) = puzzle.nodenum(empty_x,empty_y);
    Succ.puzzle(2)=tempPuzzle;
    %%%%%%%%%%%%%%%%%%%%%%%
elseif (empty_x == 1)
    Succ.size = Succ.size + 1;
    %%create a successor
    tempPuzzle.nodenum(empty_x,empty_y) = puzzle.nodenum(empty_x+1,empty_y);
    tempPuzzle.nodenum(empty_x+1,empty_y) = puzzle.nodenum(empty_x,empty_y);
    Succ.puzzle(1)=tempPuzzle;
    %%%%%%%%%%%%%%%%%%%%%%%
elseif (empty_x == puzzle.size)
    Succ.size = Succ.size + 1;
    %%create a successor
    tempPuzzle.nodenum(empty_x,empty_y) = puzzle.nodenum(empty_x-1,empty_y);
    tempPuzzle.nodenum(empty_x-1,empty_y) = puzzle.nodenum(empty_x,empty_y);
    Succ.puzzle(1)=tempPuzzle;
    %%%%%%%%%%%%%%%%%%%%%%%
end

%This line is important
tempPuzzle = puzzle;

if (empty_y > 1 && empty_y < puzzle.size)
    Succ.size = Succ.size + 2;
    %%create two successors
    tempPuzzle.nodenum(empty_x,empty_y) = puzzle.nodenum(empty_x,empty_y+1);
    tempPuzzle.nodenum(empty_x,empty_y+1) = puzzle.nodenum(empty_x,empty_y);
    Succ.puzzle(Succ.size-1)=tempPuzzle;
    
    tempPuzzle = puzzle;
    
    tempPuzzle.nodenum(empty_x,empty_y) = puzzle.nodenum(empty_x,empty_y-1);
    tempPuzzle.nodenum(empty_x,empty_y-1) = puzzle.nodenum(empty_x,empty_y);
    Succ.puzzle(Succ.size)=tempPuzzle;
    %%%%%%%%%%%%%%%%%%%%%%%
elseif (empty_y == 1)
    Succ.size = Succ.size + 1;
    %%create a successor
    tempPuzzle.nodenum(empty_x,empty_y) = puzzle.nodenum(empty_x,empty_y+1);
    tempPuzzle.nodenum(empty_x,empty_y+1) = puzzle.nodenum(empty_x,empty_y);
    Succ.puzzle(Succ.size)=tempPuzzle;
    %%%%%%%%%%%%%%%%%%%%%%%
elseif (empty_y == puzzle.size)
    Succ.size = Succ.size + 1;
    %%create a successor
    tempPuzzle.nodenum(empty_x,empty_y) = puzzle.nodenum(empty_x,empty_y-1);
    tempPuzzle.nodenum(empty_x,empty_y-1) = puzzle.nodenum(empty_x,empty_y);
    Succ.puzzle(Succ.size)=tempPuzzle;    
    %%%%%%%%%%%%%%%%%%%%%%%
end

for i=1:Succ.size
    Succ.puzzle(i).level = puzzle.level+1;
end
    
    
    
    
        
