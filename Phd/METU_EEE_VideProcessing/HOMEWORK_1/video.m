a=aviread('82.avi');
a1=a(1).cdata;
a2=a(2).cdata;
a1r=a1(:,:,1);
a1g=a1(:,:,2);
a1b=a1(:,:,3);
a2r=a2(:,:,1);
a2g=a2(:,:,2);
a2b=a2(:,:,3);
a1r=double(a1r);
a1g=double(a1g);
a1b=double(a1b);
a2r=double(a2r);
a2g=double(a2g);
a2b=double(a2b);

y1=0.299*a1r+0.587*a1g+0.114*a1b;
i1=0.596*a1r-0.275*a1g-0.321*a1b;
q1=0.212*a1r-0.523*a1g+0.311*a1b;
y2=0.299*a2r+0.587*a2g+0.114*a2b;
i2=0.596*a2r-0.275*a2g-0.321*a2b;
q2=0.212*a2r-0.523*a2g+0.311*a2b;
y1u=uint8(y1); y2u=uint8(y2);
i1u=uint8(i1); i2u=uint8(i2);
q1u=uint8(q1); q2u=uint8(q2);

figure;
subplot(1,3,1); imshow(y1);
subplot(1,3,2); imshow(i1);
subplot(1,3,3); imshow(q1);

figure;
subplot(1,3,1); imshow(y2u);
subplot(1,3,2); imshow(i2u);
subplot(1,3,3); imshow(q2u);

hy=LPF(0,(4.2/5.45));
hi=LPF(0,(1.5/5.45));
hq=LPF(0,(0.5/5.45));

%fy1=y1.*hy;
%fi1=i1.*hi;
%fq1=q1.*hq;
fy1=filter2(hy,y1)
fi1=filter2(hi,i1);
fq1=filter2(hq,q1);


for i=1:240
    for j=1:288
        fi1t(i,j)=fi1(i,j)*cos(2*pi*4830000/(288*240*5450000)*((i-1)*288+j));
    end
end
for i=1:240
    for j=1:288
        fq1t(i,j)=fq1(i,j)*sin(2*pi*4830000/(288*240*5450000)*((i-1)*288+j));
    end
end

ftt=fq1t+fi1t;

 ht=LPF(2/5.45,4.2/5.45);
 fftt=filter2(ftt,ht);
com=fftt+fy1;


ys=filter2(hy,com);
c2=com-ys;
for i=1:240
    for j=1:288
        ci(i,j)=c2(i,j)*2*cos(2*pi*4830000/(288*240*5450000)*((i-1)*288+j));
    end
end
for i=1:240
    for j=1:288
        cq(i,j)=c2(i,j)*2*sin(2*pi*4830000/(288*240*5450000)*((i-1)*288+j));
    end
end

is=filter2(hi,ci);
qs=filter2(hq,cq);
figure;
subplot(1,3,1); imshow(ys);
subplot(1,3,2); imshow(is);
subplot(1,3,3); imshow(qs);







