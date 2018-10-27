//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include <math.h>
#include "translate.h"
#include "hide.cpp"
#include "deneme1.h"
#include "point.h"
extern int box_drawn,point_3D_rotation,point_3D_translation;
extern int yellow_lighted,space,Line_2D_clicked,Point_clicked,box_clicked,hold_point_number,lighted,box_lighted;
extern double StorePoints[50][11];//,temp_matrix_a[4][1];
extern double temp_matrix_a[4][1];
extern  void Normalize_matrix(int matrix_name,int matrix_row,int matrix_column ,int row_to_normalize);
extern void metric_to_bit_3D(double x,double y);
extern double x1,x2,y1,y2,z1,z2,xx1,xx2,yy1,yy2,zz1,zz2;
extern double box_matrix1[4][8];
//----------------------------------------------------------------------
//****//

//****1

//*****

void point_2D(double x,double y,int point_size)
{
  for(int i=0;i<=point_size/2;i++)
  {
  for (int j=0;j<=point_size/2;j++)
  {
  double xxx=x+i;
  double yyy=y+j;
  Form1->PaintBox1->Canvas->Pixels[xxx][yyy]=1;
  }
  }
}
//******//
 void draw_box(void)
 { //projection on z=0
metric_to_bit_3D(box_matrix1[0][0],box_matrix1[1][0]);
Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][1],box_matrix1[1][1]);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][0],box_matrix1[1][0]);
Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][2],box_matrix1[1][2]);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][0],box_matrix1[1][0]);
Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][4],box_matrix1[1][4]);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][2],box_matrix1[1][2]);
Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][3],box_matrix1[1][3]);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][2],box_matrix1[1][2]);
Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][6],box_matrix1[1][6]);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][5],box_matrix1[1][5]);
Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][1],box_matrix1[1][1]);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][5],box_matrix1[1][5]);
Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][7],box_matrix1[1][7]);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][5],box_matrix1[1][5]);
Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][4],box_matrix1[1][4]);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][1],box_matrix1[1][1]);
Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][3],box_matrix1[1][3]);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][7],box_matrix1[1][7]);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][6],box_matrix1[1][6]);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
metric_to_bit_3D(box_matrix1[0][4],box_matrix1[1][4]);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
box_drawn=1;
}

/////****///
void light_selected_point(int x,int y,int size=6)
{
lighted=1;
Form1->PaintBox1->Canvas->Pen->Color=clRed;
for(int i=0;i<=(size/2);i++)
  {
  Form1->PaintBox1->Canvas->MoveTo(x,y+i);
  Form1->PaintBox1->Canvas->LineTo((x+size/2),(y+i));
  }
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
}
//******//

//-----------
void light_selected_yellow(int x,int y,int mode=1)
{
if(mode==1)
{
yellow_lighted=1;
Form1->PaintBox1->Canvas->Pen->Color=clYellow;
}
if(mode==2)
{
yellow_lighted=0;
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
}
for(int i=0;i<=3;i++)
  {
  Form1->PaintBox1->Canvas->MoveTo(x,y+i);
  Form1->PaintBox1->Canvas->LineTo((x+3),(y+i));
  }
  Form1->PaintBox1->Canvas->Pen->Color=clBlack;

}
//--------

//---------
void delight_selected_point(int x,int y,int size,int color=0)
{
lighted=0;
if (color==0)
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
if (color==1)
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;

for(int i=0;i<=size/2;i++)
  {
  Form1->PaintBox1->Canvas->MoveTo(x,y+i);
  Form1->PaintBox1->Canvas->LineTo((x+(size/2)),(y+i));
  }
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
}
//*****//

int TestPointonLine(double tx,double ty,double px,double py,double qx,double qy)
{
//if(abs((qy-py)*(tx-px)-(ty-py)*(qx-px))>=(max(abs(qx-px),abs(qy-py)))) return (0);
if (((qx<px) && (px<tx))||((qy<py)&&(py<ty))) return(1);
if (((tx<px) && (qx<tx))||((ty<py)&&(py<qy))) return(1);
if (((px<qx) && (qx<tx))||((py<qy)&&(qy<ty))) return(3);
if (((tx<qx) && (qx<px))||((ty<qy)&&(qy<py))) return(3);
return (2);
}
//******//
//----------------------------------------------
void translate_3D_point(int point_pos,double delx,double dely, double delz)
{
double t1,t2,t3,t4;
if(StorePoints[point_pos][1]==1)
{
t1=StorePoints[point_pos][2]+delx*25;
t2=StorePoints[point_pos][3]-dely*25;
t3=StorePoints[point_pos][6]+delz;
point_2D(t1,t2,4);
  StorePoints[point_pos][1]=1;   //hold_metric_value
  StorePoints[point_pos][2]=t1;
  StorePoints[point_pos][3]=t2;
  StorePoints[point_pos][6]=t3;
  StorePoints[point_pos][4]=StorePoints[point_pos][4]+delx;
  StorePoints[point_pos][5]=StorePoints[point_pos][5]+dely;
  StorePoints[point_pos][8]=4;
}
  if(StorePoints[point_pos][1]==4)
{
t1=StorePoints[point_pos][2]+delx;
t2=StorePoints[point_pos][3]+dely;
t3=StorePoints[point_pos][4]+delz;
metric_to_bit_3D(t1,t2);
Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
  StorePoints[point_pos][2]=t1;
  StorePoints[point_pos][3]=t2;
  StorePoints[point_pos][4]=t3;
  StorePoints[point_pos][8]=xx1;
  StorePoints[point_pos][9]=yy1;
t1=StorePoints[point_pos][5]+delx;
t2=StorePoints[point_pos][6]+dely;
t3=StorePoints[point_pos][7]+delz;
metric_to_bit_3D(t1,t2);
  StorePoints[point_pos][5]=t1;
  StorePoints[point_pos][6]=t2;
  StorePoints[point_pos][7]=t3;
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
StorePoints[point_pos][10]=xx1;
StorePoints[point_pos][11]=yy1;
}
if(StorePoints[point_found][1]==5)
  {
box_matrix1[3][0]=box_matrix1[3][1]=box_matrix1[3][2]=box_matrix1[3][3]=box_matrix1[3][4]=box_matrix1[3][5]=box_matrix1[3][6]=box_matrix1[3][7]=1;
box_matrix1[2][0]=box_matrix1[2][1]=box_matrix1[2][2]=box_matrix1[2][3]=box_matrix1[2][4]=box_matrix1[2][5]=box_matrix1[2][6]=box_matrix1[2][7]=0;
for(int i=0;i<8;i++)
{box_matrix1[0][i]=StorePoints[point_found+1][i];  }
for(int i=0;i<8;i++)
{box_matrix1[1][i]=StorePoints[point_found+2][i];}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
draw_box();
box_matrix1[3][0]=box_matrix1[3][1]=box_matrix1[3][2]=box_matrix1[3][3]=box_matrix1[3][4]=box_matrix1[3][5]=box_matrix1[3][6]=box_matrix1[3][7]=1;
box_matrix1[2][0]=box_matrix1[2][1]=box_matrix1[2][2]=box_matrix1[2][3]=box_matrix1[2][4]=box_matrix1[2][5]=box_matrix1[2][6]=box_matrix1[2][7]=0;
for(int i=0;i<8;i++)
{box_matrix1[0][i]=StorePoints[point_found+1][i]+delx;  }
for(int i=0;i<8;i++)
{box_matrix1[1][i]=StorePoints[point_found+2][i]+dely;}
//------------------------------------------
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
draw_box();

box_lighted=1;
}
}
//------------------------------------
//**/////**//

void init_point(void)
{
others_clicked();
switch(space)
{
case 2:
hide_boxes();
Form1->OK->Visible=True;
//Form1->Point_properties->Visible=True;
Form1->X1->Visible=True;
Form1->Y1->Visible=True;
Form1->Label1->Visible=True;
Form1->Label2->Visible=True;
Form1->Label1->Caption="X";
Form1->Label2->Caption="Y";
Form1->des_label1->Visible=True;
Form1->des_label1->Caption="Enter point coordinates";
Point_clicked=1;
break;
case 3:
hide_boxes();
Point_clicked=1;
Form1->OK->Visible=True;
Form1->Point_properties->Visible=False;
Form1->X1->Visible=True;
Form1->Y1->Visible=True;
Form1->X2->Visible=True;
Form1->Label1->Visible=True;
Form1->Label2->Visible=True;
Form1->Label3->Visible=True;
Form1->Label1->Caption="X";
Form1->Label2->Caption="Y";
Form1->Label3->Caption="Z";
Form1->des_label1->Visible=True;
Form1->des_label1->Caption="Enter point coordinates";
break;
}
}
