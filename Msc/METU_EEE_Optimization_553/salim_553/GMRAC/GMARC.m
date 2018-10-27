function [result]=GMARC(x0,pop_count,max_generation)
result='';
for time=1:3:1998
[x]=Genetic_Algorithm(pop_count,max_generation,x0);
result=[result;x];
x0=x(4,:);
end