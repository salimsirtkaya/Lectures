function [st, opened, i, r]=visit(a1, st, opened, i, pop, goal, r)

a=7;
b=7;

    %check if state a1 is visited before
    for k=1:(length(st)),
        a=all(all((st(k).state==a1)));
        if a==1,
            kk=k; %kk points to the state in closed which is equal to a1.
            break;
        end;
    end;
    if a~=1,
        for k=1:length(opened),
            b=all(all(opened(k).state==a1));
            if b==1,
                kb=k; %kb points to the state in opened which is equal to a1
                break;
            end;
        end;
    end;
    
    if (a~=1) & (b~=1), %the a1 state is encountered for the first time
        
        st(i).state=a1;
        st(i).pred=pop.state;
        st(i).h=misp_dist_f(st(i).state,goal); %<<------distance method !!!
        
        st(i).g=pop.g+1;
        
        st(i).f=st(i).h+st(i).g;
        i=i+1;
        
    elseif a==1, %a1 is already in closed
        st(kk).g=min(st(kk).g, (pop.g+1));
        st(kk).f=(st(kk).h+st(kk).g);
    elseif ((b==1) & (opened(kb).f > (manh_dist_f(a1,goal)+pop.g+1))), %a1 is already opened and f of a1 is less.
        opened(kb)=[]; %remove previous from opened.
        r=r-1;
        st(i).state=a1;%add to closed with new heuristic and cost.
        st(i).pred=pop.state;
        st(i).h=misp_dist_f(st(i).state,goal); %<<------distance method !!!
        
        st(i).g=pop.g+1;
        
        st(i).f=st(i).h+st(i).g;
        i=i+1;
    end;
