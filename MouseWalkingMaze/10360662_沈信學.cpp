//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "10360662_沈信學.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

Graphics::TBitmap *BMP = new Graphics::TBitmap();
int **maze,**map;//map是老鼠在走迷宮時可以做修改跟標記用的地圖
int height,width;

enum direction{N,EN,E,ES,S,WS,W,WN};//0,1,2,3,4,5,6,7
struct position{
	int x, y, dir;
};

struct cood{
	int dx,dy;
};

template <class T>
class stack{
	private:
		int top;
		T *sta;
		int max;
	public:

		stack(){
			sta=new T[100];
			top = -1;
			max = height * width;
		}
		stack(int height,int width){
			sta=new T[height * width];
			top = -1;
			max = height * width;
		}

		void push(T n){
			if(top==max-1) return;
			else sta[++top] = n;
		};
		T pop(){
			if(top == -1) Form1->Memo1->Lines->Add("stack is null");
			else return sta[top--];
		};
		bool isEmpty(){
			return top==-1;
		}
};

//---------------------------------------------------------------------------
//StringGrid相關
void gridset(TStringGrid *s){
	s->RowCount = height;//grid的col數量設定成height,不知道為甚麼RowCount加的是col
	s->ColCount = width;//grid的Row數量設定成width
    s->FixedCols = 0;
	s->FixedRows = 0;
	s->DefaultDrawing = false;
}
void cinGrid(TStringGrid *s, int **maze){
	for(int i=1; i<=height; i++){
		for(int j=1; j<=width; j++){
			s->Cells[j-1][i-1] = maze[i-1][j-1];
		}
	}
}

void setGHW(TStringGrid *s){
	int gridsize = Form1->Edit3->Text.ToInt();
	s->DefaultColWidth = gridsize;  //for(int i=0; i<s->ColCount; i++) s->ColWidths[i] = gridsize;
	s->DefaultRowHeight = gridsize;  //for(int i=0; i<s->RowCount; i++) s->RowHeights[i] = gridsize;
}

void coutInfByGrid(TStringGrid *s){//輸出格子訊息
	TRect Recto = s->CellRect(s->Col, s->Row);
	Form1->Label4->Caption = "Cell: ["+IntToStr(s->Row)+", "+IntToStr(s->Col)+"] = "+s->Cells[s->Col][s->Row];
	Form1->Label5->Caption = "Size: "+IntToStr(width)+"X"+IntToStr(height);
	if(s->Cells[s->Col][s->Row]==0)
		Form1->Label6->Caption="Road[道路]";
	else if(s->Cells[s->Col][s->Row]==1)
		Form1->Label6->Caption="Wall[牆]";
	else if(s->Cells[s->Col][s->Row]==2)
		Form1->Label6->Caption="Fence[圍牆]";
	else Form1->Label6->Caption=s->Cells[s->Col][s->Row];
}
//---------------------------------------------------------------------------


struct cood f1[4] = {{0,1},{-1,0},{0,-1},{1,0}},f2[4] = {{0,2},{-2,0},{0,-2},{2,0}};//0=上,1=左,2=下,3=右
struct cood move[8]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
struct position end;


void initiation(){
	//w[height][width];
	for (int i=0; i<height; i++){
		for (int j=0; j<width; j++){
			if(i==0||j==0||i==height-1||j==width-1)
				maze[i][j] = 2;
			else maze[i][j] = 1;
		}
	}
}

int NextMove(struct position step){
    for (int i=0; i<4; i++){
        int nextX = step.x + f2[i].dx;
        int nextY = step.y + f2[i].dy;
        if (nextX >= 0 && nextX < height && nextY >= 0 && nextY < width) {
            if (maze[nextX][nextY] == 1) {
                return 1;
            }
        }
    }
    return 0;
}


int **MazeDFS(struct position step){
	struct position next;
	stack<position> stk1(height, width);
	stk1.push(step);
	maze[step.x][step.y] = 0;
	while(!stk1.isEmpty()){
		step = stk1.pop();
		while(NextMove(step)){
			int d = rand()%4;
			next.x = step.x + f2[d].dx;
			next.y = step.y + f2[d].dy;
			Form1->Memo1->Lines->Add(maze[next.x][next.y]);

			if(maze[next.x][next.y]==1){
				maze[step.x+f1[d].dx][step.y+f1[d].dy] = 0;
				stk1.push(next);
				maze[next.x][next.y] = 0;
				step = next;
				cinGrid(Form1->StringGrid1,maze);
				Form1->StringGrid1->Refresh();
				cinGrid(Form1->StringGrid2,maze);
				Form1->StringGrid2->Refresh();
				Sleep(Form1->TrackBar1->Position);
				cinGrid(Form1->StringGrid3,maze);
				Form1->StringGrid3->Refresh();
				cinGrid(Form1->StringGrid4,maze);
				Form1->StringGrid4->Refresh();
				cinGrid(Form1->StringGrid5,maze);
				Form1->StringGrid5->Refresh();
			}
		}
	}
	return maze;
}

/*int NextStep(struct position step){
	if(step.dir%2==1)step.dir-=1;
	for (int i=step.dir; i<8; i+=2){
		Form1->Memo1->Lines->Add("--"+IntToStr(i));
		if (maze[step.x+move[i].dx][step.y+move[i].dy]==0) return i;
	}
	return 0;
} */
int NextStep(struct position step){
	for (int i=step.dir; i<8; i++){
		Form1->Memo1->Lines->Add("--"+IntToStr(i));
		if (maze[step.x+move[i].dx][step.y+move[i].dy]==0) return i;
	}
	return 0;
}

int **MouseSearch(struct position step){
    int d;
	struct position next;
	stack<position> stk1(height, width);
	stk1.push(step);
	Form1->ProgressBar1->Position = 0;
	while (!stk1.isEmpty()){
		step = stk1.pop();
		while (step.dir < 8){
			d = NextStep(step);
			Form1->Memo1->Lines->Add("d "+IntToStr(d)+"->  move.dx[d]="+IntToStr(move[d].dx)+"   move.dy[d]="+IntToStr(move[d].dy));
			next.x = step.x+move[d].dx;
			next.y = step.y+move[d].dy;
			Form1->Memo1->Lines->Add("step.x =" + IntToStr(step.x) + " ,step.y ="+ IntToStr(step.y) + " ,next.x =" + IntToStr(next.x) + " ,next.y =" + IntToStr(next.y));
			if ((!maze[next.x][next.y])&&(!map[next.x][next.y])){//可以走,且不曾走過
				map[next.x][next.y]=3;
				Form1->StringGrid3->Cells[next.x][next.y];
				step.dir++;
				stk1.push(step);
				Form1->Memo1->Lines->Add("   ->step.x =" + IntToStr(step.x) + " ,step.y ="+ IntToStr(step.y) + " ,next.x =" + IntToStr(next.x) + " ,next.y =" + IntToStr(next.y));

				if((next.x == end.x)&&(next.y == end.y)){//END
					map[step.x][step.y]=3;
					while(!stk1.isEmpty()){
						step = stk1.pop();
						map[step.x][step.y]=4;
						map[next.x][next.y]=4;
						cinGrid(Form1->StringGrid1,map);
						Form1->StringGrid1->Refresh();
						cinGrid(Form1->StringGrid2,map);
						Form1->StringGrid2->Refresh();
						Sleep(Form1->TrackBar1->Position);
						cinGrid(Form1->StringGrid3,map);
						Form1->StringGrid3->Refresh();
						cinGrid(Form1->StringGrid4,map);
						Form1->StringGrid4->Refresh();
						cinGrid(Form1->StringGrid5,map);
						Form1->StringGrid5->Refresh();
					}
					return map;
				}

				step = next;
				step.dir=0;

				cinGrid(Form1->StringGrid1,map);
				Form1->StringGrid1->Refresh();
				cinGrid(Form1->StringGrid2,map);
				Form1->StringGrid2->Refresh();
				Sleep(Form1->TrackBar1->Position);
				cinGrid(Form1->StringGrid3,map);
				Form1->StringGrid3->Refresh();
				cinGrid(Form1->StringGrid4,map);
				Form1->StringGrid4->Refresh();
				cinGrid(Form1->StringGrid5,map);
				Form1->StringGrid5->Refresh();
			}
			else step.dir++;
			//else (step.dir%=8)++;
			Form1->ProgressBar1->StepIt();
		}

	}
	Form1->Memo1->Lines->Add("maze isn't have exit");

	return map;
}


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    randomize();
	width = Edit1->Text.ToInt();
	height = Edit2->Text.ToInt();
    gridset(StringGrid1);
	setGHW(StringGrid1);
	gridset(StringGrid2);
	setGHW(StringGrid2);
	gridset(StringGrid3);
	setGHW(StringGrid3);
	gridset(StringGrid4);
	setGHW(StringGrid4);
	gridset(StringGrid5);
	setGHW(StringGrid5);
	TrackBar1->Min = 0;
	TrackBar1->Max = 100;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	FILE *fp;
	AnsiString out, fname;

	if(OpenDialog1->Execute()){
		fname = OpenDialog1->FileName;//讀檔名
		fp = fopen(fname.c_str(), "r+");//c_str函数的傳回值是 const char *->即把string轉成const char *
		fscanf(fp, "%d %d", &height, &width); //讀檔案中的迷宮寬高

		Edit1->Text = IntToStr(width);
		Edit2->Text = IntToStr(height);
		Edit4->Text = IntToStr(height-2);
		Edit5->Text = IntToStr(width-1);
		Memo1->Lines->Add(IntToStr(height) + " * " + IntToStr(width));

		maze = new int*[height];
		for(int i=0;i<=height;i++){
			maze[i] = new int[width];
		}

		for(int i=0; i<height; i++){ //讀入迷宮
			for(int j=0; j<width; j++){
				fscanf(fp, "%d", &maze[i][j]);
			}
		}

		for(int i=0; i<height; i++){
			out = "";//每開始下一行時都先清空字串
			for(int j=0; j<width; j++){
				out += "  " + IntToStr(maze[i][j]);
			}
			Memo1->Lines->Add(out);
		}
		gridset(StringGrid1);
		setGHW(StringGrid1);
		gridset(StringGrid2);
		setGHW(StringGrid2);
		gridset(StringGrid3);
		setGHW(StringGrid3);
		gridset(StringGrid4);
		setGHW(StringGrid4);
		gridset(StringGrid5);
		setGHW(StringGrid5);

		cinGrid(StringGrid1,maze);
		cinGrid(StringGrid2,maze);
		cinGrid(StringGrid3,maze);
		cinGrid(StringGrid4,maze);
		cinGrid(StringGrid5,maze);
		fclose(fp);
	}
	else  Memo1->Lines->Add("Nothing happens.");
}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	maze = new int*[height];
	for(int i=0;i<=height;i++){
		maze[i] = new int[width];
	}
	initiation();
    gridset(StringGrid1);
	setGHW(StringGrid1);
	gridset(StringGrid2);
	setGHW(StringGrid2);
	gridset(StringGrid3);
	setGHW(StringGrid3);
	gridset(StringGrid4);
	setGHW(StringGrid4);
	gridset(StringGrid5);
	setGHW(StringGrid5);

	cinGrid(StringGrid1,maze);
	cinGrid(StringGrid2,maze);
	cinGrid(StringGrid3,maze);
	cinGrid(StringGrid4,maze);
	cinGrid(StringGrid5,maze);
	struct position b = {1,1,N};
	int **mm = MazeDFS(b);
	cinGrid(StringGrid1,mm);
	cinGrid(StringGrid2,mm);
	cinGrid(StringGrid3,mm);
	cinGrid(StringGrid4,mm);
	cinGrid(StringGrid5,mm);

	Edit4->Text = IntToStr(height-2);
	Edit5->Text = IntToStr(width-2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
    map = new int*[height];
	for(int i=0;i<=height;i++){
		map[i] = new int[width];
	}
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			map[i][j] = maze[i][j];
		}
	}
	stack<position> step(height, width);
	struct position mouse;
	mouse.x = Edit6->Text.ToInt();
	mouse.y = Edit7->Text.ToInt();
	mouse.dir = N;
	int **mm = MouseSearch(mouse);
	ProgressBar1->Step = ProgressBar1->Max;
	cinGrid(StringGrid2,mm);
	cinGrid(StringGrid3,mm);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
	//StringGrid1->Canvas->Brush->Color = clWhite;
	/*StringGrid1->Canvas->Brush->Color = TColor RGB(249,231,159);//設定畫布筆刷顏色
	StringGrid1->Canvas->Font->Color = clBlue;//設定字體顏色
	StringGrid1->Canvas->FillRect(Rect);//填色
	AnsiString text = StringGrid1->Cells[ACol][ARow];//取所有文字
	StringGrid1->Canvas->TextRect(Rect, Rect.Left+8, Rect.Top+8, text);// 寫上文字 */
    int num = (Form1->Edit3->Text.ToInt());
	String text = StringGrid1->Cells[ACol][ARow];
	if (text == "0") StringGrid1->Canvas->Brush->Color = TColor RGB(252, 243, 207);
	else if (text == "1") StringGrid1->Canvas->Brush->Color = TColor (RGB(241, 196, 15));
	else if (text == "2") StringGrid1->Canvas->Brush->Color = TColor (RGB(243, 156, 18));
	else StringGrid1->Canvas->Brush->Color = TColor RGB(255, 255, 255);
	StringGrid1->Canvas->Font->Color = TColor RGB(0,0,0);
	StringGrid1->Canvas->FillRect(Rect);
	AnsiString text2 = StringGrid2->Cells[ACol][ARow];
	StringGrid1->Canvas->TextRect(Rect, Rect.Left+num/3, Rect.Top+num/4, text2);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid2DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
	int num = (Form1->Edit3->Text.ToInt());
	String text = StringGrid2->Cells[ACol][ARow];
	if (text == "0") StringGrid2->Canvas->Brush->Color = TColor RGB(252, 243, 207);
	else if (text == "1") StringGrid2->Canvas->Brush->Color = TColor (RGB(243, 156, 18));
	else if (text == "2") StringGrid2->Canvas->Brush->Color = TColor (RGB(255, 100, 18));
	else StringGrid2->Canvas->Brush->Color = TColor RGB(255, 255, 255);
	StringGrid2->Canvas->Font->Color = TColor RGB(0,0,0);
	StringGrid2->Canvas->FillRect(Rect);
	AnsiString text2 = StringGrid2->Cells[ACol][ARow];
	StringGrid2->Canvas->TextRect(Rect, Rect.Left+num/3, Rect.Top+num/4, text2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid3DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State)
{

	String text = StringGrid3->Cells[ACol][ARow];
	if (text == "0") StringGrid3->Canvas->Brush->Color = TColor RGB(254, 249, 231);
	else if (text == "1") StringGrid3->Canvas->Brush->Color = TColor (RGB(243, 156, 18));
	else if (text == "2") StringGrid3->Canvas->Brush->Color = TColor (RGB(255, 100, 18));
	else if (text == "3") StringGrid3->Canvas->Brush->Color = TColor (RGB(247, 220, 111));
	else if (text == "4") StringGrid3->Canvas->Brush->Color = TColor (RGB(241, 225, 0));
	else StringGrid3->Canvas->Brush->Color = TColor RGB(255, 255, 255);
	StringGrid3->Canvas->FillRect(Rect);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid4DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
	String text = StringGrid4->Cells[ACol][ARow];
	if (text == "0") StringGrid4->Canvas->Brush->Color = TColor RGB(206, 240, 192);
	else if (text == "1") StringGrid4->Canvas->Brush->Color = TColor (RGB(81, 188, 35));
	else if (text == "2") StringGrid4->Canvas->Brush->Color = TColor (RGB(52, 173, 0));
	else if (text == "3") StringGrid4->Canvas->Brush->Color = TColor (RGB(160, 234, 130));
	else if (text == "4") StringGrid4->Canvas->Brush->Color = TColor (RGB(77, 255, 0));
	else StringGrid4->Canvas->Brush->Color = TColor RGB(255, 255, 255);
	StringGrid4->Canvas->FillRect(Rect);

	//BMP->LoadFromFile("5.bmp");
	//if (text == "0") StringGrid5->Canvas->StretchDraw(Rect, BMP);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid5DrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
		  TGridDrawState State)
{
	String text = StringGrid5->Cells[ACol][ARow];
	if (text == "0") StringGrid5->Canvas->Brush->Color = TColor RGB(210, 221, 255);
	else if (text == "1") StringGrid5->Canvas->Brush->Color = TColor (RGB(0, 40, 160));
	else if (text == "2") StringGrid5->Canvas->Brush->Color = TColor (RGB(0, 20, 83));
	else if (text == "3") StringGrid5->Canvas->Brush->Color = TColor (RGB(180, 180, 255));
	else if (text == "4") StringGrid5->Canvas->Brush->Color = TColor (RGB(51, 100, 255));
	else StringGrid5->Canvas->Brush->Color = TColor RGB(255, 255, 255);
	StringGrid5->Canvas->FillRect(Rect);


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
	if(Edit1->Text.Trim()!=""){
		width = StrToInt(Edit1->Text);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
	if(Edit2->Text.Trim()!=""){
		height = StrToInt(Edit2->Text);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3Change(TObject *Sender)
{
	if(Edit3->Text.Trim()!=""){
		setGHW(StringGrid1);
		setGHW(StringGrid2);
		setGHW(StringGrid3);
		setGHW(StringGrid4);
		setGHW(StringGrid5);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1Click(TObject *Sender)
{
	coutInfByGrid(StringGrid1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid2Click(TObject *Sender)
{
	coutInfByGrid(StringGrid2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid3Click(TObject *Sender)
{
	coutInfByGrid(StringGrid3);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid4Click(TObject *Sender)
{
	coutInfByGrid(StringGrid4);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid5Click(TObject *Sender)
{
	coutInfByGrid(StringGrid5);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit4Change(TObject *Sender)
{
	if(Edit4->Text.Trim()!=""){
		end.x = Edit4->Text.ToInt();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit5Change(TObject *Sender)
{
	if(Edit5->Text.Trim()!=""){
		end.y = Edit5->Text.ToInt();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
	initiation();
	for (int i=0; i<height; i++){
			delete [] maze[i];
			delete [] map[i];
	}
	delete [] maze;
	delete [] map;

	cinGrid(StringGrid1,maze);
	cinGrid(StringGrid2,maze);
	cinGrid(StringGrid3,maze);
	cinGrid(StringGrid4,maze);
	cinGrid(StringGrid5,maze);
	/*for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			map[i][j] = maze[i][j];
		}
	} */
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button7Click(TObject *Sender)
{
	if (OpenDialog1->Execute()){
		BMP->LoadFromFile(OpenDialog1->FileName);
		Image1->Picture->Assign(BMP);
	}
	Form1->StringGrid4->Refresh();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
	Label10->Caption = 100-TrackBar1->Position;
}
//---------------------------------------------------------------------------

