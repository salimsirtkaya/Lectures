function dist=misp_dist_f(A,goal)


dummy=A-goal;
dummy=isfinite(dummy./dummy);
dist=sum(sum(dummy));
