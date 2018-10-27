function [succ1, succ2, succ3, succ4]=successor_f(A)

[l,m]=size(A);

[a,b]=find(A==0);
succ1=A;
succ2=A;
succ3=A;
succ4=A;

if a+1 <= l,
    succ1(a,b)=A((a+1),b);
    succ1(a+1,b)=0;
end;

if b+1 <= m;
    succ2(a,b)=A(a,b+1);
    succ2(a,b+1)=0;
end;

if a-1 >= 1,
    succ3(a,b)=A((a-1),b);
    succ3((a-1),b)=0;
end;

if b-1 >= 1,
    succ4(a,b)=A(a,b-1);
    succ4(a,b-1)=0;
end;

if succ1==A,
    succ1=[];
end;

if succ2==A,
    succ2=[];
end;
if succ3==A,
    succ3=[];
end;
if succ4==A,
    succ4=[];
end;
%A
%succ1
%succ2
%succ3
%succ4
