//---------------------------------------------------------------------------

#ifndef U5H
#define U5H
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
	TMemo *Memo1;
	TButton *Button1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TPanel *Panel1;
	TEdit *Edit1;
	TEdit *Edit2;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *Edit3;
	TLabel *Label4;
	TLabel *Label5;
	TComboBox *ComboBox1;
	TMemo *Memo2;
	TSplitter *Splitter1;
	TLabel *Label6;
	TMemo *Memo3;
	TStaticText *StaticText1;
	TStaticText *StaticText2;
	TLabel *Label7;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
