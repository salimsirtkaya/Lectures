function newPARTICLE_SET = ResampleParticles(auxPARTICLE_SET)

global no_of_particles;
sum=0;
for i=1:no_of_particles,
    sum = sum + auxPARTICLE_SET.particles(i).impFact;
end;
for i=1:no_of_particles,
    weight(i) = auxPARTICLE_SET.particles(i).impFact / sum;
end;
   
alphabet = linspace(1, no_of_particles, no_of_particles);
new_alphabet = randsrc (1,no_of_particles,[alphabet; weight]);  

for i=1:no_of_particles,
    newPARTICLE_SET.particles(i) = auxPARTICLE_SET.particles(new_alphabet(i));
end;


    
