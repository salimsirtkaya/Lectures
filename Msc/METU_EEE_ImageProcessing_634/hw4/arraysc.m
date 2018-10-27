function sca = arraysc(a,lo,hi)
% ARRAYSC  SCA=ARRAYSC(A,LO,HI) scales and maps the input array, A, linearly
%          into another array, SCA, whose upper and lower limits are set by
%          the HI and LO inputs, respectively.

max_a = max(a(:));
min_a = min(a(:));
span = max_a - min_a;
hi = double(hi);
lo = double(lo);
newspan = hi - lo;
diff = a - min_a;
sca = lo + diff*newspan/span;
%sca = round(sca);