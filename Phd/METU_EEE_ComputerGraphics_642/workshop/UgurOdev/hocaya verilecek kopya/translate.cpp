//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include <math.h>
#include "translate.h"
#include "delete.h"
#include "deneme1.h"
#include "point.h"
//-----------------------------------------------------------------------
double temp_matrix1[4][4],box_matrix[4][8],box_matrix1[4][8];
double temp_matrix2[4][1];
double temp_matrix3[4][4],temp_matrix4[4][4];
double pointtorotate[4][1];
double projection[4][4];
extern double StorePoints[50][11];
extern double temp_matrix_a[4][1];
extern double temp_matrix_b[4][4];
extern double x1,x2,y1,y2,z1,z2,xx1,xx2,yy1,yy2,zz1,zz2;
extern int fault,hold_point_number,point_found;
extern void init_temp_matrix1(void);
extern void delete_3D_point(void);
extern void point_2D(double x,double y,int point_size);
extern int translatemouse,select_clicked,selection_number,spline_selected;
extern int point_selected,line_selected,circle_selected,ellipse_selected,hyperbola_selected,parabola_selected,naspline_selected,clampedspline_selected,cyclicspline_selected,anticyclic_selected,paraspline_selected;
extern void get_coordinates(int num_of_coor);
extern void delete_point_coor(int delx,int dely,int point_number);
extern int space;
//--- //
double degree_to_radian(double deg)
{
  double rad=(2*M_PI)*deg/360;
  return rad;
}
//****
void init_projection(void)

 {
 for(int i=0;i<4;i++)
{
for(int j=0;j<4;j++)
{
projection[i][j]=0;
}
projection[i][i]=1;
}
}

/////*****//////
void multiply_matrices(int sel=1)
{ //*
  int k=1;
  double temp1=0,temp2=0;
  if(sel==1)
  {  //*
  for(int i=0;i<4;i++)
  {     ///
  for (int j=0;j<4;j++)
  {        ///
  temp1=temp1+(temp_matrix1[i][j])*(pointtorotate[j][0]);
  }           ///
  temp_matrix2[i][0]=temp1;
  temp1=0;
  }              ///
  }                 //*end if
  if(sel==2)
  {               //*
  for(int i=0;i<4;i++)
  {                  ///
  for (int j=0;j<4;j++)
  {                     ////
  temp1=temp1+(temp_matrix1[i][j])*(pointtorotate[j][0]);
  }                         ///
  temp_matrix2[i][0]=temp1;
  temp1=0;
  }                            ///
  }                               //*end if
  ///*
  if(sel==4)
  {               //*
  for(int i=0;i<4;i++)
  {                  ///
  for (int j=0;j<4;j++)
  {                     ////
  temp1=temp1+(temp_matrix3[i][j])*(pointtorotate[j][0]);
  }                         ///
  temp_matrix2[i][0]=temp1;
  temp1=0;
  }                            ///
  }
  ///*
  if(sel==5)
  {
  temp1=0;
  for(int i=0;i<4;i++)
  {     ///
  for(int k=0;k<8;k++)
  {
  for (int j=0;j<4;j++)
  {        ///
  temp1=temp1+(temp_matrix3[i][j])*(box_matrix[j][k]);
  }          ///
  box_matrix1[i][k]=temp1;
  temp1=0;
  }
  temp1=0;
  }
 }
  //***
  if(sel==6)
  {
  temp1=0;
  for(int i=0;i<4;i++)
  {     ///
  for(int k=0;k<4;k++)
  {
  for (int j=0;j<4;j++)
  {        ///
  temp1=temp1+(temp_matrix3[i][j])*(temp_matrix1[j][k]);
  }          ///
  temp_matrix4[i][k]=temp1;
  temp1=0;
  }
  temp1=0;
  }
 for(int i=0;i<4;i++)
 for(int j=0;j<4;j++)
 temp_matrix3[i][j]=temp_matrix4[i][j];
 }

  ///*
  if(sel==3)
  {
  temp1=0;
  for(int i=0;i<4;i++)
  {     ///
  for(int k=0;k<4;k++)
  {
  for (int j=0;j<4;j++)
  {        ///
  temp1=temp1+(projection[i][j])*(temp_matrix1[j][k]);
  }          ///
  temp_matrix3[i][k]=temp1;
  temp1=0;
  }
  temp1=0;
  }              ///
                   //

  }

  }
//*

void bit_to_metric(double x,double y)
{
x1=x/25;
y1=(460-y)/25;
}
//////*******//////
//----------------------------------------
void rotation_matrix(int lx,int ly,int lz)
{


temp_matrix1[0][0]=(lx*lx)*(1-cos(xx1))+cos(xx1);
temp_matrix1[0][1]=lx*ly*(1-cos(xx1))-lz*sin(xx1);
temp_matrix1[0][2]=lx*lz*(1-cos(xx1))+ly*sin(xx1);
temp_matrix1[1][0]=lx*ly*(1-cos(xx1))+lz*sin(xx1);
temp_matrix1[1][1]=ly*ly*(1-cos(xx1))+cos(xx1);
temp_matrix1[1][2]=ly*lz*(1-cos(xx1))-lx*sin(xx1);
temp_matrix1[2][0]=lx*lz*(1-cos(xx1))-ly*sin(xx1);
temp_matrix1[2][1]=ly*lz*(1-cos(xx1))+lx*sin(xx1);
temp_matrix1[2][2]=lz*lz*(1-cos(xx1))+cos(xx1);
temp_matrix1[3][3]=1;
temp_matrix1[0][3]=temp_matrix1[1][3]=temp_matrix1[2][3]=temp_matrix1[3][0]=temp_matrix1[3][1]=temp_matrix1[3][2]=0;


}
//------------------------------------------------


//////*******///////
//******

void metric_to_bit(double x,double y)
{
xx1=x*25;
yy1=460-(y*25);
}
//******
void bit_to_metric_3D(double x,double y)
{
 xx1=(x-300)/25;
 yy1=(250-y)/25;
}
//*******
void metric_to_bit_3D(double x,double y)
{
xx1=x*25+300;
yy1=250-y*25;
}
//*****

//-------------
void rotatepoint(double degree,double aroundx,double aroundy,int pointnumber)
{
double degre=degree_to_radian(degree);
double x,y;
temp_matrix1[0][0]=cos(degre);
temp_matrix1[0][1]=-sin(degre);
temp_matrix1[0][2]=-aroundx*cos(degre)+aroundy*sin(degre)+aroundx;
temp_matrix1[1][0]=sin(degre);
temp_matrix1[1][1]=cos(degre);
temp_matrix1[1][2]=-aroundx*sin(degre)-aroundy*cos(degre)+aroundy;
temp_matrix1[2][0]=temp_matrix1[2][1]=0;
temp_matrix1[2][1]=1;
bit_to_metric(StorePoints[pointnumber][2],StorePoints[pointnumber][3]);
pointtorotate[0][0]=x1;
pointtorotate[1][0]=y1;
pointtorotate[2][0]=1;
multiply_matrices();
x=temp_matrix2[0][0];
y=temp_matrix2[1][0];
metric_to_bit(x,y);
}
/////**********//////
//***-----

void delete_line(double xx,double yy,double x,double y)
{
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
Form1->PaintBox1->Canvas->MoveTo(xx,yy);
Form1->PaintBox1->Canvas->LineTo(x,y);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
}

//***----
/////*********//////
void Normalize_matrix(int matrix_name,int matrix_row,int matrix_column ,int row_to_normalize)
{
double dividing_number;
if (matrix_name==1)
{//*
dividing_number=temp_matrix_a[3][0];
if(dividing_number!=0)
{   //*
for (int i=0;i<=matrix_column-1;i++)
for (int j=0;j<matrix_row-1;j++)
{      ///
 temp_matrix_a[j][i]=temp_matrix_a[j][i]/dividing_number;
}         ///
 }         //*
 }
///
if (matrix_name==3)
{//*
for (int i=0;i<=matrix_column-1;i++)
for (int j=0;j<matrix_row-1;j++)
{      ///
 dividing_number=box_matrix1[3][i];
 box_matrix1[j][i]=box_matrix1[j][i]/dividing_number;
}         ///
         //*
}

////
if (matrix_name==4)
{//*
for (int i=0;i<=matrix_column-1;i++)
for (int j=0;j<matrix_row-1;j++)
{      ///
 dividing_number=temp_matrix3[3][i];
 temp_matrix3[j][i]=temp_matrix3[j][i]/dividing_number;
}         ///
         //*
}

////
if (matrix_name==2)
{ //*
 dividing_number=temp_matrix2[3][0];
if(dividing_number!=0)
{  //*
for (int i=0;i<=matrix_column-1;i++)
for (int j=0;j<matrix_row-1;j++)
{     ///
 temp_matrix2[j][i]=temp_matrix2[j][i]/dividing_number;
}        ///

 }       //*
}
}
 //*****///
void rotate_2D_point(double x,double y)
{
xx1=degree_to_radian(x1);
rotation_matrix(0,0,1);//rotate around (x,y) point by given degree
bit_to_metric(x,y);
pointtorotate[0][0]=x1;
pointtorotate[1][0]=y1;
pointtorotate[3][0]=1;
multiply_matrices(1);
metric_to_bit(temp_matrix2[0][0],temp_matrix2[1][0]);
}
//-----------------------------------------------------------------------------
void rotate_3D_point(void)
{
int temp_mode=StorePoints[point_found][1];
if(temp_mode==3)//point
{
pointtorotate[0][0]=StorePoints[point_found][2];
pointtorotate[1][0]=StorePoints[point_found][3];
pointtorotate[2][0]=StorePoints[point_found][4];
pointtorotate[3][0]=1;
projection[2][2]=0;//projection on z=0;
//multiply_matrices(3);//projection*rotation //instead projection on z=0 directly taken
multiply_matrices(1);//return temp_matrix2=new point
delete_3D_point();//delete old point
StorePoints[point_found][2]=temp_matrix2[0][0];
StorePoints[point_found][3]=temp_matrix2[1][0];
StorePoints[point_found][4]=temp_matrix2[2][0];
Normalize_matrix(2,4,1,4);
metric_to_bit_3D(temp_matrix2[0][0],temp_matrix2[1][0]);//origin is (300,250)
StorePoints[point_found][5]=xx1;
StorePoints[point_found][6]=yy1;
point_2D(xx1,yy1,4);//put to screen coordinates
}
if(temp_mode==4)//point
{
pointtorotate[0][0]=StorePoints[point_found][2];
pointtorotate[1][0]=StorePoints[point_found][3];
pointtorotate[2][0]=StorePoints[point_found][4];
pointtorotate[3][0]=1;
projection[2][2]=0;//projection on z=0;
//multiply_matrices(3);//projection*rotation //instead projection on z=0 directly taken
multiply_matrices(1);//return temp_matrix2=new point
StorePoints[point_found][2]=temp_matrix2[0][0];
StorePoints[point_found][3]=temp_matrix2[1][0];
StorePoints[point_found][4]=temp_matrix2[2][0];
//Normalize_matrix(2,4,1,4);
metric_to_bit_3D(temp_matrix2[0][0],temp_matrix2[1][0]);//origin is (300,250)
StorePoints[point_found][8]=xx1;
StorePoints[point_found][9]=yy1;
//point_2D(xx1,yy1,4);//put to screen coordinates
Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
pointtorotate[0][0]=StorePoints[point_found][5];
pointtorotate[1][0]=StorePoints[point_found][6];
pointtorotate[2][0]=StorePoints[point_found][7];
pointtorotate[3][0]=1;
projection[2][2]=0;//projection on z=0;
//multiply_matrices(3);//projection*rotation //instead projection on z=0 directly taken
multiply_matrices(1);//return temp_matrix2=new point
StorePoints[point_found][5]=temp_matrix2[0][0];
StorePoints[point_found][6]=temp_matrix2[1][0];
StorePoints[point_found][7]=temp_matrix2[2][0];
//Normalize_matrix(2,4,1,4);
metric_to_bit_3D(temp_matrix2[0][0],temp_matrix2[1][0]);//origin is (300,250)
StorePoints[point_found][10]=xx1;
StorePoints[point_found][11]=yy1;
//point_2D(xx1,yy1,4);//put to screen coordinates
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
}
}

//-----------------------------------------------------------------------------
void translate(void)
{
if (select_clicked==0)
{
  Application->MessageBox("You should select object(point,line,,,) by mouse first!!","Error",MB_OK);
}
else
{
//check for point
if(point_selected==1)
{
int delx=StorePoints[selection_number][2];
int dely=StorePoints[selection_number][3];
int mx=StorePoints[selection_number][8];
if(translatemouse==0)
get_coordinates(2);
if(fault==0)
{
delete_point_coor(delx,dely,selection_number);
xx1=delx+x1*25;
yy1=dely-y1*25;
point_2D(xx1,yy1,mx);
hold_point_number=hold_point_number+1;
  StorePoints[selection_number][1]=1;
  StorePoints[selection_number][2]=xx1;
  StorePoints[selection_number][3]=yy1;
  StorePoints[selection_number][8]=mx;
}  //fault
}
if(line_selected==1)
{
if(space==2)
{
get_coordinates(2);
double x=StorePoints[selection_number][2];
double y=StorePoints[selection_number][3];
double xx=StorePoints[selection_number][4];
double yy=StorePoints[selection_number][5];
x=x+x1*25;
y=y-y1*25;
xx=xx+x1*25;
yy=yy-y1*25;
  StorePoints[selection_number][2]=x;
  StorePoints[selection_number][3]=y;
  StorePoints[selection_number][4]=xx;
  StorePoints[selection_number][5]=yy;
}
if(space==3)
{
get_coordinates(3);
double x=StorePoints[selection_number][2];
double y=StorePoints[selection_number][3];
double xx=StorePoints[selection_number][4];
double yy=StorePoints[selection_number][5];
double xxx=StorePoints[selection_number][6];
double yyy=StorePoints[selection_number][7];
StorePoints[selection_number][2]=x+x1;
StorePoints[selection_number][3]=y+y1;
StorePoints[selection_number][4]=xx+x2;
StorePoints[selection_number][5]=yy+x1;
StorePoints[selection_number][6]=xxx+y1;
StorePoints[selection_number][7]=yyy+x2;
if(x2==0) x2=1;
metric_to_bit_3D((x+x1)*x2,(y+y1)*x2);
StorePoints[selection_number][8]=xx1;
StorePoints[selection_number][9]=yy1;
metric_to_bit_3D((yy+x1)*x2,(xxx+y1)*x2);
StorePoints[selection_number][10]=xx1;
StorePoints[selection_number][11]=yy1;
}
}
}
}
//---------------------------------------------------------------------------
void put3d(double x,double y,double z,double teta1=0.523599,double teta2=0.523599,double r=1.67)//x,y,z,perspective y angle,perspective x angle,viewport
{
x1=(x*cos(teta2)+z*sin(teta2));
y1=((sin(teta1))*(sin(teta2))*x+(cos(teta1))*y-(sin(teta1))*(cos(teta2))*z);
}
//---------------------------------------------------------------------------


