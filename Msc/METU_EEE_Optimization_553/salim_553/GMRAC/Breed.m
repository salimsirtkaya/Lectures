function [child1,child2]=Breed(p1,p2,population)
global n; %n is the length of the strings in the population
crossover=round(rand*(n-3))+2;
%Generates a random index between 2 and length_of_the_string-1.
% From crossover on, the genes of the parents will be interchanged.
% The generation of the index is arranged such that at least 1 gene will be interchanged.

% p_temp=population(p1,crossover:n);
% population(p1,crossover:n)=population(p2,crossover:n);
% population(p2,crossover:n)=p_temp;

child1(1:crossover-1)=population(p1,1:crossover-1);
child2(1:crossover-1)=population(p2,1:crossover-1);
child1(crossover:n)=population(p2,crossover:n);
child2(crossover:n)=population(p1,crossover:n);

child1=MutateGenotypes(child1);
child2=MutateGenotypes(child2);