//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.WinXCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TOpenPictureDialog *OpenPictureDialog1;
	TPageControl *PageControl1;
	TButton *Button1;
	TEdit *Edit2;
	TPanel *Panel1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TImage *Image1;
	TListBox *ListBox1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TStaticText *StaticText1;
	TStaticText *StaticText2;
	TEdit *Edit1;
	TProgressBar *ProgressBar1;
	TButton *Button5;
	TProgressBar *ProgressBar2;
	TStaticText *StaticText3;
	TToggleSwitch *ToggleSwitch1;
	TToggleSwitch *ToggleSwitch2;
	TMemo *Memo1;
	TButton *Button6;
	TButton *Button7;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
