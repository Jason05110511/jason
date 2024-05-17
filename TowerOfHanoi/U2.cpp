//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HW2_10360662_沈信學.h"
#include <algorithm>
#define SWAP(a,b,tem) (tem = a, a = b , b =tem)
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int counter;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//void SWAP(wchar_t a,wchar_t b,wchar_t c){c=a;a=b;b=c;}
String ss;
void perm(String s,int k,int n){
	int i;
	wchar_t tmp;
	if(k==n){
		 Form1->Memo2->Lines->Add(s+" ["+IntToStr(++counter)+"]");
		 Form1->Memo1->Lines->Add(s+" ["+IntToStr(counter)+"]");
	}
	else{
		for(i=k;i<n;i++){
			ss="";
			//Form1->Memo2 -> Lines -> Add("    >i="+IntToStr(i)+", swap(k,n)= ["+IntToStr(k)+","+IntToStr(n)+"]"+", list= "+s+",  "+s[k]+"  Swap " + s[i]);
			SWAP(s[k], s[i], tmp);
			Form1->Memo2 -> Lines -> Add("  >i="+IntToStr(i-1)+", (k,n)=("+IntToStr(k-1)+","+IntToStr(n-1)+")"+", swap[k,x]=["+IntToStr(k-1)+","+IntToStr(i-1)+"]"+", list= "+s+",  "+s[k]+"  Swap " + s[i]);
			perm(s,k+1,n);
			SWAP(s[k], s[i], tmp);
			Form1->Memo2 -> Lines -> Add("      <i="+IntToStr(i-1)+", (k,n)=("+IntToStr(k-1)+","+IntToStr(n-1)+")"+", swap[k,x]=["+IntToStr(k-1)+","+IntToStr(i-1)+"]"+", list= "+s+",  "+s[k]+"  Swap " + s[i]);

		}
	}
}
void TForm1::HanoiTowers(int n, String A, String B, String C){
	if(n == 1){
		Memo1 -> Lines -> Add(A + " to "+ C + "-Step[" + IntToStr(++counter) + "]");
	}
	else{
		HanoiTowers(n-1, A, C, B);
		HanoiTowers(1, A, B, C);
		HanoiTowers(n-1, B, A, C);
	}
}
void __fastcall TForm1::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
	if(!((((Key)>='0')&&((Key)<='9'))||((Key)==VK_BACK)||((Key)==VK_DELETE))){
		Application->MessageBox(L"輸入數字",L"Error Intput!", MB_OK | MB_ICONSTOP);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int k = StrToInt(Edit3->Text);
	int n = StrToInt(Edit4->Text);
	String s = "";
	for(int i=0;i<n;i++){
		s += (char)('A'+i);
	}
	counter = 0;
	if(CheckBox1->Checked==false){
		do{
			Memo1->Lines->Add(s+" ["+(++counter)+"]");
		}while(std::next_permutation(s.begin()+k,s.end()));
	}
	else{
		n = s.Length();
		perm(s,k+1,n+1);
	}
	Memo1 -> Lines -> Add("-------------------------\r\n");
	if(CheckBox1->Checked) Memo2 -> Lines -> Add("-------------------------\r\n");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	int k = StrToInt(Edit3->Text);
	String Ps = "";
	Ps = Edit5->Text;
	counter = 0;
	int n = Ps.Length();
	perm(Ps,k+1,n+1);
	Memo1 -> Lines -> Add("-------------------------\r\n");
	if(CheckBox1->Checked) Memo2 -> Lines -> Add("-------------------------\r\n");
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	int n = StrToInt(Edit2->Text);
	if(n>9){
		Application->MessageBox(L"輸入9以內正整數",L"Error Intput!", MB_OK | MB_ICONSTOP);
	}
	else{
		counter = 0;
		HanoiTowers(n,'A','B','C');
		Memo1 -> Lines -> Add("-------------------------\r\n");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
	/*int k = StrToInt(Edit3->Text);
	String s = "";
	s = Edit5->Text;
	prem(s,k,5);
	Memo1 -> Lines -> Add("-------------------------\r\n");   */
	char a = 'A';
	Memo1 -> Lines -> Add(a);
}
//---------------------------------------------------------------------------

