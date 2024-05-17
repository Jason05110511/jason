//---------------------------------------------------------------------------

#ifndef U2H
#define U2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TPanel *Panel1;
	TTabSheet *TabSheet2;
	TSplitter *Splitter1;
	TButton *Button1;
	TCheckBox *CheckBox1;
	TStaticText *StaticText2;
	TLabel *Label1;
	TEdit *Edit2;
	TPageControl *PageControl2;
	TTabSheet *TabSheet3;
	TTabSheet *TabSheet4;
	TButton *Button2;
	TButton *Button3;
	TEdit *Edit3;
	TEdit *Edit4;
	TStaticText *StaticText3;
	TStaticText *StaticText4;
	TMemo *Memo1;
	TMemo *Memo2;
	TStaticText *StaticText5;
	TEdit *Edit5;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations

	__fastcall TForm1(TComponent* Owner);
	void HanoiTowers(int ,String ,String ,String);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
