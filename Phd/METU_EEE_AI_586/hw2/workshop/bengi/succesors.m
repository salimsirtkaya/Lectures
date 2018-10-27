%succesor hesaplama:
function [suc]= succesors(pre);

pre_size=size(pre);
[m,n]=find(pre==-1);

i=1;
if m>1
   suc_1=pre;
   suc_1(m,n)=pre(m-1,n);
   suc_1(m-1,n)=-1;
   suc(:,:,i)= suc_1;
   i=i+1;   
end

if m<pre_size(1)
   suc_2=pre;
   suc_2(m,n)=pre(m+1,n);
   suc_2(m+1,n)=-1;
   suc(:,:,i)= suc_2;
   i=i+1;   
end

if n>1
   suc_3=pre;
   suc_3(m,n)=pre(m,n-1);
   suc_3(m,n-1)=-1;
   suc(:,:,i)=suc_3;
   i=i+1;   
end

if n<pre_size(2)
   suc_4=pre;
   suc_4(m,n)=pre(m,n+1);
   suc_4(m,n+1)=-1;
   suc(:,:,i)= suc_4;
end
