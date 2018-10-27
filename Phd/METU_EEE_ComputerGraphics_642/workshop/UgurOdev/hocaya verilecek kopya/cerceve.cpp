//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "cerceve.h"
#include "deneme1.h"
//--------------------------------------------------------------------
void cerceve(void)
{
Form1->PaintBox1->Canvas->MoveTo(0,0);
Form1->PaintBox1->Canvas->LineTo(0,462);
Form1->PaintBox1->Canvas->MoveTo(0,0);
Form1->PaintBox1->Canvas->LineTo(640,0);
Form1->PaintBox1->Canvas->MoveTo(640,462);
Form1->PaintBox1->Canvas->LineTo(0,462);
Form1->PaintBox1->Canvas->MoveTo(640,460);
Form1->PaintBox1->Canvas->LineTo(640,0);
}