#pragma warm -lin
#include <dos.h>

#ifndef  __MOUSE_H
#define  __MOUSE_H

#define BTN_Nothing 0
#define BTN_Left 1
#define BTN_Right 2
#define BTN_Middile 3
#define BST_Press 1
#define BST_Release 0
#define BST_Down BSN_Press
#define BST_Up BSN_Release
#define BST_ON 1
#define BST_OFF 0
#define BST_AllRelease 0
#define BST_LeftDown 1
#define BST_RightDown 2
#define BST_MiddileDown 3

void ResetMouse();
int  MauseInstalled();
int  NumberOfButton();
void ShowMouse();
void HideMouse();
void SetMousePosition(int,int);
void SetMouseRange(int,int,int,int);
void SetMouseXRange(int,int);
void SetMouseYRange(int,int);
void GetMousePosition(int*,int*,int*,int*);
int MouseStatus(int);
int LastPressPosition(int,int*,int*,int*);
int LastReleasePosition(int,int*,int*,int*);

#endif

#define MouseInterruptNumber 0x33

int MouseInstalledFlag=0;
int NumberOfButtons=0;

void MouseCommand(int *AX,int *BX,int *CX,int *DX)
{
	struct REGPACK R;

	R.r_ax=*AX;
	R.r_bx=*BX;
	R.r_cx=*CX;
	R.r_dx=*DX;

	intr(MouseInterruptNumber,&R);

	*AX=R.r_ax;
	*BX=R.r_bx;
	*CX=R.r_cx;
	*DX=R.r_dx;
}

void ResetMouse()
{
	int CX,DX;

	MouseInstalledFlag=0;
	MouseCommand(&MouseInstalledFlag,&NumberOfButtons,&CX,&DX);
}

int MouseInstalled()
{
	return MouseInstalledFlag;
}


int NumberOfButton()
{
	return NumberOfButtons;
}

void ShowMouse()
{
	int AX=1,BX,CX,DX;
	MouseCommand(&AX,&BX,&CX,&DX);
}

void HideMouse()
{
	int AX=2,BX,CX,DX;
	MouseCommand(&AX,&BX,&CX,&DX);
}



void SetMousePosition(int Hor,int Ver)
{
	int AX=4,BX=0;
	MouseCommand(&AX,&BX,&Hor,&Ver);
}



void SetMouseRange(int X1,int Y1,int X2,int Y2)
{
	int AX=8,BX=0;
	MouseCommand(&AX,&BX,&Y1,&Y2);
	AX=7;
	MouseCommand(&AX,&BX,&X1,&X2);
}



void GetMousePosition(int *X,int *Y,int *ST)
{
	int AX=3;
	MouseCommand(&AX,ST,X,Y);
}


int MouseStatus(int BT)
{
	int AX=3,BX=BT,CX,DX;
	MouseCommand(&AX,&BX,&CX,&DX);
	BX&=0x03;


	switch(BT)
	{
		case BTN_Left	 :  return  BX==1 || BX==3;
		case BTN_Right	 :  return  BX==2 || BX==3;
		case BTN_Middile :  return  BX==3;
	}

	return BST_Release;
}


int LastPressPosition(int BT,int *Hor,int *Ver,int *Con)
{
	int AX=5;

	*Con=BT;
	MouseCommand(&AX,Con,Hor,Ver);
	return AX;
}

int LastReleasePosition(int BT,int *Hor,int *Ver,int *Con)
{
	int AX=6;

	*Con=BT;
	MouseCommand(&AX,Con,Hor,Ver);
	return AX;
}





