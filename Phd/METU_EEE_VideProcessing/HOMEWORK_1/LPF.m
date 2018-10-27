  
function h= LPF(l1,l2);
[f1,f2] = freqspace([240 288]);
        Hd = ones(240,288);
        
        Hd((f1<l1) | (f1>l2)) = 0;
        Hd((f2<l1) | (f2>l2)) = 0;
        win = fspecial('gaussian',[240,288],0.5);
        win = win ./ max(win(:));  % Make the maximum window value be 1.
        h = fwind2(Hd,win);
       % figure;
       % freqz2(h);
 