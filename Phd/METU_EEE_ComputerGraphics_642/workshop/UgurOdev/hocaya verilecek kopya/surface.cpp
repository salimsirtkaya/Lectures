//-------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include "deneme1.h"
#include <math.h>
#include <stdio.h>
#include "surface.h"
//---------------------------------------------------------------------------
double  b1,b2,b3,b4,b11,b22,b33,b44;
double Mz[4][4],U[1][5],W[4],M1x[1][5],M1y[1][5],M1z[1][5];
double extern Mx[4][4],My[4][4];
extern double  x1,x2,y1,y2,z1,z2,xx1,xx2,yy1,yy2,zz1,zz2,x3,y3,z3,a1,a2,a3,aa1,aa2,aa3,aaa1,aaa2,aaa3;
extern double P[4][3],B[4][3],BBx[5][3],BBy[5][3],BBz[5][3];
extern int surfaceindex,order;
extern double nsegs1,nsegs2;
extern double xknot[200];
extern void light_selected_yellow(int x,int y,int mode);
extern double calculateN(int i,double t,int k);
double sumx,sumy,sumz;
extern FILE *dosya,*dosya2;
void bilinearsurface(void)
{
  double u=0,w=0;
  double qx,qy,qz;
  double du=1/nsegs1;
  double dw=1/nsegs2;

  int i,k;
  for( k=0,u=0;k<=nsegs1;k++,u+=du)
  {
   qx=(1-u)*(1-w)*P[0][0]+(1-u)*w*P[1][0]+(1-w)*u*P[2][0]+u*w*P[3][0];
   qy=(1-u)*(1-w)*P[0][1]+(1-u)*w*P[1][1]+(1-w)*u*P[2][1]+u*w*P[3][1];
   qz=(1-u)*(1-w)*P[0][2]+(1-u)*w*P[1][2]+(1-w)*u*P[2][2]+u*w*P[3][2];
   Form1->PaintBox1->Canvas->MoveTo(qx,qy);
   for( i=0,w=0;i<=nsegs2;i++,w+=dw)
   {
   qx=(1-u)*(1-w)*P[0][0]+(1-u)*w*P[1][0]+(1-w)*u*P[2][0]+u*w*P[3][0];
   qy=(1-u)*(1-w)*P[0][1]+(1-u)*w*P[1][1]+(1-w)*u*P[2][1]+u*w*P[3][1];
   qz=(1-u)*(1-w)*P[0][2]+(1-u)*w*P[1][2]+(1-w)*u*P[2][2]+u*w*P[3][2];
   Form1->PaintBox1->Canvas->LineTo(qx,qy);
   }
   w=w-dw;
   }
//****
w=0;
u=0;
for( k=0,w=0;k<=nsegs1;k++,w+=dw)
  {
   qx=(1-u)*(1-w)*P[0][0]+(1-u)*w*P[1][0]+(1-w)*u*P[2][0]+u*w*P[3][0];
   qy=(1-u)*(1-w)*P[0][1]+(1-u)*w*P[1][1]+(1-w)*u*P[2][1]+u*w*P[3][1];
   qz=(1-u)*(1-w)*P[0][2]+(1-u)*w*P[1][2]+(1-w)*u*P[2][2]+u*w*P[3][2];
   Form1->PaintBox1->Canvas->MoveTo(qx,qy);
   for( i=0,u=0;i<=nsegs2;i++,u+=du)
   {
   qx=(1-u)*(1-w)*P[0][0]+(1-u)*w*P[1][0]+(1-w)*u*P[2][0]+u*w*P[3][0];
   qy=(1-u)*(1-w)*P[0][1]+(1-u)*w*P[1][1]+(1-w)*u*P[2][1]+u*w*P[3][1];
   qz=(1-u)*(1-w)*P[0][2]+(1-u)*w*P[1][2]+(1-w)*u*P[2][2]+u*w*P[3][2];
   Form1->PaintBox1->Canvas->LineTo(qx,qy);
   }
   u=u-du;
   }
   }

//--------------------------------------------------------------------------
void rulecubic(void)
{
int i;
double u,dx;

double du=1/nsegs1;
//Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->MoveTo(P[0][0],P[0][1]);
xx1=200;
xx2=10;
//dx=sqrt((P[1][0]-P[0][0])*(P[1][0]-P[0][0])+(P[1][1]-P[0][1])*(P[1][1]-P[0][1])+(P[1][2]-P[0][2])*(P[1][2]-P[0][2]));
B[0][0]=P[0][0];
B[0][1]=P[0][1];
B[0][2]=P[0][2];
dx=1;
b3=3*(P[1][0]-P[0][0])/(dx*dx)-2*(xx1)/dx-xx2/dx;
b4=2*(P[0][0]-P[1][0])/(dx*dx*dx)+(xx1)/(dx*dx)+xx2/(dx*dx);
b33=3*(P[1][1]-P[0][1])/(dx*dx)-2*(xx1)/dx-xx2/dx;
b44=2*(P[0][1]-P[1][1])/(dx*dx*dx)+(xx1)/(dx*dx)+xx2/(dx*dx);
B[2][0]=b3;
B[2][1]=b33;
B[3][0]=b4;
B[3][1]=b44;
for(i=0,u=0;i<=nsegs1;i++,u+=du)
{
b1=P[0][0]+xx1*u+b3*u*u+b4*u*u*u;
b2=P[0][1]+xx1*u+b33*u*u+b44*u*u*u;
Form1->PaintBox1->Canvas->LineTo(b1,b2);
}
}
//-------------------------------------------------------------------------
void ruledsurface(void)
{
double u=0,du,dw,qx,qy,qz,w=0;
int k,i;
du=1/nsegs1;
dw=1/nsegs1;
  for( k=0,u=0;k<=nsegs1;k++,u+=du)
  {
   qx=(a1+xx1*u+a2*u*u+a3*u*u*u)*(1-w)+(B[0][0]+xx1*u+B[2][0]*u*u+B[3][0]*u*u*u)*w;
   qy=(aa1+xx1*u+aa2*u*u+aa3*u*u*u)*(1-w)+(B[0][1]+xx1*u+B[2][1]*u*u+B[3][1]*u*u*u)*w;
   qz=(aaa1+xx1*u+aaa2*u*u+aaa3*u*u*u)*(1-w)+(B[0][2]+xx1*u+B[2][2]*u*u+B[3][2]*u*u*u)*w;
   Form1->PaintBox1->Canvas->MoveTo(qx,qy);
   for( i=0,w=0;i<=nsegs1;i++,w+=dw)
   {
   qx=(a1+xx1*u+a2*u*u+a3*u*u*u)*(1-w)+(B[0][0]+xx1*u+B[2][0]*u*u+B[3][0]*u*u*u)*w;
   qy=(aa1+xx1*u+aa2*u*u+aa3*u*u*u)*(1-w)+(B[0][1]+xx1*u+B[2][1]*u*u+B[3][1]*u*u*u)*w;
   qz=(aaa1+xx1*u+aaa2*u*u+aaa3*u*u*u)*(1-w)+(B[0][2]+xx1*u+B[2][2]*u*u+B[3][2]*u*u*u)*w;
   Form1->PaintBox1->Canvas->LineTo(qx,qy);
   }
   w=0;
 }
//****
w=0;
u=0;
for( k=0,w=0;k<=nsegs1;k++,w+=dw)
  {
   qx=(a1+xx1*u+a2*u*u+a3*u*u*u)*(1-w)+(B[0][0]+xx1*u+B[2][0]*u*u+B[3][0]*u*u*u)*(w);
   qy=(aa1+xx1*u+aa2*u*u+aa3*u*u*u)*(1-w)+(B[0][1]+xx1*u+B[2][1]*u*u+B[3][1]*u*u*u)*(w);
   qz=(aaa1+xx1*u+aaa2*u*u+aaa3*u*u*u)*(1-w)+(B[0][2]+xx1*u+B[2][2]*u*u+B[3][2]*u*u*u)*(w);
   Form1->PaintBox1->Canvas->MoveTo(qx,qy);
   for( i=0,u=0;i<=nsegs1;i++,u+=du)
   {
   qx=(a1+xx1*u+a2*u*u+a3*u*u*u)*(1-w)+(B[0][0]+xx1*u+B[2][0]*u*u+B[3][0]*u*u*u)*(w);
   qy=(aa1+xx1*u+aa2*u*u+aa3*u*u*u)*(1-w)+(B[0][1]+xx1*u+B[2][1]*u*u+B[3][1]*u*u*u)*(w);
   qz=(aaa1+xx1*u+aaa2*u*u+aaa3*u*u*u)*(1-w)+(B[0][2]+xx1*u+B[2][2]*u*u+B[3][2]*u*u*u)*(w);
   Form1->PaintBox1->Canvas->LineTo(qx,qy);
   }
   u=0;
   }
}
//-----------------------------------------------------------------------------
void bicubicsurface(void)
{
 double u=0,w=0;
 double qx,qy,qz;
 double  du=1/nsegs1;
 double dw=1/nsegs2;
 int r,e,s;

 //initialize M matrices

if((dosya=fopen("bicubic.txt","r"))==NULL)
ShowMessage("Can not open the data file 'bicubic.txt'!");
else
{//can reach the file
//initialize M matrix
 for(int t=0;t<4;t++)
{
 for(int i=0;i<4;i++)
 {
  fscanf(dosya,"%d %d %d\n",&r,&e,&s);
  Mx[i][t]=r;
  My[i][t]=e;
  Mz[i][t]=s;
 }
}
//**
//**
fclose(dosya);
int i,k;
//******
for( i=0,u=0;i<=nsegs1;i++,u+=du)
{
 U[0][0]=2*u*u*u-3*u*u+1;
 U[0][1]=-2*u*u*u+3*u*u;
 U[0][2]=u*u*u-2*u*u+u;
 U[0][3]=u*u*u-u*u;
 //multiply U*M
 for(int t=0;t<4;t++)
 {
  sumx=sumy=sumz=0;
  for(int wq=0;wq<4;wq++)
  {
sumx=U[0][wq]*Mx[wq][t]+sumx;
sumy=U[0][wq]*My[wq][t]+sumy;
sumz=U[0][wq]*Mz[wq][t]+sumz;
if(wq==3)
{
M1x[0][t]=sumx;
M1y[0][t]=sumy;
M1z[0][t]=sumz;
}
  }
}
//
sumx=sumy=sumz=0;
Form1->PaintBox1->Canvas->MoveTo(M1x[0][0],M1y[0][0]);
for( k=0,w=0;k<=nsegs2;k++,w+=dw)
{
 W[0]=2*w*w*w-3*w*w+1;
 W[1]=-2*w*w*w+3*w*w;
 W[2]=w*w*w-2*w*w+w;
 W[3]=w*w*w-w*w;
 for(int t=0;t<4;t++)
 {
  sumx=(M1x[0][t])*W[t]+sumx;
  sumy=(M1y[0][t])*W[t]+sumy;
  sumz=(M1z[0][t])*W[t]+sumz;
 }
qx=sumx;
qy=sumy;
qz=sumz;
sumx=sumy=sumz=0;
Form1->PaintBox1->Canvas->LineTo(qx,qy);
}
w=0;
}
//----
for(i=0,w=0;i<=nsegs1;i++,w+=dw)
{
 W[0]=2*w*w*w-3*w*w+1;
 W[1]=-2*w*w*w+3*w*w;
 W[2]=w*w*w-2*w*w+w;
 W[3]=w*w*w-w*w;
 Form1->PaintBox1->Canvas->MoveTo(Mx[0][0],My[0][0]);
 for( k=0,u=0;k<=nsegs1;k++,u+=du)
{
 U[0][0]=2*u*u*u-3*u*u+1;
 U[0][1]=-2*u*u*u+3*u*u;
 U[0][2]=u*u*u-2*u*u+u;
 U[0][3]=u*u*u-u*u;
 //multiply U*M
 for(int t=0;t<4;t++)
 {
  sumx=sumy=sumz=0;
  for(int wq=0;wq<4;wq++)
  {
sumx=U[0][wq]*Mx[wq][t]+sumx;
sumy=U[0][wq]*My[wq][t]+sumy;
sumz=U[0][wq]*Mz[wq][t]+sumz;
if(wq==3)
{
M1x[0][t]=sumx;
M1y[0][t]=sumy;
M1z[0][t]=sumz;
sumx=sumy=sumz=0;
}
 }
}
 for(int t=0;t<4;t++)
 {
  sumx=(M1x[0][t])*W[t]+sumx;
  sumy=(M1y[0][t])*W[t]+sumy;
  sumz=(M1z[0][t])*W[t]+sumz;
 }
qx=sumx;
qy=sumy;
qz=sumz;
sumx=sumy=sumz=0;
Form1->PaintBox1->Canvas->LineTo(qx,qy);
}
}
}
}
//-----------------------------------------------------------------------------
void beziersurface(void)
{
double w=0,u=0,du,dw;
du=dw=1/nsegs1;
int i,k;

for(i=0,u=0;i<=nsegs1;i++,u+=du)
{
 U[0][0]=(1-u)*(1-u)*(1-u)*(1-u);
 U[0][1]=4*u*(1-u)*(1-u)*(1-u);
 U[0][2]=6*u*u*(1-u)*(1-u);
 U[0][3]=4*u*u*u*(1-u);
 U[0][4]=u*u*u*u;
sumx=sumy=sumz=0;
for(int t=0;t<3;t++)
{
for(int j=0;j<=4;j++)
{
sumx=(U[0][j])*BBx[j][t]+sumx;
sumy=(U[0][j])*BBy[j][t]+sumy;
sumz=(U[0][j])*BBz[j][t]+sumz;
if(j==4)
{
M1x[0][t]=sumx;
M1y[0][t]=sumy;
M1z[0][t]=sumz;
}
}
sumx=sumy=sumz=0;
}
Form1->PaintBox1->Canvas->MoveTo(M1x[0][0],M1y[0][0]);
for(k=0,w=0;k<=nsegs1;k++,w+=dw)
{
W[0]=(1-w)*(1-w);
W[1]=2*(1-w)*w;
W[2]=w*w;

 sumx=sumy=sumz=0;
 for(int r=0;r<3;r++)
 {
 sumx=(M1x[0][r])*W[r]+sumx;
 sumy=(M1y[0][r])*W[r]+sumy;
 sumz=(M1z[0][r])*W[r]+sumz;
 }
 Form1->PaintBox1->Canvas->LineTo(sumx,sumy);
}
w=0;
}
//--
u=0;
for(i=0,w=0;i<=nsegs1;i++,w+=dw)
{
W[0]=(1-w)*(1-w);
W[1]=2*(1-w)*w;
W[2]=w*w;
//Form1->PaintBox1->Canvas->MoveTo((1-w)*(1-w)*BBx[0][0],(1-w)*(1-w)*BBy[0][0]);
x1=BBx[0][0]*(1-w)*(1-w)+BBx[0][1]*(2*(1-w)*w)+BBx[0][2]*w*w;
y1=BBy[0][0]*(1-w)*(1-w)+BBy[0][1]*(2*(1-w)*w)+BBy[0][2]*w*w;
Form1->PaintBox1->Canvas->MoveTo(x1,y1);
for(k=0,u=0;k<=nsegs1;k++,u+=du)
{
 U[0][0]=(1-u)*(1-u)*(1-u)*(1-u);
 U[0][1]=4*u*(1-u)*(1-u)*(1-u);
 U[0][2]=6*u*u*(1-u)*(1-u);
 U[0][3]=4*u*u*u*(1-u);
 U[0][4]=u*u*u*u;
 sumx=sumy=sumz=0;
 for(int t=0;t<3;t++)
{
 for(int i=0;i<=4;i++)
 {
sumx=U[0][i]*BBx[i][t]+sumx;
sumy=U[0][i]*BBy[i][t]+sumy;
sumz=U[0][i]*BBz[i][t]+sumz;
if(i==4)
 {
M1x[0][t]=sumx;
M1y[0][t]=sumy;
M1z[0][t]=sumz;
 }
 }
sumx=sumy=sumz=0;
 }
 for(int r=0;r<3;r++)
 {
 sumx=(M1x[0][r])*W[r]+sumx;
 sumy=(M1y[0][r])*W[r]+sumy;
 sumz=(M1z[0][r])*W[r]+sumz;
 }
 Form1->PaintBox1->Canvas->LineTo(sumx,sumy);
}
u=0;
}
}
//-----------------------------------------------------------------------------
void bsplinesurface(void)
{
double tempx=10;
double w=0,u=0,du,dw;
if((nsegs1!=10)) tempx=10;
if(nsegs1==20) tempx=20;
nsegs1=tempx;
du=(1/nsegs1)*3;
dw=(1/nsegs1);
int i,k;
xknot[0]=0;
xknot[1]=0;
xknot[2]=0;
xknot[3]=1;
xknot[4]=2;
xknot[5]=3;
xknot[6]=3;
xknot[7]=3;

for(i=0,u=0;i<=(nsegs1);i++,u+=du)
{
sumx=sumy=sumz=0;
for(k=0,w=0;k<=nsegs1;k++,w+=dw)
{
for(int t=0;t<=4;t++)
{
for(int j=0;j<3;j++)
{
sumx=calculateN(t,u,order)*calculateN(j,w,order)*BBx[t][j]+sumx;
sumy=calculateN(t,u,order)*calculateN(j,w,order)*BBy[t][j]+sumy;
sumz=calculateN(t,u,order)*calculateN(j,w,order)*BBz[t][j]+sumz;
}
}
if(w==0)
Form1->PaintBox1->Canvas->MoveTo(sumx,sumy);
else
Form1->PaintBox1->Canvas->LineTo(sumx,sumy);
 sumx=sumy=sumz=0;
}
}

//--
//--
for(i=0,w=0;i<=(nsegs1);i++,w+=dw)
{
sumx=sumy=sumz=0;
for(k=0,u=0;k<=nsegs1;k++,u+=du)
{
for(int t=0;t<=4;t++)
{
for(int j=0;j<3;j++)
{
sumx=calculateN(t,u,order)*calculateN(j,w,order)*BBx[t][j]+sumx;
sumy=calculateN(t,u,order)*calculateN(j,w,order)*BBy[t][j]+sumy;
sumz=calculateN(t,u,order)*calculateN(j,w,order)*BBz[t][j]+sumz;
}
}
if(u==0)
Form1->PaintBox1->Canvas->MoveTo(sumx,sumy);
else
Form1->PaintBox1->Canvas->LineTo(sumx,sumy);
sumx=sumy=sumz=0;
}
}

}
//----------------------------------------------------------------------------

