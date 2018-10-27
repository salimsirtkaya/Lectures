//------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#include "deneme1.h"
#include "rotangle.h"
//---------------------------------------------------------------------------
extern int rotaroundx,rotaroundy;
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
rotaroundx=StrToFloat(Edit1->Text);

Form2->Visible=False;
}
//---------------------------------------------------------------------------
