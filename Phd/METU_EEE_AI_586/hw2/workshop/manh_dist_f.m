function man_dist=manh_dist_f(A,goal)

[a,b]=size(A);

dummy=A-goal;
dummy=dummy./dummy;
dummy=isfinite(dummy);

dummy=A.*dummy;

[a,b]=find(dummy ~= 0);


man_dist=0;
for i=1:length(a),
    [c,d]=find(goal==dummy(a(i),b(i)));
    man_dist=man_dist+(abs(a(i)-c)+abs(b(i)-d));
end;