function []=solve_onestep(ind);

global puzzle;
global iter;
global Solution;
global solutionLevel;

temp = Solution{ind};
      
    for i=1:puzzle.size
        for j=1:puzzle.size
            set(puzzle.squares(i,j),'string',num2str(temp(i,j)));
        end
    end
    
    %%find the square which is not assigned to a number (assigned to zero)
    [blank_x,blank_y] = find(temp==0);
    
    set(puzzle.squares(blank_x,blank_y),'string','');
