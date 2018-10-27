//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("deneme1.cpp", Form1);
USERES("Project1.res");
USEUNIT("cerceve.cpp");
USEUNIT("translate.cpp");
USEUNIT("hide.cpp");
USEUNIT("delete.cpp");
USEUNIT("curves.cpp");
USEUNIT("matrix.cpp");
USEFORM("rotangle.cpp", Form2);
USEUNIT("surface.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TForm2), &Form2);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
