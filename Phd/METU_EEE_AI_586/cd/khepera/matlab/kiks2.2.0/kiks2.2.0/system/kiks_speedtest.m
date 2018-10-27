% -----------------------------------------------------
%  (c) 2000-2004 Theodor Storm <theodor@tstorm.se>
%  http://www.tstorm.se
% -----------------------------------------------------

function res=kiks_speedtest(niter)
kiks_status('Testing Matlab speed on this computer');
if nargin<1 niter=4; end;

res=Inf;
for iter=1:niter
    t0=cputime;
    for i=1:10
        A=ones(i*10,i*10);
        for j=1:2:50
            A(i:i*10-i,i:i*10-i)=j^j;
            B=round(sin(A)*j);
            C=round(cos(A)*j);
            D=sqrt((B*C)+A);
        end;
        E=filter2([0 1 0; 1 1 1; 0 1 0]/5,A+B-C-D);
        kiks_status(['Testing Matlab speed on this computer' char(ones(1,i)*'.')]);
    end;
    bres=cputime-t0;
    kiks_status(sprintf('Test #%d: %2.2f',iter,bres));
    if bres<res res=bres; end;
end;
kiks_status(sprintf('Best result: %2.2f, test finished.',res));