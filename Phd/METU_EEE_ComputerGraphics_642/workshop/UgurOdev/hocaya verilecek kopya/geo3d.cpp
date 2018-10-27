//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "translate.h"
#include "point.h"
#include "deneme1.h"
#include "geo3d.h"
//--------------------------------------------------------------------
extern double StorePoints[50][11],box_matrix[4][8],box_matrix1[4][8];
extern void rotation_matrix(int lx,int ly,int lz);
extern double degree_to_radian(double deg);
extern void init_projection(void);
extern void multiply_matrices(int sel);
extern int hold_point_number,point_found;
extern void Normalize_matrix(int matrix_name,int matrix_row,int matrix_column ,int row_to_normalize);
extern void metric_to_bit_3D(double x,double y);
extern double projection[4][4];
extern double x1,x2,y1,y2,z1,z2,xx1,xx2,yy1,yy2,zz1,zz2;
extern int point_found;

//---------------------------------------------------------------------------
void box3D(void)
{
//box left bottom is on origin
box_matrix[0][0]=box_matrix[1][0]=box_matrix[2][0]=box_matrix[0][1]=box_matrix[0][2]=box_matrix[0][3]=box_matrix[1][1]=box_matrix[2][2]=box_matrix[1][4]=box_matrix[1][5]=box_matrix[2][4]=box_matrix[2][6]=0;
box_matrix[3][0]=box_matrix[3][1]=box_matrix[3][2]=box_matrix[3][3]=box_matrix[3][4]=box_matrix[3][5]=box_matrix[3][6]=box_matrix[3][7]=1;
box_matrix[2][1]=box_matrix[2][3]=box_matrix[2][5]=box_matrix[2][7]=x2;
box_matrix[1][2]=box_matrix[1][3]=box_matrix[1][6]=box_matrix[1][7]=y1;
box_matrix[0][4]=box_matrix[0][5]=box_matrix[0][6]=box_matrix[0][7]=x1;
xx1=degree_to_radian(30);
rotation_matrix(1,0,0);        //rotate around x by 30
init_projection();            //
multiply_matrices(3);        //get rotated  one  temp_matrix3
rotation_matrix(0,1,0);     //then rotate around y by 30
multiply_matrices(6);      //rotatex*rotatey
multiply_matrices(5);     //rotated object matrix
Normalize_matrix(3,4,8,4);//transformed into H=0 plane
hold_point_number=hold_point_number+1;
StorePoints[hold_point_number][1]=5;  //store width,heigth,depth in order
StorePoints[hold_point_number][2]=x1;
StorePoints[hold_point_number][3]=y1;
StorePoints[hold_point_number][4]=x2;
point_found=hold_point_number=hold_point_number+1;
for(int i=0;i<8;i++)
{
StorePoints[hold_point_number][i]=box_matrix1[0][i];
}
hold_point_number=hold_point_number+1;
for(int i=0;i<8;i++)
{
StorePoints[hold_point_number][i]=box_matrix1[1][i];
}
hold_point_number=hold_point_number+1;
for(int i=0;i<8;i++)
{
StorePoints[hold_point_number][i]=box_matrix1[2][i];
}
}
//--------------------------------------------------------------------------

int find_if_box_selected(double x,double y,int point)
{
point=point+1;
int biggestx,smallestx,smallestx1,biggestx1,biggesty,smallesty,smallesty1,biggesty1;
smallestx=biggestx=smallesty=biggesty=0;
smallestx1=biggestx1=smallesty1=biggesty1=-1;
int found;
for(int i=0;i<8;i++)
{
  metric_to_bit_3D(StorePoints[point][i],StorePoints[point+1][i]);

  if((xx1<=x)&&(smallestx==0))
  {
  smallestx=1;
  }
  if((xx1>=x)&&(biggestx==0))
  {
  biggestx=1;
  }
  if((yy1>=y)&&(biggesty==0))
  {
  biggesty=1;
  }
  if((yy1<=y)&&(smallesty==0))
  {
  smallesty=1;
  }
} //found left most and right most points

if((smallestx==1)&&(smallesty==1)&&(biggestx==1)&&(biggesty==1))
 {
 point_found=point-1;
 return 1;
 }
 else return 0;
 }

