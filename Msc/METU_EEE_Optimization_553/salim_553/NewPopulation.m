function [population,Fit_array]=NewPopulation(population,Fit_array,pop_count)
global n;
% %remainder stochastic sampling
% avg_fitness=sum(fitness)/pop_count;
% likelihood=fitness./avg_fitness;
% select_count=fix(likelihood);
% choose_loc=(1/n)*ones(1,n);
% for choice=1:n
%     location=randsrc(1,1,[1:n;choose_loc]);
%     population(location)
likelihood=Fit_array./sum(Fit_array);
for person=1:pop_count
    mating_pool(person,:)=population(randsrc(1,1,[1:pop_count;likelihood]),:);
end

%population=mating_pool;
for parent=1:2:pop_count/2  %%%%%%%%%%%
    [child1,child2]=Breed(parent,parent+1,mating_pool);
    value=Fit_ind(child1);
    if gt(value,min(Fit_array))
        replace=find(Fit_array==min(Fit_array));
        population(replace(1),:)=child1;
        Fit_array(replace(1))=value;
    end
    value=Fit_ind(child2);
    if gt(value,min(Fit_array))
        replace=find(Fit_array==min(Fit_array));
        population(replace(1),:)=child2;
        Fit_array(replace(1))=value;
    end    
end