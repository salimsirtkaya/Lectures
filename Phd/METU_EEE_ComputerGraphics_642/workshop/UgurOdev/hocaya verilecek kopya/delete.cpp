//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "deneme1.h"
#include "delete.h"
//---------------------------------------------------------------------
extern double StorePoints[50][11];
extern int point_found,hold_point_number;
//----------------------------
void delete_3D_point(void)
{
int j;
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
int which=StorePoints[point_found][1];
if(which==3)
{
int  x=StorePoints[point_found][5];
int  y=StorePoints[point_found][6];
 for ( j=0;j<3;j++)
 {
 Form1->PaintBox1->Canvas->MoveTo(x,y+j);
 Form1->PaintBox1->Canvas->LineTo(x+2,y+j);
 }
}
 if(which==4)
 {
int  x=StorePoints[point_found][8];
int  y=StorePoints[point_found][9];

 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 Form1->PaintBox1->Canvas->MoveTo(x,y);
 x=StorePoints[point_found][10];
 y=StorePoints[point_found][11];
 Form1->PaintBox1->Canvas->LineTo(x,y);
 }
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
}
//---------------------------------------

void delete_point_coor(int delx,int dely,int point_number)
{
int j;
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
int  x=StorePoints[point_number][2];
int  y=StorePoints[point_number][3];
int size=StorePoints[point_number][8];
switch (size)
{
 case 4:
 for ( j=0;j<3;j++)
 {
 Form1->PaintBox1->Canvas->MoveTo(x,y+j);
 Form1->PaintBox1->Canvas->LineTo(x+2,y+j);
 }
 break;

 case 8:
 for (j=0;j<5;j++)
 {
 Form1->PaintBox1->Canvas->MoveTo(x,y+j);
 Form1->PaintBox1->Canvas->LineTo(x+4,y+j);
 }
 break;
case 12:
 for ( j=0;j<7;j++)
 {
 Form1->PaintBox1->Canvas->MoveTo(x,y+j);
 Form1->PaintBox1->Canvas->LineTo(x+6,y+j);
 }
 break;

  case 16:
for ( j=0;j<9;j++)
{
 Form1->PaintBox1->Canvas->MoveTo(x,y+j);
 Form1->PaintBox1->Canvas->LineTo(x+8,y+j);
}
 break;

}
}
//***//**////***///
//**********

 void delete_point(int delx,int dely)//get screen coordinates
  { //*
  int size=0,mode=0,i=0,point_to_delete=0,found=0;

  while((found==0)&&(i<=hold_point_number))//not all points inspected
  { //*
  i=i+1;
  mode=StorePoints[i][1];
  switch (mode)
  {  //*
  case 1:
  size=StorePoints[i][8];
  switch (size)
  {   //*
  case 4:
  if((delx-StorePoints[i][2])<=2)
  if((dely-StorePoints[i][3])<=2)
  {   ///
  point_to_delete=i;
  found=1;
  }      ///
  break;
  case 8:
  if((delx-StorePoints[i][2])<=4)
  if((dely-StorePoints[i][3])<=4)
  {         ///
  point_to_delete=i;
  found=1;
  }            ///
  break;
  case 12:
  if((delx-StorePoints[i][2])<=6)
  if((dely-StorePoints[i][3])<=6)
  {               ///
  point_to_delete=i;
  found=1;
  }                  ///
  break;
 case 16:
 if((delx-StorePoints[i][2])<=8)
 if((dely-StorePoints[i][3])<=8)
  {                     ///
  point_to_delete=i;
  found=1;
  }                        ///
break;
}//end switch size//*
break;
}//end mode  //*

} //end while  //*
if(found==1)
{           //*
int j;
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
if(mode==1)
{              //*
int  x=StorePoints[point_to_delete][2];
int  y=StorePoints[point_to_delete][3];

switch (size)
{                 //*

 case 4:
 for ( j=0;j<3;j++)
 {                   ///
 Form1->PaintBox1->Canvas->MoveTo(x,y+j);
 Form1->PaintBox1->Canvas->LineTo(x+2,y+j);
 }                      ///
 break;

 case 8:
 for (j=0;j<5;j++)
 {                         ///
 Form1->PaintBox1->Canvas->MoveTo(x,y+j);
 Form1->PaintBox1->Canvas->LineTo(x+4,y+j);
 }                            ///
 break;
case 12:
 for ( j=0;j<7;j++)
 {                               ///
 Form1->PaintBox1->Canvas->MoveTo(x,y+j);
 Form1->PaintBox1->Canvas->LineTo(x+6,y+j);
 }                                  ///
 break;

  case 16:
for ( j=0;j<9;j++)
{                                      ///
 Form1->PaintBox1->Canvas->MoveTo(x,y+j);
 Form1->PaintBox1->Canvas->LineTo(x+8,y+j);
}                                         ///
 break;

}        //*end switch size
}        //*end mode
}        //*end found
}        //////**
