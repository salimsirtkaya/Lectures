function [Fit_array]=Population_Fitness(population,pop_count)
for member=1:pop_count
    Fit_array(member)=Fit_ind(population(member,:));
end