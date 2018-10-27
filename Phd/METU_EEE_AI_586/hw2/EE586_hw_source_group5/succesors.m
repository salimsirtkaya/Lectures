
% Succesors Function
% 
% Given any state, this function can produce the possible puzzle moves (next states) from that
% state in the chosen representation. By using the output of this function, 
% main program (Breath_first.m) can move to those next states in the chosen representation. 
% The function can also handle L-puzzle case where L is configurable by the user.

function [suc]= succesors(pre);

% "pre" is the input matrix whose succesors are to be calculated.
% "suc" is the output matrix which includes all the succesors of the input
% matrix "pre".

pre_size=size(pre); %"pre_size" keeps the size information of the input matrix "pre"
[m,n]=find(pre==0); %[m,n] keeps the location information  of the "0 (empty)" tile in the puzzle.


% If there is no wall next to "0 (empty)" tile, number of succesors is 4.
% But if there is a wall next to "0 (empty)" tile, then it is not possible
% for "0 (empty)" tile to move to all directions.
% the following 4 if loops determines if there exist a wall or not in all
% directions ()

i=1;

if m>1 % determines if it is possible for "0 (empty)" tile to move to left.
   suc_1=pre;
   suc_1(m,n)=pre(m-1,n);
   suc_1(m-1,n)=0;
   suc(:,:,i)= suc_1;
   i=i+1;   
end

if m<pre_size(1) % determines if it is possible for "0 (empty)" tile to move to right.
   suc_2=pre;
   suc_2(m,n)=pre(m+1,n);
   suc_2(m+1,n)=0;
   suc(:,:,i)= suc_2;
   i=i+1;   
end

if n>1 % determines if it is possible for "0 (empty)" tile to move to up.
   suc_3=pre;
   suc_3(m,n)=pre(m,n-1);
   suc_3(m,n-1)=0;
   suc(:,:,i)=suc_3;
   i=i+1;   
end

if n<pre_size(2) % determines if it is possible for "0 (empty)" tile to move to down.
   suc_4=pre;
   suc_4(m,n)=pre(m,n+1);
   suc_4(m,n+1)=0;
   suc(:,:,i)= suc_4;
end
