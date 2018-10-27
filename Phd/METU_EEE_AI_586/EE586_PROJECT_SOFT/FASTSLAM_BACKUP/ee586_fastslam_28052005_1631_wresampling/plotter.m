figure
t=30; %time
for jj=1:no_of_particles,
    for q=1:t,
        pp(q,:)=PARTICLE_SET(q).particles(jj).pose;
    end;
    hold on;
    plot(pp(:,1),pp(:,2),'r')
end
hold on
for jj=1:no_of_particles,
    for q=1:PARTICLE_SET(t).particles(jj).no_of_landmarks,
        xm = PARTICLE_SET(t).particles(jj).landmark(q).mean;
        plot(xm(1),xm(2),'*')
    end;
end;
grid on
    