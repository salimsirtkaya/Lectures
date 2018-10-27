//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include <math.h>
#include "deneme1.h"
#include "hide.h"
#include "select.h"
//--------------------------------------------------------------------
extern int splinepointnumber,anticyclic_spline_clicked,cyclic_spline_clicked,naspline_clicked,nonnatcubicspline_clicked,fit_point_to_spline_clicked,para_blend,box_drawn,box_clicked,Line_2D_clicked,rotation_3D,translation_3D,Point_clicked;
extern int bilinearsurf_clicked,space,ruledsurface_clicked;
extern int bezier_clicked,bilinearsurf_clicked,beziersurface_clicked,surfacerotate;
extern int point_2D_rotate,translation_2D,line_3D_clicked;
extern int aroundz_clicked,aroundx_clicked,aroundy_clicked,point_found,spline_selected;
extern int translatesurface,bspline_clicked,bsplinesurface_clicked;
//---------------------------------------------------------------------------
void hide_boxes(void)
{
//*
Form1->Panel22->Visible=False;
Form1->Button15->Visible=False;
Form1->X1->Visible=False;
Form1->X2->Visible=False;
Form1->Y1->Visible=False;
Form1->Y2->Visible=False;
Form1->Z1->Visible=False;
Form1->Z2->Visible=False;
//Form1->ApplytoAll->Visible=False;
Form1->X1->Text="";
Form1->X2->Text="";
Form1->Y1->Text="";
Form1->Y2->Text="";
Form1->Z1->Text="";  
Form1->Z2->Text="";
Form1->Label12->Visible=False;
Form1->des_label1->Visible=False;
Form1->Label1->Visible=False;
Form1->Label2->Visible=False;
Form1->Label3->Visible=False;
Form1->Label4->Visible=False;
Form1->Label5->Visible=False;
Form1->Label6->Visible=False;
Form1->Label17->Visible=False;

Form1->OK->Visible=False;
Form1->Panel5->Visible=False;
Form1->aroundx->Visible=False;
Form1->aroundy->Visible=False;
Form1->aroundz->Visible=False;
Form1->degree->Visible=False;
Form1->OKrotate->Visible=False;
//Form1->arbitraryaxis->Visible=False;
Form1->labeldegree->Visible=False;
//Form1->Box->Visible=False;
Form1->Panel6->Visible=False;
Form1->Panel14->Visible=False;
Form1->Panel15->Visible=False;
Form1->Panel13->Visible=False;
Form1->Panel5->Visible=False;
Form1->Panel17->Visible=False;
Form1->Panel11->Visible=False;
Form1->Panel3->Visible=False;


Form1->Panel24->Visible=False;
box_drawn=0;
if(space==3) Form1->Button15->Visible=True;
}   //**

void others_clicked(void)
{
box_clicked=0;
//spline_selected=0;//*/*/
Line_2D_clicked=0;
rotation_3D=0;
translation_3D=0;
Point_clicked=0;
fit_point_to_spline_clicked=0;
para_blend=0;
naspline_clicked=0;
nonnatcubicspline_clicked=0;
cyclic_spline_clicked=0;
anticyclic_spline_clicked=0;
splinepointnumber=0;
//bilinearsurf_clicked=0;
bezier_clicked=0;
beziersurface_clicked=0;
bilinearsurf_clicked=0;
surfacerotate=0;
ruledsurface_clicked=0;
point_2D_rotate=0;
translation_2D=0;
line_3D_clicked=0;
aroundz_clicked=aroundx_clicked=aroundy_clicked=point_found=0;
translatesurface=0;
bspline_clicked=0;
bsplinesurface_clicked=0;
}
//----
void wait(void)
{
int q=1;
for (int i=0;i<50000;i++)
{
 q=q*sqrt(1222);
}
}