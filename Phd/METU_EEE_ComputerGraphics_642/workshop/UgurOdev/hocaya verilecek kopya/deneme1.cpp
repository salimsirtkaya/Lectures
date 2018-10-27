//----ugur gungor 109252-7----------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include <math.h>
#include "geo3d.cpp"
#include "point.cpp"
#include "cerceve.cpp"
#include "translate.cpp"
#include "select.cpp"
#include "delete.cpp"
#include "curves.cpp"
#include "surface.cpp"
#include "rotangle.h"
#include "deneme1.h"
//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
double StorePoints[50][11],temp_matrix_a[4][1],temp_matrix_b[4][4],StoreConic[100][6],StoreSpline[200][8],StoreSplineReal[200][8],Spline_mode[200],StoreBezier[200][5],StoreBspline[200][7];//mode,x1,y1,x2,y2,z1,z2,size
double knot[20],knot1[100];
int vn[120][5],numfaces=12,ne=12,tab1=12,tab2=10,numFaces=120;
int n00,n11;
double vert[143][3];
double xp0[20],yp0[20],zp0[20],xp1[20],yp1[20],zp1[20],xp2[20],yp2[20],zp2[20],xp3[20],yp3[20],zp3[20];
double P[4][3],B[4][3],BBx[5][3],BBy[5][3],BBz[5][3];
int tempx[4][4],tempy[4][4],tempz[4][4];
 FILE *dosya,*dosya2,*tempdosya;
int surfaceindex,surfind;
//-------------                                                     //splinenum,x,y,z                                      //x,y,relativepointpos,curvepointnumber
double x1,x2,y1,y2,z1,z2,xx1,xx2,yy1,yy2,zz1,zz2,x3,y3,z3,a1,a2,a3,aa1,aa2,aa3,aaa1,aaa2,aaa3;
int conic_index,scale,scale_clicked,translation_2D=0,lorp,translation_3D=0,rotation_2D=0,point_found=0,point_2D_translation=0,point_2D_trans=0,transformation_clicked=0,origin_state,mouse_down,mouse_up,space=3,hit_to_delete,fault,hold_point_number;
int circlex,circley,Point_size=4,Point_properties_clicked=0;
int p_2D_t=0,h_to_d=0,l_2D_t=0;
int point_2D_rotate,p_2D_r,lighted=0,line_lighted=0,box_lighted=0;
int Line_2D_clicked=0,first_touch=0,line_two_end=1,line_con=0,line_end=0,cont_line=0;
int line_2D_translation=0,line_2D_trans=0;
int Point_clicked=0,p_3D_tr=0,point_3D_translation=0,rotation_3D=0;
int circle_clicked,ellipse_clicked,parabola_clicked,hyperbola_clicked,perspective_clicked,box_drawn,aroundx_clicked,aroundy_clicked,aroundz_clicked,p_3D_t,l_3D_t,line_3D_clicked=0,box_clicked;
int fit_point_to_spline_clicked,spline_drawn,cubicspline_clicked,nonnatcubicspline_clicked,splinepointnumber,naspline_clicked;
int hold_spline_point,spline_mode;
double splinex[20],spliney[20],splinez[20],slope1,slope2;
int para_blend,cyclic_spline_clicked,anticyclic_spline_clicked=0,spline_index=0,spline_number=1;
int select_clicked,yellow_lighted;
int point_selected,line_selected,circle_selected,ellipse_selected,hyperbola_selected,parabola_selected,naspline_selected,clampedspline_selected,cyclicspline_selected,anticyclic_selected,paraspline_selected;
int selection_number,spline_selected,go_to_select;
int bezier_clicked,bezier_index,selectbezier_clicked,bezier_clickedup,count,sel1,bezier_selected;
int   bezier_knotmove,bezier_knotmovedown,selectedbezierknot,bezier_knotmoved,check=0;
int bspline_clicked,bspline_index,bindex=1,zentered;
int rotaroundx=30,rotaroundy=30;
int ruledsurface_clicked,term,bsurface_clicked,n22,n33;
int bilinearsurf_clicked,changesurface_clicked;
double nsegs1=10,nsegs2=10;
int foundsurfindex,surfpointindex,surfaceknotselected,rulecheck,e1,r1,s1;
void lightsurface(void);
void delightsurface(void);
void redrawsurfaces(void);
double Mx[4][4],My[4][4];
int numofbicubicsurf,bicubicind=-1;
int beziersurface_clicked,beziersurfind,bbindex,bezcheck,surfpointindex2;
void drawpolygon(void);
int surfaceselected,translatesurface;
void surfacetransformation(int i);
int surfacerotate;
int t1,t2,t3,t4,translatemouse;
void rotatearoundx(double x,double y,double z,double teta);
void rotatearoundy(double x,double y,double z,double teta);
void rotatearoundz(double x,double y,double z,double teta);
void perspectivetrans(double x,double y,double z,double e,double r,double k);
int first3dline=1,f1=0,mode=0;
double zz3;
double xknot[200],knotocc[50],xknotnum,occindex;
int bsplinesurface_clicked,order=3,sel11,selectbspline_clicked;
int bspline_selected,bspline_knotmove,bspline_knotmovedown,selectedbsplineknot,bspline_knotmoved;
int selectedbspline;
int vertexnum,changevertex_clicked;
int bsplinesurfind,bspindex,bsplinecheck,scalesurface;
double zzz1,zzz2,zzz3;
double xpos,ypos;
int conic_selected,cmode;

//--------------------------------------------------------------------------
void initializeknot(void);

//-----
__fastcall TForm1::TForm1(TComponent* Owner): TForm(Owner)
{
hide_boxes();
}
//---------------------------------------------------------------------------
typedef struct
{
double p[4][3];
double bx[5][3],by[5][3],bz[5][3];
//double qy[4][4];
int selfindex;
int mode;
} node;
node StoreSurface[50];
//---------------------------------------------------------------------------
void init_temp_matrix1(void)
{
for(int i=0;i<4;i++)
{
for(int j=0;j<4;j++)
temp_matrix1[i][j]=0;
}
}

//---------------------------------------------------------------------------
void get_coordinates(int num_of_coor)
{ //*
switch (num_of_coor)
{    //*
case 1:
if (Form1->X1->Text=="") fault=1;
else  x1=StrToFloat(Form1->X1->Text);
break;
case 2:
if (Form1->X1->Text=="") fault=1;
else  x1=StrToFloat(Form1->X1->Text);
if (Form1->Y1->Text=="") fault=1;
else  y1=StrToFloat(Form1->Y1->Text);
break;
case 3:
if (Form1->X1->Text=="") fault=1;
else  x1=StrToFloat(Form1->X1->Text);
if (Form1->Y1->Text=="") fault=1;
else  y1=StrToFloat(Form1->Y1->Text);
if (Form1->X2->Text=="") fault=1;
else  x2=StrToFloat(Form1->X2->Text);
break;
case 4:
if (Form1->X1->Text=="") fault=1;
else  x1=StrToFloat(Form1->X1->Text);
if (Form1->Y1->Text=="") fault=1;
else  y1=StrToFloat(Form1->Y1->Text);
if (Form1->X2->Text=="") fault=1;
else  x2=StrToFloat(Form1->X2->Text);
if (Form1->Y2->Text=="") fault=1;
else  y2=StrToFloat(Form1->Y2->Text);
break;
case 6:
if (Form1->X1->Text=="") fault=1;
else  x1=StrToFloat(Form1->X1->Text);
if (Form1->Y1->Text=="") fault=1;
else  y1=StrToFloat(Form1->Y1->Text);
if (Form1->X2->Text=="") fault=1;
else  x2=StrToFloat(Form1->X2->Text);
if (Form1->Y2->Text=="") fault=1;
else  y2=StrToFloat(Form1->Y2->Text);
if (Form1->Z1->Text=="") fault=1;
else  z1=StrToFloat(Form1->Z1->Text);
if (Form1->Z2->Text=="") fault=1;
else  z2=StrToFloat(Form1->Z2->Text);
break;
}
if (fault==1)
{      ///
Application->MessageBox("You should enter a valid coordinate value!!","Error",MB_OK);
}         ///
} //**///


void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
space=2;
hide_boxes();
Button15->Visible=False;
Panel4->Visible=False;
Translation->Visible=False;
Rotation->Visible=False;
perspective->Visible=False;
Transformation->Caption="+ Transformation" ;
transformation_clicked=0;
Transformation->Visible=True;
Form1->Box->Visible=False;
RadioButton1->Checked=True;
RadioButton2->Checked=False;
PaintBox1->Canvas->Brush->Color=clBtnFace;
TRect t;
t.Left=0;
t.Top=0;
t.Right=641;
t.Bottom=461;
PaintBox1->Canvas->FillRect(t);
hold_point_number=0;
Curves->Visible=True;
Splines->Visible=True;
Bezier->Visible=True;
Button15->Visible=False;
}
////////***********////////
///////**********//////////
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
space=3;
hide_boxes();

spline_drawn=0;
Splines->Visible=True;
Panel4->Visible=False;
Button8->Visible=False;
Bezier->Visible=False;
Translation->Visible=False;
Rotation->Visible=False;
perspective->Visible=False;
Transformation->Caption="+ Transformation" ;
transformation_clicked=0;

Form1->Box->Visible=True;
Button15->Visible=True;

RadioButton1->Checked=False;
RadioButton2->Checked=True;;
PaintBox1->Canvas->Brush->Color=clBtnFace;
TRect t;
t.Left=0;
t.Top=0;
t.Right=641;
t.Bottom=461;
PaintBox1->Canvas->FillRect(t);
hold_point_number=0;
Curves->Visible=False;
}
//---------------------------------------------------------------------------
///////*********////////
////////********////////

void __fastcall TForm1::PaintBox1MouseMove(TObject *Sender, TShiftState Shift,
	int X, int Y)
{
xpos=(X-300)/25;
ypos=(250-Y)/25;
Edit1->Text=FloatToStr(xpos)+","+FloatToStr(ypos);
//-----
 if((translation_2D==1)&&(translatemouse==1))
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
int  delx=StorePoints[selection_number][2];
int dely=StorePoints[selection_number][3];
int  mx=StorePoints[selection_number][8];
delete_point_coor(delx,dely,selection_number);
point_2D(X,Y,mx);
hold_point_number=hold_point_number+1;
  StorePoints[selection_number][1]=1;
  StorePoints[selection_number][2]=X;
  StorePoints[selection_number][3]=Y;
  StorePoints[selection_number][8]=mx;
}  //fault
 }
}

//-----
if((circle_clicked==1)&&(mouse_down==1))
{
 double ry=Y-circley;
 double rx=X-circlex;
 double rr=ry*ry+rx*rx;
 float r=sqrt(rr);
 draw_circle(circlex,circley,r);
}
//-----
if ((cont_line==1)&&(line_end==0))
{
Form1->PaintBox1->Canvas->LineTo(X,Y);
Form1->PaintBox1->Canvas->MoveTo(X,Y);
}
//-----
if(bezier_knotmovedown==1)
{
bezier_knotmoved=1;
if(StoreBezier[selectedbezierknot][2]==0)
Form1->PaintBox1->Canvas->MoveTo(StoreBezier[selectedbezierknot+1][0],StoreBezier[selectedbezierknot+1][1]);
else
Form1->PaintBox1->Canvas->MoveTo(StoreBezier[selectedbezierknot-1][0],StoreBezier[selectedbezierknot-1][1]);
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
if(check==0)
Form1->PaintBox1->Canvas->LineTo(StoreBezier[selectedbezierknot][0],StoreBezier[selectedbezierknot][1]);
else
Form1->PaintBox1->Canvas->LineTo(x1,y1);
if(StoreBezier[selectedbezierknot][2]==0)
Form1->PaintBox1->Canvas->MoveTo(StoreBezier[selectedbezierknot+1][0],StoreBezier[selectedbezierknot+1][1]);
else
Form1->PaintBox1->Canvas->MoveTo(StoreBezier[selectedbezierknot-1][0],StoreBezier[selectedbezierknot-1][1]);
Form1->PaintBox1->Canvas->Pen->Color=clYellow;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
Form1->PaintBox1->Canvas->LineTo(X,Y);
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
//****

if(StoreBezier[selectedbezierknot][2]==StoreBezier[selectedbezierknot][3]-1)
Form1->PaintBox1->Canvas->MoveTo(StoreBezier[selectedbezierknot-1][0],StoreBezier[selectedbezierknot-1][1]);
else
Form1->PaintBox1->Canvas->MoveTo(StoreBezier[selectedbezierknot+1][0],StoreBezier[selectedbezierknot+1][1]);
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
if(check==0)
Form1->PaintBox1->Canvas->LineTo(StoreBezier[selectedbezierknot][0],StoreBezier[selectedbezierknot][1]);
else
Form1->PaintBox1->Canvas->LineTo(x1,y1);
if(StoreBezier[selectedbezierknot][2]==StoreBezier[selectedbezierknot][3]-1)
{
Form1->PaintBox1->Canvas->MoveTo(StoreBezier[selectedbezierknot-1][0],StoreBezier[selectedbezierknot-1][1]);
}
else
Form1->PaintBox1->Canvas->MoveTo(StoreBezier[selectedbezierknot+1][0],StoreBezier[selectedbezierknot+1][1]);
Form1->PaintBox1->Canvas->Pen->Style=psDash;
Form1->PaintBox1->Canvas->Pen->Color=clYellow;
Form1->PaintBox1->Canvas->LineTo(X,Y);
wait();
wait();
wait();
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
check=1;
}
//-----------------------
if(bspline_knotmovedown==1)
{
bspline_knotmoved=1;
if(StoreBspline[selectedbsplineknot][2]==0)
Form1->PaintBox1->Canvas->MoveTo(StoreBspline[selectedbsplineknot+1][0],StoreBspline[selectedbsplineknot+1][1]);
else
Form1->PaintBox1->Canvas->MoveTo(StoreBspline[selectedbsplineknot-1][0],StoreBspline[selectedbsplineknot-1][1]);
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
if(check==0)
Form1->PaintBox1->Canvas->LineTo(StoreBspline[selectedbsplineknot][0],StoreBspline[selectedbsplineknot][1]);
else
Form1->PaintBox1->Canvas->LineTo(x1,y1);
if(StoreBspline[selectedbsplineknot][2]==0)
Form1->PaintBox1->Canvas->MoveTo(StoreBspline[selectedbsplineknot+1][0],StoreBspline[selectedbsplineknot+1][1]);
else
Form1->PaintBox1->Canvas->MoveTo(StoreBspline[selectedbsplineknot-1][0],StoreBspline[selectedbsplineknot-1][1]);
Form1->PaintBox1->Canvas->Pen->Color=clYellow;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
Form1->PaintBox1->Canvas->LineTo(X,Y);
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
//****

if(StoreBspline[selectedbsplineknot][2]==StoreBspline[selectedbsplineknot][3]-1)
Form1->PaintBox1->Canvas->MoveTo(StoreBspline[selectedbsplineknot-1][0],StoreBspline[selectedbsplineknot-1][1]);
else
Form1->PaintBox1->Canvas->MoveTo(StoreBspline[selectedbsplineknot+1][0],StoreBspline[selectedbsplineknot+1][1]);
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
if(check==0)
Form1->PaintBox1->Canvas->LineTo(StoreBezier[selectedbsplineknot][0],StoreBezier[selectedbsplineknot][1]);
else
Form1->PaintBox1->Canvas->LineTo(x1,y1);
if(StoreBezier[selectedbezierknot][2]==StoreBspline[selectedbspline][3]-1)
{
Form1->PaintBox1->Canvas->MoveTo(StoreBspline[selectedbsplineknot-1][0],StoreBspline[selectedbsplineknot-1][1]);
}
else
Form1->PaintBox1->Canvas->MoveTo(StoreBspline[selectedbsplineknot+1][0],StoreBspline[selectedbsplineknot+1][1]);
Form1->PaintBox1->Canvas->Pen->Style=psDash;
Form1->PaintBox1->Canvas->Pen->Color=clYellow;
Form1->PaintBox1->Canvas->LineTo(X,Y);
wait();
wait();
wait();
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
check=1;
}
//-----------------------
if(surfaceknotselected==1)
{
changesurface_clicked=0;
delightsurface();
if(StoreSurface[foundsurfindex].mode==1)
  {
 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 bilinearsurface();
 x1=X;
 y1=Y;
 StoreSurface[foundsurfindex].p[surfpointindex][0]=X;
 StoreSurface[foundsurfindex].p[surfpointindex][1]=Y;
 Form1->PaintBox1->Canvas->Pen->Color=clBlack;
  for(int m=0;m<4;m++)
 {
  P[m][0]=StoreSurface[foundsurfindex].p[m][0];
  P[m][1]=StoreSurface[foundsurfindex].p[m][1];
 }
 P[surfpointindex][0]=x1;
 P[surfpointindex][1]=y1;
 // bilinearsurface();
  redrawsurfaces();
 wait();
 wait();
 }
//---
if(StoreSurface[foundsurfindex].mode==2)
  {
 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 ruledsurface();
 x1=X;
 y1=Y;
 StoreSurface[foundsurfindex].p[surfpointindex][0]=X;
 StoreSurface[foundsurfindex].p[surfpointindex][1]=Y;
 Form1->PaintBox1->Canvas->Pen->Color=clBlack;
 redrawsurfaces();
  for(int m=0;m<4;m++)
 {
  P[m][0]=StoreSurface[foundsurfindex].p[m][0];
  P[m][1]=StoreSurface[foundsurfindex].p[m][1];
 }
 P[surfpointindex][0]=x1;
 P[surfpointindex][1]=y1;

 // bilinearsurface();
 wait();
 wait();
 }
//---
if(StoreSurface[foundsurfindex].mode==3)
  {
 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 dosya2=fopen("bicubicdata.txt","r");
 for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n",&e1,&r1,&s1);
 dosya=fopen("bicubic.txt","w");
 for(int i=0;i<16;i++)
{
fscanf(dosya2,"%d %d %d\n",&r1,&e1,&s1);
fprintf(dosya,"%d %d %d\n",r1,e1,s1);
}
fclose(dosya2);
fclose(dosya);
bicubicsurface();
 x1=X;
 y1=Y;
dosya=fopen("bicubic.txt","r");
 for(int t=0;t<4;t++)
{
 for(int i=0;i<4;i++)
 {
  fscanf(dosya,"%d %d %d\n",&r1,&e1,&s1);
  tempx[i][t]=r1;
  tempy[i][t]=e1;
  tempz[i][t]=s1;
 }
}
fclose(dosya);
if(surfpointindex==0)
{
tempx[0][0]=X;
tempy[0][0]=Y;
}
if(surfpointindex==1)
{
 tempx[0][1]=X;
 tempy[0][1]=Y;
}
if(surfpointindex==2)
{
 tempx[1][0]=X;
 tempy[1][0]=Y;
}
if(surfpointindex==3)
{
 tempx[1][1]=X;
 tempy[1][1]=Y;
}
//***
dosya=fopen("bicubic.txt","w");
 for(int t=0;t<4;t++)
{
 for(int i=0;i<4;i++)
 {
  fprintf(dosya,"%d %d %d\n",tempx[i][t],tempy[i][t],tempz[i][t]);
 }
}
fclose(dosya);
dosya2=fopen("bicubicdata.txt","r+");
for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
fscanf(dosya2,"%d %d %d\n",&e1,&r1,&s1);
dosya=fopen("bicubic.txt","r");
for(int i=0;i<16;i++)
{
fscanf(dosya,"%d %d %d\n",&r1,&e1,&s1);
fprintf(dosya2,"%d %d %d\n",r1,e1,s1);
}
fclose(dosya2);
fclose(dosya);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
redrawsurfaces();
 wait();
 wait();
}
//-----
if(StoreSurface[foundsurfindex].mode==4)
  {
 bezier_clicked=0;
 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 for(int t=0;t<3;t++)
 for(int i=0;i<5;i++)
 {
 BBx[i][t]=StoreSurface[foundsurfindex].bx[i][t];
 BBy[i][t]=StoreSurface[foundsurfindex].by[i][t];
 BBz[i][t]=StoreSurface[foundsurfindex].bz[i][t];
 }
beziersurface();
delightsurface();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
 StoreSurface[foundsurfindex].bx[surfpointindex][surfpointindex2]=X;
 StoreSurface[foundsurfindex].by[surfpointindex][surfpointindex2]=Y;
 BBx[surfpointindex][surfpointindex2]=X;
 BBy[surfpointindex][surfpointindex2]=Y;
Form1->PaintBox1->Canvas->Pen->Color=clYellow;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
redrawsurfaces();
 // bilinearsurface();
 wait();
 wait();
 wait();
 wait();
 }
 //---
 if(StoreSurface[foundsurfindex].mode==5)
  {
 bspline_clicked=0;
 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 for(int t=0;t<3;t++)
 for(int i=0;i<5;i++)
 {
 BBx[i][t]=StoreSurface[foundsurfindex].bx[i][t];
 BBy[i][t]=StoreSurface[foundsurfindex].by[i][t];
 BBz[i][t]=StoreSurface[foundsurfindex].bz[i][t];
 }
bsplinesurface();
delightsurface();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
 StoreSurface[foundsurfindex].bx[surfpointindex][surfpointindex2]=X;
 StoreSurface[foundsurfindex].by[surfpointindex][surfpointindex2]=Y;
 BBx[surfpointindex][surfpointindex2]=X;
 BBy[surfpointindex][surfpointindex2]=Y;
Form1->PaintBox1->Canvas->Pen->Color=clYellow;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
redrawsurfaces();
 // bilinearsurface();
 wait();
 wait();
 wait();
 wait();
 }
//-----
}
x1=X;
y1=Y;
//check=1;
}
//---------------------------------------------------------------------------
///////*********//////
//////*******/////////


//---------------------------------------------------------------------------
/////******//////
///////******//////////

void __fastcall TForm1::Point_propertiesClick(TObject *Sender)
{
if(Point_properties_clicked==0)
{
Panel3->Visible=True;
Point_properties->Caption="-     Properties" ;
if((space==2)&&(Point_clicked==1))
{
Point_properties_size->Visible=True;
Point_properties_size->Text="Size";
}
if(Line_2D_clicked==1)
{
LineProperties->Visible=True;
LineProperties->Text="Line";
}
Point_properties_clicked=1;
}
else if (Point_properties_clicked==1)
{
Panel3->Visible=False;
Point_properties->Caption="+     Properties" ;
Point_properties_size->Visible=False;
LineProperties->Visible=False;
Point_properties_clicked=0;
}
}
//---------------------------------------------------------------------------
/////*****/////
/////*****////
//---------------------------------------------------------------------------

void __fastcall TForm1::OKClick(TObject *Sender)
{
int p_2D_tr=0,p_2D_rr=0,l_2D_tr=0,l_2D_rr=0,p_3D_tr=0,l_3D_tr=0;
//-------------------------------------------------------------------------
deselectall();
if (box_clicked==1) //draw a box with =30,y=30 rotated
{
get_coordinates(3);
box3D();
draw_box();
}
//--------------------------------------
if((translation_3D==1)&&(bezier_selected==1)&&(space==3))
{
get_coordinates(3);
double x22;
if(((x2<=0)&&(x2<1))||((-1<x2)&&(x2<0))) x22=1;
else if (x2<=-1) x22=-1/x2;
else x22=x2;
double g=StoreBezier[selection_number][2];
double t=StoreBezier[selection_number][3];
double r,e;
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for (int i=0;i<StoreBezier[selection_number][3];i++)
{
splinex[i]=StoreBezier[selection_number+i-(int)g][0];
spliney[i]=StoreBezier[selection_number+i-(int)g][1];
if(i==0)
Form1->PaintBox1->Canvas->MoveTo(splinex[i],spliney[i]);
else
Form1->PaintBox1->Canvas->LineTo(splinex[i],spliney[i]);
}
bezier(t,splinex,spliney,2);
Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
for (int i=0;i<StoreBezier[selection_number][3];i++)
{
bit_to_metric_3D(splinex[i],spliney[i]);
metric_to_bit_3D((xx1+x1)*x22,(yy1+y1)*x22);
splinex[i]=StoreBezier[selection_number+i-(int)g][0]=xx1;
spliney[i]=StoreBezier[selection_number+i-(int)g][1]=yy1;
StoreBezier[selection_number+i-(int)g][4]=StoreBezier[selection_number+i-(int)g][4]+x2;
if(i==0)
Form1->PaintBox1->Canvas->MoveTo(splinex[i],spliney[i]);
else
Form1->PaintBox1->Canvas->LineTo(splinex[i],spliney[i]);
}
bezier(t,splinex,spliney,1);
}
//-------------------------------------
if((translation_3D==1)&&(bspline_selected==1)&&(space==3))
{
get_coordinates(3);
double x22;
if(((x2<=0)&&(x2<1))||((-1<x2)&&(x2<0))) x22=1;
else if (x2<=-1) x22=-1/x2;
else x22=x2;
double g=StoreBspline[selection_number][2];
double t=StoreBspline[selection_number][3];
double r,e;
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for (int i=0;i<StoreBspline[selection_number][3];i++)
{
splinex[i]=StoreBspline[selection_number+i-(int)g][0];
spliney[i]=StoreBspline[selection_number+i-(int)g][1];
knotocc[i]=StoreBspline[selection_number+i-(int)g][6];
if(i==0)
Form1->PaintBox1->Canvas->MoveTo(splinex[i],spliney[i]);
else
Form1->PaintBox1->Canvas->LineTo(splinex[i],spliney[i]);
}
splinepointnumber=StoreBspline[selection_number][3];
bspline(t,StoreBspline[selection_number][5],splinex,spliney,2);
Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
for (int i=0;i<StoreBspline[selection_number][3];i++)
{
bit_to_metric_3D(splinex[i],spliney[i]);
metric_to_bit_3D((xx1+x1)*x22,(yy1+y1)*x22);
splinex[i]=StoreBspline[selection_number+i-(int)g][0]=xx1;
spliney[i]=StoreBspline[selection_number+i-(int)g][1]=yy1;
StoreBspline[selection_number+i-(int)g][4]=StoreBspline[selection_number+i-(int)g][4]+x2;
if(i==0)
Form1->PaintBox1->Canvas->MoveTo(splinex[i],spliney[i]);
else
Form1->PaintBox1->Canvas->LineTo(splinex[i],spliney[i]);
}
bspline(t,StoreBspline[selection_number][5],splinex,spliney,1);
}
//-------------------------------------
if((translation_3D==1)&&(conic_selected==1)&&(space==3))
{
get_coordinates(3);
if(fault==0)
{
if(StoreConic[selection_number][0]==1)//circle
{
xx1=StoreConic[selection_number][1];
xx2=StoreConic[selection_number][2];
yy1=StoreConic[selection_number][3];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
cmode=1;
draw_circle(xx1,xx2,yy1);
xx1=StoreConic[selection_number][1]=StoreConic[selection_number][1]+x1;
xx2=StoreConic[selection_number][2]=StoreConic[selection_number][2]+y1;
StoreConic[selection_number][5]=StoreConic[selection_number][5]+y1;

Form1->PaintBox1->Canvas->Pen->Color=clBlack;
cmode=0;
draw_circle(xx1,xx2,yy1);
}
//-
if(StoreConic[selection_number][0]==2)//circle
{
xx1=StoreConic[selection_number][1];
xx2=StoreConic[selection_number][2];
yy1=StoreConic[selection_number][3];
yy2=StoreConic[selection_number][4];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
draw_ellipse(xx1,xx2,yy1,yy2);
xx1=StoreConic[selection_number][1]=StoreConic[selection_number][1]+x1;
xx2=StoreConic[selection_number][2]=StoreConic[selection_number][2]+y1;
StoreConic[selection_number][5]=StoreConic[selection_number][5]+y1;
//yy1=StoreConic[selection_number][3]=StoreConic[selection_number][3]+y1;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
draw_ellipse(xx1,xx2,yy1,yy2);
}
//-
if(StoreConic[selection_number][0]==3)//circle
{
xx1=StoreConic[selection_number][1];
xx2=StoreConic[selection_number][2];
yy1=StoreConic[selection_number][3];
yy2=StoreConic[selection_number][4];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
draw_hyperbola(xx1,xx2,yy1,yy2);
xx1=StoreConic[selection_number][1]=StoreConic[selection_number][1]-x1;
xx2=StoreConic[selection_number][2]=StoreConic[selection_number][2]-x2;
StoreConic[selection_number][5]=StoreConic[selection_number][5]+y1;
//yy1=StoreConic[selection_number][3]=StoreConic[selection_number][3]+y1;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
draw_hyperbola(xx1,xx2,yy1,yy2);
}
//--
if(StoreConic[selection_number][0]==4)//circle
{
xx1=StoreConic[selection_number][1];
xx2=StoreConic[selection_number][2];
yy1=StoreConic[selection_number][3];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
draw_parabola(xx1,xx2,yy1);
xx2=StoreConic[selection_number][1]=2*xx1*xx2-2*xx1*x1;
xx2=StoreConic[selection_number][2]=StoreConic[selection_number][3]+x2;
StoreConic[selection_number][5]=StoreConic[selection_number][5]+y1;
//yy1=StoreConic[selection_number][3]=StoreConic[selection_number][3]+y1;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
draw_parabola(xx1,xx2,yy1);
}
//--
}
}
//--------------------------------------
if((translation_3D==1)&&(spline_selected==1)&&(space==3))
{
if(Spline_mode[selection_number]==1)
{
get_coordinates(3);
if(x2==0) x2=1;
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
natcubicspline(t,splinex,spliney);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
StoreSplineReal[selection_number][1]=StoreSplineReal[selection_number][1]+x1;
StoreSplineReal[selection_number][2]=StoreSplineReal[selection_number][2]+y1;
metric_to_bit_3D(StoreSplineReal[selection_number][1],StoreSplineReal[selection_number][2]);
StoreSpline[selection_number][1]=xx1;
StoreSpline[selection_number][2]=yy1;
for(int k=0;k<t;k++)
{
StoreSplineReal[selection_number+k-(int)g][1]=StoreSplineReal[selection_number+k-(int)g][1]+x1;
StoreSplineReal[selection_number+k-(int)g][2]=StoreSplineReal[selection_number+k-(int)g][2]+y1;
StoreSplineReal[selection_number+k-(int)g][8]=StoreSplineReal[selection_number+k-(int)g][8]+x2;
metric_to_bit_3D(StoreSplineReal[selection_number+k-(int)g][1]*x2,StoreSplineReal[selection_number+k-(int)g][2]*x2);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
splinex[k]=xx1;
spliney[k]=yy1;
}
natcubicspline(t,splinex,spliney);
}
//---
if(StoreSpline[selection_number][0]==2)
{
get_coordinates(3);
if(fault==0)
{
double s=StoreSpline[selection_number][5];
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1];
spliney[i]=StoreSpline[selection_number+i-(int)s][2];
slope1=StoreSpline[selection_number][3];
slope2=StoreSpline[selection_number][7];
}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
cubicspline(StoreSpline[selection_number][4],splinex,spliney,slope1,slope2);

for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1]=splinex[i]+x1*25;
spliney[i]=StoreSpline[selection_number+i-(int)s][2]=spliney[i]-y1*25;
StoreSpline[selection_number+i-(int)s][6]=StoreSpline[selection_number+i-(int)s][6]+z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
cubicspline(StoreSpline[selection_number][4],splinex,spliney,slope1,slope2);
}
else fault=0;
}
//----
if(StoreSpline[selection_number][0]==5)
{
get_coordinates(3);
if(fault==0)
{
double s=StoreSpline[selection_number][5];
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1];
spliney[i]=StoreSpline[selection_number+i-(int)s][2];
}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
mode=1;
parblend(StoreSpline[selection_number][4],splinex,spliney);
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1]=splinex[i]+x1*25;
spliney[i]=StoreSpline[selection_number+i-(int)s][2]=spliney[i]-y1*25;
StoreSpline[selection_number+i-(int)s][6]=StoreSpline[selection_number+i-(int)s][6]+z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
mode=0;
parblend(StoreSpline[selection_number][4],splinex,spliney);
}
}
//----
if(StoreSpline[selection_number][0]==3)
{
get_coordinates(3);
if(fault==0)
{
double s=StoreSpline[selection_number][5];
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1];
spliney[i]=StoreSpline[selection_number+i-(int)s][2];
}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
cycliccubicspline(StoreSpline[selection_number][4],splinex,spliney);
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1]=splinex[i]+x1*25;
spliney[i]=StoreSpline[selection_number+i-(int)s][2]=spliney[i]-y1*25;
StoreSpline[selection_number+i-(int)s][6]=StoreSpline[selection_number+i-(int)s][6]+z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
cycliccubicspline(StoreSpline[selection_number][4],splinex,spliney);
}
}
//----
if(StoreSpline[selection_number][0]==4)
{
get_coordinates(3);
if(fault==0)
{
double s=StoreSpline[selection_number][5];
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1];
spliney[i]=StoreSpline[selection_number+i-(int)s][2];
}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
anticycliccubicspline(StoreSpline[selection_number][4],splinex,spliney);
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1]=splinex[i]+x1*25;
spliney[i]=StoreSpline[selection_number+i-(int)s][2]=spliney[i]-y1*25;
StoreSpline[selection_number+i-(int)s][6]=StoreSpline[selection_number+i-(int)s][6]+z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
anticycliccubicspline(StoreSpline[selection_number][4],splinex,spliney);
}
}
//----
}
//----------------------------------------------
if(translatesurface==1)
{
//int i=foundsurfindex;
get_coordinates(3);//x1,y1
zz1=x1;
zz2=-y1;
zz3=x2;
surfacetransformation(foundsurfindex);
//translatesurface=0;
}
//-------------------------------------
if (point_2D_rotate==1)
{
p_2D_rr=1;
//point_2D_rotate;
point_found=selection_number;
if(point_found==0)
{
  Application->MessageBox("You should select object(point,line,,,) by mouse first!!","Error",MB_OK);
}
if (point_found!=0)
{
if(StorePoints[point_found][1]==1)
{
int mx=StorePoints[point_found][8];
get_coordinates(1);
if(fault==0)
{
int delx=StorePoints[point_found][2];
int dely=StorePoints[point_found][3];
delete_point_coor(delx,dely,point_found);
rotate_2D_point(delx,dely);
point_2D(xx1,yy1,mx);
  StorePoints[point_found][1]=1;
  StorePoints[point_found][2]=xx1;
  StorePoints[point_found][3]=yy1;
  }   ///
  else fault=0;
  }     //*
  }
if(StorePoints[point_found][1]==2)
{
get_coordinates(1);
double temp=x1;
if(fault==0)
{
delete_line(StorePoints[point_found][2],StorePoints[point_found][3],StorePoints[point_found][4],StorePoints[point_found][5]);
if(line_lighted==1)
{
delight_selected_point(StorePoints[point_found][2],StorePoints[point_found][3],2,1);
delight_selected_point(StorePoints[point_found][4],StorePoints[point_found][5],2,1);
line_lighted=0;
}
rotate_2D_point(StorePoints[point_found][2],StorePoints[point_found][3]);
 StorePoints[point_found][2]=xx1;
 StorePoints[point_found][3]=yy1;

Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
 x1=temp;
 rotate_2D_point(StorePoints[point_found][4],StorePoints[point_found][5]);
 StorePoints[point_found][4]=xx1;
 StorePoints[point_found][5]=yy1;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->LineTo( StorePoints[point_found][4],StorePoints[point_found][5]);
}
else fault=0;
}
}    //**

//------------------------------------------------------------------------------

if ((point_2D_trans==1)&&(space==3))
{
p_3D_tr=1;
l_3D_tr=1;
point_2D_trans=0;
if(point_found==0)
{
  Application->MessageBox("You should select object(point,line,,,) by mouse first!!","Error",MB_OK);
}
if (point_found!=0)
{
get_coordinates(3);
if(fault==0)
{
delete_3D_point();  //deletes line or point
delight_selected_point(StorePoints[point_found][10],StorePoints[point_found][11],2,1);
delight_selected_point(StorePoints[point_found][8],StorePoints[point_found][9],2,1);
line_lighted=0;
translate_3D_point(point_found,x1,y1,x2);  //translates line or point
}
  else fault=0;
}
}
//---------------------------------------------
if(scale==1)
{
p_2D_tr=1;
scale=0;
int lorp;
point_found=select_clicked;
if(point_found==0)
{
  Application->MessageBox("You should select object(point,line,,,) by mouse first!!","Error",MB_OK);
}
if (point_found!=0)
{
lorp=StorePoints[point_found][1];
}
if(lorp==2)
{
if(line_lighted==1)
{
delight_selected_point(StorePoints[point_found][2],StorePoints[point_found][3],2,1);
delight_selected_point(StorePoints[point_found][4],StorePoints[point_found][5],2,1);
line_lighted=0;
}
double x=StorePoints[point_found][2];
double y=StorePoints[point_found][3];
double xx=StorePoints[point_found][4];
double yy=StorePoints[point_found][5];
get_coordinates(1);
if(fault==0)
{
delete_line(x,y,xx,yy);
x=x*x1;
y=y*x1;
xx=xx*x1;
yy=yy*x1;
Form1->PaintBox1->Canvas->MoveTo(x,y);
Form1->PaintBox1->Canvas->LineTo(xx,yy);
  StorePoints[point_found][1]=2;
  StorePoints[point_found][2]=x;
  StorePoints[point_found][3]=y;
  StorePoints[point_found][4]=xx;
  StorePoints[point_found][5]=yy;
}
  else fault=0;
}
//---
}
//------------------
if((scale_clicked==1)&&(space==3))
{
deselectall();
if(line_selected==1)
{
get_coordinates(1);
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
Form1->PaintBox1->Canvas->MoveTo(StorePoints[selection_number][8],StorePoints[selection_number][9]);
Form1->PaintBox1->Canvas->LineTo(StorePoints[selection_number][10],StorePoints[selection_number][11]);
StorePoints[selection_number][2]=StorePoints[selection_number][2]*xx1;
StorePoints[selection_number][3]=StorePoints[selection_number][3]*xx1;
StorePoints[selection_number][4]=StorePoints[selection_number][4]*xx1;
StorePoints[selection_number][5]=StorePoints[selection_number][5]*xx1;
StorePoints[selection_number][6]=StorePoints[selection_number][6]*xx1;
StorePoints[selection_number][7]=StorePoints[selection_number][7]*xx1;
metric_to_bit_3D(StorePoints[selection_number][2],StorePoints[selection_number][3]);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
StorePoints[selection_number][8]=xx1;
StorePoints[selection_number][9]=yy1;
metric_to_bit_3D(StorePoints[selection_number][5],StorePoints[selection_number][6]);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
StorePoints[selection_number][10]=xx1;
StorePoints[selection_number][11]=yy1;
}
//-----
if(spline_selected==1)
{
get_coordinates(1);
if(fault==0)
{
if(Spline_mode[selection_number]==1)
{
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
natcubicspline(t,splinex,spliney);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
StoreSplineReal[selection_number][1]=StoreSplineReal[selection_number][1]+x1;
StoreSplineReal[selection_number][2]=StoreSplineReal[selection_number][2]+y1;
metric_to_bit_3D(StoreSplineReal[selection_number][1],StoreSplineReal[selection_number][2]);
StoreSpline[selection_number][1]=xx1;
StoreSpline[selection_number][2]=yy1;
for(int k=0;k<t;k++)
{
StoreSplineReal[selection_number+k-(int)g][1]=StoreSplineReal[selection_number+k-(int)g][1]+x1;
StoreSplineReal[selection_number+k-(int)g][2]=StoreSplineReal[selection_number+k-(int)g][2]+y1;
StoreSplineReal[selection_number+k-(int)g][8]=StoreSplineReal[selection_number+k-(int)g][8]+x2;
metric_to_bit_3D(StoreSplineReal[selection_number+k-(int)g][1]*x2,StoreSplineReal[selection_number+k-(int)g][2]*x2);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
splinex[k]=xx1;
spliney[k]=yy1;
}
natcubicspline(t,splinex,spliney);
}
//---
if(StoreSpline[selection_number][0]==2)
{
get_coordinates(3);
if(fault==0)
{
double s=StoreSpline[selection_number][5];
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1];
spliney[i]=StoreSpline[selection_number+i-(int)s][2];
slope1=StoreSpline[selection_number][3];
slope2=StoreSpline[selection_number][7];
}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
cubicspline(StoreSpline[selection_number][4],splinex,spliney,slope1,slope2);

for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1]=splinex[i]+x1*25;
spliney[i]=StoreSpline[selection_number+i-(int)s][2]=spliney[i]-y1*25;
StoreSpline[selection_number+i-(int)s][6]=StoreSpline[selection_number+i-(int)s][6]+z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
cubicspline(StoreSpline[selection_number][4],splinex,spliney,slope1,slope2);
}
else fault=0;
}
//----
if(StoreSpline[selection_number][0]==5)
{
get_coordinates(3);
if(fault==0)
{
double s=StoreSpline[selection_number][5];
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1];
spliney[i]=StoreSpline[selection_number+i-(int)s][2];
}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
mode=1;
parblend(StoreSpline[selection_number][4],splinex,spliney);
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1]=splinex[i]+x1*25;
spliney[i]=StoreSpline[selection_number+i-(int)s][2]=spliney[i]-y1*25;
StoreSpline[selection_number+i-(int)s][6]=StoreSpline[selection_number+i-(int)s][6]+z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
mode=0;
parblend(StoreSpline[selection_number][4],splinex,spliney);
}
}
//----
if(StoreSpline[selection_number][0]==3)
{
get_coordinates(3);
if(fault==0)
{
double s=StoreSpline[selection_number][5];
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1];
spliney[i]=StoreSpline[selection_number+i-(int)s][2];
}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
cycliccubicspline(StoreSpline[selection_number][4],splinex,spliney);
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1]=splinex[i]+x1*25;
spliney[i]=StoreSpline[selection_number+i-(int)s][2]=spliney[i]-y1*25;
StoreSpline[selection_number+i-(int)s][6]=StoreSpline[selection_number+i-(int)s][6]+z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
cycliccubicspline(StoreSpline[selection_number][4],splinex,spliney);
}
}
//----
if(StoreSpline[selection_number][0]==4)
{
get_coordinates(3);
if(fault==0)
{
double s=StoreSpline[selection_number][5];
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1];
spliney[i]=StoreSpline[selection_number+i-(int)s][2];
}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
anticycliccubicspline(StoreSpline[selection_number][4],splinex,spliney);
for (int i=0;i<StoreSpline[selection_number][4];i++)
{
splinex[i]=StoreSpline[selection_number+i-(int)s][1]=splinex[i]+x1*25;
spliney[i]=StoreSpline[selection_number+i-(int)s][2]=spliney[i]-y1*25;
StoreSpline[selection_number+i-(int)s][6]=StoreSpline[selection_number+i-(int)s][6]+z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
anticycliccubicspline(StoreSpline[selection_number][4],splinex,spliney);
}
}
}
else fault=0;

}
//-----
if(surfaceselected==1)
{
get_coordinates(1);
zz1=x1;
scalesurface=1;
surfacetransformation(foundsurfindex);
}
}
//---------------------------------------------
if((line_selected==1)&&(space==3)&&(translation_3D==1))
{
deselectall();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
Form1->PaintBox1->Canvas->MoveTo(StorePoints[selection_number][8],StorePoints[selection_number][9]);
Form1->PaintBox1->Canvas->LineTo(StorePoints[selection_number][10],StorePoints[selection_number][11]);
translate();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->MoveTo(StorePoints[selection_number][8],StorePoints[selection_number][9]);
Form1->PaintBox1->Canvas->LineTo(StorePoints[selection_number][10],StorePoints[selection_number][11]);
}
//--------------------------------------------
if ((translation_2D==1)&&(space==2))
{
p_2D_tr=1;
point_2D_trans=0;

if (point_selected==1)
{
translate();
}
if(line_selected==1)
{
point_found=select_clicked;
double x=StorePoints[point_found][2];
double y=StorePoints[point_found][3];
double xx=StorePoints[point_found][4];
double yy=StorePoints[point_found][5];
get_coordinates(2);
if(fault==0)
{
delete_line(x,y,xx,yy);
x=x+x1*25;
y=y-y1*25;
xx=xx+x1*25;
yy=yy-y1*25;
Form1->PaintBox1->Canvas->MoveTo(x,y);
Form1->PaintBox1->Canvas->LineTo(xx,yy);
  StorePoints[point_found][1]=2;
  StorePoints[point_found][2]=x;
  StorePoints[point_found][3]=y;
  StorePoints[point_found][4]=xx;
  StorePoints[point_found][5]=yy;
}     //fault
else fault=0;
}
}
//----------------------------------------------------

if ((space==2)&&(Point_clicked==1)&&(p_2D_tr==0))
{               //*
get_coordinates(2);
if (fault==0)
{                  //*
metric_to_bit(x1,y1);
point_2D(xx1,yy1,Point_size);
hold_point_number=hold_point_number+1;
  StorePoints[hold_point_number][1]=1;
  StorePoints[hold_point_number][2]=xx1;
  StorePoints[hold_point_number][3]=yy1;
  StorePoints[hold_point_number][8]=Point_size;
}
else fault=0;
}
//----
if ((Line_2D_clicked==1)&&(p_2D_tr==0)&&(p_2D_rr==0))
{
get_coordinates(4);
if (fault==0)
{
metric_to_bit(x1,y1);
Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
hold_point_number=hold_point_number+1;
  StorePoints[hold_point_number][1]=2;
  StorePoints[hold_point_number][2]=xx1;
  StorePoints[hold_point_number][3]=yy1;
metric_to_bit(x2,y2);
Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
  StorePoints[hold_point_number][4]=xx1;
  StorePoints[hold_point_number][5]=yy1;
}                  //*
else fault=0;
}                     //*

if((space==3)&&(point_selected==1))
{
p_3D_tr=1;
l_3D_tr=1;
point_2D_trans=0;
point_found=selection_number;
if(point_found==0)
{
  Application->MessageBox("You should select object(point,line,,,) by mouse first!!","Error",MB_OK);
}
if (point_found!=0)
{
get_coordinates(3);
if(fault==0)
{
deselectall();
delete_point_coor(1,1,selection_number);
//line_lighted=0;
translate_3D_point(point_found,x1,y1,x2);
}
  else fault=0;
}
}

//-----------------------------------------
if ((space==3)&&(Point_clicked==1)&&(p_3D_tr==0))
{              //*
get_coordinates(3);
metric_to_bit_3D(x1,y1);
point_2D(xx1,yy1,4);  //projection on z=0
hold_point_number=hold_point_number+1;
  StorePoints[hold_point_number][1]=1;
  StorePoints[hold_point_number][2]=xx1;
  StorePoints[hold_point_number][3]=yy1;
  StorePoints[hold_point_number][4]=x1;
  StorePoints[hold_point_number][5]=y1;
  StorePoints[hold_point_number][6]=x2;
  StorePoints[hold_point_number][8]=Point_size;
}                 //*
//-----------------------------------------

if((space==3)&&(line_3D_clicked==1)&&(l_3D_tr==0))
{
get_coordinates(6);
if(fault==0)
{
hold_point_number=hold_point_number+1;
StorePoints[hold_point_number][1]=4;
StorePoints[hold_point_number][2]=x1;
StorePoints[hold_point_number][3]=y1;
StorePoints[hold_point_number][4]=x2;
StorePoints[hold_point_number][5]=y2;
StorePoints[hold_point_number][6]=z1;
StorePoints[hold_point_number][7]=z2;
metric_to_bit_3D(x1,y1);
int tempx=xx1;                            //draw what is seen from on z=0;
int tempy=yy1;
metric_to_bit_3D(y2,z1);
StorePoints[hold_point_number][8]=tempx;
StorePoints[hold_point_number][9]=tempy;
StorePoints[hold_point_number][10]=xx1;
StorePoints[hold_point_number][11]=yy1;
PaintBox1->Canvas->Pen->Color=clBlack;
PaintBox1->Canvas->MoveTo(tempx,tempy);
PaintBox1->Canvas->LineTo(xx1,yy1);
}
}
}
//-------------------------------
void __fastcall TForm1::Point_properties_sizeChange(TObject *Sender)
{ //*
int selection=Point_properties_size->ItemIndex;
switch (selection)
{    //**
case 0:
Point_size=4;
break;
case 1:
Point_size=8;
break;
case 2:
Point_size=12;
break;
case 3:
Point_size=16;
break;
default:
Application->MessageBox("Point Size must be 4,8,12 or 16","Error",MB_OK);
}      //*
}         //*
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox1MouseDown(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
mouse_down=1;
if(select_clicked==1)
deselectall();
//------------
if(circle_clicked==1)
{
circlex=X;
circley=Y;

}
//------------
 if(translation_2D==1)
 {
t1=X;
t2=Y;
translatemouse=1;
 }
//-----------
if (Line_2D_clicked==1)
{
if (line_con==1)
{       ///
cont_line=1;
line_end=0;
Form1->PaintBox1->Canvas->MoveTo(X,Y);
}          ///
else
{             ///
cont_line=0;
if(first_touch==0)
first_touch=1;
if (first_touch==2)
first_touch=3;
}                ///
}                   //*
//----------------------
if(  bezier_knotmove==1)
{
 int f=0,k=0;
 int j=selection_number;

  if(StoreBezier[j][2]==(StoreBezier[j][3]-1))
  j=j-StoreBezier[j][3]+1;
 k=j;
 while(f==0)
 {
  if((abs(StoreBezier[j][0]-X)<5) && (abs(StoreBezier[j][1]-Y)<5))
  {
   bezier_knotmovedown=1;
   bezier_knotmove=0;
   selectedbezierknot=j;
   f=1;
   }
  else
  {
  j+=1;
  if(j>(k+StoreBezier[j-1][3]-1))
  f=1;
 }
 }
 }
 //--------------
 if(bspline_knotmove==1)
{
 int f=0,k=0;
 int j=selection_number;

  if(StoreBspline[j][2]==(StoreBspline[j][3]-1))
  j=j-StoreBspline[j][3]+1;
 k=j;
 while(f==0)
 {
  if((abs(StoreBspline[j][0]-X)<5) && (abs(StoreBspline[j][1]-Y)<5))
  {
   bspline_knotmovedown=1;
   selectedbsplineknot=j;
   f=1;
   }
  else
  {
  j+=1;
  if(j>(k+StoreBspline[j-1][3]-1))
  f=1;
 }
 }
 }
 //--------------
if(changesurface_clicked==1)
{
int go=0,i=0,f=0,t=0,h=0;
while((f==0)&&(i<surfaceindex))
{
if(StoreSurface[i].mode==1)
{
 while((go==0)&&(t<4))
 {
 if((abs(X-StoreSurface[i].p[t][0])<5)&&(abs(Y-StoreSurface[i].p[t][1])<5))
 go=1;
 else t++;
 }
 if(go==1)
 {
 foundsurfindex=i;//point found
 f=1;
 surfpointindex=t;//relative position in the P[][] matrix
 for(int m=0;m<4;m++)
 {
  P[m][0]=StoreSurface[i].p[m][0];
  P[m][1]=StoreSurface[i].p[m][1];
 }
 }
}
//-----
if(StoreSurface[i].mode==2)
{
 while((go==0)&&(t<4))
 {
 if((abs(X-StoreSurface[i].p[t][0])<5)&&(abs(Y-StoreSurface[i].p[t][1])<5))
 go=1;
 else t++;
 }
 if(go==1)
 {
 foundsurfindex=i;//point found
 f=1;
 surfpointindex=t;//relative position in the P[][] matrix
 for(int m=0;m<4;m++)
 {
  P[m][0]=StoreSurface[i].p[m][0];
  P[m][1]=StoreSurface[i].p[m][1];
 }
 }
}
//---
if(StoreSurface[i].mode==3)
{
 while((go==0)&&(t<4))
 {
 if((abs(X-StoreSurface[i].p[t][0])<5)&&(abs(Y-StoreSurface[i].p[t][1])<5))
 go=1;
 else t++;
 }
 if(go==1)
 {
 foundsurfindex=i;//point found
 f=1;
 surfpointindex=t;//relative position in the P[][] matrix
 for(int m=0;m<4;m++)
 {
  P[m][0]=StoreSurface[i].p[m][0];
  P[m][1]=StoreSurface[i].p[m][1];
 }
 }
}
//---
if(StoreSurface[i].mode==4)
{
 while((go==0)&&(t<3))
 {
 if((abs(X-StoreSurface[i].bx[h][t])<5)&&(abs(Y-StoreSurface[i].by[h][t])<5))
 go=1;
 else
 {
 h++;
 if(h==5)
 {
 h=0;
 t++;
 }
 }
 if(go==1)
 {
 foundsurfindex=i;//point found
 f=1;
 surfpointindex=h;//relative position in the P[][] matrix
 surfpointindex2=t;
 }
 }
}
//---
if(StoreSurface[i].mode==5)
{
 while((go==0)&&(t<3))
 {
 if((abs(X-StoreSurface[i].bx[h][t])<5)&&(abs(Y-StoreSurface[i].by[h][t])<5))
 go=1;
 else
 {
 h++;
 if(h==5)
 {
 h=0;
 t++;
 }
 }
 if(go==1)
 {
 foundsurfindex=i;//point found
 f=1;
 surfpointindex=h;//relative position in the P[][] matrix
 surfpointindex2=t;
 }
 }
}
 //---
i++;
t=0;
}
if (f==1) surfaceknotselected=1;
}
//-----------------------------------
wait();
wait();
}

//---------------------------------------------------------------------------

void __fastcall TForm1::PaintBox1MouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{//*
l_2D_t=0;
p_2D_t=0;
p_2D_r=0;
h_to_d=0;
//------------------------------------------------
 if(translation_2D==1)
 {
 translation_2D=0;
 translatemouse=0;
 }
//------------------------------------------------
if(lighted==1)
{
if(space==2)
{
delight_selected_point(StorePoints[point_found][2],StorePoints[point_found][3],StorePoints[point_found][8]);
}
if(space==3)
{
delight_selected_point(StorePoints[point_found][5],StorePoints[point_found][6],4);
}
}
//-----
if(line_lighted==1)
{
if(space==2)
{
delight_selected_point(StorePoints[point_found][2],StorePoints[point_found][3],2);
delight_selected_point(StorePoints[point_found][4],StorePoints[point_found][5],2);
line_lighted=0;
}
if(space==3)
{
delight_selected_point(StorePoints[point_found][8],StorePoints[point_found][9],2);
delight_selected_point(StorePoints[point_found][10],StorePoints[point_found][11],2);
line_lighted=0;
}
}

//-----

//-----------------
if(go_to_select==1)
{
select_clicked=0;
select_yellow(X,Y);
Form1->Cursor=crDefault;
}
//------------------------------------------------
if(circle_clicked==1)
{

 circle_clicked=0;
 mouse_down=0;
}
//-----
if(fit_point_to_spline_clicked==1)
{
fit_point_to_spline_clicked=0;
fit_spline(X,Y);

}
//---------------------------------
if(bezier_knotmoved==1)
{
bezier_knotmoved=0;
bezier_knotmovedown=0;
  int k=selection_number;
  int j=0;
  if(StoreBezier[selection_number][2]==(StoreBezier[selection_number][3]-1))
  j=selection_number-StoreBezier[selection_number][3]+1;
for(int i=j;i<=k;i++)
{
splinex[i-j]=StoreBezier[i][0];
spliney[i-j]=StoreBezier[i][1];
}
bezier(StoreBezier[j][3],splinex,spliney,2);
StoreBezier[selectedbezierknot][0]=X;
StoreBezier[selectedbezierknot][1]=Y;
splinex[selectedbezierknot]=X;
spliney[selectedbezierknot]=Y;
bezier(StoreBezier[j][3],splinex,spliney,1);
}
//--------------------------------
if(bspline_knotmoved==1)
{
bspline_knotmoved=0;
bspline_knotmovedown=0;
bspline_knotmove=0;
  int k=selection_number;
  int j=0;
  if(StoreBspline[selection_number][2]==(StoreBspline[selection_number][3]-1))
  j=selection_number-StoreBspline[selection_number][3]+1;
for(int i=j;i<=k;i++)
{
splinex[i-j]=StoreBspline[i][0];
spliney[i-j]=StoreBspline[i][1];
}
bspline(StoreBspline[j][3],StoreBspline[selection_number][5],splinex,spliney,2);
StoreBspline[selectedbsplineknot][0]=X;
StoreBspline[selectedbsplineknot][1]=Y;
order=StoreBspline[selectedbsplineknot][5];
splinex[selectedbsplineknot]=X;
spliney[selectedbsplineknot]=Y;
initializeknot();
bspline(StoreBspline[j][3],order,splinex,spliney,1);
}
//--------------------------------
if (bezier_clicked==1)
{
if( mouse_down==1)
{
mouse_down=0;
if(selectbezier_clicked==1)
{
Form1->Cursor=crDefault;
selectbezier_clicked=0;
select_yellow(X,Y);
}
else
{
splinex[splinepointnumber]=X;
spliney[splinepointnumber]=Y;
Form1->PaintBox1->Canvas->Pixels[X][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X+1][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X][Y+1]=clRed;
splinepointnumber=splinepointnumber+1;
if(splinepointnumber==1)
Form1->PaintBox1->Canvas->MoveTo(X,Y);
Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
if(splinepointnumber!=1)
{
Form1->PaintBox1->Canvas->LineTo(X,Y);
}
}
}
}
//------------------------------------
if(bspline_clicked==1)
{
if(selectbspline_clicked==1)
{
Form1->Cursor=crDefault;
selectbspline_clicked=0;
select_yellow(X,Y);
}
else
{
splinex[splinepointnumber]=X;
spliney[splinepointnumber]=Y;
Form1->PaintBox1->Canvas->Pixels[X][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X+1][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X][Y+1]=clRed;
splinepointnumber=splinepointnumber+1;
if(splinepointnumber==1)
Form1->PaintBox1->Canvas->MoveTo(X,Y);
Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
if(splinepointnumber!=1)
{
Form1->PaintBox1->Canvas->LineTo(X,Y);
}
}
}
//-----------------------------------
if((bilinearsurf_clicked==1)&&(changesurface_clicked==0)&&(surfaceknotselected==0))
{
Form1->PaintBox1->Canvas->Pixels[X][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X+1][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X][Y+1]=clRed;
StoreSurface[surfaceindex].mode=1;//bilinear
if(surfind!=4)
{
P[surfind][0]=X;
P[surfind][1]=Y;
surfind++;
}
if(surfind==4)
{
for(int t=0;t<4;t++)
{
StoreSurface[surfaceindex].p[t][0]=P[t][0];
StoreSurface[surfaceindex].p[t][1]=P[t][1];
}
surfaceindex++;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
bilinearsurface();
surfind=0;
}
}
//----------------------------------
if((beziersurface_clicked==1)&&(changesurface_clicked==0)&&(surfaceknotselected==0))
{
 BBx[beziersurfind][bbindex]=X;
 BBy[beziersurfind][bbindex]=Y;
 beziersurfind++;
if((bbindex==0)||(bbindex==1))
{
 if(beziersurfind==5)
 {
  bbindex++;
  beziersurfind=0;
  Button5Click(Button5);
  splinepointnumber=0;
 }
 }
if(bbindex==2)
{
/**/
if((beziersurfind==1)&&(bezcheck==0))
{
Form1->PaintBox1->Canvas->MoveTo(BBx[0][0],BBy[0][0]);
Form1->PaintBox1->Canvas->Pen->Color=clYellow;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
Form1->PaintBox1->Canvas->LineTo(BBx[0][2],BBy[0][2]);
Form1->PaintBox1->Canvas->LineTo(BBx[0][1],BBy[0][1]);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
splinex[0]=BBx[0][0];
splinex[1]=BBx[0][2];
splinex[2]=BBx[0][1];
spliney[0]=BBy[0][0];
spliney[1]=BBy[0][2];
spliney[2]=BBy[0][1];
splinepointnumber=3;
Button5Click(Button5);
beziersurfind=4;
bezcheck=1;
}
if((beziersurfind==5)&&(bezcheck==1))
{
Form1->PaintBox1->Canvas->MoveTo(BBx[4][0],BBy[4][0]);
Form1->PaintBox1->Canvas->Pen->Color=clYellow;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
Form1->PaintBox1->Canvas->LineTo(BBx[4][2],BBy[4][2]);
Form1->PaintBox1->Canvas->LineTo(BBx[4][1],BBy[4][1]);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
splinex[0]=BBx[4][0];
splinex[1]=BBx[4][2];
splinex[2]=BBx[4][1];
spliney[0]=BBy[4][0];
spliney[1]=BBy[4][2];
spliney[2]=BBy[4][1];
splinepointnumber=3;
Button5Click(Button5);
beziersurfind=1;
bezcheck=0;

}
//*****
if((beziersurfind==2)&&(bezcheck==0))
{
Form1->PaintBox1->Canvas->Pen->Color=clYellow;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
Form1->PaintBox1->Canvas->MoveTo(BBx[0][2],BBy[0][2]);
Form1->PaintBox1->Canvas->LineTo(BBx[1][2],BBy[1][2]);
}
if((beziersurfind==3)&&(bezcheck==0))
{
Form1->PaintBox1->Canvas->LineTo(BBx[2][2],BBy[2][2]);
}
if((beziersurfind==4)&&(bezcheck==0))
{
beziersurfind=0;
bbindex++;
Form1->PaintBox1->Canvas->LineTo(BBx[3][2],BBy[3][2]);
Form1->PaintBox1->Canvas->LineTo(BBx[4][2],BBy[4][2]);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
}
}

if(bbindex==3)
 {
  for(int i=0;i<5;i++)
  {
   xx1=BBx[i][1];
   BBx[i][1]=BBx[i][2];
   BBx[i][2]=xx1;
   xx1=BBy[i][1];
   BBy[i][1]=BBy[i][2];
   BBy[i][2]=xx1;
   xx1=BBz[i][1];
   BBz[i][1]=BBz[i][2];
   BBz[i][2]=xx1;
  }
  StoreSurface[surfaceindex].mode=4;
   for(int t=0;t<3;t++)
  for(int i=0;i<5;i++)
 {
  StoreSurface[surfaceindex].bx[i][t]=BBx[i][t];
  StoreSurface[surfaceindex].by[i][t]=BBy[i][t];
  StoreSurface[surfaceindex].bz[i][t]=BBz[i][t];
}
 surfaceindex++;
  Form1->PaintBox1->Canvas->Pen->Style=psSolid;
  beziersurface();
  bbindex=0;
  //bezier_clicked=0;
  beziersurfind=0;
  bezcheck=0;
  splinepointnumber=0;
 }
}
//----------------------------------
if((bsplinesurface_clicked==1)&&(changesurface_clicked==0)&&(surfaceknotselected==0))
{
 //
 BBx[bsplinesurfind][bspindex]=X;
 BBy[bsplinesurfind][bspindex]=Y;
 bsplinesurfind++;
if((bspindex==0)||(bspindex==1))
{
 if(bsplinesurfind==5)
 {
  bspindex++;
  bsplinesurfind=0;
 // Button23Click(Button23);
  splinepointnumber=0;
 }
}
if(bspindex==2)
{
/**/
if((bsplinesurfind==1)&&(bsplinecheck==0))
{
Form1->PaintBox1->Canvas->MoveTo(BBx[0][0],BBy[0][0]);
Form1->PaintBox1->Canvas->Pen->Color=clYellow;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
Form1->PaintBox1->Canvas->LineTo(BBx[0][2],BBy[0][2]);
Form1->PaintBox1->Canvas->LineTo(BBx[0][1],BBy[0][1]);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
splinex[0]=BBx[0][0];
splinex[1]=BBx[0][2];
splinex[2]=BBx[0][1];
spliney[0]=BBy[0][0];
spliney[1]=BBy[0][2];
spliney[2]=BBy[0][1];
splinepointnumber=3;
//Button23Click(Button23);
bsplinesurfind=4;
bsplinecheck=1;
}
if((bsplinesurfind==5)&&(bsplinecheck==1))
{
Form1->PaintBox1->Canvas->MoveTo(BBx[4][0],BBy[4][0]);
Form1->PaintBox1->Canvas->Pen->Color=clYellow;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
Form1->PaintBox1->Canvas->LineTo(BBx[4][2],BBy[4][2]);
Form1->PaintBox1->Canvas->LineTo(BBx[4][1],BBy[4][1]);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
splinex[0]=BBx[4][0];
splinex[1]=BBx[4][2];
splinex[2]=BBx[4][1];
spliney[0]=BBy[4][0];
spliney[1]=BBy[4][2];
spliney[2]=BBy[4][1];
splinepointnumber=3;
//Button23Click(Button23);
bsplinesurfind=1;
bsplinecheck=0;
}
//*****
if((bsplinesurfind==2)&&(bsplinecheck==0))
{
Form1->PaintBox1->Canvas->Pen->Color=clYellow;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
Form1->PaintBox1->Canvas->MoveTo(BBx[0][2],BBy[0][2]);
Form1->PaintBox1->Canvas->LineTo(BBx[1][2],BBy[1][2]);
}
if((bsplinesurfind==3)&&(bsplinecheck==0))
{
Form1->PaintBox1->Canvas->LineTo(BBx[2][2],BBy[2][2]);
}
if((bsplinesurfind==4)&&(bsplinecheck==0))
{
bsplinesurfind=0;
bspindex++;
Form1->PaintBox1->Canvas->LineTo(BBx[3][2],BBy[3][2]);
Form1->PaintBox1->Canvas->LineTo(BBx[4][2],BBy[4][2]);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
}
}
//draw others
if(bspindex==3)
 {
  for(int i=0;i<5;i++)
  {
   xx1=BBx[i][1];
   BBx[i][1]=BBx[i][2];
   BBx[i][2]=xx1;
   xx1=BBy[i][1];
   BBy[i][1]=BBy[i][2];
   BBy[i][2]=xx1;
   xx1=BBz[i][1];
   BBz[i][1]=BBz[i][2];
   BBz[i][2]=xx1;
  }
  StoreSurface[surfaceindex].mode=5;
  for(int t=0;t<3;t++)
  for(int i=0;i<5;i++)
 {
  StoreSurface[surfaceindex].bx[i][t]=BBx[i][t];
  StoreSurface[surfaceindex].by[i][t]=BBy[i][t];
  StoreSurface[surfaceindex].bz[i][t]=BBz[i][t];
}
  surfaceindex++;
  Form1->PaintBox1->Canvas->Pen->Style=psSolid;
  initializeknot();
  bsplinesurface();
  bspindex=0;
  //bezier_clicked=0;
  bsplinesurfind=0;
  bsplinecheck=0;
  splinepointnumber=0;
 }
}
//----------------------------------
if((ruledsurface_clicked==1)&&(changesurface_clicked==0)&&(surfaceknotselected==0))
{
Form1->PaintBox1->Canvas->Pixels[X][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X+1][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X][Y+1]=clRed;
P[surfind][0]=X;
P[surfind][1]=Y;
StoreSurface[surfaceindex].mode=2;
surfind++;
if(surfind==2)
{
if(rulecheck==0)
{
StoreSurface[surfaceindex].p[0][0]=P[0][0];
StoreSurface[surfaceindex].p[0][1]=P[0][1];
StoreSurface[surfaceindex].p[1][0]=P[1][0];
StoreSurface[surfaceindex].p[1][1]=P[1][1];
rulecheck=1;
rulecubic();
a1=B[0][0];
aa1=B[0][1];
aaa1=B[0][2];
a2=B[2][0];
aa2=B[2][1];
aaa2=B[2][2];
a3=B[3][0];
aa3=B[3][1];
aaa3=B[3][2];
surfind=0;
}
else
{
StoreSurface[surfaceindex].p[2][0]=P[0][0];
StoreSurface[surfaceindex].p[2][1]=P[0][1];
StoreSurface[surfaceindex].p[3][0]=P[1][0];
StoreSurface[surfaceindex].p[3][1]=P[1][1];
surfaceindex++;
rulecheck=0;
ruledsurface_clicked=0;
surfind=0;
rulecubic();
ruledsurface();
}
}
}
//-----------------------------------
if(changesurface_clicked==1)
{
delightsurface();
redrawsurfaces();
changesurface_clicked=0;
}
//---------------------------------
if(line_3D_clicked==1)
{

if((first3dline==0)&&(zentered==1))
{
first3dline=1;
StorePoints[hold_point_number][10]=X;
StorePoints[hold_point_number][11]=Y;
bit_to_metric_3D(X,Y);
StorePoints[hold_point_number][5]=xx1;
StorePoints[hold_point_number][6]=yy1;
zentered=0;
f1=1;
Form1->Panel20->Visible=True;
}
else if(first3dline==1)
{
first3dline=0;
hold_point_number=hold_point_number+1;
StorePoints[hold_point_number][1]=4;
StorePoints[hold_point_number][8]=X;
StorePoints[hold_point_number][9]=Y;
bit_to_metric_3D(X,Y);
StorePoints[hold_point_number][2]=xx1;
StorePoints[hold_point_number][3]=yy1;
Form1->Panel20->Visible=True;
}

}
//---------------------------------
if(surfaceknotselected==1)
{
surfaceknotselected=0;
if((StoreSurface[foundsurfindex].mode!=4)||(StoreSurface[foundsurfindex].mode!=5))
{
StoreSurface[foundsurfindex].p[surfpointindex][0]=X;
StoreSurface[foundsurfindex].p[surfpointindex][1]=Y;
}
if(StoreSurface[foundsurfindex].mode==4)
{
 StoreSurface[foundsurfindex].bx[surfpointindex][surfpointindex2]=X;
 StoreSurface[foundsurfindex].by[surfpointindex][surfpointindex2]=Y;
}
if(StoreSurface[foundsurfindex].mode==5)
{
 StoreSurface[foundsurfindex].bx[surfpointindex][surfpointindex2]=X;
 StoreSurface[foundsurfindex].by[surfpointindex][surfpointindex2]=Y;
}

}
//--------------------------------
if (cubicspline_clicked==1)
{
if( mouse_down==1)
{
mouse_down=0;
splinex[splinepointnumber]=X;
spliney[splinepointnumber]=Y;
Form1->PaintBox1->Canvas->Pixels[X][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X+1][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X][Y+1]=clRed;
splinepointnumber=splinepointnumber+1;
}
}
//-----
if (para_blend==1)
{
if( mouse_down==1)
{
mouse_down=0;
splinex[splinepointnumber]=X;
spliney[splinepointnumber]=Y;
Form1->PaintBox1->Canvas->Pixels[X][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X+1][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X][Y+1]=clRed;
splinepointnumber=splinepointnumber+1;
}
}
//-----
if (cyclic_spline_clicked==1)
{
if( mouse_down==1)
{
mouse_down=0;
splinex[splinepointnumber]=X;
spliney[splinepointnumber]=Y;
Form1->PaintBox1->Canvas->Pixels[X][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X+1][Y]=clRed;
Form1->PaintBox1->Canvas->Pixels[X][Y+1]=clRed;
splinepointnumber=splinepointnumber+1;
}
}
//-----------------------------------------------------------------------------
if(box_lighted==1)
{
box_matrix1[3][0]=box_matrix1[3][1]=box_matrix1[3][2]=box_matrix1[3][3]=box_matrix1[3][4]=box_matrix1[3][5]=box_matrix1[3][6]=box_matrix1[3][7]=1;
box_matrix1[2][0]=box_matrix1[2][1]=box_matrix1[2][2]=box_matrix1[2][3]=box_matrix1[2][4]=box_matrix1[2][5]=box_matrix1[2][6]=box_matrix1[2][7]=0;
for(int i=0;i<8;i++)
{box_matrix1[0][i]=StorePoints[point_found+1][i];  }
for(int i=0;i<8;i++)
{box_matrix1[1][i]=StorePoints[point_found+2][i];}
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
draw_box();
box_lighted=0;
}
//-----------------------------------------------------------------------------
if(scale_clicked==1)
{
select_point_translate(X,Y);
p_2D_t=1;
scale=1;
scale_clicked=0;
}
//------------------------------------------------
if(translation_2D==1)
{
Line_2D_clicked=0;
select_point_translate(X,Y);//get the
p_2D_t=1;
}
//-----------------------------------------------
if(translation_3D==1)
select_point_translate(X,Y);
//-----------------------------------------------
if(rotation_2D==1)
{
select_point_translate(X,Y);
Line_2D_clicked=0;
}
//----------------------------------------------
if(rotation_3D==1)
{
if(surfaceselected==1)
point_found=1;

}
//---------------------------------------------
if(perspective_clicked==1)
select_point_translate(X,Y);
//---------------------------------------------
if (hit_to_delete==1)
{   //*
if (mouse_down==1)
{      ///
 x1=StorePoints[point_found][2];
 y1=StorePoints[point_found][3];
 x2=StorePoints[point_found][4];
 y2=StorePoints[point_found][5];
 find_point_number(X,Y);
 Form1->Cursor=crDefault;
 if(point_found!=0)
 {        ///
 delete_line(x1,y1,x2,y2);
 }           ///
 hit_to_delete=0;
 mouse_down=0;
 h_to_d=1;
 }              ///
 }                 //*
 //***
//----------------------------

if ((Point_clicked==1)&&(h_to_d==0)&&(p_2D_t==0)&&(p_2D_r==0))
{           //*
if(space==2)
{
if (mouse_down==1)
{              ///
if(point_2D_trans==1)
{                 ///
delight_selected_point(StorePoints[point_found][2],StorePoints[point_found][3],StorePoints[point_found][8]);
}                    ///
point_2D(X,Y,Point_size);
hold_point_number=hold_point_number+1;
  StorePoints[hold_point_number][1]=1;
  StorePoints[hold_point_number][2]=X;
  StorePoints[hold_point_number][3]=Y;
  StorePoints[hold_point_number][8]=Point_size;
mouse_down=0;
}                       ///
}
//**
if (space==3)
{
hold_point_number=hold_point_number+1;
  StorePoints[hold_point_number][1]=1;
  bit_to_metric_3D(X,Y);
  StorePoints[hold_point_number][2]=X;
  StorePoints[hold_point_number][3]=Y;
  StorePoints[hold_point_number][5]=xx1;
  StorePoints[hold_point_number][6]=yy1;
  StorePoints[hold_point_number][8]=Point_size;
mouse_down=0;
Form1->Panel20->Visible=True;
}

}                          //*
//----------------------------

//---------------------------
if ((space==2)&&(Line_2D_clicked==1)&&(l_2D_t==0))
{   //*
mouse_down=0;
  if(line_2D_trans==1)
  {  ///
  delight_selected_point(StorePoints[point_found][2],StorePoints[point_found][3],2);
  delight_selected_point(StorePoints[point_found][4],StorePoints[point_found][5],2);
  line_lighted=0;
  } ///
 if (cont_line==1)
  line_end=1;
 else
 {   //*
  if (first_touch==1)
  {     ///
  Form1->PaintBox1->Canvas->MoveTo(X,Y);
  hold_point_number=hold_point_number+1;
  StorePoints[hold_point_number][1]=2;
  StorePoints[hold_point_number][2]=X;
  StorePoints[hold_point_number][3]=Y;
  Form1->PaintBox1->Canvas->Pixels[X][Y]=clRed;
  Form1->PaintBox1->Canvas->Pixels[X+1][Y]=clRed;
  Form1->PaintBox1->Canvas->Pixels[X][Y+1]=clRed;
  first_touch=2;
  }        ///
 if (first_touch==3)
 {        ///
    Form1->PaintBox1->Canvas->MoveTo(StorePoints[hold_point_number][2],StorePoints[hold_point_number][3]);


  Form1->PaintBox1->Canvas->LineTo(X,Y);
  StorePoints[hold_point_number][4]=X;
  StorePoints[hold_point_number][5]=Y;
  Form1->PaintBox1->Canvas->Pixels[X][Y]=clRed;
  Form1->PaintBox1->Canvas->Pixels[X+1][Y]=clRed;
  Form1->PaintBox1->Canvas->Pixels[X][Y+1]=clRed;
  first_touch=0;
 }          ///
 }          //* else
 }          //*if
 }
//---------------------------------------------------------------------------


void __fastcall TForm1::Erase1Click(TObject *Sender)
{
Form1->Cursor=crCross;
hit_to_delete=1;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::On1Click(TObject *Sender)
{
     Form1->PaintBox1->Canvas->Pen->Color=clNavy;
     cerceve();
     Form1->PaintBox1->Canvas->Pen->Color=clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Off1Click(TObject *Sender)
{
  Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
  cerceve();
  Form1->PaintBox1->Canvas->Pen->Color=clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TransformationClick(TObject *Sender)
{
if(transformation_clicked==0)
{
if(space==3)
{
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
Form1->Label17->Visible=True;
Form1->Label12->Visible=True;
// perspective->Visible=True;
Form1->Label12->Caption="First press 'Select' Button. You will see that objects on the work area are lighted.Then, click the lighted point on the object to select it. ";
Form1->Label17->Caption="Red points show valid selection. First, you have to select an object. Click the transformation you want then. ";
Translation->Visible=True;

 }
Panel4->Visible=True;
if(space==2)
{
 perspective->Visible=False;

 }
Translation->Visible=True;
Rotation->Visible=True;

perspective->Visible=False;
Transformation->Caption="- Transformation" ;
transformation_clicked=1;
}
else
{
Panel4->Visible=False;
Translation->Visible=False;
Rotation->Visible=False;
perspective->Visible=False;

Transformation->Caption="+ Transformation" ;
transformation_clicked=0;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TranslationClick(TObject *Sender)
{
//*
others_clicked();
if (space==2)
{
hide_boxes();
Panel4->Visible=True;
Translation->Visible=True;
Rotation->Visible=True;
Form1->OK->Visible=True;
X1->Visible=True;
Y1->Visible=True;
Label1->Visible=True;
Label2->Visible=True;
Label1->Caption="by X";
Label2->Caption="by Y";
des_label1->Visible=True;
des_label1->Caption="Move selected point,line... by X and Y values";
if(select_clicked==1)
{
translation_2D=1;
}
else
Application->MessageBox("You have not selected an object yet!!","Error",MB_OK);
}
//--------------------
if (space==3)
{
Form1->degree->Visible=False;
Form1->OKrotate->Visible=False;
Form1->labeldegree->Visible=False;
Panel5->Visible=False;
Form1->aroundx->Visible=False;
Form1->aroundy->Visible=False;
Form1->aroundz->Visible=False;
hide_boxes();
Form1->OK->Visible=True;
X1->Visible=True;
//if(surfaceselected!=1)
X2->Visible=True;
Y1->Visible=True;
Label1->Visible=True;
Label2->Visible=True;
Label3->Visible=True;
Label1->Caption="by X";
Label2->Caption="by Y";
//if(surfaceselected!=1)
Label3->Caption="by Z";
des_label1->Visible=True;
des_label1->Caption="Move selected point,line... by X ,Y Z values";
//Form1->Cursor=crCross;
translation_3D=1;
box_clicked=0;
if(surfaceselected==1)
{
translatesurface=1;
surfaceselected=0;
}
if(select_clicked==1)
{
}
else
Application->MessageBox("You have not selected an object yet!!","Error",MB_OK);
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RotationClick(TObject *Sender)
{
others_clicked();
point_found=0;
if(select_clicked==1)
{
if (space==2)
{
hide_boxes();
Panel4->Visible=True;
Translation->Visible=True;
Rotation->Visible=True;
Form1->OK->Visible=True;
X1->Visible=True;
Label1->Visible=True;
Label1->Caption=" degrees";
des_label1->Visible=True;
des_label1->Caption="Rotate selected point,line... around (0,0) point by given degrees";
//Form1->Cursor=crCross;
point_2D_rotate=1;
}
if(space==3)
{
hide_boxes();
Panel5->Visible=True;
//if(surfaceselected!=1)
//{
//Form1->Cursor=crCross;
Form1->aroundx->Visible=True;
//}
//if(surfaceselected!=1)
Form1->aroundy->Visible=True;
Form1->aroundz->Visible=True;
if(surfaceselected==1)
{
point_found=1;
surfacerotate=1;
}
rotation_3D=1;

}//space3
}
else
Application->MessageBox("You have not selected an object yet!!","Error",MB_OK);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void __fastcall TForm1::LinePropertiesChange(TObject *Sender)
{
int sel=LineProperties->ItemIndex;
switch (sel)
{
case 0:
line_con=1;
line_two_end=0;
break;
case 1:
line_two_end=1;
line_con=0;
break;
}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::aroundxClick(TObject *Sender)
{
aroundz_clicked=aroundx_clicked=aroundy_clicked=point_found=0;
if (select_clicked==0)
  Application->MessageBox("You should select object(point,line,,,) by mouse first!!Then press the  rotation button","Error",MB_OK);
if (select_clicked!=0)
{
Form1->degree->Visible=True;
Form1->OKrotate->Visible=True;
Form1->labeldegree->Visible=True;
aroundx_clicked=1;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::aroundyClick(TObject *Sender)
{
aroundz_clicked=aroundx_clicked=aroundy_clicked=point_found=0;
point_found=select_clicked;
if (point_found==0)
  Application->MessageBox("You should select object(point,line,,,) by mouse first!!Then press the  rotation button","Error",MB_OK);
if (point_found!=0)
{
Form1->degree->Visible=True;
Form1->OKrotate->Visible=True;
Form1->labeldegree->Visible=True;
aroundy_clicked=1;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::aroundzClick(TObject *Sender)
{
aroundz_clicked=aroundx_clicked=aroundy_clicked=point_found=0;
point_found=select_clicked;
if (point_found==0)
  Application->MessageBox("You should select object(point,line,,,) by mouse first!!Then press the  rotation button","Error",MB_OK);
if (point_found!=0)
{
Form1->degree->Visible=True;
Form1->OKrotate->Visible=True;
Form1->labeldegree->Visible=True;
aroundz_clicked=1;
}
}


//---------------------------------------------------------------------------
void __fastcall TForm1::OKrotateClick(TObject *Sender)
{//*
double tet;
if(degree->Text=="")
{   ///
Application->MessageBox("You should enter a valid  coordinate value!!","Error",MB_OK);
fault=1;
}      ///
else
{
//****
fault=0;
xx1=StrToFloat(degree->Text);
//xx1=degree_to_radian(xx1);
tet=xx1;
}
//-----

//----------------------------------
if(aroundx_clicked==1)
{
rotation_matrix(1,0,0);
if(point_selected==1)
{
 deselectall();
 delete_point_coor(1,1,selection_number);
 rotatearoundx(StorePoints[selection_number][4],StorePoints[selection_number][5],StorePoints[selection_number][6],xx1);
 StorePoints[selection_number][4]=x1;
 StorePoints[selection_number][5]=y1;
 StorePoints[selection_number][6]=z1;
 metric_to_bit_3D(x1,y1);
 StorePoints[selection_number][2]=xx1;
 StorePoints[selection_number][3]=yy1;
 point_2D(xx1,yy1,4);
}
//----
if(spline_selected==1)
{
if(StoreSpline[selection_number][0]==1)
{
if(x2==0) x2=1;
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
natcubicspline(t,splinex,spliney);
//***
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
rotatearoundx(StoreSplineReal[selection_number+k-(int)g][1],StoreSplineReal[selection_number+k-(int)g][2],StoreSplineReal[selection_number+k-(int)g][8],tet);
StoreSplineReal[selection_number+k-(int)g][1]=x1;
StoreSplineReal[selection_number+k-(int)g][2]=y1;
StoreSplineReal[selection_number+k-(int)g][8]=z1;
metric_to_bit_3D(StoreSplineReal[selection_number+k-(int)g][1],StoreSplineReal[selection_number+k-(int)g][2]);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
splinex[k]=xx1;
spliney[k]=yy1;
}
natcubicspline(t,splinex,spliney);
}
//---
if(StoreSpline[selection_number][0]==2)
{
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
cubicspline(t,splinex,spliney,StoreSpline[selection_number][3],StoreSpline[selection_number][7]);
//***
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
bit_to_metric_3D(StoreSpline[selection_number+k-(int)g][1],StoreSpline[selection_number+k-(int)g][2]);
rotatearoundx(xx1,yy1,StoreSpline[selection_number+k-(int)g][6],tet);
metric_to_bit_3D(x1,y1);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
StoreSpline[selection_number+k-(int)g][6]=z1;
splinex[k]=xx1;
spliney[k]=yy1;
}
cubicspline(t,splinex,spliney,StoreSpline[selection_number][3],StoreSpline[selection_number][7]);
}
//---
if(StoreSpline[selection_number][0]==5)
{
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
mode=1;
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
parblend(t,splinex,spliney);
//***
mode=0;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
bit_to_metric_3D(StoreSpline[selection_number+k-(int)g][1],StoreSpline[selection_number+k-(int)g][2]);
rotatearoundx(xx1,yy1,StoreSpline[selection_number+k-(int)g][6],tet);
metric_to_bit_3D(x1,y1);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
StoreSpline[selection_number+k-(int)g][6]=z1;
splinex[k]=xx1;
spliney[k]=yy1;
}
parblend(t,splinex,spliney);
}
//---
if(StoreSpline[selection_number][0]==3)
{
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
cycliccubicspline(t,splinex,spliney);
//***
mode=0;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
bit_to_metric_3D(StoreSpline[selection_number+k-(int)g][1],StoreSpline[selection_number+k-(int)g][2]);
rotatearoundx(xx1,yy1,StoreSpline[selection_number+k-(int)g][6],tet);
metric_to_bit_3D(x1,y1);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
StoreSpline[selection_number+k-(int)g][6]=z1;
splinex[k]=xx1;
spliney[k]=yy1;
}
cycliccubicspline(t,splinex,spliney);
}
//---
if(StoreSpline[selection_number][0]==4)
{
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
mode=1;
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
anticycliccubicspline(t,splinex,spliney);
//***
mode=0;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
bit_to_metric_3D(StoreSpline[selection_number+k-(int)g][1],StoreSpline[selection_number+k-(int)g][2]);
rotatearoundx(xx1,yy1,StoreSpline[selection_number+k-(int)g][6],tet);
metric_to_bit_3D(x1,y1);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
StoreSpline[selection_number+k-(int)g][6]=z1;
splinex[k]=xx1;
spliney[k]=yy1;
}
anticycliccubicspline(t,splinex,spliney);
}
//---
}
//---------------
if(line_selected==1)
{
 deselectall();
 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 Form1->PaintBox1->Canvas->MoveTo(StorePoints[selection_number][8],StorePoints[selection_number][9]);
 Form1->PaintBox1->Canvas->LineTo(StorePoints[selection_number][10],StorePoints[selection_number][11]);
 Form1->PaintBox1->Canvas->Pen->Color=clBlack;
 double tet=xx1;
 rotatearoundx(StorePoints[selection_number][2],StorePoints[selection_number][3],StorePoints[selection_number][4],xx1);
 StorePoints[selection_number][2]=x1;
 StorePoints[selection_number][3]=y1;
 StorePoints[selection_number][4]=z1;
 metric_to_bit_3D(x1,y1);
 StorePoints[selection_number][8]=xx1;
 StorePoints[selection_number][9]=yy1;
 Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
 rotatearoundx(StorePoints[selection_number][5],StorePoints[selection_number][6],StorePoints[selection_number][7],tet);
 StorePoints[selection_number][5]=x1;
 StorePoints[selection_number][6]=y1;
 StorePoints[selection_number][7]=z1;
 metric_to_bit_3D(x1,y1);
 StorePoints[selection_number][10]=xx1;
 StorePoints[selection_number][11]=yy1;
 Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
}
//----
if(surfaceselected==1)
{
int i=foundsurfindex;
if(StoreSurface[foundsurfindex].mode==1)
{
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0];
P[t1][1]=StoreSurface[i].p[t1][1];
}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
bilinearsurface();
delightsurface();
for(int t1=0;t1<4;t1++)
{
bit_to_metric_3D(StoreSurface[i].p[t1][0],StoreSurface[i].p[t1][1]);
rotatearoundx(xx1,yy1,StoreSurface[i].p[t1][2],tet);
metric_to_bit_3D(x1,y1);
P[t1][0]=StoreSurface[i].p[t1][0]=xx1;
P[t1][1]=StoreSurface[i].p[t1][1]=yy1;
StoreSurface[i].p[t1][2]=z1;
}
/*if(surfacerotate==1)
*/
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
redrawsurfaces();
}
//---
if(StoreSurface[i].mode==2)
{
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0]=StoreSurface[i].p[t1][0];
P[t1][1]=StoreSurface[i].p[t1][1]=StoreSurface[i].p[t1][1];
}
rulecubic();
a1=B[0][0];
aa1=B[0][1];
aaa1=B[0][2];
a2=B[2][0];
aa2=B[2][1];
aaa2=B[2][2];
a3=B[3][0];
aa3=B[3][1];
aaa3=B[3][2];
P[0][0]=P[2][0];
P[0][1]=P[2][1];
P[1][0]=P[3][0];
P[1][1]=P[3][1];
rulecubic();
ruledsurface();
delightsurface();
//**
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int t1=0;t1<4;t1++)
{
bit_to_metric_3D(StoreSurface[i].p[t1][0],StoreSurface[i].p[t1][1]);
rotatearoundx(xx1,yy1,StoreSurface[i].p[t1][2],tet);
metric_to_bit_3D(x1,y1);
P[t1][0]=StoreSurface[i].p[t1][0]=xx1;
P[t1][1]=StoreSurface[i].p[t1][1]=yy1;
StoreSurface[i].p[t1][2]=z1;
}
//--
rulecubic();
a1=B[0][0];
aa1=B[0][1];
aaa1=B[0][2];
a2=B[2][0];
aa2=B[2][1];
aaa2=B[2][2];
a3=B[3][0];
aa3=B[3][1];
aaa3=B[3][2];
P[0][0]=P[2][0];
P[0][1]=P[2][1];
P[1][0]=P[3][0];
P[1][1]=P[3][1];
rulecubic();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
redrawsurfaces();
//ruledsurface();
}
//---
if(StoreSurface[i].mode==3)
{
//
 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 dosya2=fopen("bicubicdata.txt","r");
 for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n");
 dosya=fopen("bicubic.txt","w");
 for(int i=0;i<16;i++)
{
fscanf(dosya2,"%d %d %d\n",&r1,&e1,&s1);
fprintf(dosya,"%d %d %d\n",r1,e1,s1);
}
fclose(dosya2);
fclose(dosya);
delightsurface();
bicubicsurface();
//---
 Form1->PaintBox1->Canvas->Pen->Color=clBlack;
 dosya2=fopen("bicubicdata.txt","r");
 for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n");
 dosya=fopen("bicubic.txt","w");
 for(int i=0;i<16;i++)
{
fscanf(dosya2,"%d %d %d\n",&r1,&e1,&s1);
bit_to_metric_3D(r1,e1);
rotatearoundx(xx1,yy1,s1,tet);
metric_to_bit_3D(x1,y1);
fprintf(dosya,"%d %d %d\n",xx1,yy1,z1);
}
fclose(dosya2);
fclose(dosya);
dosya2=fopen("bicubicdata.txt","r+");
for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n");
dosya=fopen("bicubic.txt","r");
 for(int i=0;i<16;i++)
{
fscanf(dosya,"%d %d %d\n",&r1,&e1,&s1);
fprintf(dosya2,"%d %d %d\n",r1,e1,s1);
}
 redrawsurfaces();
//bicubicsurface();
}
//---
if(StoreSurface[i].mode==4)
{
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t];
BBy[k][t]=StoreSurface[i].by[k][t];
BBz[k][t]=StoreSurface[i].bz[k][t];
}
delightsurface();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
drawpolygon();
beziersurface();
//**
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
bit_to_metric_3D(StoreSurface[i].bx[k][t],StoreSurface[i].by[k][t]);
rotatearoundx(xx1,yy1,StoreSurface[i].bz[k][t],tet);
metric_to_bit_3D(x1,y1);
BBx[k][t]=StoreSurface[i].bx[k][t]=xx1;
BBy[k][t]=StoreSurface[i].by[k][t]=yy1;
BBz[k][t]=StoreSurface[i].bz[k][t]=z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
redrawsurfaces();
//beziersurface();
}
//---
if(StoreSurface[i].mode==5)
{
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t];
BBy[k][t]=StoreSurface[i].by[k][t];
BBz[k][t]=StoreSurface[i].bz[k][t];
}
delightsurface();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
drawpolygon();
bsplinesurface();
//**
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
bit_to_metric_3D(StoreSurface[i].bx[k][t],StoreSurface[i].by[k][t]);
rotatearoundx(xx1,yy1,StoreSurface[i].bz[k][t],tet);
metric_to_bit_3D(x1,y1);
BBx[k][t]=StoreSurface[i].bx[k][t]=xx1;
BBy[k][t]=StoreSurface[i].by[k][t]=yy1;
BBz[k][t]=StoreSurface[i].bz[k][t]=z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
redrawsurfaces();
//beziersurface();
}

}
}
//------------------
//--------------------------------------
//--------------------------------------------
if(aroundy_clicked==1)
{
rotation_matrix(0,1,0);
if(point_selected==1)
{
 deselectall();
 delete_point_coor(1,1,selection_number);
 rotatearoundy(StorePoints[selection_number][4],StorePoints[selection_number][5],StorePoints[selection_number][6],xx1);
 StorePoints[selection_number][4]=x1;
 StorePoints[selection_number][5]=y1;
 StorePoints[selection_number][6]=z1;
 metric_to_bit_3D(x1,y1);
 StorePoints[selection_number][2]=xx1;
 StorePoints[selection_number][3]=yy1;
 point_2D(xx1,yy1,4);
}
//----
if(spline_selected==1)
{
if(Spline_mode[selection_number]==1)
{
if(x2==0) x2=1;
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
natcubicspline(t,splinex,spliney);
//***
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
rotatearoundy(StoreSplineReal[selection_number+k-(int)g][1],StoreSplineReal[selection_number+k-(int)g][2],StoreSplineReal[selection_number+k-(int)g][8],tet);
StoreSplineReal[selection_number+k-(int)g][1]=x1;
StoreSplineReal[selection_number+k-(int)g][2]=y1;
StoreSplineReal[selection_number+k-(int)g][8]=z1;
metric_to_bit_3D(StoreSplineReal[selection_number+k-(int)g][1],StoreSplineReal[selection_number+k-(int)g][2]);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
splinex[k]=xx1;
spliney[k]=yy1;
}
natcubicspline(t,splinex,spliney);
}
//---
if(StoreSpline[selection_number][0]==2)
{
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
cubicspline(t,splinex,spliney,StoreSpline[selection_number][3],StoreSpline[selection_number][7]);
//***
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
bit_to_metric_3D(StoreSpline[selection_number+k-(int)g][1],StoreSpline[selection_number+k-(int)g][2]);
rotatearoundy(xx1,yy1,StoreSpline[selection_number+k-(int)g][6],tet);
metric_to_bit_3D(x1,y1);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
StoreSpline[selection_number+k-(int)g][6]=z1;
splinex[k]=xx1;
spliney[k]=yy1;
}
cubicspline(t,splinex,spliney,StoreSpline[selection_number][3],StoreSpline[selection_number][7]);
}
//---
if(StoreSpline[selection_number][0]==5)
{
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
mode=1;
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
parblend(t,splinex,spliney);
//***
mode=0;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
bit_to_metric_3D(StoreSpline[selection_number+k-(int)g][1],StoreSpline[selection_number+k-(int)g][2]);
rotatearoundy(xx1,yy1,StoreSpline[selection_number+k-(int)g][6],tet);
metric_to_bit_3D(x1,y1);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
StoreSpline[selection_number+k-(int)g][6]=z1;
splinex[k]=xx1;
spliney[k]=yy1;
}
parblend(t,splinex,spliney);
}
//---
if(StoreSpline[selection_number][0]==3)
{
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
cycliccubicspline(t,splinex,spliney);
//***
mode=0;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
bit_to_metric_3D(StoreSpline[selection_number+k-(int)g][1],StoreSpline[selection_number+k-(int)g][2]);
rotatearoundy(xx1,yy1,StoreSpline[selection_number+k-(int)g][6],tet);
metric_to_bit_3D(x1,y1);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
StoreSpline[selection_number+k-(int)g][6]=z1;
splinex[k]=xx1;
spliney[k]=yy1;
}
cycliccubicspline(t,splinex,spliney);
}
//---
if(StoreSpline[selection_number][0]==4)
{
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
mode=1;
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
anticycliccubicspline(t,splinex,spliney);
//***
mode=0;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
bit_to_metric_3D(StoreSpline[selection_number+k-(int)g][1],StoreSpline[selection_number+k-(int)g][2]);
rotatearoundy(xx1,yy1,StoreSpline[selection_number+k-(int)g][6],tet);
metric_to_bit_3D(x1,y1);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
StoreSpline[selection_number+k-(int)g][6]=z1;
splinex[k]=xx1;
spliney[k]=yy1;
}
anticycliccubicspline(t,splinex,spliney);
}
//---
//---
}
//-------
if(line_selected==1)
{
 deselectall();
 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 Form1->PaintBox1->Canvas->MoveTo(StorePoints[selection_number][8],StorePoints[selection_number][9]);
 Form1->PaintBox1->Canvas->LineTo(StorePoints[selection_number][10],StorePoints[selection_number][11]);
 Form1->PaintBox1->Canvas->Pen->Color=clBlack;
 double tet=xx1;
 rotatearoundy(StorePoints[selection_number][2],StorePoints[selection_number][3],StorePoints[selection_number][4],xx1);
 StorePoints[selection_number][2]=x1;
 StorePoints[selection_number][3]=y1;
 StorePoints[selection_number][4]=z1;
 metric_to_bit_3D(x1,y1);
 StorePoints[selection_number][8]=xx1;
 StorePoints[selection_number][9]=yy1;
 Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
 rotatearoundy(StorePoints[selection_number][5],StorePoints[selection_number][6],StorePoints[selection_number][7],tet);
 StorePoints[selection_number][5]=x1;
 StorePoints[selection_number][6]=y1;
 StorePoints[selection_number][7]=z1;
 metric_to_bit_3D(x1,y1);
 StorePoints[selection_number][10]=xx1;
 StorePoints[selection_number][11]=yy1;
 Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
}
//---
if(surfaceselected==1)
{
int i=selection_number;
if(StoreSurface[foundsurfindex].mode==1)
{
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0];
P[t1][1]=StoreSurface[i].p[t1][1];
}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
bilinearsurface();
delightsurface();
for(int t1=0;t1<4;t1++)
{
bit_to_metric_3D(StoreSurface[i].p[t1][0],StoreSurface[i].p[t1][1]);
rotatearoundy(xx1,yy1,StoreSurface[i].p[t1][2],tet);
metric_to_bit_3D(x1,y1);
P[t1][0]=StoreSurface[i].p[t1][0]=xx1;
P[t1][1]=StoreSurface[i].p[t1][1]=yy1;
StoreSurface[i].p[t1][2]=z1;
}
/*if(surfacerotate==1)
*/
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
redrawsurfaces();
}
//---
if(StoreSurface[i].mode==2)
{
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0]=StoreSurface[i].p[t1][0];
P[t1][1]=StoreSurface[i].p[t1][1]=StoreSurface[i].p[t1][1];
}
rulecubic();
a1=B[0][0];
aa1=B[0][1];
aaa1=B[0][2];
a2=B[2][0];
aa2=B[2][1];
aaa2=B[2][2];
a3=B[3][0];
aa3=B[3][1];
aaa3=B[3][2];
P[0][0]=P[2][0];
P[0][1]=P[2][1];
P[1][0]=P[3][0];
P[1][1]=P[3][1];
rulecubic();
ruledsurface();
delightsurface();
//**
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int t1=0;t1<4;t1++)
{
bit_to_metric_3D(StoreSurface[i].p[t1][0],StoreSurface[i].p[t1][1]);
rotatearoundy(xx1,yy1,StoreSurface[i].p[t1][2],tet);
metric_to_bit_3D(x1,y1);
P[t1][0]=StoreSurface[i].p[t1][0]=xx1;
P[t1][1]=StoreSurface[i].p[t1][1]=yy1;
StoreSurface[i].p[t1][2]=z1;
}
//--
rulecubic();
a1=B[0][0];
aa1=B[0][1];
aaa1=B[0][2];
a2=B[2][0];
aa2=B[2][1];
aaa2=B[2][2];
a3=B[3][0];
aa3=B[3][1];
aaa3=B[3][2];
P[0][0]=P[2][0];
P[0][1]=P[2][1];
P[1][0]=P[3][0];
P[1][1]=P[3][1];
rulecubic();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
redrawsurfaces();
//ruledsurface();
}
//---
if(StoreSurface[i].mode==3)
{
//
 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 dosya2=fopen("bicubicdata.txt","r");
 for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n");
 dosya=fopen("bicubic.txt","w");
 for(int i=0;i<16;i++)
{
fscanf(dosya2,"%d %d %d\n",&r1,&e1,&s1);
fprintf(dosya,"%d %d %d\n",r1,e1,s1);
}
fclose(dosya2);
fclose(dosya);
delightsurface();
bicubicsurface();
//---
 Form1->PaintBox1->Canvas->Pen->Color=clBlack;
 dosya2=fopen("bicubicdata.txt","r");
 for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n");
 dosya=fopen("bicubic.txt","w");
 for(int i=0;i<16;i++)
{
fscanf(dosya2,"%d %d %d\n",&r1,&e1,&s1);
bit_to_metric_3D(r1,e1);
rotatearoundy(xx1,yy1,s1,tet);
metric_to_bit_3D(x1,y1);
fprintf(dosya,"%d %d %d\n",xx1,yy1,z1);
}
fclose(dosya2);
fclose(dosya);
dosya2=fopen("bicubicdata.txt","r+");
for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n");
 dosya=fopen("bicubic.txt","r");
 for(int i=0;i<16;i++)
{
fscanf(dosya,"%d %d %d\n",&r1,&e1,&s1);
fprintf(dosya2,"%d %d %d\n",r1,e1,s1);
}
 redrawsurfaces();
//bicubicsurface();
}
//---
if(StoreSurface[i].mode==4)
{
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t];
BBy[k][t]=StoreSurface[i].by[k][t];
BBz[k][t]=StoreSurface[i].bz[k][t];
}
delightsurface();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
drawpolygon();
beziersurface();
//**
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
bit_to_metric_3D(StoreSurface[i].bx[k][t],StoreSurface[i].by[k][t]);
rotatearoundy(xx1,yy1,StoreSurface[i].bz[k][t],tet);
metric_to_bit_3D(x1,y1);
BBx[k][t]=StoreSurface[i].bx[k][t]=xx1;
BBy[k][t]=StoreSurface[i].by[k][t]=yy1;
BBz[k][t]=StoreSurface[i].bz[k][t]=z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
redrawsurfaces();
//beziersurface();
}
//---
if(StoreSurface[i].mode==5)
{
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t];
BBy[k][t]=StoreSurface[i].by[k][t];
BBz[k][t]=StoreSurface[i].bz[k][t];
}
delightsurface();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
drawpolygon();
bsplinesurface();
//**
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
bit_to_metric_3D(StoreSurface[i].bx[k][t],StoreSurface[i].by[k][t]);
rotatearoundy(xx1,yy1,StoreSurface[i].bz[k][t],tet);
metric_to_bit_3D(x1,y1);
BBx[k][t]=StoreSurface[i].bx[k][t]=xx1;
BBy[k][t]=StoreSurface[i].by[k][t]=yy1;
BBz[k][t]=StoreSurface[i].bz[k][t]=z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
redrawsurfaces();
//beziersurface();
}
}
}
//------------------
if(aroundz_clicked==1)
{
rotation_matrix(0,0,1);
if(point_selected==1)
{
 deselectall();
 delete_point_coor(1,1,selection_number);
 rotatearoundz(StorePoints[selection_number][4],StorePoints[selection_number][5],StorePoints[selection_number][6],xx1);
 StorePoints[selection_number][4]=x1;
 StorePoints[selection_number][5]=y1;
 StorePoints[selection_number][6]=z1;
 metric_to_bit_3D(x1,y1);
 StorePoints[selection_number][2]=xx1;
 StorePoints[selection_number][3]=yy1;
 point_2D(xx1,yy1,4);
}
//----
if(spline_selected==1)
{
if(Spline_mode[selection_number]==1)
{
if(x2==0) x2=1;
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
natcubicspline(t,splinex,spliney);
//***
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
rotatearoundz(StoreSplineReal[selection_number+k-(int)g][1],StoreSplineReal[selection_number+k-(int)g][2],StoreSplineReal[selection_number+k-(int)g][8],tet);
StoreSplineReal[selection_number+k-(int)g][1]=x1;
StoreSplineReal[selection_number+k-(int)g][2]=y1;
StoreSplineReal[selection_number+k-(int)g][8]=z1;
metric_to_bit_3D(StoreSplineReal[selection_number+k-(int)g][1],StoreSplineReal[selection_number+k-(int)g][2]);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
splinex[k]=xx1;
spliney[k]=yy1;
}
natcubicspline(t,splinex,spliney);
}
//---
if(StoreSpline[selection_number][0]==2)
{
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
cubicspline(t,splinex,spliney,StoreSpline[selection_number][3],StoreSpline[selection_number][7]);
//***
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
bit_to_metric_3D(StoreSpline[selection_number+k-(int)g][1],StoreSpline[selection_number+k-(int)g][2]);
rotatearoundz(xx1,yy1,StoreSpline[selection_number+k-(int)g][6],tet);
metric_to_bit_3D(x1,y1);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
StoreSpline[selection_number+k-(int)g][6]=z1;
splinex[k]=xx1;
spliney[k]=yy1;
}
cubicspline(t,splinex,spliney,StoreSpline[selection_number][3],StoreSpline[selection_number][7]);
}
//---
if(StoreSpline[selection_number][0]==5)
{
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
mode=1;
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
parblend(t,splinex,spliney);
//***
mode=0;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
bit_to_metric_3D(StoreSpline[selection_number+k-(int)g][1],StoreSpline[selection_number+k-(int)g][2]);
rotatearoundz(xx1,yy1,StoreSpline[selection_number+k-(int)g][6],tet);
metric_to_bit_3D(x1,y1);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
StoreSpline[selection_number+k-(int)g][6]=z1;
splinex[k]=xx1;
spliney[k]=yy1;
}
parblend(t,splinex,spliney);
}
//---
if(StoreSpline[selection_number][0]==3)
{
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
cycliccubicspline(t,splinex,spliney);
//***
mode=0;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
bit_to_metric_3D(StoreSpline[selection_number+k-(int)g][1],StoreSpline[selection_number+k-(int)g][2]);
rotatearoundz(xx1,yy1,StoreSpline[selection_number+k-(int)g][6],tet);
metric_to_bit_3D(x1,y1);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
StoreSpline[selection_number+k-(int)g][6]=z1;
splinex[k]=xx1;
spliney[k]=yy1;
}
cycliccubicspline(t,splinex,spliney);
}
//---
if(StoreSpline[selection_number][0]==4)
{
double g=StoreSpline[selection_number][5];
double t=StoreSpline[selection_number][4];
mode=1;
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int k=0;k<t;k++)
{
double r=StoreSpline[selection_number+k-(int)g][1];
double e=StoreSpline[selection_number+k-(int)g][2];
splinex[k]=r;
spliney[k]=e;
}
anticycliccubicspline(t,splinex,spliney);
//***
mode=0;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int k=0;k<t;k++)
{
bit_to_metric_3D(StoreSpline[selection_number+k-(int)g][1],StoreSpline[selection_number+k-(int)g][2]);
rotatearoundz(xx1,yy1,StoreSpline[selection_number+k-(int)g][6],tet);
metric_to_bit_3D(x1,y1);
StoreSpline[selection_number+k-(int)g][1]=xx1;
StoreSpline[selection_number+k-(int)g][2]=yy1;
StoreSpline[selection_number+k-(int)g][6]=z1;
splinex[k]=xx1;
spliney[k]=yy1;
}
anticycliccubicspline(t,splinex,spliney);
}
}
//---
if(line_selected==1)
{
 deselectall();
 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 Form1->PaintBox1->Canvas->MoveTo(StorePoints[selection_number][8],StorePoints[selection_number][9]);
 Form1->PaintBox1->Canvas->LineTo(StorePoints[selection_number][10],StorePoints[selection_number][11]);
 Form1->PaintBox1->Canvas->Pen->Color=clBlack;
 double tet=xx1;
 rotatearoundz(StorePoints[selection_number][2],StorePoints[selection_number][3],StorePoints[selection_number][4],xx1);
 StorePoints[selection_number][2]=x1;
 StorePoints[selection_number][3]=y1;
 StorePoints[selection_number][4]=z1;
 metric_to_bit_3D(x1,y1);
 StorePoints[selection_number][8]=xx1;
 StorePoints[selection_number][9]=yy1;
 Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
 rotatearoundz(StorePoints[selection_number][5],StorePoints[selection_number][6],StorePoints[selection_number][7],tet);
 StorePoints[selection_number][5]=x1;
 StorePoints[selection_number][6]=y1;
 StorePoints[selection_number][7]=z1;
 metric_to_bit_3D(x1,y1);
 StorePoints[selection_number][10]=xx1;
 StorePoints[selection_number][11]=yy1;
 Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
}
//--
if(surfaceselected==1)
{
int i=selection_number;
if(StoreSurface[foundsurfindex].mode==1)
{
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0];
P[t1][1]=StoreSurface[i].p[t1][1];
}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
bilinearsurface();
delightsurface();
for(int t1=0;t1<4;t1++)
{
bit_to_metric_3D(StoreSurface[i].p[t1][0],StoreSurface[i].p[t1][1]);
rotatearoundz(xx1,yy1,StoreSurface[i].p[t1][2],tet);
metric_to_bit_3D(x1,y1);
P[t1][0]=StoreSurface[i].p[t1][0]=xx1;
P[t1][1]=StoreSurface[i].p[t1][1]=yy1;
StoreSurface[i].p[t1][2]=z1;
}
/*if(surfacerotate==1)
*/
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
redrawsurfaces();
}
//---
if(StoreSurface[i].mode==2)
{
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0]=StoreSurface[i].p[t1][0];
P[t1][1]=StoreSurface[i].p[t1][1]=StoreSurface[i].p[t1][1];
}
rulecubic();
a1=B[0][0];
aa1=B[0][1];
aaa1=B[0][2];
a2=B[2][0];
aa2=B[2][1];
aaa2=B[2][2];
a3=B[3][0];
aa3=B[3][1];
aaa3=B[3][2];
P[0][0]=P[2][0];
P[0][1]=P[2][1];
P[1][0]=P[3][0];
P[1][1]=P[3][1];
rulecubic();
ruledsurface();
delightsurface();
//**
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
for(int t1=0;t1<4;t1++)
{
bit_to_metric_3D(StoreSurface[i].p[t1][0],StoreSurface[i].p[t1][1]);
rotatearoundz(xx1,yy1,StoreSurface[i].p[t1][2],tet);
metric_to_bit_3D(x1,y1);
P[t1][0]=StoreSurface[i].p[t1][0]=xx1;
P[t1][1]=StoreSurface[i].p[t1][1]=yy1;
StoreSurface[i].p[t1][2]=z1;
}
//--
rulecubic();
a1=B[0][0];
aa1=B[0][1];
aaa1=B[0][2];
a2=B[2][0];
aa2=B[2][1];
aaa2=B[2][2];
a3=B[3][0];
aa3=B[3][1];
aaa3=B[3][2];
P[0][0]=P[2][0];
P[0][1]=P[2][1];
P[1][0]=P[3][0];
P[1][1]=P[3][1];
rulecubic();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
redrawsurfaces();
//ruledsurface();
}
//---
if(StoreSurface[i].mode==3)
{
//
 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 dosya2=fopen("bicubicdata.txt","r");
 for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n");
 dosya=fopen("bicubic.txt","w");
 for(int i=0;i<16;i++)
{
fscanf(dosya2,"%d %d %d\n",&r1,&e1,&s1);
fprintf(dosya,"%d %d %d\n",r1,e1,s1);
}
fclose(dosya2);
fclose(dosya);
delightsurface();
bicubicsurface();
//---
 Form1->PaintBox1->Canvas->Pen->Color=clBlack;
 dosya2=fopen("bicubicdata.txt","r");
 for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n");
 dosya=fopen("bicubic.txt","w");
 for(int i=0;i<16;i++)
{
fscanf(dosya2,"%d %d %d\n",&r1,&e1,&s1);
bit_to_metric_3D(r1,e1);
rotatearoundz(xx1,yy1,s1,tet);
metric_to_bit_3D(x1,y1);
fprintf(dosya,"%d %d %d\n",xx1,yy1,z1);
}
fclose(dosya2);
fclose(dosya);
dosya2=fopen("bicubicdata.txt","r+");
for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n");
 dosya=fopen("bicubic.txt","r");
 for(int i=0;i<16;i++)
{
fscanf(dosya,"%d %d %d\n",&r1,&e1,&s1);
fprintf(dosya2,"%d %d %d\n",r1,e1,s1);
}
 redrawsurfaces();
//bicubicsurface();
}
//---
if(StoreSurface[i].mode==4)
{
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t];
BBy[k][t]=StoreSurface[i].by[k][t];
BBz[k][t]=StoreSurface[i].bz[k][t];
}
delightsurface();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
drawpolygon();
beziersurface();
//**
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
bit_to_metric_3D(StoreSurface[i].bx[k][t],StoreSurface[i].by[k][t]);
rotatearoundz(xx1,yy1,StoreSurface[i].bz[k][t],tet);
metric_to_bit_3D(x1,y1);
BBx[k][t]=StoreSurface[i].bx[k][t]=xx1;
BBy[k][t]=StoreSurface[i].by[k][t]=yy1;
BBz[k][t]=StoreSurface[i].bz[k][t]=z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
redrawsurfaces();
//beziersurface();
}
//--
if(StoreSurface[i].mode==5)
{
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t];
BBy[k][t]=StoreSurface[i].by[k][t];
BBz[k][t]=StoreSurface[i].bz[k][t];
}
delightsurface();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
drawpolygon();
bsplinesurface();
//**
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
bit_to_metric_3D(StoreSurface[i].bx[k][t],StoreSurface[i].by[k][t]);
rotatearoundz(xx1,yy1,StoreSurface[i].bz[k][t],tet);
metric_to_bit_3D(x1,y1);
BBx[k][t]=StoreSurface[i].bx[k][t]=xx1;
BBy[k][t]=StoreSurface[i].by[k][t]=yy1;
BBz[k][t]=StoreSurface[i].bz[k][t]=z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
redrawsurfaces();
//beziersurface();
}
}
}

//------------------
/*init_projection();//initialize projection matrix
delete_3D_point();  //deletes line or point
if(StorePoints[point_found][1]==3)
{
delight_selected_point(StorePoints[point_found][5],StorePoints[point_found][6],2,1);
}
if(StorePoints[point_found][1]==4)
{
delight_selected_point(StorePoints[point_found][10],StorePoints[point_found][11],2,1);
delight_selected_point(StorePoints[point_found][8],StorePoints[point_found][9],2,1);
line_lighted=0;
}
rotate_3D_point();//rotate line or point
}
*/
//aroundz_clicked=aroundx_clicked=aroundy_clicked=point_found=0;
}
//----
void __fastcall TForm1::BoxClick(TObject *Sender)
{
hide_boxes();
Box->Visible=True;
//Transformation->Visible=False;
Form1->OK->Visible=True;
X1->Visible=True;
Y1->Visible=True;
Label1->Visible=True;
Label2->Visible=True;
X2->Visible=True;
Label3->Visible=True;
Label1->Caption="width";
Label2->Caption="heigth";
Label3->Caption="depth";
box_clicked=1;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::perspectiveClick(TObject *Sender)
{
//ApplytoAll->visible=True;
if(select_clicked==1)
{
}
else
Application->MessageBox("You have not selected an object yet!!","Error",MB_OK);
perspective_clicked=1;
hide_boxes();
//Form1->Cursor=crCross;
Panel6->Visible=True;
Edit3->Text="0";
Edit4->Text="0";
Edit5->Text="256";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ApplyClick(TObject *Sender)
{
point_found=select_clicked;
if (Form1->Edit3->Text=="") fault=1;
else  z1=StrToFloat(Form1->Edit3->Text);
if (Form1->Edit4->Text=="") fault=1;
else  z2=StrToFloat(Form1->Edit4->Text);
if (Form1->Edit5->Text=="") fault=1;
else  z3=StrToFloat(Form1->Edit5->Text);
//--------------------------------------
if (fault==1)
Application->MessageBox("You should enter a valid coordinate value!!","Error",MB_OK);
//--------------------------------------
else
{
if(point_found==0)
Application->MessageBox("You should select object first!!","Error",MB_OK);
else
{
init_projection();
if(point_selected==1)
{
deselectall();
delete_point_coor(StorePoints[selection_number][2],StorePoints[selection_number][3],selection_number);
perspectivetrans(StorePoints[selection_number][4],StorePoints[selection_number][5],StorePoints[selection_number][6],z1,z2,z3);
metric_to_bit_3D(x1,y1);
StorePoints[selection_number][2]=xx1;
StorePoints[selection_number][3]=yy1;
point_2D(xx1,yy1,4);
}
//----
if((line_selected==1)&&(space==3))
{
deselectall();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
Form1->PaintBox1->Canvas->MoveTo(StorePoints[selection_number][8],StorePoints[selection_number][9]);
Form1->PaintBox1->Canvas->LineTo(StorePoints[selection_number][10],StorePoints[selection_number][11]);
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
perspectivetrans(StorePoints[selection_number][2],StorePoints[selection_number][3],StorePoints[selection_number][4],z1,z2,z3);
metric_to_bit_3D(x1,y1);
StorePoints[selection_number][8]=xx1;
StorePoints[selection_number][9]=yy1;
perspectivetrans(StorePoints[selection_number][5],StorePoints[selection_number][6],StorePoints[selection_number][7],z1,z2,z3);
metric_to_bit_3D(x1,y1);
StorePoints[selection_number][10]=xx1;
StorePoints[selection_number][11]=yy1;
Form1->PaintBox1->Canvas->MoveTo(StorePoints[selection_number][8],StorePoints[selection_number][9]);
Form1->PaintBox1->Canvas->LineTo(StorePoints[selection_number][10],StorePoints[selection_number][11]);
}
//----
if(surfaceselected==1)
{
zzz1=z1;
zzz2=z2;
zzz3=z3;
int i=foundsurfindex;
if(StoreSurface[i].mode==1)
{
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0]=StoreSurface[i].p[t1][0];
P[t1][1]=StoreSurface[i].p[t1][1]=StoreSurface[i].p[t1][1];
}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
bilinearsurface();
delightsurface();

for(int t1=0;t1<4;t1++)
{
bit_to_metric_3D(StoreSurface[i].p[t1][0],StoreSurface[i].p[t1][1]);
perspectivetrans(xx1,yy1,StoreSurface[i].p[t1][2],zzz1,zzz2,zzz3);
metric_to_bit_3D(x1,y1);
P[t1][0]=StoreSurface[i].p[t1][0]=xx1;
P[t1][1]=StoreSurface[i].p[t1][1]=yy1;
P[t1][2]=StoreSurface[i].p[t1][2]=z1;
}
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
redrawsurfaces();
}
//---
if(StoreSurface[i].mode==2)
{
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0]=StoreSurface[i].p[t1][0];
P[t1][1]=StoreSurface[i].p[t1][1]=StoreSurface[i].p[t1][1];
}
rulecubic();
a1=B[0][0];
aa1=B[0][1];
aaa1=B[0][2];
a2=B[2][0];
aa2=B[2][1];
aaa2=B[2][2];
a3=B[3][0];
aa3=B[3][1];
aaa3=B[3][2];
P[0][0]=P[2][0];
P[0][1]=P[2][1];
P[1][0]=P[3][0];
P[1][1]=P[3][1];
rulecubic();
ruledsurface();
delightsurface();
//**

for(int t1=0;t1<4;t1++)
{
bit_to_metric_3D(StoreSurface[i].p[t1][0],StoreSurface[i].p[t1][1]);
perspectivetrans(xx1,yy1,StoreSurface[i].p[t1][2],zzz1,zzz2,zzz3);
metric_to_bit_3D(x1,y1);
P[t1][0]=StoreSurface[i].p[t1][0]=xx1;
P[t1][1]=StoreSurface[i].p[t1][1]=yy1;
P[t1][2]=StoreSurface[i].p[t1][2]=z1;
StoreSurface[i].p[t1][0]=P[t1][0];
StoreSurface[i].p[t1][1]=P[t1][1];
}
rulecubic();
a1=B[0][0];
aa1=B[0][1];
aaa1=B[0][2];
a2=B[2][0];
aa2=B[2][1];
aaa2=B[2][2];
a3=B[3][0];
aa3=B[3][1];
aaa3=B[3][2];
P[0][0]=P[2][0];
P[0][1]=P[2][1];
P[1][0]=P[3][0];
P[1][1]=P[3][1];
rulecubic();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
redrawsurfaces();
//ruledsurface();
}
//---
if(StoreSurface[i].mode==3)
{
//
 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 dosya2=fopen("bicubicdata.txt","r");
 for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n");
 dosya=fopen("bicubic.txt","w");
 for(int i=0;i<16;i++)
{
fscanf(dosya2,"%d %d %d\n",&r1,&e1,&s1);
fprintf(dosya,"%d %d %d\n",r1,e1,s1);
}
fclose(dosya2);
fclose(dosya);
delightsurface();
bicubicsurface();

//
 Form1->PaintBox1->Canvas->Pen->Color=clBlack;
 dosya2=fopen("bicubicdata.txt","r");
 for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n");
 dosya=fopen("bicubic.txt","w");

 for(int i=0;i<16;i++)
{
fscanf(dosya2,"%d %d %d\n",&r1,&e1,&s1);
bit_to_metric_3D(r1,e1);
perspectivetrans(xx1,yy1,s1,zzz1,zzz2,zzz3);
metric_to_bit_3D(x1,y1);
r1=(int) xx1;
e1=(int) yy1;
s1=(int) z1;
fprintf(dosya,"%d %d %d\n",r1,e1,s1);
}
fclose(dosya2);
fclose(dosya);
redrawsurfaces();
//bicubicsurface();
}
//---
if(StoreSurface[i].mode==4)
{

for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t];
BBy[k][t]=StoreSurface[i].by[k][t];
BBz[k][t]=StoreSurface[i].bz[k][t];
}
delightsurface();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
drawpolygon();
beziersurface();
//**

for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
bit_to_metric_3D((StoreSurface[i].bx[k][t]),StoreSurface[i].by[k][t]);
perspectivetrans(xx1,yy1,StoreSurface[i].bz[k][t],zzz1,zzz2,zzz3);
metric_to_bit_3D(x1,y1);
BBx[k][t]=StoreSurface[i].bx[k][t]=xx1;
BBy[k][t]=StoreSurface[i].by[k][t]=yy1;
BBz[k][t]=StoreSurface[i].bz[k][t]=z1;
StoreSurface[i].bx[k][t]=BBx[k][t];
StoreSurface[i].by[k][t]=BBy[k][t];
}

Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
redrawsurfaces();
//beziersurface();
}
if(StoreSurface[i].mode==5)
{

for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t];
BBy[k][t]=StoreSurface[i].by[k][t];
BBz[k][t]=StoreSurface[i].bz[k][t];
}
delightsurface();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
drawpolygon();
bsplinesurface();
//---

for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
bit_to_metric_3D((StoreSurface[i].bx[k][t]),StoreSurface[i].by[k][t]);
perspectivetrans(xx1,yy1,StoreSurface[i].bz[k][t],zzz1,zzz2,zzz3);
metric_to_bit_3D(x1,y1);
BBx[k][t]=StoreSurface[i].bx[k][t]=xx1;
BBy[k][t]=StoreSurface[i].by[k][t]=yy1;
BBz[k][t]=StoreSurface[i].bz[k][t]=z1;
StoreSurface[i].bx[k][t]=BBx[k][t];
StoreSurface[i].by[k][t]=BBy[k][t];

}
Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
redrawsurfaces();
}
}
}   //point_found

//if(StorePoints[point_found][1]==1)
//Application->MessageBox("Sorry!Perspective transformation is not available on points!!","Error",MB_OK);
/*
if(StorePoints[point_found][1]==4)
{
 temp_matrix1[0][0]=StorePoints[point_found][2];
 temp_matrix1[1][0]=StorePoints[point_found][3];
 temp_matrix1[2][0]=StorePoints[point_found][4];
 temp_matrix1[3][0]=temp_matrix1[3][1]=1;
 temp_matrix1[0][1]=StorePoints[point_found][5];
 temp_matrix1[1][1]=StorePoints[point_found][6];
 temp_matrix1[2][1]=StorePoints[point_found][7];
 multiply_matrices(3);
 Normalize_matrix(4,4,2,4);//mode,row,column,to norm
 metric_to_bit_3D(temp_matrix3[0][0],temp_matrix3[1][0]);
 StorePoints[point_found][8]=xx1;
 StorePoints[point_found][9]=yy1;
 Form1->PaintBox1->Canvas->MoveTo(xx1,yy1);
 metric_to_bit_3D(temp_matrix3[0][1],temp_matrix3[1][1]);
 StorePoints[point_found][10]=xx1;
 StorePoints[point_found][11]=yy1;
 Form1->PaintBox1->Canvas->LineTo(xx1,yy1);
 }
 */  //for line
}   //point_found
}   //fault0

//---------------------------------------------------------------------------

void __fastcall TForm1::CurvesClick(TObject *Sender)
{
hide_boxes();

Point_properties->Visible=False;
Panel11->Visible=True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{

parabola_clicked=0;
hyperbola_clicked=ellipse_clicked=0;
hide_boxes();
Panel11->Visible=True;
Label11->Visible=False;
Edit9->Visible=False;
Label10->Visible=False;
des_label1->Visible=True;
des_label1->Caption="Point (300,250) is taken as origin!!!!";
Panel13->Visible=True;
Label7->Caption="xcenter";
Label8->Caption="ycenter";
Label9->Caption="radius";
Edit6->Text="";
Edit7->Text="";
Edit8->Text="";
circle_clicked=1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawClick(TObject *Sender)
{
if(circle_clicked==1)
{
if(Edit6->Text=="") fault=1;
if(Edit7->Text=="") fault=1;
if(Edit8->Text=="") fault=1;
if (fault==1)
Application->MessageBox("You should enter a valid coordinate value!!","Error",MB_OK);
else
{
x1=StrToFloat(Edit6->Text);
x2=StrToFloat(Edit7->Text);
y1=StrToFloat(Edit8->Text);
StoreConic[conic_index][0]=1;//circle
StoreConic[conic_index][1]=x1;
StoreConic[conic_index][2]=x2;
StoreConic[conic_index][3]=y1;
conic_index+=1;
draw_circle(x1,x2,y1);
}
}//circle-clkicked
fault=0;
//////////
if(ellipse_clicked==1)
{

if(Edit6->Text=="") fault=1;
if(Edit7->Text=="") fault=1;
if(Edit8->Text=="") fault=1;
if(Edit9->Text=="") fault=1;
if (fault==1)
Application->MessageBox("You should enter a valid coordinate value!!","Error",MB_OK);
else
{
x1=StrToFloat(Edit6->Text);
x2=StrToFloat(Edit7->Text);
y1=StrToFloat(Edit8->Text);
y2=StrToFloat(Edit9->Text);
}
StoreConic[conic_index][0]=2;//ellipse
StoreConic[conic_index][1]=x1;
StoreConic[conic_index][2]=x2;
StoreConic[conic_index][3]=y1;
StoreConic[conic_index][4]=y2;
conic_index+=1;
draw_ellipse(x1,x2,y1,y2);
}//ellipse
fault=0;
////////////
if(hyperbola_clicked==1)
{

if(Edit6->Text=="") fault=1;
if(Edit7->Text=="") fault=1;
if(Edit8->Text=="") fault=1;
if(Edit9->Text=="") fault=1;
if (fault==1)
Application->MessageBox("You should enter a valid coordinate value!!","Error",MB_OK);
else
{
x1=StrToFloat(Edit6->Text);
x2=StrToFloat(Edit7->Text);
y1=StrToFloat(Edit8->Text);
y2=StrToFloat(Edit9->Text);
}
StoreConic[conic_index][0]=3;//hyperbola
StoreConic[conic_index][1]=x1;
StoreConic[conic_index][2]=x2;
StoreConic[conic_index][3]=y1;
StoreConic[conic_index][4]=y2;
conic_index+=1;
draw_hyperbola(x1,x2,y1,y2);
}//ellipse
fault=0;
//////////////
if(parabola_clicked==1)
{
if(Edit6->Text=="") fault=1;
if(Edit7->Text=="") fault=1;
if(Edit8->Text=="") fault=1;
if (fault==1)
Application->MessageBox("You should enter a valid coordinate value!!","Error",MB_OK);
else
{
x1=StrToFloat(Edit6->Text);
x2=StrToFloat(Edit7->Text);
y1=StrToFloat(Edit8->Text);
}
StoreConic[conic_index][0]=4;//parabola
StoreConic[conic_index][1]=x1;
StoreConic[conic_index][2]=x2;
StoreConic[conic_index][3]=y1;
conic_index+=1;
draw_parabola(x1,x2,y1);
}//ellipse
fault=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
circle_clicked=0;
hyperbola_clicked=parabola_clicked=0;
hide_boxes();
Panel11->Visible=True;
Label11->Visible=False;
des_label1->Visible=True;
des_label1->Caption="Point (300,250) is taken as origin!!!!";
Panel13->Visible=True;
Label7->Caption="xcenter";
Label8->Caption="ycenter";
Label9->Caption="semimajor";
Label10->Visible=True;
Label10->Caption="semiminor";
Edit6->Text="";
Edit7->Text="";
Edit8->Text="";
Edit9->Visible=True;
Edit9->Text="";
ellipse_clicked=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::hyperbolaClick(TObject *Sender)
{
circle_clicked=0;
parabola_clicked=ellipse_clicked=0;
hide_boxes();
Panel11->Visible=True;
Label11->Visible=False;
des_label1->Visible=True;
des_label1->Caption="Point (300,250) is taken as origin!!!!";
Panel13->Visible=True;
Label7->Caption="xcenter";
Label8->Caption="ycenter";
Label9->Caption="xintersect";
Label10->Visible=True;
Label10->Caption="yintersect";
Edit6->Text="";
Edit7->Text="";
Edit8->Text="";
Edit9->Visible=True;
Edit9->Text="";
hyperbola_clicked=1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::parabolaClick(TObject *Sender)
{

circle_clicked=0;
hyperbola_clicked=ellipse_clicked=0;
hide_boxes();
Panel11->Visible=True;
Label11->Visible=True;
des_label1->Visible=True;
des_label1->Caption="Point (300,250) is taken as origin!!!!";
Panel13->Visible=True;
Label7->Caption="a";
Label8->Caption="b";
Label9->Caption="c";
Label10->Visible=False;
Edit6->Text="";
Edit7->Text="";
Edit8->Text="";
Edit9->Visible=False;
parabola_clicked=1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Panel12Click(TObject *Sender)
{
Panel13->Visible=False;
Panel11->Visible=False;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Color1Click(TObject *Sender)
{

for(int i=0;i<=640;i++)
{
for(int j=0;j<=460;j++)
{
if(PaintBox1->Canvas->Pixels[i][j]==clBtnFace)
PaintBox1->Canvas->Pixels[i][j]=clRed;
}
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CubicSplineClick(TObject *Sender)
{
others_clicked();
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption="First select Mode. Then with mouse select points on the spline and press OK button to draw the spline";
Panel14->Visible=False;
cubicspline_clicked=1;
naspline_clicked=1;
Button4->Visible=True;
nonnatcubicspline_clicked=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::EndSplineClick(TObject *Sender)
{
int index;
int relative_position=0;
cubicspline_clicked=0;
if(splinepointnumber<2)
Application->MessageBox("To draw a spline you should first click on the spline method you want and then select at least two coordinates with mouse!!","Error",MB_OK);
else
{
if(naspline_clicked==1)
{
for (int i=0;i<splinepointnumber;i++)
{
Spline_mode[spline_index]=1;
StoreSpline[spline_index][4]=splinepointnumber;
StoreSpline[spline_index][0]=1;//na=1,cub=2,cyc=3,anticyc=4,para=5
StoreSpline[spline_index][1]=splinex[i];
StoreSpline[spline_index][2]=spliney[i];
bit_to_metric_3D(splinex[i],spliney[i]);
StoreSplineReal[spline_index][1]=xx1;;
StoreSplineReal[spline_index][2]=yy1;
StoreSplineReal[spline_index][8]=splinez[i];
StoreSpline[spline_index][5]=relative_position;
spline_index+=1;
relative_position+=1;
}
spline_mode=0;
natcubicspline(splinepointnumber,splinex,spliney);
spline_drawn=1;
hold_spline_point=splinepointnumber;
}
//------------------
if(nonnatcubicspline_clicked==1)
{
if((Edit10->Text=="")||(Edit11->Text==""))
Application->MessageBox("You should enter valid slope values!!Click ClampEnd Button again,enter slope values ,click several points on the window and press OK button!!","Error",MB_OK);
else
{
spline_number+=1;
Spline_mode[spline_number]=2;
slope1=StrToFloat(Edit10->Text);
slope2=StrToFloat(Edit11->Text);
for (int i=0;i<splinepointnumber;i++)
{
Spline_mode[spline_index]=2;
StoreSpline[spline_index][0]=2;//na=1,cub=2,cyc=3,anticyc=4,para=5
StoreSpline[spline_index][1]=splinex[i];
StoreSpline[spline_index][2]=spliney[i];
StoreSpline[spline_index][3]=slope1;
StoreSpline[spline_index][7]=slope2;
StoreSpline[spline_index][5]=relative_position;
StoreSpline[spline_index][4]=splinepointnumber;
spline_index+=1;
relative_position+=1;
}
spline_mode=1;
cubicspline(splinepointnumber,splinex,spliney,slope1,slope2);
hold_spline_point=splinepointnumber;
spline_drawn=1;
}
}
//--------------------
if(para_blend==1)
{
if(splinepointnumber==2)
Application->MessageBox("Sorry! For parabolic blending calculations at least three points are needed!!! Four points define the parabolic blend truely ","Error",MB_OK);
else
{
for (int i=0;i<splinepointnumber;i++)
{
StoreSpline[spline_index][0]=5;//na=1,cub=2,cyc=3,anticyc=4,para=5
StoreSpline[spline_index][1]=splinex[i];
StoreSpline[spline_index][2]=spliney[i];
StoreSpline[spline_index][5]=relative_position;
StoreSpline[spline_index][4]=splinepointnumber;
spline_index+=1;
relative_position+=1;
}
spline_number+=1;
Spline_mode[spline_number]=5;
mode=0;
parblend(splinepointnumber,splinex,spliney);
spline_drawn=0;
}
}
//-------------------
if(cyclic_spline_clicked==1)
{

for (int i=0;i<splinepointnumber;i++)
{
StoreSpline[spline_index][0]=3;//na=1,cub=2,cyc=3,anticyc=4,para=5
StoreSpline[spline_index][1]=splinex[i];
StoreSpline[spline_index][2]=spliney[i];
StoreSpline[spline_index][5]=relative_position;
StoreSpline[spline_index][4]=splinepointnumber;
spline_index+=1;

relative_position+=1;
}
spline_number+=1;
Spline_mode[spline_number]=3;

cycliccubicspline(splinepointnumber,splinex,spliney);
spline_drawn=0;
}
//-----------------
if(anticyclic_spline_clicked==1)
{

for (int i=0;i<splinepointnumber;i++)
{
StoreSpline[spline_index][0]=4;//na=1,cub=2,cyc=3,anticyc=4,para=5
StoreSpline[spline_index][1]=splinex[i];
StoreSpline[spline_index][2]=spliney[i];
StoreSpline[spline_index][5]=relative_position;
StoreSpline[spline_index][4]=splinepointnumber;
spline_index+=1;

relative_position+=1;
}
spline_number+=1;
Spline_mode[spline_number]=4;

anticycliccubicspline(splinepointnumber,splinex,spliney);
spline_drawn=0;
}



//------------------
splinepointnumber=0;
naspline_clicked=0;
para_blend=0;
nonnatcubicspline_clicked=0;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
others_clicked();
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption="First select Mode. Then with mouse select points on the spline and press OK button to draw the spline";
Button4->Visible=True;
cubicspline_clicked=1;
nonnatcubicspline_clicked=1;
naspline_clicked=0;
Panel14->Visible=True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SplinesClick(TObject *Sender)
{
hide_boxes();
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption="First select Mode. Then with mouse select points on the spline and press OK button to draw the spline";
Point_properties->Visible=False;
Button4->Visible=False;
Panel15->Visible=True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
Label12->Visible=True;
Label12->Color=cl3DLight;
Label12->Font->Color=clFuchsia;
Label12->Caption="Click a point on screen with mouse.The last drawn spline will fit to that point. Have to click Add Point at each point addition.";
if(spline_drawn==1)
{
fit_point_to_spline_clicked=1;
cubicspline_clicked=0;
}
else
Application->MessageBox("Sorry!No spline drawn yet!! Add point is applicable to only the currently drawn natural or clamped end cubic splines!!!**First select which spline you would like to draw and then use mouse to select points.Finally, click the OK button to draw the spline!!","Error",MB_OK);

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::ParaBlendClick(TObject *Sender)
{
others_clicked();
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption="With mouse click points to construct  spline and press OK button to draw the spline";
spline_drawn=0;
Panel14->Visible=False;
cubicspline_clicked=1;
naspline_clicked=0;
Button4->Visible=True;
nonnatcubicspline_clicked=0;
//--
others_clicked();
para_blend=1;
splinepointnumber=0;
Button4->Visible=False;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::cyclicendClick(TObject *Sender)
{
others_clicked();
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption="First select Mode. Then with mouse select points on the spline and press OK button to draw the spline";
Panel14->Visible=False;
cubicspline_clicked=1;
cyclic_spline_clicked=1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::anticyclicClick(TObject *Sender)
{
others_clicked();
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption="First select Mode. Then with mouse select points on the spline and press OK button to draw the spline";
Panel14->Visible=False;
cubicspline_clicked=1;
anticyclic_spline_clicked=1;	
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SelectClick(TObject *Sender)
{
others_clicked();
hide_boxes();
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
Form1->Label17->Visible=True;
Form1->Label12->Visible=True;
// perspective->Visible=True;
Form1->Label12->Caption="You  see that objects on the work area are lighted.Click a lighted point on the object to select it. ";
Form1->Label17->Caption="Red points show valid selection.  Then press the following transformation method you want.";
int ia,i2,i3,i4,i5;
go_to_select=1;
Form1->Cursor=crCross;
//splines
selectall(1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
/*/int count,t=1;
//int index=ListBox1->Items->ItemIndex;
int i,mode=Spline_mode[index+1],i=0;

while((t==1)&&(i<spline_index))
{
i++;
{
if((StoreSpline[0][i]==mode)&&(count==index+1))
{
t=0;
count+=1;
found=i;
}
}

for(int j=0;j<8;j++)
{
PaintBox1->Canvas->Pixels[StoreSpline[found][1]][StoreSpline[found][2]]=clBlue;

}*/
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BezierClick(TObject *Sender)
{
others_clicked();
bezier_clicked=1;
hide_boxes();
count=0;
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption="With mouse select points of the bezier and press OK button to draw the curve.Each time you have to press this";

Label17->Visible=True;
Label17->Color=clBtnHighlight;
Label17->Font->Color=clRed;
Label17->Caption="button to draw a new bezier curve!!";
Point_properties->Visible=False;
Button4->Visible=False;
Panel17->Visible=True;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
int index;
int relative_position=0;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
if(beziersurface_clicked==0)
{
if(splinepointnumber<2)
Application->MessageBox("To draw a bezier curve you should first select at least two coordinates with mouse!!","Error",MB_OK);
else
{
for (int i=0;i<splinepointnumber;i++)
{
StoreBezier[bezier_index][3]=splinepointnumber;
StoreBezier[bezier_index][0]=splinex[i];
StoreBezier[bezier_index][1]=spliney[i];
StoreBezier[bezier_index][2]=relative_position;
bezier_index+=1;
relative_position+=1;
}
}
}
bezier(splinepointnumber,splinex,spliney);
splinepointnumber=0;
//---
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void initializeknot1(void)
{
int d=1;

knot1[0]=0;
knot1[1]=0;
knot1[2]=0;
int f=3;
while(d<splinepointnumber-1)
{
for(int t=0;t<knot[d];t++)
{
 knot1[f]=d;
 f++;
}
d++;
}
knot1[f]=splinepointnumber-1;
knot1[f+1]=splinepointnumber-1;
knot1[f+2]=splinepointnumber-1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
others_clicked();
hide_boxes();
initializeknot();
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption="With mouse select points of the bezier and press OK button to draw the curve.Each time you have to press this";

Label17->Visible=True;
Label17->Color=clBtnHighlight;
Label17->Font->Color=clRed;
Label17->Caption="button to draw a new bspline curve!!";

bspline_clicked=1;
Panel24->Visible=True;

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void initializeknot(void)
{
for(int i=0;i<splinepointnumber;i++)
knotocc[i]=1;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::Button13Click(TObject *Sender)
{
int Z=StrToFloat(Form1->Edit13->Text);
zz1=Z;
zentered=1;
//---
if(Point_clicked==1)
{
point_2D(StorePoints[hold_point_number][2],StorePoints[hold_point_number][3],Point_size);
StorePoints[hold_point_number][6]=Z;
}
//---
if(line_3D_clicked==1)
{
if(f1==0)
{
StorePoints[hold_point_number][4]=Z;
}
if(f1==1)
{
f1=0;
StorePoints[hold_point_number][7]=Z;
PaintBox1->Canvas->Pen->Color=clBlack;
PaintBox1->Canvas->MoveTo(StorePoints[hold_point_number][8],StorePoints[hold_point_number][9]);
PaintBox1->Canvas->LineTo(StorePoints[hold_point_number][10],StorePoints[hold_point_number][11]);
}
}
//---
if (cubicspline_clicked==1)
{
 splinepointnumber=splinepointnumber-1;
 splinez[splinepointnumber]=Z;
 if(ruledsurface_clicked==1)  splinez[splinepointnumber]=Z;
 bit_to_metric_3D(splinex[splinepointnumber],spliney[splinepointnumber]);
 put3d(xx1,yy1,Z,rotaroundx*2*(M_PI)/360,rotaroundy*2*M_PI/360);
 metric_to_bit_3D(x1,y1);
 splinex[splinepointnumber]=xx1;
 spliney[splinepointnumber]=yy1;

 splinepointnumber=splinepointnumber+1;
 zentered=1;
}
 Form1->Panel20->Visible=False;
 }
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm1::Button15Click(TObject *Sender)
{
hide_boxes();
others_clicked();
Panel22->Visible=True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button16Click(TObject *Sender)
{
others_clicked();
hide_boxes();
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption="Click two points.A curve(one edge) will be drawn.Click two other points to draw the other edge.The surface will be drawn automatically.";
Label17->Visible=True;
Label17->Color=clBtnHighlight;
Label17->Font->Color=clRed;
Label17->Caption="Click the ChangeSurface button to make changes on a surface";
ruledsurface_clicked=1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button17Click(TObject *Sender)
{
if(ruledsurface_clicked==1)
{
if(term==0)
{
n00=splinepointnumber;
splinepointnumber=0;
term=1;
ShowMessage("Now you have to click points for the other side of the surface and then press OK");
}
else
{
 n11=splinepointnumber;
 double r[6]={1,2.5,2.5,2,2.5,3};
double r1[6]={1,1,2,2.5,3,3};
double r2[6]={0,0,.5,.5,1,1};
double r3[5]={3,3,4,5,5};
 double r4[5]={0,0,1,1.5,2.5};
 double r5[5]={0,0,1,1,2};

 rulesurf(6,5,r,r1,r2,r3,r4,r5);
//rulesurf(n00,n11,xp0,yp0,zp0,xp1,yp1,zp1);
ruledsurface_clicked=0;
}
}
if(bsurface_clicked==1)
{
if(term==0)
{
n00=splinepointnumber;
splinepointnumber=0;
term=1;
ShowMessage("Now you have to click points for the other side of the surface and then press OK");
}
else if(term==1)
{
 n11=splinepointnumber;
 splinepointnumber=0;
term=2;
ShowMessage("Now you have to click points for the other side of the surface and then press OK");
}
else if(term==2)
{
 n22=splinepointnumber;
 splinepointnumber=0;
term=3;
ShowMessage("Now you have to click points for the other side of the surface and then press OK");
}
else if(term==3)
{
 n33=splinepointnumber;
 splinepointnumber=0;
term=0;

 edgesurf(n00,n11,n22,n33,xp0,yp0,zp0,xp1,yp1,zp1,xp2,yp2,zp2,xp3,yp3,zp3);
//rulesurf(n00,n11,xp0,yp0,zp0,xp1,yp1,zp1);
ruledsurface_clicked=0;
}
}


 }
//---------------------------------------------------------------------------
void __fastcall TForm1::Button18Click(TObject *Sender)
{
others_clicked();
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption="The surface is drawn by using the data set provided in he text file 'tempbicubic.txt'.  The text file provides 16 data values";
Label17->Visible=True;
Label17->Color=clBtnHighlight;
Label17->Font->Color=clRed;
Label17->Caption="which correspond to the elements of the matrix given in the class. This file can be changed in order to see the effects of the changes.  Also ChangeSurface can be used to modify the surface.";
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
bicubicind++;
if((tempdosya=fopen("tempbicubic.txt","r"))==NULL)
ShowMessage("Can not open the data file 'bicubic.txt'!");
else
{
  for(int t=0;t<4;t++)
{
 for(int i=0;i<4;i++)
 {
  fscanf(tempdosya,"%d %d %d\n",&r1,&e1,&s1);
  Mx[i][t]=r1;
  My[i][t]=e1;
  Mz[i][t]=s1;
 }
}
}
fclose(tempdosya);
 StoreSurface[surfaceindex].mode=3;
 StoreSurface[surfaceindex].p[0][0]=Mx[0][0];
 StoreSurface[surfaceindex].p[0][1]=My[0][0];
 StoreSurface[surfaceindex].p[0][2]=Mz[0][0];
 StoreSurface[surfaceindex].p[1][0]=Mx[0][1];
 StoreSurface[surfaceindex].p[1][1]=My[0][1];
 StoreSurface[surfaceindex].p[1][2]=Mz[0][1];
 StoreSurface[surfaceindex].p[2][0]=Mx[1][0];
 StoreSurface[surfaceindex].p[2][1]=My[1][0];
 StoreSurface[surfaceindex].p[2][2]=Mz[1][0];
 StoreSurface[surfaceindex].p[3][0]=Mx[1][1];
 StoreSurface[surfaceindex].p[3][1]=My[1][1];
 StoreSurface[surfaceindex].p[3][2]=Mz[1][1];
 numofbicubicsurf++;
 StoreSurface[surfaceindex].selfindex=numofbicubicsurf;
 surfaceindex++;
//fclose(dosya);
//**
//store each one in another file
if(bicubicind==0)
{
 tempdosya=fopen("tempbicubic.txt","r");
dosya2=fopen("bicubicdata.txt","w");
  for(int t=0;t<4;t++)
{
 for(int i=0;i<4;i++)
 {
  fscanf(tempdosya,"%d %d %d\n",&r1,&e1,&s1);
  fprintf(dosya2,"%d %d %d\n",r1,e1,s1);
 }
}
fclose(tempdosya);
fclose(dosya2);
}
else
{
dosya2=fopen("bicubicdata.txt","a+");
tempdosya=fopen("tempbicubic.txt","r");
if(dosya2==NULL)
ShowMessage("Can not open the temp data file 'bicubicdata.txt'!");
else
{
//  fseek(dosya,0,SEEK_SET);
  for(int t=0;t<4;t++)
{
 for(int i=0;i<4;i++)
 {
  fscanf(tempdosya,"%d %d %d\n",&r1,&e1,&s1);
  fprintf(dosya2,"%d %d %d\n",r1,e1,s1);
 }
}
fclose(dosya2);
}
}
fclose(tempdosya);
//***
tempdosya=fopen("tempbicubic.txt","r");
dosya=fopen("bicubic.txt","r+");
  for(int t=0;t<4;t++)
{
 for(int i=0;i<4;i++)
 {
  fscanf(tempdosya,"%d %d %d\n",&r1,&e1,&s1);
  fprintf(dosya,"%d %d %d\n",r1,e1,s1);
 }
}
//***
fclose(tempdosya);
fclose(dosya);
bicubicsurface();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button19Click(TObject *Sender)
{
others_clicked();
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption="Click 4 points(corners) with mouse. After the surface is drawn you can modify";
Label17->Visible=True;
Label17->Color=clBtnHighlight;
Label17->Font->Color=clRed;
Label17->Caption="it by pressing the ChangeSurface button";
bilinearsurf_clicked=1;
surfind=0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button20Click(TObject *Sender)
{
others_clicked();
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption="Click and drag the yellow dots to play with the surface. You have to click ChangeSurface button each time you want to make a change on a surface";
changesurface_clicked=1;
lightsurface();
}
//---------------------------------------------------------------------------
void lightsurfacered(int x,int y)
{
int i=0,found=0,go=0,t=0,h=0;
surfaceselected=0;
while((found==0)&&(i<surfaceindex))
{
if(StoreSurface[i].mode==1)
{
 while((go==0)&&(t<4))
 {
 if((abs(x-StoreSurface[i].p[t][0])<5)&&(abs(y-StoreSurface[i].p[t][1])<5))
 go=1;
 else t++;
 }
 if(go==1)
 {
 foundsurfindex=i;//point found
 found=1;
 surfpointindex=t;//relative position in the P[][] matrix
 for(int m=0;m<4;m++)
 {
  P[m][0]=StoreSurface[i].p[m][0];
  P[m][1]=StoreSurface[i].p[m][1];
 }
 }
}
//-----
if(StoreSurface[i].mode==2)
{
 while((go==0)&&(t<4))
 {
 if((abs(x-StoreSurface[i].p[t][0])<5)&&(abs(y-StoreSurface[i].p[t][1])<5))
 go=1;
 else t++;
 }
 if(go==1)
 {
 foundsurfindex=i;//point found
 found=1;
 surfpointindex=t;//relative position in the P[][] matrix
 for(int m=0;m<4;m++)
 {
  P[m][0]=StoreSurface[i].p[m][0];
  P[m][1]=StoreSurface[i].p[m][1];
 }
 }
}
//---
if(StoreSurface[i].mode==3)
{
 while((go==0)&&(t<4))
 {
 if((abs(x-StoreSurface[i].p[t][0])<5)&&(abs(y-StoreSurface[i].p[t][1])<5))
 go=1;
 else t++;
 }
 if(go==1)
 {

 foundsurfindex=i;//point found
 found=1;
 surfpointindex=t;//relative position in the P[][] matrix
 for(int m=0;m<4;m++)
 {
  P[m][0]=StoreSurface[i].p[m][0];
  P[m][1]=StoreSurface[i].p[m][1];
 }
 }
}
//---
if(StoreSurface[i].mode==4)
{
 while((go==0)&&(t<3))
 {
 if((abs(x-StoreSurface[i].bx[h][t])<5)&&(abs(y-StoreSurface[i].by[h][t])<5))
 go=1;
 else
 {
 h++;
 if(h==5)
 {
 h=0;
 t++;
 }
 }
 if(go==1)
 {

 foundsurfindex=i;//point found
 found=1;
 surfpointindex=h;//relative position in the P[][] matrix
 surfpointindex2=t;
 }
 }
}
//----
if(StoreSurface[i].mode==5)
{
 while((go==0)&&(t<3))
 {
 if((abs(x-StoreSurface[i].bx[h][t])<5)&&(abs(y-StoreSurface[i].by[h][t])<5))
 go=1;
 else
 {
 h++;
 if(h==5)
 {
 h=0;
 t++;
 }
 }
 if(go==1)
 {
 foundsurfindex=i;//point found
 found=1;
 surfpointindex=h;//relative position in the P[][] matrix
 surfpointindex2=t;
 }
 }
}
 //---
i++;
t=0;
}
//**
if(found==1)
{
surfaceselected=1;
int index=foundsurfindex;
if(StoreSurface[index].mode!=4)
{
for(int t=0;t<4;t++)
light_selected_point(StoreSurface[index].p[t][0],StoreSurface[index].p[t][1],6);
}
if(StoreSurface[index].mode==4)
{
for(int t=0;t<3;t++)
for(int f=0;f<5;f++)
light_selected_point(StoreSurface[index].bx[f][t],StoreSurface[index].by[f][t],6);
}
if(StoreSurface[index].mode==5)
{
for(int t=0;t<3;t++)
for(int f=0;f<5;f++)
light_selected_point(StoreSurface[index].bx[f][t],StoreSurface[index].by[f][t],6);
}
}
}
//---------------------------------------------------------------------------
void lightsurface(void)
{
for(int i=0;i<surfaceindex;i++)
{
if(StoreSurface[i].mode==1)
{
for(int t=0;t<4;t++)
light_selected_yellow(StoreSurface[i].p[t][0],StoreSurface[i].p[t][1],1);
}
//---
if(StoreSurface[i].mode==2)
{
for(int t=0;t<4;t++)
light_selected_yellow(StoreSurface[i].p[t][0],StoreSurface[i].p[t][1],1);
}
//---
if(StoreSurface[i].mode==3)
{
for(int t=0;t<4;t++)
light_selected_yellow(StoreSurface[i].p[t][0],StoreSurface[i].p[t][1],1);
}
//---
if(StoreSurface[i].mode==4)
{
for(int t=0;t<3;t++)
for(int f=0;f<5;f++)
light_selected_yellow(StoreSurface[i].bx[f][t],StoreSurface[i].by[f][t],1);
}
//---
if(StoreSurface[i].mode==5)
{
for(int t=0;t<3;t++)
for(int f=0;f<5;f++)
light_selected_yellow(StoreSurface[i].bx[f][t],StoreSurface[i].by[f][t],1);
}
}
}
//---------------------------------------------------------------------------
void delightsurface(void)
{
for(int i=0;i<surfaceindex;i++)
{
if(StoreSurface[i].mode==1)
{
for(int t=0;t<4;t++)
light_selected_yellow(StoreSurface[i].p[t][0],StoreSurface[i].p[t][1],2);
}
//---
if(StoreSurface[i].mode==2)
{
for(int t=0;t<4;t++)
light_selected_yellow(StoreSurface[i].p[t][0],StoreSurface[i].p[t][1],2);
}
//---
if(StoreSurface[i].mode==3)
{
for(int t=0;t<4;t++)
light_selected_yellow(StoreSurface[i].p[t][0],StoreSurface[i].p[t][1],2);
}
//---
if(StoreSurface[i].mode==4)
{
for(int t=0;t<3;t++)
for(int f=0;f<5;f++)
light_selected_yellow(StoreSurface[i].bx[f][t],StoreSurface[i].by[f][t],2);
}
//---
if(StoreSurface[i].mode==5)
{
for(int t=0;t<3;t++)
for(int f=0;f<5;f++)
light_selected_yellow(StoreSurface[i].bx[f][t],StoreSurface[i].by[f][t],2);
}
}
}
//--------------------------------------------------------------------------
void redrawsurfaces(void)
{
for(int i=0;i<surfaceindex;i++)
{
if(StoreSurface[i].mode==1)
{
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0];
P[t1][1]=StoreSurface[i].p[t1][1];
}
bilinearsurface();
}
//---
if(StoreSurface[i].mode==2)
{
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0];
P[t1][1]=StoreSurface[i].p[t1][1];
}
rulecubic();
a1=B[0][0];
aa1=B[0][1];
aaa1=B[0][2];
a2=B[2][0];
aa2=B[2][1];
aaa2=B[2][2];
a3=B[3][0];
aa3=B[3][1];
aaa3=B[3][2];
P[0][0]=P[2][0];
P[0][1]=P[2][1];
P[1][0]=P[3][0];
P[1][1]=P[3][1];
rulecubic();
ruledsurface();
}
//---
if(StoreSurface[i].mode==3)
{
 dosya2=fopen("bicubicdata.txt","r");
 for(int j=0;j<(16*(StoreSurface[i].selfindex-1));j++)
 fscanf(dosya2,"%d %d %d\n",&e1,&r1,&s1);
 dosya=fopen("bicubic.txt","w");
 for(int j=0;j<16;j++)
{
fscanf(dosya2,"%d %d %d\n",&r1,&e1,&s1);
fprintf(dosya,"%d %d %d\n",r1,e1,s1);
}
fclose(dosya2);
fclose(dosya);
bicubicsurface();
}
//---
if(StoreSurface[i].mode==4)
{
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t];
BBy[k][t]=StoreSurface[i].by[k][t];
BBz[k][t]=StoreSurface[i].bz[k][t];
}
beziersurface();
}
//---
if(StoreSurface[i].mode==5)
{
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t];
BBy[k][t]=StoreSurface[i].by[k][t];
BBz[k][t]=StoreSurface[i].bz[k][t];
}
bsplinesurface();
}
//---
}
}
void __fastcall TForm1::Button21Click(TObject *Sender)
{
Panel23->Visible=False;
xx1=StrToFloat(Edit16->Text);
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
redrawsurfaces();
nsegs1=nsegs2=xx1;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
redrawsurfaces();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SurfaceLines1Click(TObject *Sender)
{
Panel23->Visible=True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button22Click(TObject *Sender)
{
others_clicked();
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption=" 5*3 Bezier surface.Click 5 points and a Bezier curve will be drawn.Click 5 more points to draw the other edge.Click a point and ";
Label17->Visible=True;
Label17->Color=clBtnHighlight;
Label17->Font->Color=clRed;
Label17->Caption="one neighbour edge will be drawn.Click a new point to draw last edge.Click 3 more points(defines interior corners)";
beziersurface_clicked=1;
bezier_clicked=1;
}
//---------------------------------------------------------------------------
void drawpolygon(void)
{
 Form1->PaintBox1->Canvas->MoveTo(BBx[0][0],BBy[0][0]);
 for(int i=1;i<5;i++)
 {
  Form1->PaintBox1->Canvas->LineTo(BBx[i][0],BBy[i][0]);
 }
 Form1->PaintBox1->Canvas->MoveTo(BBx[0][2],BBy[0][2]);
 for(int i=1;i<5;i++)
 {
  Form1->PaintBox1->Canvas->LineTo(BBx[i][2],BBy[i][2]);
 }
 Form1->PaintBox1->Canvas->MoveTo(BBx[0][1],BBy[0][1]);
 for(int i=1;i<5;i++)
 {
  Form1->PaintBox1->Canvas->LineTo(BBx[i][1],BBy[i][1]);
 }
 Form1->PaintBox1->Canvas->MoveTo(BBx[0][0],BBy[0][0]);
 Form1->PaintBox1->Canvas->LineTo(BBx[0][1],BBy[0][1]);
 Form1->PaintBox1->Canvas->LineTo(BBx[0][2],BBy[0][2]);
 Form1->PaintBox1->Canvas->MoveTo(BBx[4][0],BBy[4][0]);
 Form1->PaintBox1->Canvas->LineTo(BBx[4][1],BBy[4][1]);
 Form1->PaintBox1->Canvas->LineTo(BBx[4][2],BBy[4][2]);
 }
//--------------------------------------------------------------------------
void surfacetransformation(int i)
{
if(StoreSurface[i].mode==1)
{
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0]=StoreSurface[i].p[t1][0];
P[t1][1]=StoreSurface[i].p[t1][1]=StoreSurface[i].p[t1][1];
}
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
bilinearsurface();
delightsurface();
if(translatesurface==1)
{
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0]=StoreSurface[i].p[t1][0]+zz1*25;
P[t1][1]=StoreSurface[i].p[t1][1]=StoreSurface[i].p[t1][1]+zz2*25;
}
}

/*if(surfacerotate==1)
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0]*cos(xx1)-sin(xx1)*StoreSurface[i].p[t1][1];
P[t1][1]=StoreSurface[i].p[t1][0]*sin(xx1)+StoreSurface[i].p[t1][1]*cos(xx1);
StoreSurface[i].p[t1][0]=P[t1][0];
StoreSurface[i].p[t1][1]=P[t1][1];
} */
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
redrawsurfaces();
}
//---
if(StoreSurface[i].mode==2)
{
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0]=StoreSurface[i].p[t1][0];
P[t1][1]=StoreSurface[i].p[t1][1]=StoreSurface[i].p[t1][1];
}
rulecubic();
a1=B[0][0];
aa1=B[0][1];
aaa1=B[0][2];
a2=B[2][0];
aa2=B[2][1];
aaa2=B[2][2];
a3=B[3][0];
aa3=B[3][1];
aaa3=B[3][2];
P[0][0]=P[2][0];
P[0][1]=P[2][1];
P[1][0]=P[3][0];
P[1][1]=P[3][1];
rulecubic();
ruledsurface();
delightsurface();
//**
if(translatesurface==1)
{
for(int t1=0;t1<4;t1++)
{
P[t1][0]=StoreSurface[i].p[t1][0]=StoreSurface[i].p[t1][0]+zz1*25;
P[t1][1]=StoreSurface[i].p[t1][1]=StoreSurface[i].p[t1][1]+zz2*25;
}
}
else if(scalesurface==1)
{
for(int t1=0;t1<4;t1++)
{
bit_to_metric_3D(StoreSurface[i].p[t1][0],StoreSurface[i].p[t1][1]);
metric_to_bit_3D(xx1*zz1,yy1*zz1);
P[t1][0]=StoreSurface[i].p[t1][0]=xx1;
P[t1][1]=StoreSurface[i].p[t1][0]=yy1;
StoreSurface[i].p[t1][0]=P[t1][0];
StoreSurface[i].p[t1][1]=P[t1][1];
}
}
rulecubic();
a1=B[0][0];
aa1=B[0][1];
aaa1=B[0][2];
a2=B[2][0];
aa2=B[2][1];
aaa2=B[2][2];
a3=B[3][0];
aa3=B[3][1];
aaa3=B[3][2];
P[0][0]=P[2][0];
P[0][1]=P[2][1];
P[1][0]=P[3][0];
P[1][1]=P[3][1];
rulecubic();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
redrawsurfaces();
//ruledsurface();
}
//---
if(StoreSurface[i].mode==3)
{
//
 Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
 dosya2=fopen("bicubicdata.txt","r");
 for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n");
 dosya=fopen("bicubic.txt","w");
 for(int i=0;i<16;i++)
{
fscanf(dosya2,"%d %d %d\n",&r1,&e1,&s1);
fprintf(dosya,"%d %d %d\n",r1,e1,s1);
}
fclose(dosya2);
fclose(dosya);
delightsurface();
bicubicsurface();

//
 Form1->PaintBox1->Canvas->Pen->Color=clBlack;
 dosya2=fopen("bicubicdata.txt","r");
 for(int i=0;i<(16*(StoreSurface[foundsurfindex].selfindex-1));i++)
 fscanf(dosya2,"%d %d %d\n");
 dosya=fopen("bicubic.txt","w");
if(translatesurface==1)
{
 for(int i=0;i<16;i++)
{
fscanf(dosya2,"%d %d %d\n",&r1,&e1,&s1);
fprintf(dosya,"%d %d %d\n",(r1+zz1*25),(e1+zz2*25),s1);
}
}
else
{
 for(int i=0;i<16;i++)
{
fscanf(dosya2,"%d %d %d\n",&r1,&e1,&s1);
fprintf(dosya,"%d %d %d\n",(r1*cos(xx1)-e1*sin(xx1)),(r1*sin(xx1)+e1*cos(xx1)),s1);
}
}
fclose(dosya2);
fclose(dosya);
redrawsurfaces();
//bicubicsurface();
}
//---
if(StoreSurface[i].mode==4)
{

for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t];
BBy[k][t]=StoreSurface[i].by[k][t];
BBz[k][t]=StoreSurface[i].bz[k][t];
}
delightsurface();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
drawpolygon();
beziersurface();
//**
if(translatesurface==1)
{
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t]=(StoreSurface[i].bx[k][t])+zz1*25;
BBy[k][t]=StoreSurface[i].by[k][t]=(StoreSurface[i].by[k][t])+zz2*25;
BBz[k][t]=StoreSurface[i].bz[k][t];
}
}
else if(scalesurface==1)
{
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
bit_to_metric_3D((StoreSurface[i].bx[k][t]),StoreSurface[i].by[k][t]);
metric_to_bit_3D(xx1*zz1,yy1*zz1);
BBx[k][t]=StoreSurface[i].bx[k][t]=xx1;
BBy[k][t]=StoreSurface[i].by[k][t]=yy1;
BBz[k][t]=StoreSurface[i].bz[k][t]=StoreSurface[i].bz[k][t]*zz1;
StoreSurface[i].bx[k][t]=BBx[k][t];
StoreSurface[i].by[k][t]=BBy[k][t];
}
}
Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
redrawsurfaces();
//beziersurface();
}
if(StoreSurface[i].mode==5)
{

for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t];
BBy[k][t]=StoreSurface[i].by[k][t];
BBz[k][t]=StoreSurface[i].bz[k][t];
}
delightsurface();
Form1->PaintBox1->Canvas->Pen->Color=clBtnFace;
drawpolygon();
bsplinesurface();
//---
if(translatesurface==1)
{
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
BBx[k][t]=StoreSurface[i].bx[k][t]=(StoreSurface[i].bx[k][t])+zz1*25;
BBy[k][t]=StoreSurface[i].by[k][t]=(StoreSurface[i].by[k][t])+zz2*25;
BBz[k][t]=StoreSurface[i].bz[k][t];
}
}
else if(scalesurface==1)
{
for(int t=0;t<3;t++)
for(int k=0;k<5;k++)
{
bit_to_metric_3D((StoreSurface[i].bx[k][t]),StoreSurface[i].by[k][t]);
metric_to_bit_3D(xx1*zz1,yy1*zz1);
BBx[k][t]=StoreSurface[i].bx[k][t]=xx1;
BBy[k][t]=StoreSurface[i].by[k][t]=yy1;
BBz[k][t]=StoreSurface[i].bz[k][t]=StoreSurface[i].bz[k][t]*zz1;
StoreSurface[i].bx[k][t]=BBx[k][t];
StoreSurface[i].by[k][t]=BBy[k][t];
}
}
Form1->PaintBox1->Canvas->Pen->Color=clYellow;;
Form1->PaintBox1->Canvas->Pen->Style=psDash;
drawpolygon();
Form1->PaintBox1->Canvas->Pen->Color=clBlack;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
redrawsurfaces();
//beziersurface();

}
}
//-----------------------------------------------------------------------------
void rotatearoundz(double x,double y,double z,double teta)
{
 double t=degree_to_radian(teta);
 x1=x*cos(t)-y*sin(t);
 y1=x*sin(t)+y*cos(t);
 z1=z;
}
//---
void rotatearoundy(double x,double y,double z,double teta)
{
 double t=degree_to_radian(teta);
 x1=x*cos(t)+z*sin(t);
 z1=-x*sin(t)+z*cos(t);
 y1=y;
}
//---
void rotatearoundx(double x,double y,double z,double teta)
{
 double t=degree_to_radian(teta);
 y1=y*cos(t)-z*sin(t);
 z1=y*sin(t)+z*cos(t);
 x1=x;
}
//---------------
void perspectivetrans(double x,double y,double z,double e,double r,double k)
{
 if(e==0) e=999999;
 if(r==0) r=999999;
 if(k==0) k=999999;
 x1=x/(x/e+y/r+z/k+1);
 y1=y/(x/e+y/r+z/k+1);
}
void __fastcall TForm1::Button23Click(TObject *Sender)
{
int index;
int relative_position=0;
Form1->PaintBox1->Canvas->Pen->Color=clBlack;;
Form1->PaintBox1->Canvas->Pen->Style=psSolid;
if(Edit17->Text=="")
{
Application->MessageBox("invalid order, taking it as 3","Error",MB_OK);
order=3;
}
else  order=StrToInt(Edit17->Text);
if(splinepointnumber<2)
Application->MessageBox("To draw a bezier curve you should first select at least two coordinates with mouse!!","Error",MB_OK);
else
{
if((order<2)||(order>splinepointnumber))
ShowMessage("order has to be between 2 and "+IntToStr(splinepointnumber));
else
{
if(bsplinesurface_clicked==0)
{
for (int i=0;i<splinepointnumber;i++)
{
StoreBspline[bspline_index][3]=splinepointnumber;
StoreBspline[bspline_index][0]=splinex[i];
StoreBspline[bspline_index][1]=spliney[i];
StoreBspline[bspline_index][2]=relative_position;
StoreBspline[bspline_index][5]=order;
StoreBspline[bspline_index][6]=1;
bspline_index+=1;
relative_position+=1;
}
}
initializeknot();
bspline(splinepointnumber,order,splinex,spliney);
}
splinepointnumber=0;
//---
}
}
//---------------------------------------------------------------------------
double calculateN(int i,double t,int k)
{
 double w,w1,q,a,l;
 if(k==1)
 {
 if((xknot[i]<=t)&&(t<xknot[i+1])) l=1;
 else l=0;
 }
else
{
w=xknot[i+k-1]-xknot[i];
w1=xknot[i+k]-xknot[i+1];
if(w==0) w=99999;
if(w1==0) w1=99999;
q=((t-xknot[i])*calculateN(i,t,k-1))/w;
a=((xknot[i+k]-t)*calculateN(i+1,t,k-1))/w1;
l=(q+a);
}
return l;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button29Click(TObject *Sender)
{
others_clicked();
Label12->Visible=True;
Label12->Color=clBtnHighlight;
Label12->Font->Color=clRed;
Label12->Caption=" 5*3 BsplineSurface.Click 5 points to define one edge.Click 5 more points to draw the opposite edge.Click a point(left point) and ";
Label17->Visible=True;
Label17->Color=clBtnHighlight;
Label17->Font->Color=clRed;
Label17->Caption="for the side edge.Click a new point(right) to draw last edge.Click 3 more points(interior corners) Then the surface will be drawn!";
bsplinesurface_clicked=1;
bspline_clicked=1;
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

