//---------------------------------------------------------------------------

#ifndef U4H
#define U4H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TSpeedButton *SpeedButton1;
	TPanel *Panel1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TProgressBar *ProgressBar1;
	TButton *Button1;
	TEdit *Edit1;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit2;
	TTabSheet *TabSheet2;
	TStringGrid *StringGrid1;
	TButton *Button2;
	TButton *Button3;
	TLabel *Label3;
	TEdit *Edit3;
	TTabSheet *TabSheet3;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet5;
	TTabSheet *TabSheet6;
	TStringGrid *StringGrid2;
	TStringGrid *StringGrid3;
	TStringGrid *StringGrid4;
	TStringGrid *StringGrid5;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TPageControl *PageControl2;
	TTabSheet *TabSheet7;
	TTabSheet *TabSheet8;
	TPageControl *PageControl3;
	TTabSheet *TabSheet9;
	TComboBox *ComboBox1;
	TTabSheet *TabSheet10;
	TButton *Button4;
	TButton *Button5;
	TOpenDialog *OpenDialog1;
	TEdit *Edit4;
	TEdit *Edit5;
	TButton *Button6;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *Edit6;
	TEdit *Edit7;
	TLabel *Label9;
	TTabSheet *TabSheet11;
	TButton *Button7;
	TImage *Image1;
	TTrackBar *TrackBar1;
	TLabel *Label10;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall Edit2Change(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Edit3Change(TObject *Sender);
	void __fastcall StringGrid1Click(TObject *Sender);
	void __fastcall StringGrid2DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall StringGrid3DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall StringGrid4DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall StringGrid5DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall StringGrid2Click(TObject *Sender);
	void __fastcall StringGrid3Click(TObject *Sender);
	void __fastcall StringGrid4Click(TObject *Sender);
	void __fastcall StringGrid5Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Edit4Change(TObject *Sender);
	void __fastcall Edit5Change(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
