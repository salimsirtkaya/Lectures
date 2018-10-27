//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include <math.h>
#include "curves.h"
#include "translate.h"
#include "matrix.h"
#include "deneme1.h"
//-----------------------------------------------------------------
#define Round(a) ((int)(a+0.5));
extern void metric_to_bit_3D(double x,double y);
extern double x1,x2,y1,y2,z1,z2,xx1,xx2,yy1,yy2,zz1,zz2,slope1,slope2;
extern double temp_matrix1[4][4];
extern int conic_index,spline_mode,splinepointnumber,hold_spline_point;
extern double dot_product(double a1=0,double a2=0,double a3=0,double b1=0,double b2=0,double b3=0);
extern double StoreConic[100][6],splinex[20],spliney[20];
extern void bit_to_metric_3D(double x,double y);
double Tt[4][4],T1[4][4],T2[4][4];
int faul;
extern int vn[120][5],numfaces,ne,tab1,tab2,numFaces,mode,cmode;
extern double vert[143][3];
extern double xknot[200],knotocc[50],xknotnum,occindex;
extern double calculateN(int i,double t,int k);
extern double nsegs1;
//----------------------------------------
/* Tt[0][0]=0.2679;  Tt[1][0]=-0.0718;
 Tt[0][1]=-0.0718; Tt[1][1]=0.2871;
 Tt[0][2]=0.0191;  Tt[1][2]=-0.0766;
 Tt[0][3]=-0.048;  Tt[1][3]=0.019;
 Tt[2][0]=0.0191;  Tt[3][0]=-0.0048;
 Tt[2][1]=-0.0766; Tt[3][1]=0.0191;
 Tt[2][2]=0.2871;  Tt[3][2]=-0.0718;
 Tt[2][3]=-0.0718; Tt[3][3]=0.2679;
//---------
 T1[0][0]=0.2679 ;       T1[1][0]=-0.0714;
 T1[0][1]=-0.0714;       T1[1][1]=0.2857;
 T1[0][2]=0.0179;        T1[1][2]=-0.0714;
 T1[0][3]=0;             T1[1][3]=0;
 T1[2][0]=0.0179 ;       T1[3][0]=0;
 T1[2][1]=-0.0714 ;      T1[3][1]=0;
 T1[2][2]=0.2679 ;       T1[3][2]=0;
 T1[2][3]=0;             T1[3][3]=0;
//--------
 T2[0][0]=0.2667;  T2[1][0]=-0.0667;
 T2[0][1]=-0.0667; T2[1][1]=0.2667;
 T2[0][2]=0;       T2[1][2]=0;
 T2[0][3]=0;       T2[1][3]=0;
 T2[2][0]=0;       T2[3][0]=0;
 T2[2][1]=0;       T2[3][1]=0;
 T2[2][2]=0;       T2[3][2]=0;
 T2[2][3]=0;       T2[3][3]=0;*/
//--------


//----------------------------------------
void circleplotpoints(int xcenter,int ycenter,int x,int y,int mode=0)
{
if(mode==0)
{
Form1->PaintBox1->Canvas->Pixels[xcenter+x][ycenter+y]=clBlack;
Form1->PaintBox1->Canvas->Pixels[xcenter-x][ycenter+y]=clBlack;
Form1->PaintBox1->Canvas->Pixels[xcenter+x][ycenter-y]=clBlack;
Form1->PaintBox1->Canvas->Pixels[xcenter-x][ycenter-y]=clBlack;
Form1->PaintBox1->Canvas->Pixels[xcenter+y][ycenter+x]=clBlack;
Form1->PaintBox1->Canvas->Pixels[xcenter-y][ycenter+x]=clBlack;
Form1->PaintBox1->Canvas->Pixels[xcenter+y][ycenter-x]=clBlack;
Form1->PaintBox1->Canvas->Pixels[xcenter-y][ycenter-x]=clBlack;
}
else
{
Form1->PaintBox1->Canvas->Pixels[xcenter+x][ycenter+y]=clBtnFace;
Form1->PaintBox1->Canvas->Pixels[xcenter-x][ycenter+y]=clBtnFace;
Form1->PaintBox1->Canvas->Pixels[xcenter+x][ycenter-y]=clBtnFace;
Form1->PaintBox1->Canvas->Pixels[xcenter-x][ycenter-y]=clBtnFace;
Form1->PaintBox1->Canvas->Pixels[xcenter+y][ycenter+x]=clBtnFace;
Form1->PaintBox1->Canvas->Pixels[xcenter-y][ycenter+x]=clBtnFace;
Form1->PaintBox1->Canvas->Pixels[xcenter+y][ycenter-x]=clBtnFace;
Form1->PaintBox1->Canvas->Pixels[xcenter-y][ycenter-x]=clBtnFace;
}
}
//--------------------------------------------------------------------------

void draw_circle(int xcenter,int ycenter,int radius)
{
 int x=0;
 int y=radius*25;
 int p=1-radius*25;
 xcenter=300+xcenter*25;
 ycenter=250-ycenter*25;
 circleplotpoints(xcenter,ycenter,x,y,cmode);

 while(x<y)
 {
 x++;
 if (p<0) p+=2*x+1;
 else
 {
 y--;
 p+=2*(x-y)+1;
 }
 circleplotpoints(xcenter,ycenter,x,y,cmode);
 }
}
//--------------------------------------------------------------------------

void ellipseplotpoint(int xcenter,int ycenter,int x,int y)
{
Form1->PaintBox1->Canvas->Pixels[xcenter+x][ycenter+y]=1;
Form1->PaintBox1->Canvas->Pixels[xcenter-x][ycenter+y]=1;
Form1->PaintBox1->Canvas->Pixels[xcenter+x][ycenter-y]=1;
Form1->PaintBox1->Canvas->Pixels[xcenter-x][ycenter-y]=1;
}
//--------------------------------------------------------------------------
void draw_ellipse(int xcenter,int ycenter,int rx,int ry)
{
//for the sake of speed polar coordinates are not used
rx=rx*25;
ry=ry*25;
int rx2=rx*rx;
int ry2=ry*ry;
int tworx2=2*rx2;
int twory2=2*ry2;
int p;
int x=0;
int y=ry;
int px=0;
int py=tworx2*y;
 xcenter=300+xcenter*25;
 ycenter=250-ycenter*25;
ellipseplotpoint(xcenter,ycenter,x,y);
p=Round(ry2-(rx2*ry)+(0.25*rx2));


while(px<py)
{
x++;
px+=ry2+px;
if(p<0)
p+=ry2+px;
else
{
y--;
py=tworx2;
p+=ry2+px-py;
}
int r=xcenter+x;
int r1=ycenter+y;

ellipseplotpoint(xcenter,ycenter,x,y);
}//region1
p=Round(ry2*(x+0.5)*(x+0.5)+rx2*(y-1)*(y-1)-rx2*ry2);
while(y>0)
{
y--;
py-=tworx2;
if(p>0)
p+=rx2-py;
else
{
x++;
px+=twory2;
p+=rx2-py+px;
}
int r=xcenter+x;
int r1=ycenter+y;
ellipseplotpoint(xcenter,ycenter,x,y);
}
}
//--------------------------------------------------------------------------
void hyperbolaplotpoint(int xcenter,int ycenter,int x,int y)
{
Form1->PaintBox1->Canvas->Pixels[xcenter+x][ycenter+y]=1;
Form1->PaintBox1->Canvas->Pixels[xcenter-x][ycenter+y]=1;
Form1->PaintBox1->Canvas->Pixels[xcenter+x][ycenter-y]=1;
Form1->PaintBox1->Canvas->Pixels[xcenter-x][ycenter-y]=1;
}
//--------------------------------------------------------------------------
void draw_hyperbola(double xcenter,double ycenter,double rx,double ry)
{
//slow methood
//polar coordinates are used
double teta;
double x,y;
rx=rx*25;
ry=ry*25;
xcenter=300+xcenter*25;
ycenter=250-ycenter*25;


while(teta<1.35)
{
x=rx*(1/cos(teta));
y=ry*(tan(teta));
hyperbolaplotpoint(xcenter,ycenter,x,y);
teta=teta+0.0002;
}
}
//----------------------------------------------------------------------------
void parabolaplotpoint(int xcenter,int ycenter,int x,int y)
{
Form1->PaintBox1->Canvas->Pixels[xcenter+x][ycenter-y]=1;
Form1->PaintBox1->Canvas->Pixels[xcenter-x][ycenter-y]=1;
//Form1->PaintBox1->Canvas->Pixels[xcenter+x][ycenter-y]=1;
//Form1->PaintBox1->Canvas->Pixels[xcenter-x][ycenter-y]=1;
}

//----------------------
void draw_parabola(double a,double b,double c)
{
 double x=0,r=0,k=0;
 double teta;
 double xt,yt,t,y,ytemp;
if(a==0)
Application->MessageBox("You can not assign 0 to a!!","Error",MB_OK);
else
{
 ytemp=sqrt(a);
 int xcenter=300;
 int ycenter=250;
 t=sqrt(100/a);
 r=(-1)*(b/(2*a));
 k=(4*a*c-b*b)/(4*a);

while(x<t)
{
y=a*x*x;
xt=x;
yt=y;
if(r>0) xt=x+r*25;
if(r<0) xt=x+r*25;
if(k>0) yt=y+k*25;
if(k<0) yt=y+k*25;
if(b==0)
parabolaplotpoint(xcenter,ycenter,xt,yt);
else
{
Form1->PaintBox1->Canvas->Pixels[xcenter+xt][ycenter-y]=1;
Form1->PaintBox1->Canvas->Pixels[xcenter-xt+r*50][ycenter-y]=1;
}

x=x+0.04;
}
}
}
//----------------------------------------------------------------------------
//knot method for cubic spline
/*void cubicspline_knot(int n,double x[],double y[])
{
 int i,j,nisegs,ntsegs;
 double t,dt,b0,b1,b2,b3,xp,yp;
 nisegs=n-3;
 ntsegs=200;
 dt=1/ntsegs;
 for(i=3;i<=nisegs+2;i++)
 {
 for (j=0;j<=ntsegs;j++,t+=dt)
 {
  b0=t*t*t/6;
  b1=(1+3*t+3*t*t-3*t*t*t)/6;
  b2=(4-6*t*t+3*t*t*t)/6;
  b3=(1-t)*(1-t)*(1-t)/6;
  xp=b3*x[i-3]+b2*x[i-2]+b1*x[i-1]+b0*x[i];
  yp=b3*y[i-3]+b2*y[i-2]+b1*y[i-1]+b0*y[i];
  if((i==3)&&(j==0))
  Form1->PaintBox1->Canvas->MoveTo( (int) xp,(int) yp);
  else
  Form1->PaintBox1->Canvas->LineTo( (int) xp,(int) yp);
 }
 }
 }*/
 //-------------------------------------------------------------------------
 //Natural cubic spline:n data points:given coordinates x[], y[];
 void natcubicspline(int n,double x[],double y[])
 {
 int i,j,nsegs,m,xp,yp;
 double ax[50],bx[50],cx[50],dx[50];
 double ay[50],by[50],cy[50],dy[50];
 double der[50],gam[50],del[50];
 double t,dt;

 m=n-1;
 gam[0]=0.5;
 for(i=1;i<m;i++)
 {
 gam[i]=1/(4-gam[i-1]);
 }
 gam[m]=1/(2-gam[m-1]);
 del[0]=3*(x[1]-x[0])*gam[0];
 for (i=1;i<m;i++)
 {
 del[i]=(3*(x[i+1]-x[i-1])-del[i-1])*gam[i];
 }
 //---
 del[m]=(3*(x[m]-x[m-1])-del[m-1])*gam[m];
 der[m]=del[m];
 for (i=m-1;i>=0;i=i-1)
 {
 der[i]=del[i]-gam[i]*der[i+1];
 }
 for(i=0;i<m;i++)
 {
 ax[i]=x[i];
 bx[i]=der[i];
 cx[i]=3*(x[i+1]-x[i])-2*der[i]-der[i+1];
 dx[i]=2*(x[i]-x[i+1])+der[i]+der[i+1];
 }
 del[0]=3*(y[1]-y[0])*gam[0];
 for(i=1;i<m;i++)
 {
 del[i]=(3*(y[i+1]-y[i-1])-del[i-1])*gam[i];
 }
 del[m]=(3*(y[m]-y[m-1])-del[m-1])*gam[m];
 der[m]=del[m];
 for(i=m-1;i<0;i=i-1)
 {
 der[i]=del[i]-gam[i]*der[i+1];
 }
 for(i=0;i<m;i++)
 {
 ay[i]=y[i];
 by[i]=der[i];
 cy[i]=3*(y[i+1]-y[i])-2*der[i]-der[i+1];
 dy[i]=2*(y[i]-y[i+1])+der[i]+der[i+1];
 }
 nsegs=20;
 dt=1/(double) nsegs;
 Form1->PaintBox1->Canvas->MoveTo((int) x[0],(int) y[0]);
 for (i=0;i<m;i++)
{
for(j=1,t=dt;j<=nsegs;j++,t+=dt)
{
xp=(int) (ax[i]+bx[i]*t+cx[i]*t*t+dx[i]*t*t*t);
yp=(int) (ay[i]+by[i]*t+cy[i]*t*t+dy[i]*t*t*t);
Form1->PaintBox1->Canvas->LineTo(xp,yp);
}
}
}
//---------------------------------------------------------------------------
 void cubicspline(int n,double x[],double y[],double sl1,double sl2)
 {
 int i,j,nsegs,m,xp,yp;
 double ax[50],bx[50],cx[50],dx[50];
 double ay[50],by[50],cy[50],dy[50];
 double der[50],gam[50],del[50];
 double t,dt;
 sl1=sl1*25;
 sl2=sl2*25;
 m=n-1;
 gam[0]=1;
 gam[1]=0.125;
 for(i=2;i<m;i++)
 {
 gam[i]=1/(4-gam[i-1]);
 }
 gam[m]=1;
 del[0]=sl1;
 for (i=1;i<m;i++)
 {
 del[i]=(3*(x[i+1]-x[i-1])-del[i-1])*gam[i];
 }
 //---
 del[m]=sl2;
 der[m]=del[m];
 for (i=m-1;i>=0;i=i-1)
 {
 der[i]=del[i]-gam[i]*der[i+1];
 }
 for(i=0;i<m;i++)
 {
 ax[i]=x[i];
 bx[i]=der[i];
 cx[i]=3*(x[i+1]-x[i])-2*der[i]-der[i+1];
 dx[i]=2*(x[i]-x[i+1])+der[i]+der[i+1];
 }
 del[0]=sl1;
 for(i=1;i<m;i++)
 {
 del[i]=(3*(y[i+1]-y[i-1])-del[i-1])*gam[i];
 }
 del[m]=sl2;
 der[m]=del[m];
 for(i=m-1;i<0;i=i-1)
 {
 der[i]=del[i]-gam[i]*der[i+1];
 }
 for(i=0;i<m;i++)
 {
 ay[i]=y[i];
 by[i]=der[i];
 cy[i]=3*(y[i+1]-y[i])-2*der[i]-der[i+1];
 dy[i]=2*(y[i]-y[i+1])+der[i]+der[i+1];
 }
 nsegs=20;
 dt=1/(double) nsegs;
 Form1->PaintBox1->Canvas->MoveTo((int) x[0],(int) y[0]);
 for (i=0;i<m;i++)
{
for(j=1,t=dt;j<=nsegs;j++,t+=dt)
{
xp=(int) (ax[i]+bx[i]*t+cx[i]*t*t+dx[i]*t*t*t);
yp=(int) (ay[i]+by[i]*t+cy[i]*t*t+dy[i]*t*t*t);
Form1->PaintBox1->Canvas->LineTo(xp,yp);
}
}
}
//--------------------------------------------------------------------------
void fit_spline(int x,int y)
{
int i=0,go=1;
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
if(spline_mode==0)
natcubicspline(hold_spline_point,splinex,spliney);
if(spline_mode==1)
cubicspline(hold_spline_point,splinex,spliney,slope1,slope2);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
while((i<hold_spline_point)&&(go==1))
{
if((splinex[i]>x && x>splinex[i+1])||(splinex[i]<x && x<splinex[i+1]))
{
go=0;
for(int j=hold_spline_point;j>i+1;j--)
{
 splinex[j]=splinex[j-1];
 spliney[j]=spliney[j-1];
}
splinex[i+1]=x;
spliney[i+1]=y;
hold_spline_point+=1;
if(spline_mode==0)
natcubicspline(hold_spline_point,splinex,spliney);
if(spline_mode==1)
cubicspline(hold_spline_point,splinex,spliney,slope1,slope2);
}
i=i+1;
}
if(go==1)
{
Application->MessageBox("Sorry can not handle that point.Drawing the last one!!","Error",MB_OK);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
if(spline_mode==0)
natcubicspline(hold_spline_point,splinex,spliney);
if(spline_mode==1)
cubicspline(hold_spline_point,splinex,spliney,slope1,slope2);
}
}
//-----------------------------------------------------------------------------
/*void parabolic_blend(int n,double x[],double y[])
{
double alfa1,alfa2,gama1,gama2,betax,drx,d,sx,cos1,cos2,sd,se;
double t,dt,betay,t0,ry,sy;
double r,s,temp1,temp2,temp3,temp4,st0,e,px,py,cx,cy,qx,qy;

temp1=x[2]-x[0];
temp2=y[2]-y[0];
d=dot_product(temp1,temp2,0,temp1,temp2);   //d^2
sd=sqrt(d);
temp1=x[2]-x[1];
temp2=y[2]-y[1];
t0=dot_product(temp1,temp2,0,temp1,temp2);   //t0^2
st0=sqrt(t0);
cos1=(dot_product(temp1,temp2,0,(x[2]-x[0]),(y[2]-y[0]),0))/(st0*sd);
gama1=(dot_product((x[1]-x[0]),(y[1]-y[0]),0,(x[2]-x[1]),(y[2]-y[1]),0)/d);
alfa1= 1/(d*gama1*(1-gama1));
temp3=gama1*sd;
//-----
temp1=x[3]-x[1];
temp2=y[3]-y[1];
e=dot_product(temp1,temp2,0,temp1,temp2);   //d^2
se=sqrt(e);
temp1=x[2]-x[1];
temp2=y[2]-y[1];
cos2=(dot_product(temp1,temp2,0,(x[3]-x[1]),(y[3]-y[1]),0))/(sqrt(t0*e));
gama2=(dot_product((x[2]-x[1]),(y[2]-y[1]),0,(x[3]-x[2]),(y[3]-y[2]),0)/e);
alfa2= 1/(e*gama2*(1-gama2));
temp4=gama2*se;
//----
dt=1/20;
t=0;
Form1->PaintBox1->Canvas->MoveTo(x[0],y[0]);
Form1->PaintBox1->Canvas->Pen->Color=clGreen;
for(int j=1;j<=20;j++,t+=dt)
{
 r=temp3+t*cos1;
 px=x[0]+gama1*(x[2]-x[0])+alfa1*r*(sd-r)*((x[1]-x[0])-gama1*(x[2]-x[0]));
 py=y[0]+gama1*(y[2]-y[0])+alfa1*r*(sd-r)*((y[1]-y[0])-gama1*(y[2]-y[0]));
 Form1->PaintBox1->Canvas->LineTo(px,py);
}
//---
Form1->PaintBox1->Canvas->MoveTo(x[3],y[3]);
Form1->PaintBox1->Canvas->Pen->Color=clBlue;
t=0;
for(int j=1;j<=20;j++,t+=dt)
{
 s=temp4+t*cos2;
 qx=x[1]+gama2*(x[3]-x[1])+alfa2*s*(se-s)*((x[2]-x[1])-gama2*(x[3]-x[1]));
 qy=y[1]+gama2*(y[3]-y[1])+alfa2*s*(se-s)*((y[2]-y[1])-gama2*(y[3]-y[1]));
 Form1->PaintBox1->Canvas->LineTo(qx,qy);
}
//-----
Form1->PaintBox1->Canvas->MoveTo(x[1],y[1]);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
t=0;
for(int j=1;j<=20;j++,t+=dt)
{
 s=temp4+t*cos2;
 qx=x[1]+gama2*(x[3]-x[1])+alfa2*s*(se-s)*((x[2]-x[1])-gama2*(x[3]-x[2]));
 qy=y[1]+gama2*(y[3]-y[1])+alfa2*s*(se-s)*((y[2]-y[1])-gama2*(y[3]-y[2]));
 r=temp3+t*cos1;
 px=x[0]+gama1*(x[2]-x[0])+alfa1*r*(sd-r)*((x[1]-x[0])-gama1*(x[2]-x[1]));
 py=y[0]+gama1*(y[2]-y[0])+alfa1*r*(sd-r)*((y[1]-y[0])-gama1*(y[2]-y[1]));
 cx=(1-(t/st0))*px+(t/st0)*qx;
 cy=(1-(t/st0))*py+(t/st0)*qy;
 Form1->PaintBox1->Canvas->LineTo(cx,cy);
}
   }*/
//------------------------------------------------------------------------------

void parblend(int n,double x[],double y[])
{
int i,j,nsegs,xp,yp;
double t,dt,f1,f2,f3,f4;

nsegs=20;
dt=1/(double) nsegs;
if (mode==0)
Form1->PaintBox1->Canvas->Pen->Color=clBlue;
if(mode==1)
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
Form1->PaintBox1->Canvas->MoveTo(x[0],y[0]);

for (j=1,t=dt;j<=nsegs;j++,t+=dt)
{
f1=0.5*(1-t)*(2-t);
f2=(2-t)*t;
f3=0.5*(t-1)*t;
xp=(f1*x[0]+f2*x[1]+f3*x[2]);
yp=(f1*y[0]+f2*y[1]+f3*y[2]);
Form1->PaintBox1->Canvas->LineTo(xp,yp);
}
if(mode==0)
Form1->PaintBox1->Canvas->Pen->Color=clRed;
if(mode==1)
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for (i=1;i<n-2;i++)
{
for(j=1,t=dt;j<=nsegs;j++,t+=dt)
{
f1=-0.5*(1-t)*(1-t)*t;
f2=0.5*(3*t*t*t-5*t*t+2);
f3=0.5*((-3)*t*t+4*t+1)*t;
f4=0.5*(t-1)*t*t;
xp=(f1*x[i-1]+f2*x[i]+f3*x[i+1]+f4*x[i+2]);
yp=(f1*y[i-1]+f2*y[i]+f3*y[i+1]+f4*y[i+2]);
Form1->PaintBox1->Canvas->LineTo(xp,yp);
}
}
if(mode==0)
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
if(mode==1)
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(j=1,t=dt;j<=nsegs;j++,t+=dt)
{
f2=0.5*(t-1)*t;
f3=1-t*t;
f4=0.5*(t+1)*t;
xp=(f2*x[n-3]+f3*x[n-2]+f4*x[n-1]);
yp=(f2*y[n-3]+f3*y[n-2]+f4*y[n-1]);
Form1->PaintBox1->Canvas->LineTo(xp,yp);
}
}
//-----------------------------------------------------------------------------
 void cycliccubicspline(int n,double x[],double y[])
 {
 int i,j,nsegs,m,xp,yp;
 double ax[50],bx[50],cx[50],dx[50];
 double ay[50],by[50],cy[50],dy[50];
 double der[50],gam[50],del[50];
 double div,t,dt,tn,to;
 m=n-1;

 tn=sqrt((x[m]-x[m-1])*(x[m]-x[m-1])+(y[m]-y[m-1])*(y[m]-y[m-1]));
 to=sqrt((x[1]-x[0])*(x[1]-x[0])+(y[1]-y[0])*(y[1]-y[0]));
 div=tn/to;
 gam[0]=1/(2*(1+(1/div)));
 for(i=1;i<m;i++)
 {
 gam[i]=1/(4-gam[i-1]);
 }
 gam[m]=0;
 del[0]=(3*(x[1]-x[0])-3*(x[m-1]-x[m]))*gam[0]/div;;
 for (i=1;i<m;i++)
 {
 del[i]=(3*(x[i+1]-x[i-1])-del[i-1])*gam[i];
 }
 //---
 del[m]=0;
 der[m]=0;
 for (i=m-1;i>=1;i=i-1)
 {
 der[i]=del[i]-gam[i]*der[i+1];
 }
 der[0]=del[0]-gam[0]*der[1]-0.25*der[m-1];

 for(i=0;i<m;i++)
 {
 ax[i]=x[i];
 bx[i]=der[i];
 cx[i]=3*(x[i+1]-x[i])-2*der[i]-der[i+1];
 dx[i]=2*(x[i]-x[i+1])+der[i]+der[i+1];
 }
 del[0]=3*(y[1]-y[0])*gam[0];
 for(i=1;i<m;i++)
 {
 del[i]=(3*(y[i+1]-y[i-1])-del[i-1])*gam[i];
 }
 del[m]=(3*(y[m]-y[m-1])-del[m-1])*gam[m];
 der[m]=del[m];
 for(i=m-1;i<0;i=i-1)
 {
 der[i]=del[i]-gam[i]*der[i+1];
 }
 for(i=0;i<m;i++)
 {
 ay[i]=y[i];
 by[i]=der[i];
 cy[i]=3*(y[i+1]-y[i])-2*der[i]-der[i+1];
 dy[i]=2*(y[i]-y[i+1])+der[i]+der[i+1];
 }
 nsegs=20;
 dt=1/(double) nsegs;
 Form1->PaintBox1->Canvas->MoveTo((int) x[0],(int) y[0]);
 for (i=0;i<m;i++)
{
for(j=1,t=dt;j<=nsegs;j++,t+=dt)
{
xp=(int) (ax[i]+bx[i]*t+cx[i]*t*t+dx[i]*t*t*t);
yp=(int) (ay[i]+by[i]*t+cy[i]*t*t+dy[i]*t*t*t);
Form1->PaintBox1->Canvas->LineTo(xp,yp);
}
}
}
//-----------------------------------------------------------------------------
 void anticycliccubicspline(int n,double x[],double y[])
 {
 int i,j,nsegs,m,xp,yp;
 double ax[50],bx[50],cx[50],dx[50];
 double ay[50],by[50],cy[50],dy[50];
 double der[50],gam[50],del[50];
 double t,dt;

 m=n-1;
 gam[0]=0.25;
 for(i=1;i<m;i++)
 {
 gam[i]=1/(4-gam[i-1]);
 }
 gam[m]=0;
 del[0]=(3*(x[1]-x[0])+3*(x[m-1]-x[m]))*gam[0];
 for (i=1;i<m;i++)
 {
 del[i]=(3*(x[i+1]-x[i-1])-del[i-1])*gam[i];
 }
 //---
 del[m]=0;
 der[m]=0;
 for (i=m-1;i>=1;i=i-1)
 {
 der[i]=del[i]-gam[i]*der[i+1];
 }
 der[0]=del[0]-gam[0]*der[1]+0.25*der[m-1];

 for(i=0;i<m;i++)
 {
 ax[i]=x[i];
 bx[i]=der[i];
 cx[i]=3*(x[i+1]-x[i])-2*der[i]-der[i+1];
 dx[i]=2*(x[i]-x[i+1])+der[i]+der[i+1];
 }
 del[0]=3*(y[1]-y[0])*gam[0];
 for(i=1;i<m;i++)
 {
 del[i]=(3*(y[i+1]-y[i-1])-del[i-1])*gam[i];
 }
 del[m]=(3*(y[m]-y[m-1])-del[m-1])*gam[m];
 der[m]=del[m];
 for(i=m-1;i<0;i=i-1)
 {
 der[i]=del[i]-gam[i]*der[i+1];
 }
 for(i=0;i<m;i++)
 {
 ay[i]=y[i];
 by[i]=der[i];
 cy[i]=3*(y[i+1]-y[i])-2*der[i]-der[i+1];
 dy[i]=2*(y[i]-y[i+1])+der[i]+der[i+1];
 }
 nsegs=20;
 dt=1/(double) nsegs;
 Form1->PaintBox1->Canvas->MoveTo((int) x[0],(int) y[0]);
 for (i=0;i<m;i++)
{
for(j=1,t=dt;j<=nsegs;j++,t+=dt)
{
xp=(int) (ax[i]+bx[i]*t+cx[i]*t*t+dx[i]*t*t*t);
yp=(int) (ay[i]+by[i]*t+cy[i]*t*t+dy[i]*t*t*t);
Form1->PaintBox1->Canvas->LineTo(xp,yp);
}
}
}
//-----------------------------------------------------------------------------
void bezier(int n,double x[],double y[],int mode=1)
{
int i,j,k,d,nsegs;
double t,dt;
double p[20][20],xp,yp;
d=n-1;
nsegs=50;
dt=1/(double) nsegs;
if(mode==2)
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
else
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->MoveTo((int) x[0],(int) y[0]);
for (j=1,t=dt;j<=nsegs;j++,t+=dt)
{
p[0][0]=1;
for(k=1;k<=d;k++)
{
p[0][k]=(1-t)*p[0][k-1];
for(i=1;i<k;i++)
{
p[i][k]=(1-t)*p[i][k-1]+t*p[i-1][k-1];
}
p[k][k]=t*p[k-1][k-1];
}
xp=0;
yp=0;
for(i=0;i<=d;i++)
{
xp=xp+x[i]*p[i][d];
yp=yp+y[i]*p[i][d];
}
Form1->PaintBox1->Canvas->LineTo((int) xp,(int) yp);
}
}
//----------------------------------------------------------------------------
/*bspline(int n,double x[], double y[],double tknot[])
{
int i,j,nisegs,ntsegs;
double t,dt,b0,b1,b2,xp,yp;
double tn1,t0,t1,t2;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
nisegs=n-2;
ntsegs=20;

for(i=2;i<=nisegs+1;i++)
{
tn1=tknot[i-1];
t0=tknot[i];
t1=tknot[i+1];
t2=tknot[i+2];
if(t1>t0)
{
dt=(t1-t0)/(double) ntsegs;
for (j=0,t=t0;j<=ntsegs;j++,t+=dt)
{
b0=(t-t0)*(t-t0)/((t2-t0)*(t1-t0));
b1=(t1-t)*(t-tn1)/((t1-t0)*((t1-tn1))+(t2-t)*(t-t0))/((t2-t0)*(t1-t0));
b2=(t1-t)*(t1-t)/((t1-tn1)*(t1-t0));
xp=b2*x[i-2]+b1*x[i-1]+b0*x[i];
yp=b2*y[i-2]+b1*y[i-1]+b0*y[i];
if(j==0)
Form1->PaintBox1->Canvas->MoveTo((int) xp, (int) yp);
else
Form1->PaintBox1->Canvas->LineTo((int) xp, (int) yp);
}
}
}
} */
//---------------------------------------------------------------------------
void rulebspline(int splnum,int n,double x[],double y[],double z[])
{
int i,j,k,nisegs,ntsegs;
double t,dt,b0,b1,b2,b3,xp,yp,zp;
double xstart,ystart,zstart,xend,yend,zend;
double s,length,dx,dy,dz,ds,len[12];

xstart=x[0];
ystart=y[0];
zstart=z[0];

xend=x[n-1];
yend=y[n-1];
zend=z[n-1];

x[0]=x[2]+6*(x[0]-x[1]);
x[1]=1.5*x[1]-.5*x[2];
y[0]=y[2]+6*(y[0]-y[1]);
y[1]=1.5*y[1]-.5*y[2];
z[0]=z[2]+6*(z[0]-z[1]);
z[1]=1.5*z[1]-.5*z[2];

x[n-1]=x[n-3]+6*(x[n-1]-x[n-2]);
x[n-2]=1.5*x[n-2]-.5*x[n-3];
y[n-1]=y[n-3]+6*(y[n-1]-y[n-2]);
y[n-2]=1.5*y[n-2]-.5*y[n-3];
z[n-1]=z[n-3]+6*(z[n-1]-z[n-2]);
z[n-2]=1.5*z[n-2]-.5*z[n-3];

nisegs=n-3;
ntsegs=20;
dt=1/(double) ntsegs;

xp=xstart;
yp=ystart;
zp=zstart;
s=0;
for(int i=3;i<nisegs+2;i++)
{
 for(int j=0,t=0;j<=ntsegs;j++,t+=dt)
 {
  b0=t*t*t/6;
  b1=(1+3*t+3*t*t-3*t*t*t)/6;
  b2=(4-6*t*t+3*t*t*t)/6;
  b3=(1-3*t+3*t*t-t*t*t)/6;
  dx=b3*x[i-3]+b2*x[i-2]+b1*x[i-1]+b0*x[i]-xp;
  dy=b3*y[i-3]+b2*y[i-2]+b1*y[i-1]+b0*y[i]-yp;
  dz=b3*z[i-3]+b2*z[i-2]+b1*z[i-1]+b0*z[i]-zp;
  ds=sqrt(dx*dx+dy*dy+dz*dz);
  s=s+ds;
  xp=xp+dx;
  yp=yp+dy;
  zp=zp+dz;
 }
}

length=s;



for(int k=1;k<ne;k++)
{
len[k]=(k*length)/(double) ne;
}

xp=vert[splnum][0]=xstart;
yp=vert[splnum][1]=ystart;
zp=vert[splnum][2]=zstart;

s=0;

for(int i=3;i<=nisegs+2;i++)
{
for(int j=0,t=0;j<=ntsegs;j++,t+=dt)
{
b0=t*t*t/6;
b1=(1+3*t+3*t*t-3*t*t*t)/6;
b2=(4-6*t*t+3*t*t*t)/6;
b3=(1-3*t+3*t*t-t*t*t)/6;
dx=b3*x[i-3]+b2*x[i-2]+b1*x[i-1]+b0*x[i]-xp;
dy=b3*y[i-3]+b2*y[i-2]+b1*y[i-1]+b0*y[i]-yp;
dz=b3*z[i-3]+b2*z[i-2]+b1*z[i-1]+b0*z[i]-zp;
ds=sqrt(dx*dx+dy*dy+dz*dz);

for(int k=1;k<ne;k++)
{
if((s<len[k])&&((s+ds)>=len[k]))
{
vert[2*k+splnum][0]=xp+(len[k]-s)*dx/ds;
vert[2*k+splnum][1]=yp+(len[k]-s)*dy/ds;
vert[2*k+splnum][2]=zp+(len[k]-s)*dz/ds;
}
}
s=s+ds;
xp=xp+dx;
yp=yp+dy;
zp=zp+dz;
}
}
vert[2*ne+splnum][0]=xend;
vert[2*ne+splnum][1]=yend;
vert[2*ne+splnum][2]=zend;
}
//----------------------------------------------------------------------------
void rulesurf(int n1,int n2,double xspl0[],double yspl0[], double zspl0[],double xspl1[],double yspl1[],double zspl1[])
{
rulebspline(0,n1,xspl0,yspl0,zspl0);
rulebspline(1,n2,xspl1,yspl1,zspl1);
for(int i=0;i<numfaces;i++)
{
vn[i][0]=vn[i][4]=2*i;
vn[i][1]=2*i+1;
vn[i][2]=2*i+3;
vn[i][3]=2*i+2;
}
int xcen=300;
int ycen=250;
double  yw,xw,zw;
double xplot,yplot;
int sf=50,vnum;
double sinp=sin(70*M_PI/180);
double cosp=cos(70*M_PI/180);

for(int m=0;m<numfaces;m++)
{

for(int k=0;k<=5;k++)
{
vnum=vn[m][k];
xw=vert[vnum][0];
yw=vert[vnum][1];
zw=vert[vnum][2];
xplot=xcen+(sf*xw);
yplot=ycen-(sf*(yw*cosp+zw*sinp));
if(k==0)
Form1->PaintBox1->Canvas->MoveTo(xplot,yplot);
else
Form1->PaintBox1->Canvas->LineTo(xplot,yplot);
}
}
}
//---------
void ruleb2spline(int splnum,int n,double x[],double y[],double z[])
{
int i,j,k,m,nisegs,ntsegs;
double t,dt,b0,b1,b2,b3,xp,yp,zp;
double xstart,ystart,zstart,xend,yend,zend;
double s,length,dx,dy,dz,ds,len[12];

xstart=x[0];
ystart=y[0];
zstart=z[0];

xend=x[n-1];
yend=y[n-1];
zend=z[n-1];

x[0]=x[2]+6*(x[0]-x[1]);
x[1]=1.5*x[1]-.5*x[2];
y[0]=y[2]+6*(y[0]-y[1]);
y[1]=1.5*y[1]-.5*y[2];
z[0]=z[2]+6*(z[0]-z[1]);
z[1]=1.5*z[1]-.5*z[2];

x[n-1]=x[n-3]+6*(x[n-1]-x[n-2]);
x[n-2]=1.5*x[n-2]-.5*x[n-3];
y[n-1]=y[n-3]+6*(y[n-1]-y[n-2]);
y[n-2]=1.5*y[n-2]-.5*y[n-3];
z[n-1]=z[n-3]+6*(z[n-1]-z[n-2]);
z[n-2]=1.5*z[n-2]-.5*z[n-3];

nisegs=n-3;
ntsegs=20;
dt=1/(double) ntsegs;

xp=xstart;
yp=ystart;
zp=zstart;
s=0;
for(int i=3;i<nisegs+2;i++)
{
 for(int j=0,t=0;j<=ntsegs;j++,t+=dt)
 {
  b0=t*t*t/6;
  b1=(1+3*t+3*t*t-3*t*t*t)/6;
  b2=(4-6*t*t+3*t*t*t)/6;
  b3=(1-3*t+3*t*t-t*t*t)/6;
  dx=b3*x[i-3]+b2*x[i-2]+b1*x[i-1]+b0*x[i]-xp;
  dy=b3*y[i-3]+b2*y[i-2]+b1*y[i-1]+b0*y[i]-yp;
  dz=b3*z[i-3]+b2*z[i-2]+b1*z[i-1]+b0*z[i]-zp;
  ds=sqrt(dx*dx+dy*dy+dz*dz);
  s=s+ds;
  xp=xp+dx;
  yp=yp+dy;
  zp=zp+dz;
 }
}

length=s;

if((splnum==0) || (splnum==2)) ne=tab1;
else ne=tab2;

for(int k=1;k<ne;k++)
{
len[k]=(k*length)/(double) ne;
}

xp=xstart;
yp=ystart;
zp=zstart;

s=0;

for(int i=3;i<=nisegs+2;i++)
{
for(int j=0,t=0;j<=ntsegs;j++,t+=dt)
{
b0=t*t*t/6;
b1=(1+3*t+3*t*t-3*t*t*t)/6;
b2=(4-6*t*t+3*t*t*t)/6;
b3=(1-3*t+3*t*t-t*t*t)/6;
dx=b3*x[i-3]+b2*x[i-2]+b1*x[i-1]+b0*x[i]-xp;
dy=b3*y[i-3]+b2*y[i-2]+b1*y[i-1]+b0*y[i]-yp;
dz=b3*z[i-3]+b2*z[i-2]+b1*z[i-1]+b0*z[i]-zp;
ds=sqrt(dx*dx+dy*dy+dz*dz);

for(int k=1;k<ne;k++)
{
if((s<len[k])&&((s+ds)>=len[k]))
{
if(splnum==0) m=k*(tab2+1);
if(splnum==1) m=k;
if (splnum==2) m=(k+1)*tab2+k;
if (splnum==3) m=tab1*(tab2+1)+k;
vert[m][0]=xp+(len[k]-s)*dx/ds;
vert[m][1]=yp+(len[k]-s)*dy/ds;
vert[m][2]=zp+(len[k]-s)*dz/ds;
}
}
s=s+ds;
xp=xp+dx;
yp=yp+dy;
zp=zp+dz;
}
}
}
//------------------------
void edgesurf(int n0,int n1,int n2,int n3,double xsp0[],double ysp0[],double zsp0[],double xsp1[],double ysp1[],double zsp1[],double xsp2[],double ysp2[],double zsp2[],double xsp3[],double ysp3[],double zsp3[])
{
int i,j,k,m;
double u,v,f1u,f2u,f1v,f2v,rtab1=1/12,rtab2=1/10;
vert[0][0]=1;
vert[0][1]=1;
vert[0][2]=0;
vert[tab2][0]=3;
vert[tab2][1]=0;
vert[tab2][2]=0;
vert[tab1*(tab2+1)][0]=3;
vert[tab1*(tab2+1)][1]=3;
vert[tab1*(tab2+1)][2]=1;
vert[(tab1+1)*(tab2+1)-1][0]=5;
vert[(tab1+1)*(tab2+1)-1][1]=2.5;
vert[(tab1+1)*(tab2+1)-1][2]=2;

//***


ruleb2spline(0,6,xsp0,ysp0,zsp0);
ruleb2spline(1,5,xsp1,ysp1,zsp1);
ruleb2spline(2,5,xsp2,ysp2,zsp2);
ruleb2spline(3,6,xsp3,ysp3,zsp3);
//***
/*rulebspline(0,n0,xsp0,ysp0,zsp0);
rulebspline(1,n1,xsp1,ysp1,zsp1);
rulebspline(2,n2,xsp2,ysp2,zsp2);
rulebspline(3,n3,xsp3,ysp3,zsp3);
*/
for(int i=1;i<tab1;i++)
{
for(int j=1;j<tab2;j++)
{

v=i*rtab1;
u=j*rtab2;
f1u=(2*u-3)*u*u+1;
f1v=(2*v-3)*v*v+1;
f2u=(-2*u+3)*u*u;
f2v=(-2*v+3)*v*v;
m=i*(tab2+1)+j;
for(int k=0;k<3;k++)
{
vert[m][k]=f1v*vert[j][k]+f2v*vert[tab1*(tab2+1)+j][k]+f1u*vert[i*(tab2+1)][k]+f2u*vert[i*(tab2+1)+tab2][k]-(f2v*vert[tab1*(tab2+1)][0]+f1v*vert[0][0])*f1u-(f2v*vert[(tab1+1)*(tab2+1)-1][k]+f1v*vert[tab2][k])*f2u;
}
}
}

for(int i=0;i<tab1;i++)
{
for(j=0;j<tab2;j++)
{
m=i*tab2+j;
vn[m][0]=vn[m][4]=m+i;
vn[m][1]=m+i+1;
vn[m][2]=m+i+tab2+2;
vn[m][3]=m+i+tab2+1;

}
}
//**

int vm,xplot,yplot,xcen=300,ycen=250;
double xw,yw,zw,sf=35;
double sinp=sin(70*M_PI/180);
double cosp=cos(70*M_PI/180);

for(int m=0;m<numFaces;m++)
{
for (int k=0;k<=3;k++)
{
vm=vn[m][k];
xw=vert[vm][0];
yw=vert[vm][1];
zw=vert[vm][2];
xplot=xcen+(int) (sf*xw);
yplot=ycen-(int) (sf*(yw*cosp+zw*sinp));
if(k==0)  Form1->PaintBox1->Canvas->MoveTo(xplot,yplot);
else
Form1->PaintBox1->Canvas->LineTo(xplot,yplot);
}
}
}
//------------------------------------------------------------------------------
void bspline(int n,int k,double x[],double y[],int mode=1)
{
int i=0,j,d,nsegs;
double t,dt;
double xp,yp;
nsegs=50;
n=n-1;
dt=1/(double) nsegs;
dt=dt*(n-k+2);
if(mode==2)
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
else
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
//---
int go=1,occindex=1,t1=1;
while(go)
{
if(i<k) xknot[i]=0;
else if(i<n+1)
{
for(int j=0;j<knotocc[occindex];j++)
{
xknot[i]=t1;
i++;
}
i--;
t1++;
occindex++;
}
else
{
for(int j=0;j<k;j++)
{
xknot[i]=t1;
i++;
}
go=0;
i--;
}
i++;
}
xknotnum=i;
//---
Form1->PaintBox1->Canvas->MoveTo((int) x[0],(int) y[0]);
for (i=0,t=0;i<nsegs;i++,t+=dt)
{
xp=0;
yp=0;
for(int j=0;j<=n+1;j++)
{
bit_to_metric_3D(splinex[j],spliney[j]);
xp=xp+xx1*calculateN(j,t,k);
yp=yp+yy1*calculateN(j,t,k);
}
metric_to_bit_3D(xp,yp);
Form1->PaintBox1->Canvas->LineTo((int) xx1,(int) yy1);
}
}
//--------------------------------------------------

