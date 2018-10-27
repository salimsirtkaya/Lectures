function [x]=Genetic_Algorithm(pop_count,max_generation,x0)
global n;
n=24;
% global x0;
population=randint(pop_count,n); %Creates initial population
Fit_array=Population_Fitness(population,pop_count,x0);%%%%%%%%%%%%
for generation=1:max_generation
    [population,Fit_array]=NewPopulation(population,Fit_array,pop_count,x0);
end
% fitness=Fitness_Evaluation(population);%%%%%%%%%%%%
fittest=find(Fit_array==max(Fit_array));
fittest=population(fittest(1),:);

% bias1=0;
mult=[2^5 2^4 2^3 2^2 2 1];
Kd=[100+sum(fittest(1:6).*mult),-30+sum(fittest(7:12).*mult),sum(fittest(13:18).*mult),-10+sum(fittest(19:24).*mult),0];
%%%%%%%biaslar ve eksiler!!!

A=[0 1 0 0 0; 0 -16 -9.8178 0 623.16; 0 0 0 1 0; -8.7478 0.15147 -3.2745 -0.02575 0; 0 -144740 0 0 -475];
B=[0 0 0 0 250]';
C=eye(5);
D=[0 0 0 0 0]';
A_fed=A-B*Kd;
B_fed=zeros(5,1);
sys_fed=ss(A_fed,B_fed,C,D);
t=0:0.01:0.03;
[y,t,x]=initial(sys_fed,x0,t);
% initial(sys_fed,x0,t);

% fitt=max(Fit_array);
%%%%%%%%%%%epsilon yazilacak....