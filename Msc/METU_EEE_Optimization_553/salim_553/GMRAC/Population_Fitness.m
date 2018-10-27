function [Fit_array]=Population_Fitness(population,pop_count,x0)
for member=1:pop_count
    Fit_array(member)=Fit_ind(population(member,:),x0);
end