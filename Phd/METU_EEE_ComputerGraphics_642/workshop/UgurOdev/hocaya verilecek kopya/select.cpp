//--------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include"geo3d.h"
#include"point.h"
#include "select.h"
#include "deneme1.h"
//---------------------------------------------------------------------
/*#ifndef TestPointonLine()
extern int TestPointonLine(double tx,double ty,double px,double py,double qx,double qy);
#endif*/
extern int spline_index,box_lighted,point_found,hold_point_number,space,line_lighted,line_2D_translation,line_2D_trans;
extern int l_2D_t,line_lighted,mouse_down,translation_2D,translation_3D, point_2D_trans,p_2D_t;
extern int p_3D_t,l_3D_t,rotation_2D,point_2D_rotate,p_2D_r,rotation_3D;
extern double StorePoints[50][11];
extern int conic_index,find_if_box_selected(double x,double y,int point);
extern double StoreSpline[200][8];
extern void light_selected_yellow(int x,int y);
extern double StoreConic[100][6];
extern int point_selected,line_selected,circle_selected,ellipse_selected,hyperbola_selected,parabola_selected,naspline_selected,clampedspline_selected,cyclicspline_selected,anticyclic_selected,paraspline_selected;
extern int select_clicked,selection_number,spline_selected,go_to_select;
extern double splinex[20],spliney[20];
extern void natcubicspline(int n,double x[],double y[]);
extern void cubicspline(int n,double x[],double y[],double sl1,double sl2);
extern void parblend(int n,double x[],double y[]);
extern void cycliccubicspline(int n,double x[],double y[]);
extern void anticycliccubicspline(int n,double x[],double y[]);
extern int bezier_index,bezier_selected;
extern void lightsurface(void);
extern void delightsurface(void);
extern double StoreBezier[200][5];
extern double StoreBspline[200][7];
extern void lightsurfacered(int x,int y);
extern int surfaceindex,surfaceselected,bspline_index,bspline_selected;
extern int conic_selected;
//-------------------------------------------
int find_point_number(double delx,double dely)
{
//*
 int found=0,i=0,point_num=0;
 point_found=0;
 double px1,py1,qx1,qy1;
 int size,test_result;
 while((found==0)&&(i<=hold_point_number))//not all points inspected
  {//*
  i=i+1;
  int mode=StorePoints[i][1];
  if (space==2)
  {   //*
  switch (mode)
  {  //*
  case 1:
  size=StorePoints[i][8];
  switch (size)
  {    //*
  case 4:
  if((delx-StorePoints[i][2])<=2)
  if((dely-StorePoints[i][3])<=2)
  {     ///
  point_num=i;
  found=1;
  }      ///
  break;
  case 8:
  if((delx-StorePoints[i][2])<=4)
  if((dely-StorePoints[i][3])<=4)
  {      ///
  point_num=i;
  found=1;
  }        ///
  break;
  case 12:
  if((delx-StorePoints[i][2])<=6)
  if((dely-StorePoints[i][3])<=6)
  {          ///
  point_num=i;
  found=1;
  }            ///
  break;
 case 16:
 if((delx-StorePoints[i][2])<=8)
 if((dely-StorePoints[i][3])<=8)
  {              ///
  point_num=i;
  found=1;
  }                 ///
break;
}//end switch size//*
break;
case 2:
 px1=StorePoints[i][2];
 py1=StorePoints[i][3];
 qx1=StorePoints[i][4];
 qy1=StorePoints[i][5];
 test_result=TestPointonLine(delx,dely,px1,py1,qx1,qy1);
if(test_result==2)
{            ///
point_num=i;
found=1;
}               ///
break;
}//end mode  //*
}//*

if(space==3)
{   //*
 switch (mode)
  {    //*
  case 3:
  if((delx-StorePoints[i][5])<=2)
  if((dely-StorePoints[i][6])<=2)
  {       ///
  point_num=i;
  found=1;
  }          ///
  break;
  case 4:
 px1=StorePoints[i][8];
 py1=StorePoints[i][9];
 qx1=StorePoints[i][10];
 qy1=StorePoints[i][11];
 test_result=TestPointonLine(delx,dely,px1,py1,qx1,qy1);
if(test_result==2)
{              ///
point_num=i;
found=1;
}                 ///
 break;
 case 5:
 int e=find_if_box_selected(delx,dely ,i);
 if(e==1)
 {
 point_num=point_found;
 found=1;
 }
 break;
}//switch
}//*if
} //end while
if(found==1)
point_found=point_num;
else point_found=0;
return point_num;
}//////
//*******************************************
//*******************************************

/*void select_line_translate(int x,int y)
{
if(lighted==1)
{
delight_selected_point(StorePoints[point_found][2],StorePoints[point_found][3],StorePoints[point_found][8]);
}
if(line_lighted==1)
{
delight_selected_point(StorePoints[point_found][2],StorePoints[point_found][3],2);
}
if(line_lighted==1)
{
delight_selected_point(StorePoints[point_found][4],StorePoints[point_found][5],2);
line_lighted=0;
}
if(mouse_down==1)
{
 mouse_down=0;
 Form1->Cursor=crDefault;
 find_point_number(x,y);
 line_2D_translation=0;
 line_2D_trans=1;
 if(point_found!=0)
 {
 light_selected_point(StorePoints[point_found][2],StorePoints[point_found][3],2);
 light_selected_point(StorePoints[point_found][4],StorePoints[point_found][5],2);
 line_lighted=1;
 l_2D_t=1;
 }
}
}
//*
//*******
//-----------------------------
*/
void select_point_translate(int x,int y)
{
//-----
//----
 if (translation_2D==1) point_2D_trans=1;//turn on OK button
 if (translation_3D==1) point_2D_trans=1;
 if (rotation_2D==1) point_2D_rotate=1;
 if (rotation_3D==1) point_2D_rotate=1;
 if( space==2) {translation_2D=0,rotation_2D=0;}
 if( space==3) {translation_3D=0,rotation_3D=0;}
 Form1->Cursor=crDefault;
 point_found=find_point_number(x,y);


 if(point_found!=0)
 {
 if(space==2)
 {
 if(StorePoints[point_found][1]==1)
 {
 light_selected_point(StorePoints[point_found][2],StorePoints[point_found][3],StorePoints[point_found][8]);
 p_2D_t=1;
 }
 if(StorePoints[point_found][1]==2)
 {
 light_selected_point(StorePoints[point_found][2],StorePoints[point_found][3],2);
 light_selected_point(StorePoints[point_found][4],StorePoints[point_found][5],2);
 line_lighted=1;
 l_2D_t=1;
 }
 }
 if(space==3)
 {
  if(StorePoints[point_found][1]==3)
  {
  light_selected_point(StorePoints[point_found][5],StorePoints[point_found][6],4);
  p_3D_t=1;
  }
  if (StorePoints[point_found][1]==4)
  {
  light_selected_point(StorePoints[point_found][10],StorePoints[point_found][11],2);
  light_selected_point(StorePoints[point_found][8],StorePoints[point_found][9],2);
  line_lighted=1;
  l_3D_t=1;
  }
  if(StorePoints[point_found][1]==5)
  {
box_matrix1[3][0]=box_matrix1[3][1]=box_matrix1[3][2]=box_matrix1[3][3]=box_matrix1[3][4]=box_matrix1[3][5]=box_matrix1[3][6]=box_matrix1[3][7]=1;
box_matrix1[2][0]=box_matrix1[2][1]=box_matrix1[2][2]=box_matrix1[2][3]=box_matrix1[2][4]=box_matrix1[2][5]=box_matrix1[2][6]=box_matrix1[2][7]=0;
for(int i=0;i<8;i++)
{box_matrix1[0][i]=StorePoints[point_found+1][i];  }
for(int i=0;i<8;i++)
{box_matrix1[1][i]=StorePoints[point_found+2][i];}
Form1->PaintBox1->Canvas->Pen->Color=clRed;
draw_box();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
box_lighted=1;

   }

  }
}
}
//-------------------------------
//*
////////***************/////////////////

/*void select_point_rotate(int x,int y)
{
if(lighted==1)
{
delight_selected_point(StorePoints[point_found][2],StorePoints[point_found][3],StorePoints[point_found][8]);
}
if(mouse_down==1)
{
 mouse_down=0;
 Form1->Cursor=crDefault;
 find_point_number(x,y);
 point_2D_rotation=0;
 point_2D_rotate=1;
 if(point_found!=0)
 {
 light_selected_point(StorePoints[point_found][2],StorePoints[point_found][3],StorePoints[point_found][8]);
 p_2D_r=1;
 }
}
}   */
//----------------------------------------------------------------------------
void select_yellow(int x,int y)
{  //Turns into red
int i=1,found=0;
while((found==0)&&(i<=hold_point_number))
{
 if (StorePoints[i][1]==1)
 {
  if((abs(StorePoints[i][2]-x)<4) && (abs(StorePoints[i][3]-y)<4))
  {
//  Form1->Labe12->Visible=True;
  Form1->Label12->Caption="First click on the transformation you want to do. Then click on the point again for transformation!";
  light_selected_point(StorePoints[i][2],StorePoints[i][3],6);
  found=1;
  point_selected=1;
  select_clicked=1;
  selection_number=i;
  line_selected=0;
  }
}
 if (StorePoints[i][1]==2)
 {
  if(((abs(StorePoints[i][2]-x)<5) && (abs(StorePoints[i][3]-y)<5)) || ((abs(StorePoints[i][4]-x)<5) && (abs(StorePoints[i][5]-y)<5)))
 {
  //Form1->Panel2->Labe12->Visible=True;
  Form1->Label12->Caption="First click on the transformation you want to do. Then click on the line(not yellow boxes) for transformation!";
  light_selected_point(StorePoints[i][2],StorePoints[i][3],6);
  light_selected_point(StorePoints[i][4],StorePoints[i][5],6);
  found=1;
   selection_number=i;
   select_clicked=1;
   line_selected=1;
   point_selected=0;
 }
 }
 if (StorePoints[i][1]==4)
 {
  if(((abs(StorePoints[i][8]-x)<4) && (abs(StorePoints[i][9]-y)<4))||((abs(StorePoints[i][10]-x)<4) && (abs(StorePoints[i][11]-y)<4)))
 {
//  Form1->Labe12->Visible=True;
  Form1->Label12->Caption="First click on the transformation you want to do. Then click on the point again for transformation!";
  light_selected_point(StorePoints[i][8],StorePoints[i][9],6);
  light_selected_point(StorePoints[i][10],StorePoints[i][11],6);
  found=1;
  line_selected=1;
  select_clicked=1;
  selection_number=i;
  point_selected=0;
 }
 }
 i+=1;
 } //while
 if(found==0)
 {
 int f=0,j=0;
 double g;
 while((f==0)&&(j<=spline_index))
{
  double t=StoreSpline[j][4];//spline point number
  if((abs(StoreSpline[j][1]-x)<5) && (abs(StoreSpline[j][2]-y)<5))
  {
//Form1->Panel2->Labe12->Visible=True;
//Form1->Label12->Caption="Sorry!!Transformations for splines are not available yet!!";
  g=StoreSpline[j][5];
  light_selected_point(StoreSpline[j][1],StoreSpline[j][2],6);
  selection_number=j;
  spline_selected=1;
  select_clicked=1;
  line_selected=point_selected=0;
  for(int k=0;k<t;k++)
  light_selected_point(StoreSpline[j+k-(int)g][1],StoreSpline[j+k- (int)g][2],6);
  f=1;
  found=1;
  }
j+=1;
  }
}
//---------------
if(found==0)
{
i=0;
 while((found==0)&&(i<conic_index))
{
if(StoreConic[i][0]==1)
{
//light xcenter+radius,xcenter-radius
metric_to_bit_3D((StoreConic[i][1])+(StoreConic[i][3]),StoreConic[i][2]);
y1=xx1;
y2=yy1;
metric_to_bit_3D((StoreConic[i][1])-(StoreConic[i][3]),StoreConic[i][2]);
if(((abs(xx1-x)<5) && (abs(yy1-y)<5))||((abs(y1-x)<5) && (abs(y2-y)<5)))
{
 light_selected_point(xx1,yy1,6);
 light_selected_point(y1,y2,6);
 selection_number=i;
 conic_selected=1;
 found=1;
 select_clicked=1;
}
}
if(StoreConic[i][0]==2)
{
//light xcenter+radius,xcenter-radius
metric_to_bit_3D((StoreConic[i][1]),(StoreConic[i][2])+StoreConic[i][3]);
y1=xx1;
y2=yy1;
metric_to_bit_3D((StoreConic[i][1]),(StoreConic[i][2])-StoreConic[i][3]);
if(((abs(xx1-x)<5) && (abs(yy1-y)<5))||((abs(y1-x)<5) && (abs(y2-y)<5)))
{
 light_selected_point(xx1,yy1,6);
 light_selected_point(y1,y2,6);
 selection_number=i;
 conic_selected=1;
 found=1;
 select_clicked=1;
}
}

if(StoreConic[i][0]==3)
{
//light xcenter+radius,xcenter-radius
metric_to_bit_3D((StoreConic[i][1])+(StoreConic[i][3]),StoreConic[i][2]);
y1=xx1;
y2=yy1;
metric_to_bit_3D((StoreConic[i][1])-(StoreConic[i][3]),StoreConic[i][2]);
if(((abs(xx1-x)<5) && (abs(yy1-y)<5))||((abs(y1-x)<5) && (abs(y2-y)<5)))
{
 light_selected_point(xx1,yy1,6);
 light_selected_point(y1,y2,6);
 selection_number=i;
 conic_selected=1;
 found=1;
 select_clicked=1;
}
}
if(StoreConic[i][0]==4)
{
//light xcenter+radius,xcenter-radius
xx1=-StoreConic[i][2]/(2*StoreConic[i][1]);
yy1=(4*StoreConic[i][1]*StoreConic[i][3]-StoreConic[i][2]*StoreConic[i][2])/(4*StoreConic[i][1]);
metric_to_bit_3D(xx1,yy1);
if((abs(y1-x)<5) && (abs(y2-y)<5))
{
 light_selected_point(xx1,yy1,6);
// light_selected_point(y1,y2,6);
 selection_number=i;
 conic_selected=1;
 found=1;
 select_clicked=1;
}
//metric_to_bit_3D((StoreConic[i][1])-(StoreConic[i][3]),StoreConic[i][2]);
//light_selected_yellow(xx1,yy1,light);
}
i++;
}

//---

/* if(found==0)
 {
 int f=0,j=0;
 double g;
 while((found==0)&&(j<conic_index))
{
    bit_to_metric_3D(StoreConic[j][1],StoreConic[j][2]);
    if((abs(xx1-x<5)) && (abs(yy1-y)<5))
  {
//Form1->Panel2->Labe12->Visible=True;
//Form1->Label12->Caption="Sorry!!Transformations for splines are not available yet!!";
  light_selected_point(xx1,yy1,6);
  light_selected_point(StoreBezier[j+t][0],StoreBezier[j+t][1],6);
    selection_number=j;
  bezier_selected=1;
  found=1;
//  select_clicked=1;
  }
j+=1;
  }
} */

}
//---------------------------------------------------------------------------
 if(found==0)
 {
 int f=0,j=0;
 double g;
 while((found==0)&&(j<bezier_index))
{
  int t=StoreBezier[j][3]-1;//spline point number
  if((abs(StoreBezier[j][0]-x)<5) && (abs(StoreBezier[j][1]-y)<5))
  {
//Form1->Panel2->Labe12->Visible=True;
//Form1->Label12->Caption="Sorry!!Transformations for splines are not available yet!!";
  if(StoreBezier[j][2]==(StoreBezier[j][3]-1))
  {
  light_selected_point(StoreBezier[j-t][0],StoreBezier[j-t][1],6);
  light_selected_point(StoreBezier[j][0],StoreBezier[j][1],6);
  }
  else
  {
  light_selected_point(StoreBezier[j][0],StoreBezier[j][1],6);
  light_selected_point(StoreBezier[j+t][0],StoreBezier[j+t][1],6);
  }
  selection_number=j;
  bezier_selected=1;
  found=1;
  select_clicked=1;
  }
j+=1;
  }
}
//--------------------
 if(found==0)
 {
 int f=0,j=0;
 double g;
 while((found==0)&&(j<bspline_index))
{
  int t=StoreBspline[j][3]-1;//spline point number
  if((abs(StoreBspline[j][0]-x)<5) && (abs(StoreBspline[j][1]-y)<5))
  {
//Form1->Panel2->Labe12->Visible=True;
//Form1->Label12->Caption="Sorry!!Transformations for splines are not available yet!!";
  if(StoreBspline[j][2]==(StoreBspline[j][3]-1))
  {
  light_selected_point(StoreBspline[j-t][0],StoreBspline[j-t][1],6);
  light_selected_point(StoreBspline[j][0],StoreBspline[j][1],6);
  }
  else
  {
  light_selected_point(StoreBspline[j][0],StoreBspline[j][1],6);
  light_selected_point(StoreBspline[j+t][0],StoreBspline[j+t][1],6);
  }
  selection_number=j;
  bspline_selected=1;
  found=1;
  select_clicked=1;
  }
j+=1;
  }
}
//--------------------
if(found==0)
{
 lightsurfacered(x,y);
 if(surfaceselected==1)
 {
 found=1;
 select_clicked=1;
 }
 }
//--------------------
if(found==0)
{
int i=0;
/*
if(StoreConic[i][0]==1)
{
//light xcenter+radius,xcenter-radius
light_selected_point((StoreConic[i][1])+25*(StoreConic[i][3]),StoreConic[i][2]);
light_selected_point((StoreConic[i][1])-25*(StoreConic[i][3]),StoreConic[i][2]);
 selection_number=i;
 circle_selected=1;
   select_clicked=1;
 }
if(StoreConic[i][0]==2)
{
//light xcenter+radius,xcenter-radius
light_selected_point((StoreConic[i][1]),StoreConic[i][2]+(StoreConic[i][3]));
light_selected_point((StoreConic[i][1]),StoreConic[i][2]-(StoreConic[i][3]));
selection_number=i;
ellipse_selected=1;
  select_clicked=1;
}

if(StoreConic[i][0]==3)
{
//light xcenter+radius,xcenter-radius
light_selected_point((StoreConic[i][1])+(StoreConic[i][3]),StoreConic[i][2]);
light_selected_point((StoreConic[i][1])-(StoreConic[i][3]),StoreConic[i][2]);
hyperbola_selected=1;
selection_number=i;
  select_clicked=1;
}

if(StoreConic[i][0]==4)
{
//light xcenter+radius,xcenter-radius
light_selected_point((StoreConic[i][1])+(StoreConic[i][3]),StoreConic[i][2]);
light_selected_point((StoreConic[i][1])-(StoreConic[i][3]),StoreConic[i][2]);
selection_number=i;
parabola_selected=1;
  select_clicked=1;
} */

}
}
//-----------------------------------------------------------------------------
void selectall(int light)
{   //turn into yellow selection point
for(int i=0;i<=spline_index;i++)
{
light_selected_yellow(StoreSpline[i][1],StoreSpline[i][2],light);
}
//points and lines
for(int i=1;i<=hold_point_number;i++)
{
if(StorePoints[i][1]==1)
light_selected_yellow(StorePoints[i][2],StorePoints[i][3],light);
if(StorePoints[i][1]==2)
{
light_selected_yellow(StorePoints[i][2],StorePoints[i][3],light);
light_selected_yellow(StorePoints[i][4],StorePoints[i][5],light);
Form1->PaintBox1->Canvas->Pixels[StorePoints[i][4]][StorePoints[i][5]]=clBtnFace;
}
if (StorePoints[i][1]==4)
{
light_selected_yellow(StorePoints[i][8],StorePoints[i][9],light);
light_selected_yellow(StorePoints[i][10],StorePoints[i][11],light);
}
}
//conic sections
int i=0;
while(i<bspline_index)
{
light_selected_yellow(StoreBspline[i][0],StoreBspline[i][1],light);
i=i+StoreBspline[i][3]-1;
light_selected_yellow(StoreBspline[i][0],StoreBspline[i][1],light);
i+=1;
}
//---
i=0;
while(i<bezier_index)
{
light_selected_yellow(StoreBezier[i][0],StoreBezier[i][1],light);
i=i+StoreBezier[i][3]-1;
light_selected_yellow(StoreBezier[i][0],StoreBezier[i][1],light);
i+=1;

}
//---
for(int i=0;i<conic_index;i++)
{
if(StoreConic[i][0]==1)
{
//light xcenter+radius,xcenter-radius
metric_to_bit_3D((StoreConic[i][1])+(StoreConic[i][3]),StoreConic[i][2]);
light_selected_yellow(xx1,yy1,1);
metric_to_bit_3D((StoreConic[i][1])-(StoreConic[i][3]),StoreConic[i][2]);
light_selected_yellow(xx1,yy1,1);
}
if(StoreConic[i][0]==2)
{
//light xcenter+radius,xcenter-radius
metric_to_bit_3D((StoreConic[i][1]),(StoreConic[i][2])+StoreConic[i][3]);
light_selected_yellow(xx1,yy1,light);
metric_to_bit_3D((StoreConic[i][1]),(StoreConic[i][2])-StoreConic[i][3]);
light_selected_yellow(xx1,yy1,light);
}
if(StoreConic[i][0]==3)
{
//light xcenter+radius,xcenter-radius
metric_to_bit_3D((StoreConic[i][1])+(StoreConic[i][3]),StoreConic[i][2]);
light_selected_yellow(xx1,yy1,light);
metric_to_bit_3D((StoreConic[i][1])-(StoreConic[i][3]),StoreConic[i][2]);
light_selected_yellow(xx1,yy1,light);
}
if(StoreConic[i][0]==4)
{
//light xcenter+radius,xcenter-radius
xx1=-StoreConic[i][2]/(2*StoreConic[i][1]);
yy1=(4*StoreConic[i][1]*StoreConic[i][3]-StoreConic[i][2]*StoreConic[i][2])/(4*StoreConic[i][1]);
metric_to_bit_3D(xx1,yy1);
light_selected_yellow(xx1,yy1,light);
//metric_to_bit_3D((StoreConic[i][1])-(StoreConic[i][3]),StoreConic[i][2]);
//light_selected_yellow(xx1,yy1,light);
}
}
//light surfaces
lightsurface();
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void deselectall(void)
{
selectall(2);//everything lost
//relocate lost points in true format
int i=0;
while(i<spline_index)
{
  if(StoreSpline[i][0]==1)
  {
  for(int l=0;l<StoreSpline[i][4];l++)
  {
   splinex[l]=StoreSpline[i][1];
   spliney[l]=StoreSpline[i][2];
   i+=1;
  }
  natcubicspline(StoreSpline[i-1][4],splinex,spliney);
  }
  //----------------------
  if(StoreSpline[i][0]==2)
  {
  for(int l=0;l<StoreSpline[i][4];l++)
  {
   splinex[l]=StoreSpline[i][1];
   spliney[l]=StoreSpline[i][2];
   i+=1;
  }
  cubicspline(StoreSpline[i-1][4],splinex,spliney,StoreSpline[i-1][3],StoreSpline[i-1][7]);
  }
 //----------------------
  if(StoreSpline[i][0]==5)
  {
  for(int l=0;l<StoreSpline[i][4];l++)
  {
   splinex[l]=StoreSpline[i][1];
   spliney[l]=StoreSpline[i][2];
   i+=1;
  }
 parblend(StoreSpline[i-1][4],splinex,spliney);
  }
 //---------------------
  if(StoreSpline[i][0]==3)
  {
  for(int l=0;l<StoreSpline[i][4];l++)
  {
   splinex[l]=StoreSpline[i][1];
   spliney[l]=StoreSpline[i][2];
   i+=1;
  }
 cycliccubicspline(StoreSpline[i-1][4],splinex,spliney);
  }
  //---------------------
  if(StoreSpline[i][0]==4)
  {
  for(int l=0;l<StoreSpline[i][4];l++)
  {
   splinex[l]=StoreSpline[i][1];
   spliney[l]=StoreSpline[i][2];
   i+=1;
  }
 anticycliccubicspline(StoreSpline[i-1][4],splinex,spliney);
  }

}
//points and lines
for(int i=1;i<=hold_point_number;i++)
{
if(StorePoints[i][1]==1)
point_2D(StorePoints[i][2],StorePoints[i][3],4);
if(StorePoints[i][1]==2)
{
Form1->PaintBox1->Canvas->MoveTo(StorePoints[i][2],StorePoints[i][3]);
Form1->PaintBox1->Canvas->LineTo(StorePoints[i][4],StorePoints[i][5]);
}
}
//conic sections
for(int i=0;i<conic_index;i++)
{
if(StoreConic[i][0]==1)
{
//light xcenter+radius,xcenter-radius
Form1->PaintBox1->Canvas->Pixels[(StoreConic[i][1])+25*(StoreConic[i][3])][StoreConic[i][2]]=1;
Form1->PaintBox1->Canvas->Pixels[(StoreConic[i][1])-25*(StoreConic[i][3])][StoreConic[i][2]]=1;
}
if(StoreConic[i][0]==2)
{
//light xcenter+radius,xcenter-radius
Form1->PaintBox1->Canvas->Pixels[(StoreConic[i][1])][StoreConic[i][2]+(StoreConic[i][3])]=1;
Form1->PaintBox1->Canvas->Pixels[(StoreConic[i][1])][StoreConic[i][2]-(StoreConic[i][3])]=1;
}

if(StoreConic[i][0]==3)
{
//light xcenter+radius,xcenter-radius
Form1->PaintBox1->Canvas->Pixels[(StoreConic[i][1])+(StoreConic[i][3])][StoreConic[i][2]]=1;
Form1->PaintBox1->Canvas->Pixels[(StoreConic[i][1])-(StoreConic[i][3])][StoreConic[i][2]]=1;
}

if(StoreConic[i][0]==4)
{
//light xcenter+radius,xcenter-radius
Form1->PaintBox1->Canvas->Pixels[(StoreConic[i][1])+(StoreConic[i][3])][StoreConic[i][2]]=1;
Form1->PaintBox1->Canvas->Pixels[(StoreConic[i][1])-(StoreConic[i][3])][StoreConic[i][2]]=1;
}
}
delightsurface();
}
