//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define bottlemax 150
#define K (TColor)RGB(0,0,0)
#define W (TColor)RGB(255,255,255)

#define C (TColor)RGB(0,255,255)
#define M (TColor)RGB(255,0,255)
#define Y (TColor)RGB(255,255,0)
#define R (TColor)RGB(255,0,0)
#define G (TColor)RGB(0,255,0)
#define Bo (TColor)RGB(0,0,255)

TForm1 *Form1;
Graphics::TBitmap *BMP,**S;

int indexS,size=bottlemax;
String fname,dir;
//bool CMY(int cmy,int b){}

void saveB(Graphics::TBitmap *Bmp, String CooName){
	Form1->ProgressBar2 -> Step = -1;
	Form1->ProgressBar2->StepIt();
	Form1->ListBox1->Items->Add(CooName);
	Form1->Memo1->Lines->Add(indexS);
	S[indexS] = Bmp;
	S[indexS] -> Width = Bmp -> Width;
	S[indexS] -> Height = Bmp -> Height;
	if(++indexS == size) Application->MessageBox(L"空間已被用完了",L"Error", MB_OK | MB_ICONSTOP);
	else if(indexS+3 >= size) Application->MessageBox(L"空間快用完了",L"Error", MB_OK | MB_ICONSTOP);
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	randomize();
	S =new Graphics::TBitmap *[size];
	for(int i=0;i<size;i++){
		S[i] = new Graphics::TBitmap();
		S[i] ->PixelFormat = pf24bit;
	}
	ProgressBar2->Position = size;
	ProgressBar2->Max = size;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if (OpenPictureDialog1->Execute()){
		BMP = new Graphics::TBitmap();
		BMP->PixelFormat = pf24bit;
		BMP->LoadFromFile(OpenPictureDialog1->FileName);
		Image1->Picture->Assign(BMP);
		Edit1->Text = BMP->Width;
		Edit2->Text = BMP->Height;
	}
	dir = ExtractFileDir(OpenPictureDialog1->FileName);
	fname = OpenPictureDialog1->FileName.SubString(dir.Length()+2, OpenPictureDialog1->FileName.Length()-dir.Length()-5);
	saveB(BMP,"BMP-"+fname);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
	int rr,gg,bb,i,j;
	Graphics::TBitmap *B2 = new Graphics::TBitmap();
	B2->Width = BMP->Width;
	B2->Height = BMP->Height;
	ProgressBar1->Position = 0;
	ProgressBar1->Max = B2->Height;
	for (i=0; i<B2->Width; i++)
		for(j=0; j<B2->Height; j++){
			rr = (GetRValue(BMP->Canvas->Pixels[i][j]) <= 127) ? 0:255;
			gg = (GetGValue(BMP->Canvas->Pixels[i][j]) <= 127) ? 0:255;
			bb = (GetBValue(BMP->Canvas->Pixels[i][j]) <= 127) ? 0:255;
			ProgressBar1->StepIt();
			B2->Canvas->Pixels[i][j] = (TColor)RGB(rr,gg,bb);
		}
	saveB(B2,"RGB-0:255-"+fname);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
	int rr, gg, bb, i, j,gray;
	Graphics::TBitmap *B3 = new Graphics::TBitmap();
	B3->Width = BMP->Width;
	B3->Height = BMP->Height;
	ProgressBar1->Position = 0;
	ProgressBar1->Max = B3->Height;
	for (i=0; i<B3->Width; i++)
		for(j=0; j<B3->Height; j++){
			rr = (GetRValue(BMP->Canvas->Pixels[i][j]) <= 127) ? 0:255;
			gg = (GetGValue(BMP->Canvas->Pixels[i][j]) <= 127) ? 0:255;
			bb = (GetBValue(BMP->Canvas->Pixels[i][j]) <= 127) ? 0:255;
			gray = ((rr+gg+bb)/3);
			ProgressBar1->StepIt();
			B3->Canvas->Pixels[i][j] = (TColor)RGB(gray,gray,gray);
		}
	saveB(B3,"WGK-"+fname);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
	int ind = this->ListBox1->ItemIndex;
	int rr, gg, bb, i, j, gray;
	Graphics::TBitmap *B4 = new Graphics::TBitmap();
	B4->Width = BMP->Width;
	B4->Height = BMP->Height;
	ProgressBar1->Position = 0;
	ProgressBar1->Max = B4->Height;
	for (i=0; i<B4->Width; i++){
		for(j=0; j<B4->Height; j++){
			rr = (GetRValue(BMP->Canvas->Pixels[i][j]) <= 127) ? 0:255;
			gg = (GetGValue(BMP->Canvas->Pixels[i][j]) <= 127) ? 0:255;
			bb = (GetBValue(BMP->Canvas->Pixels[i][j]) <= 127) ? 0:255;
			gray = ((rr+gg+bb)/3<=127) ? 0:255;
			ProgressBar1->StepIt();
			B4->Canvas->Pixels[i][j] = (TColor)RGB(gray,gray,gray);
		}
	}
	saveB(B4,"KW-"+fname);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListBox1Click(TObject *Sender)
{

	int ind = ListBox1->ItemIndex;
	Image1->Picture->Bitmap->Assign(S[ind]);
	Edit1->Text = S[ind]->Width;
	Edit2->Text = S[ind]->Height;
	BMP = S[ind];
	Form1->Memo1->Lines->Add(ind);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button5Click(TObject *Sender)
{
	int ind = ListBox1->ItemIndex;
	String prefix = ListBox1->Items->Strings[ind].SubString(1, 2);
	if(ToggleSwitch2->IsOn()==false){
		if (prefix != "KW"){
			Application->MessageBox(L"Please choose a binry image!",L"Error", MB_OK | MB_ICONSTOP);
			return;
		}
	}
	prefix = ListBox1->Items->Strings[ind].SubString(1, 9);
	if(ToggleSwitch2->IsOn()==true){
		if (prefix != "RGB-0:255"){
			Application->MessageBox(L"Please choose a RGB-0:255 image!",L"Error", MB_OK | MB_ICONSTOP);
			return;
		}
	}
	int i, j;
	if(indexS+3 > size&&ToggleSwitch2->IsOn()==false){
		Application->MessageBox(L"空間不夠""\n"L"[至少需要3]",L"Error", MB_OK | MB_ICONSTOP);
		return;
	}
	else if(indexS+13 > size&&ToggleSwitch2->IsOn()==true){
		Application->MessageBox(L"空間不夠""\n"L"[至少需要12]",L"Error", MB_OK | MB_ICONSTOP);
		return;
	}

	if(ToggleSwitch1->IsOn()==true&&ToggleSwitch2->IsOn()==false){

		int s1=ind+indexS+1, s2=ind+indexS+2, r=ind+indexS+3;

		S[s1]->Width = 2*S[ind]->Width; S[s2]->Width = 2*S[ind]->Width;
		S[s1]->Height = S[ind]->Height; S[s2]->Height = S[ind]->Height;
		ProgressBar1->Position = 0;
		ProgressBar1->Max = S[ind]->Height;
		for (i=0; i<S[ind]->Height; i++){
			for (j=0; j<S[ind]->Width; j++){
				if (S[ind]->Canvas->Pixels[j][i] == W){
					if (random(2)==0){
						S[s1]->Canvas->Pixels[2*j][i] = W;
						S[s1]->Canvas->Pixels[2*j+1][i] = K;
						S[s2]->Canvas->Pixels[2*j][i] = W;
						S[s2]->Canvas->Pixels[2*j+1][i] = K;
					}
					else{
						S[s1]->Canvas->Pixels[2*j][i] = K;
						S[s1]->Canvas->Pixels[2*j+1][i] = W;
						S[s2]->Canvas->Pixels[2*j][i] = K;
						S[s2]->Canvas->Pixels[2*j+1][i] = W;
					}
				}
				else{
					if (random(2)==0){
						S[s1]->Canvas->Pixels[2*j][i] = W;
						S[s1]->Canvas->Pixels[2*j+1][i] = K;
						S[s2]->Canvas->Pixels[2*j][i] = K;
						S[s2]->Canvas->Pixels[2*j+1][i] = W;
					}
					else{
						S[s1]->Canvas->Pixels[2*j][i] = K;
						S[s1]->Canvas->Pixels[2*j+1][i] = W;
						S[s2]->Canvas->Pixels[2*j][i] = W;
						S[s2]->Canvas->Pixels[2*j+1][i] = K;
					}
				}
			}
			ProgressBar1->StepIt();
		}
		Edit1->Text = S[s1]->Width;
		Edit2->Text = S[s1]->Height;
		String sName = ListBox1->Items->Strings[ind];
		saveB(S[s1], "S1_1x2-"+sName);
		saveB(S[s2], "S2_1x2-"+sName);
		S[r]->Width = 2*S[ind]->Width;
		S[r]->Height = S[ind]->Height;
		ProgressBar1->Position = 0;
		ProgressBar1->Max = S[r]->Height;
		for (i=0; i<S[r]->Height; i++){
			for (j=0; j<S[r]->Width; j++){
				if (S[s1]->Canvas->Pixels[j][i] == W && S[s2]->Canvas->Pixels[j][i] == W)
					S[r]->Canvas->Pixels[j][i] = W;
				else
					S[r]->Canvas->Pixels[j][i] = K;
			}
			ProgressBar1->StepIt();
		}
		saveB(S[r], "S1+S2_1x2-"+sName);
		Image1->Picture->Assign(S[r]);
	}

	else if(ToggleSwitch1->IsOn()==false&&ToggleSwitch2->IsOn()==false) {

		int s1=ind+indexS+1, s2=ind+indexS+2, r=ind+indexS+3;

		S[s1]->Width = 2*S[ind]->Width; S[s2]->Width = 2*S[ind]->Width;
		S[s1]->Height = 2*S[ind]->Height; S[s2]->Height = 2*S[ind]->Height;
		ProgressBar1->Position = 0;
		ProgressBar1->Max = S[indexS]->Height;
		for (i=0; i<S[ind]->Height; i++){
			for (j=0; j<S[ind]->Width; j++){
				for(int x=0;x<=1;x++){
					if (S[ind]->Canvas->Pixels[j][i] == W){
						if (random(2)==0){
							S[s1]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s1]->Canvas->Pixels[2*j+1][2*i+x] = K;
							S[s2]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s2]->Canvas->Pixels[2*j+1][2*i+x] = K;
						}
					else{
							S[s1]->Canvas->Pixels[2*j][2*i+x] = K;
							S[s1]->Canvas->Pixels[2*j+1][2*i+x] = W;
							S[s2]->Canvas->Pixels[2*j][2*i+x] = K;
							S[s2]->Canvas->Pixels[2*j+1][2*i+x] = W;
						}
					}
					else{
						if (random(2)==0){
							S[s1]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s1]->Canvas->Pixels[2*j+1][2*i+x] = K;
							S[s2]->Canvas->Pixels[2*j][2*i+x] = K;
							S[s2]->Canvas->Pixels[2*j+1][2*i+x] = W;
						}
						else{
							S[s1]->Canvas->Pixels[2*j][2*i+x] = K;
							S[s1]->Canvas->Pixels[2*j+1][2*i+x] = W;
							S[s2]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s2]->Canvas->Pixels[2*j+1][2*i+x] = K;
						}
					}
				}
			}
			ProgressBar1->StepIt();
		}
		Edit1->Text = S[s1]->Width;
		Edit2->Text = S[s1]->Height;
		String sName = ListBox1->Items->Strings[ind];
		saveB(S[s1], "S1_2x2-"+sName);
		saveB(S[s2], "S2_2x2-"+sName);
		S[r]->Width = 2*S[ind]->Width;
		S[r]->Height = 2*S[ind]->Height;
		ProgressBar1->Position = 0;
		ProgressBar1->Max = S[r]->Height;
		for (i=0; i<S[r]->Height; i++){
			for (j=0; j<S[r]->Width; j++){
				if (S[s1]->Canvas->Pixels[j][i] == W && S[s2]->Canvas->Pixels[j][i] == W)
					S[r]->Canvas->Pixels[j][i] = W;
				else
					S[r]->Canvas->Pixels[j][i] = K;
			}
		ProgressBar1->StepIt();
		}
		saveB(S[r], "S1+S2_2x2-"+sName);
		Image1->Picture->Assign(S[r]);
	}
	else if(ToggleSwitch1->IsOn()==true&&ToggleSwitch2->IsOn()==true){
		int c=ind+indexS+1,m=ind+indexS+2,y=ind+indexS+3;
		int s1=ind+indexS+4, s2=ind+indexS+5,s3=ind+indexS+6, s4=ind+indexS+7,s5=ind+indexS+8, s6=ind+indexS+9;
		int r1=ind+indexS+10, r2=ind+indexS+11, r=ind+indexS+12;
		int rr,gg,bb;
		Form1->Memo1->Lines->Add(ind);

		S[c]->Width = S[ind]->Width;   S[m]->Width = S[ind]->Width;   S[y]->Width = S[ind]->Width;
		S[c]->Height = S[ind]->Height; S[m]->Height = S[ind]->Height; S[y]->Height = S[ind]->Height;

		S[s1]->Width = 2*S[ind]->Width;   S[s2]->Width = 2*S[ind]->Width;
		S[s1]->Height = S[ind]->Height; S[s2]->Height = S[ind]->Height;
		S[s3]->Width = 2*S[ind]->Width;   S[s4]->Width = 2*S[ind]->Width;
		S[s3]->Height = S[ind]->Height; S[s4]->Height = S[ind]->Height;
		S[s5]->Width = 2*S[ind]->Width;   S[s6]->Width = 2*S[ind]->Width;
		S[s5]->Height = S[ind]->Height; S[s6]->Height = S[ind]->Height;

        ProgressBar1->Position = 0;
		ProgressBar1->Max = S[s1]->Height;
		for (i=0; i<S[s1]->Height; i++){
			for(j=0; j<S[s1]->Width; j++){
				rr = (GetRValue(S[ind]->Canvas->Pixels[j][i]) <= 127) ? 0:255;
				gg = (GetGValue(S[ind]->Canvas->Pixels[j][i]) <= 127) ? 0:255;
				bb = (GetBValue(S[ind]->Canvas->Pixels[j][i]) <= 127) ? 0:255;

				for(int x=0;x<=1;x++){
					if (rr==0){
						S[c]->Canvas->Pixels[j][i] = C;
					}
					else{
						S[c]->Canvas->Pixels[j][i] = W;
					}

					if(gg==0){
						S[m]->Canvas->Pixels[j][i] = M;
					}
					else{
						S[m]->Canvas->Pixels[j][i] = W;
					}

					if(bb==0){
						S[y]->Canvas->Pixels[j][i] = Y;
					}
					else{
						S[y]->Canvas->Pixels[j][i] = W;
					}

					if (S[c]->Canvas->Pixels[j][i] == W){
						if (random(2)==0){
							S[s1]->Canvas->Pixels[2*j][i] = W;
							S[s1]->Canvas->Pixels[2*j+1][i] = C;
							S[s2]->Canvas->Pixels[2*j][i] = W;
							S[s2]->Canvas->Pixels[2*j+1][i] = C;
						}
						else{
							S[s1]->Canvas->Pixels[2*j][i] = C;
							S[s1]->Canvas->Pixels[2*j+1][i] = W;
							S[s2]->Canvas->Pixels[2*j][i] = C;
							S[s2]->Canvas->Pixels[2*j+1][i] = W;
						}
					}
					else{

						if (random(2)==0){
							S[s1]->Canvas->Pixels[2*j][i] = W;
							S[s1]->Canvas->Pixels[2*j+1][i] = C;
							S[s2]->Canvas->Pixels[2*j][i] = C;
							S[s2]->Canvas->Pixels[2*j+1][i] = W;
						}
						else{
							S[s1]->Canvas->Pixels[2*j][i] = C;
							S[s1]->Canvas->Pixels[2*j+1][i] = W;
							S[s2]->Canvas->Pixels[2*j][i] = W;
							S[s2]->Canvas->Pixels[2*j+1][i] = C;
						}
					}

					if (S[m]->Canvas->Pixels[j][i] == W){
						if (random(2)==0){
							S[s3]->Canvas->Pixels[2*j][i] = W;
							S[s3]->Canvas->Pixels[2*j+1][i] = M;
							S[s4]->Canvas->Pixels[2*j][i] = W;
							S[s4]->Canvas->Pixels[2*j+1][i] = M;
						}
						else{
							S[s3]->Canvas->Pixels[2*j][i] = M;
							S[s3]->Canvas->Pixels[2*j+1][i] = W;
							S[s4]->Canvas->Pixels[2*j][i] = M;
							S[s4]->Canvas->Pixels[2*j+1][i] = W;
						}
					}
					else{
						if (random(2)==0){
							S[s3]->Canvas->Pixels[2*j][i] = W;
							S[s3]->Canvas->Pixels[2*j+1][i] = M;
							S[s4]->Canvas->Pixels[2*j][i] = M;
							S[s4]->Canvas->Pixels[2*j+1][i] = W;
						}
						else{
							S[s3]->Canvas->Pixels[2*j][i] = M;
							S[s3]->Canvas->Pixels[2*j+1][i] = W;
							S[s4]->Canvas->Pixels[2*j][i] = W;
							S[s4]->Canvas->Pixels[2*j+1][i] = M;
						}
					}

					if (S[y]->Canvas->Pixels[j][i] == W){
						if (random(2)==0){
							S[s5]->Canvas->Pixels[2*j][i] = W;
							S[s5]->Canvas->Pixels[2*j+1][i] = Y;
							S[s6]->Canvas->Pixels[2*j][i] = W;
							S[s6]->Canvas->Pixels[2*j+1][i] = Y;
						}
						else{
							S[s5]->Canvas->Pixels[2*j][i] = Y;
							S[s5]->Canvas->Pixels[2*j+1][i] = W;
							S[s6]->Canvas->Pixels[2*j][i] = Y;
							S[s6]->Canvas->Pixels[2*j+1][i] = W;
						}
					}
					else{
						if (random(2)==0){
							S[s5]->Canvas->Pixels[2*j][i] = W;
							S[s5]->Canvas->Pixels[2*j+1][i] = Y;
							S[s6]->Canvas->Pixels[2*j][i] = Y;
							S[s6]->Canvas->Pixels[2*j+1][i] = W;
						}
						else{
							S[s5]->Canvas->Pixels[2*j][i] = Y;
							S[s5]->Canvas->Pixels[2*j+1][i] = W;
							S[s6]->Canvas->Pixels[2*j][i] = W;
							S[s6]->Canvas->Pixels[2*j+1][i] = Y;
						}
					}
				}
			}
			ProgressBar1->StepIt();
		}


		String sName = ListBox1->Items->Strings[ind];

		saveB(S[c], "RGB-C_1x2-"+sName);
		saveB(S[m], "RGB-M_1x2-"+sName);
		saveB(S[y], "RGB-Y_1x2-"+sName);
		Form1->Memo1->Lines->Add(IntToStr(c)+IntToStr(m)+IntToStr(y)+IntToStr(s1)+IntToStr(s2)+IntToStr(s3)+IntToStr(s4)+IntToStr(s5)+IntToStr(s6));
		/*
		saveB(S[s1], "RGB->S1_1x2->"+sName);
		saveB(S[s2], "RGB->S2_1x2->"+sName);

		saveB(S[s3], "RGB->S3_1x2->"+sName);
		saveB(S[s4], "RGB->S4_1x2->"+sName);

		saveB(S[s5], "RGB->S5_1x2->"+sName);
		saveB(S[s6], "RGB->S6_1x2->"+sName);
		*/

		S[r1]->Width = 2*S[ind]->Width;
		S[r1]->Height = S[ind]->Height;
		S[r2]->Width = 2*S[ind]->Width;
		S[r2]->Height = S[ind]->Height;

		S[r]->Width = 2*S[ind]->Width;
		S[r]->Height = S[ind]->Height;

		ProgressBar1->Position = 0;
		ProgressBar1->Max = S[r]->Height;
		for (i=0; i<S[r]->Height; i++){
			for (j=0; j<S[r]->Width; j++){
				for(int x=s1;x<=s1+1;x++){
					if(i==0&&j==0) Form1->Memo1->Lines->Add(x);
					bool cc,mm,yy;
					cc = (S[x]->Canvas->Pixels[j][i] == W) ? 1 : 0;
					mm = (S[x+2]->Canvas->Pixels[j][i] == W) ? 1 : 0;
					yy = (S[x+4]->Canvas->Pixels[j][i] == W) ? 1 : 0;


					if (cc && mm && yy) S[r1+x-s1]->Canvas->Pixels[j][i] = W;
					else if (cc && mm && !(yy)) S[r1+x-s1]->Canvas->Pixels[j][i] = Y;
					else if (cc && !(mm) && yy) S[r1+x-s1]->Canvas->Pixels[j][i] = M;
					else if (cc && !(mm || yy)) S[r1+x-s1]->Canvas->Pixels[j][i] = R;
					else if (!(cc) && mm && yy) S[r1+x-s1]->Canvas->Pixels[j][i] = C;
					else if (!(cc) && mm && !(yy)) S[r1+x-s1]->Canvas->Pixels[j][i] = G;
					else if (!(cc || mm) && yy) S[r1+x-s1]->Canvas->Pixels[j][i] = Bo;
					else if (!(cc && mm && yy)) S[r1+x-s1]->Canvas->Pixels[j][i] = K;

				}
			}
			ProgressBar1->StepIt();
		}

		saveB(S[r1], "RGB-r1_1x2-"+sName);
		saveB(S[r2], "RGB-r2_1x2-"+sName);

		ProgressBar1->Position = 0;
		ProgressBar1->Max = S[r]->Height;
		for (i=0; i<S[r]->Height; i++){
			for (j=0; j<S[r]->Width; j++){
					bool rr,gg,bb;
					rr = ((GetRValue(S[r1]->Canvas->Pixels[j][i])==255)&&((GetRValue(S[r2]->Canvas->Pixels[j][i])==255))) ? 1 : 0;
					gg = ((GetGValue(S[r1]->Canvas->Pixels[j][i])==255)&&((GetGValue(S[r2]->Canvas->Pixels[j][i])==255))) ? 1 : 0;
					bb = ((GetBValue(S[r1]->Canvas->Pixels[j][i])==255)&&((GetBValue(S[r2]->Canvas->Pixels[j][i])==255))) ? 1 : 0;

					if (rr && gg && bb) S[r]->Canvas->Pixels[j][i] = W;
					else if (rr && gg && !(bb)) S[r]->Canvas->Pixels[j][i] = Y;
					else if (rr && !(gg) && bb) S[r]->Canvas->Pixels[j][i] = M;
					else if (rr && !(gg || bb)) S[r]->Canvas->Pixels[j][i] = R;
					else if (!(rr) && gg && bb) S[r]->Canvas->Pixels[j][i] = C;
					else if (!(rr) && gg && !(bb)) S[r]->Canvas->Pixels[j][i] = G;
					else if (!(rr || gg) && bb) S[r]->Canvas->Pixels[j][i] = Bo;
					else if (!(rr && gg && bb)) S[r]->Canvas->Pixels[j][i] = K;

			}
			ProgressBar1->StepIt();
		}
		saveB(S[r], "RGB-S1+S2_1x2-"+sName);
		Edit1->Text = S[r]->Width;
		Edit2->Text = S[r]->Height;
		Image1->Picture->Assign(S[r]);
	}

	else if(ToggleSwitch1->IsOn()==false&&ToggleSwitch2->IsOn()==true){
		int c=ind+indexS+1,m=ind+indexS+2,y=ind+indexS+3;
		int s1=ind+indexS+4, s2=ind+indexS+5,s3=ind+indexS+6, s4=ind+indexS+7,s5=ind+indexS+8, s6=ind+indexS+9;
		int r1=ind+indexS+10, r2=ind+indexS+11, r=ind+indexS+12;
		int rr,gg,bb;
		Form1->Memo1->Lines->Add(ind);

		S[c]->Width = S[ind]->Width;   S[m]->Width = S[ind]->Width;   S[y]->Width = S[ind]->Width;
		S[c]->Height = S[ind]->Height; S[m]->Height = S[ind]->Height; S[y]->Height = S[ind]->Height;

		S[s1]->Width = 2*S[ind]->Width;   S[s2]->Width = 2*S[ind]->Width;
		S[s1]->Height = 2*S[ind]->Height; S[s2]->Height = 2*S[ind]->Height;
		S[s3]->Width = 2*S[ind]->Width;   S[s4]->Width = 2*S[ind]->Width;
		S[s3]->Height = 2*S[ind]->Height; S[s4]->Height = 2*S[ind]->Height;
		S[s5]->Width = 2*S[ind]->Width;   S[s6]->Width = 2*S[ind]->Width;
		S[s5]->Height = 2*S[ind]->Height; S[s6]->Height = 2*S[ind]->Height;

        ProgressBar1->Position = 0;
		ProgressBar1->Max = S[s1]->Height;
		for (i=0; i<S[s1]->Height; i++){
			for(j=0; j<S[s1]->Width; j++){
				rr = (GetRValue(S[ind]->Canvas->Pixels[j][i]) <= 127) ? 0:255;
				gg = (GetGValue(S[ind]->Canvas->Pixels[j][i]) <= 127) ? 0:255;
				bb = (GetBValue(S[ind]->Canvas->Pixels[j][i]) <= 127) ? 0:255;

				for(int x=0;x<=1;x++){
					if (rr==0){
						S[c]->Canvas->Pixels[j][i] = C;
					}
					else{
						S[c]->Canvas->Pixels[j][i] = W;
					}

					if(gg==0){
						S[m]->Canvas->Pixels[j][i] = M;
					}
					else{
						S[m]->Canvas->Pixels[j][i] = W;
					}

					if(bb==0){
						S[y]->Canvas->Pixels[j][i] = Y;
					}
					else{
						S[y]->Canvas->Pixels[j][i] = W;
					}

					if (S[c]->Canvas->Pixels[j][i] == W){
						if (random(2)==0){
							S[s1]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s1]->Canvas->Pixels[2*j+1][2*i+x] = C;
							S[s2]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s2]->Canvas->Pixels[2*j+1][2*i+x] = C;
						}
						else{
							S[s1]->Canvas->Pixels[2*j][2*i+x] = C;
							S[s1]->Canvas->Pixels[2*j+1][2*i+x] = W;
							S[s2]->Canvas->Pixels[2*j][2*i+x] = C;
							S[s2]->Canvas->Pixels[2*j+1][2*i+x] = W;
						}
					}
					else{

						if (random(2)==0){
							S[s1]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s1]->Canvas->Pixels[2*j+1][2*i+x] = C;
							S[s2]->Canvas->Pixels[2*j][2*i+x] = C;
							S[s2]->Canvas->Pixels[2*j+1][2*i+x] = W;
						}
						else{
							S[s1]->Canvas->Pixels[2*j][2*i+x] = C;
							S[s1]->Canvas->Pixels[2*j+1][2*i+x] = W;
							S[s2]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s2]->Canvas->Pixels[2*j+1][2*i+x] = C;
						}
					}

					if (S[m]->Canvas->Pixels[j][i] == W){
						if (random(2)==0){
							S[s3]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s3]->Canvas->Pixels[2*j+1][2*i+x] = M;
							S[s4]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s4]->Canvas->Pixels[2*j+1][2*i+x] = M;
						}
						else{
							S[s3]->Canvas->Pixels[2*j][2*i+x] = M;
							S[s3]->Canvas->Pixels[2*j+1][2*i+x] = W;
							S[s4]->Canvas->Pixels[2*j][2*i+x] = M;
							S[s4]->Canvas->Pixels[2*j+1][2*i+x] = W;
						}
					}
					else{
						if (random(2)==0){
							S[s3]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s3]->Canvas->Pixels[2*j+1][2*i+x] = M;
							S[s4]->Canvas->Pixels[2*j][2*i+x] = M;
							S[s4]->Canvas->Pixels[2*j+1][2*i+x] = W;
						}
						else{
							S[s3]->Canvas->Pixels[2*j][2*i+x] = M;
							S[s3]->Canvas->Pixels[2*j+1][2*i+x] = W;
							S[s4]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s4]->Canvas->Pixels[2*j+1][2*i+x] = M;
						}
					}

					if (S[y]->Canvas->Pixels[j][i] == W){
						if (random(2)==0){
							S[s5]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s5]->Canvas->Pixels[2*j+1][2*i+x] = Y;
							S[s6]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s6]->Canvas->Pixels[2*j+1][2*i+x] = Y;
						}
						else{
							S[s5]->Canvas->Pixels[2*j][2*i+x] = Y;
							S[s5]->Canvas->Pixels[2*j+1][2*i+x] = W;
							S[s6]->Canvas->Pixels[2*j][2*i+x] = Y;
							S[s6]->Canvas->Pixels[2*j+1][2*i+x] = W;
						}
					}
					else{
						if (random(2)==0){
							S[s5]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s5]->Canvas->Pixels[2*j+1][2*i+x] = Y;
							S[s6]->Canvas->Pixels[2*j][2*i+x] = Y;
							S[s6]->Canvas->Pixels[2*j+1][2*i+x] = W;
						}
						else{
							S[s5]->Canvas->Pixels[2*j][2*i+x] = Y;
							S[s5]->Canvas->Pixels[2*j+1][2*i+x] = W;
							S[s6]->Canvas->Pixels[2*j][2*i+x] = W;
							S[s6]->Canvas->Pixels[2*j+1][2*i+x] = Y;
						}
					}
				}
			}
			ProgressBar1->StepIt();
		}


		String sName = ListBox1->Items->Strings[ind];

		saveB(S[c], "RGB-C_2x2-"+sName);
		saveB(S[m], "RGB-M_2x2-"+sName);
		saveB(S[y], "RGB-Y_2x2-"+sName);
		Form1->Memo1->Lines->Add(IntToStr(c)+IntToStr(m)+IntToStr(y)+IntToStr(s1)+IntToStr(s2)+IntToStr(s3)+IntToStr(s4)+IntToStr(s5)+IntToStr(s6));
		/*
		saveB(S[s1], "RGB->S1_2x2->"+sName);
		saveB(S[s2], "RGB->S2_2x2->"+sName);

		saveB(S[s3], "RGB->S3_2x2->"+sName);
		saveB(S[s4], "RGB->S4_2x2->"+sName);

		saveB(S[s5], "RGB->S5_2x2->"+sName);
		saveB(S[s6], "RGB->S6_2x2->"+sName);
		 /*
		saveB(S[s1], "RGB->S1_2x2->"+sName);
		saveB(S[s2], "RGB->S2_2x2->"+sName);
		*/
		S[r1]->Width = 2*S[ind]->Width;
		S[r1]->Height = 2*S[ind]->Height;
		S[r2]->Width = 2*S[ind]->Width;
		S[r2]->Height = 2*S[ind]->Height;

		S[r]->Width = 2*S[ind]->Width;
		S[r]->Height = 2*S[ind]->Height;

		ProgressBar1->Position = 0;
		ProgressBar1->Max = S[r]->Height;
		for (i=0; i<S[r]->Height; i++){
			for (j=0; j<S[r]->Width; j++){
				for(int x=s1;x<=s1+1;x++){
					if(i==0&&j==0) Form1->Memo1->Lines->Add(x);
					bool cc,mm,yy;
					cc = (S[x]->Canvas->Pixels[j][i] == W) ? 1 : 0;
					mm = (S[x+2]->Canvas->Pixels[j][i] == W) ? 1 : 0;
					yy = (S[x+4]->Canvas->Pixels[j][i] == W) ? 1 : 0;


					if (cc && mm && yy) S[r1+x-s1]->Canvas->Pixels[j][i] = W;
					else if (cc && mm && !(yy)) S[r1+x-s1]->Canvas->Pixels[j][i] = Y;
					else if (cc && !(mm) && yy) S[r1+x-s1]->Canvas->Pixels[j][i] = M;
					else if (cc && !(mm || yy)) S[r1+x-s1]->Canvas->Pixels[j][i] = R;
					else if (!(cc) && mm && yy) S[r1+x-s1]->Canvas->Pixels[j][i] = C;
					else if (!(cc) && mm && !(yy)) S[r1+x-s1]->Canvas->Pixels[j][i] = G;
					else if (!(cc || mm) && yy) S[r1+x-s1]->Canvas->Pixels[j][i] = Bo;
					else if (!(cc && mm && yy)) S[r1+x-s1]->Canvas->Pixels[j][i] = K;



					//if (cc && mm && yy) S[r]->Canvas->Pixels[j][i] = K;
					//else if (cc && mm && !(yy)) S[r1+x-s1]->Canvas->Pixels[j][i] = Bo;
					//else if (cc && !(mm) && yy) S[r1+x-s1]->Canvas->Pixels[j][i] = G;
					//else if (cc && !(mm || yy)) S[r1+x-s1]->Canvas->Pixels[j][i] = C;
					//else if (!(cc) && mm && yy) S[r1+x-s1]->Canvas->Pixels[j][i] = R;
					//else if (!(cc) && mm && !(yy)) S[r1+x-s1]->Canvas->Pixels[j][i] = M;
					//else if (!(cc || mm) && yy) S[r1+x-s1]->Canvas->Pixels[j][i] = Y;
					//else if (!(cc && mm && yy)) S[r1+x-s1]->Canvas->Pixels[j][i] = W;
				}
			}
			ProgressBar1->StepIt();
		}

		/*
		for (i=0; i<S[r]->Height; i++){
			for (j=0; j<S[r]->Width; j++){
				if (S[s1]->Canvas->Pixels[j][i] == W && S[s2]->Canvas->Pixels[j][i] == W)
					S[r1]->Canvas->Pixels[j][i] = W;
				else
					S[r1]->Canvas->Pixels[j][i] = C;
			}
			ProgressBar1->StepIt();
		}
		//saveB(S[s3], "RGB->S3_2x2->"+sName);
		//saveB(S[s4], "RGB->S4_2x2->"+sName);
		for (i=0; i<S[r]->Height; i++){
			for (j=0; j<S[r]->Width; j++){
				if (S[s3]->Canvas->Pixels[j][i] == W && S[s4]->Canvas->Pixels[j][i] == W)
					S[r2]->Canvas->Pixels[j][i] = W;
				else
					S[r2]->Canvas->Pixels[j][i] = M;
			}
			ProgressBar1->StepIt();
		}
		//saveB(S[s5], "RGB->S5_2x2->"+sName);
		//saveB(S[s6], "RGB->S6_2x2->"+sName);
		for (i=0; i<S[r]->Height; i++){
			for (j=0; j<S[r]->Width; j++){
				if (S[s5]->Canvas->Pixels[j][i] == W && S[s6]->Canvas->Pixels[j][i] == W)
					S[r]->Canvas->Pixels[j][i] = W;
				else
					S[r]->Canvas->Pixels[j][i] = Y;
			}
			ProgressBar1->StepIt();
		}
		*/

		saveB(S[r1], "RGB-r1_2x2-"+sName);
		saveB(S[r2], "RGB-r2_2x2-"+sName);

		ProgressBar1->Position = 0;
		ProgressBar1->Max = S[r]->Height;
		for (i=0; i<S[r]->Height; i++){
			for (j=0; j<S[r]->Width; j++){
					bool rr,gg,bb;
					rr = ((GetRValue(S[r1]->Canvas->Pixels[j][i])==255)&&((GetRValue(S[r2]->Canvas->Pixels[j][i])==255))) ? 1 : 0;
					gg = ((GetGValue(S[r1]->Canvas->Pixels[j][i])==255)&&((GetGValue(S[r2]->Canvas->Pixels[j][i])==255))) ? 1 : 0;
					bb = ((GetBValue(S[r1]->Canvas->Pixels[j][i])==255)&&((GetBValue(S[r2]->Canvas->Pixels[j][i])==255))) ? 1 : 0;

					//if (rr && gg && bb) S[r]->Canvas->Pixels[j][i] = K;
					//else if (rr && gg && !(bb)) S[r]->Canvas->Pixels[j][i] = Bo;
					//else if (rr && !(gg) && bb) S[r]->Canvas->Pixels[j][i] = G;
					//else if (rr && !(gg || bb)) S[r]->Canvas->Pixels[j][i] = C;
					//else if (!(rr) && gg && bb) S[r]->Canvas->Pixels[j][i] = R;
					//else if (!(rr) && gg && !(bb)) S[r]->Canvas->Pixels[j][i] = M;
					//else if (!(rr || gg) && bb) S[r]->Canvas->Pixels[j][i] = Y;
					//else if (!(rr && gg && bb)) S[r]->Canvas->Pixels[j][i] = W;

					if (rr && gg && bb) S[r]->Canvas->Pixels[j][i] = W;
					else if (rr && gg && !(bb)) S[r]->Canvas->Pixels[j][i] = Y;
					else if (rr && !(gg) && bb) S[r]->Canvas->Pixels[j][i] = M;
					else if (rr && !(gg || bb)) S[r]->Canvas->Pixels[j][i] = R;
					else if (!(rr) && gg && bb) S[r]->Canvas->Pixels[j][i] = C;
					else if (!(rr) && gg && !(bb)) S[r]->Canvas->Pixels[j][i] = G;
					else if (!(rr || gg) && bb) S[r]->Canvas->Pixels[j][i] = Bo;
					else if (!(rr && gg && bb)) S[r]->Canvas->Pixels[j][i] = K;

			}
			ProgressBar1->StepIt();
		}
		saveB(S[r], "RGB-S1+S2_2x2-"+sName);
		Edit1->Text = S[r]->Width;
		Edit2->Text = S[r]->Height;
		Image1->Picture->Assign(S[r]);
	}
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
	ListBox1->Items->Clear();
	indexS = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
	for(int i=0;i<ListBox1->Items->Count; i++){
		String sName = ListBox1->Items->Strings[i];
		sName += ".bmp";
		Memo1->Lines->Add(sName);
		Image1->Picture->Assign(S[i]);
		Image1->Picture->SaveToFile(sName);
	}
}
//---------------------------------------------------------------------------

