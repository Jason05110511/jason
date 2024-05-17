//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "U5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


template <class T>
class stack{
	public:
		T *stk;
		int top;

		stack(){
			stk = new T [100];
			/*
			for(int i=0;i<100;i++){
				stk[i] = new T;
			}  */
			top = -1;
		}
		stack(T n){
			stk = new T *[n];
			/*
			for(int i=0;i<n;i++){
				stk[i] = new T;
			} */
			top = -1;
		}

		void push(T n){
			if(top == 100) Form1->Memo1->Lines->Add("stack is FULL");
			else stk[++top] = n;
		}

		T pop(){
			if(top == -1){
				Form1->Memo1->Lines->Add("stack is NULL");
				}
			else return stk[top--];
		}

		bool IsEmpty(){
			return top == -1;
		}
};

bool IsOperat(char c){
	return (c=='#'||c=='|'||c=='&'||c=='+'||c=='-'||c=='*'||c=='/'||c=='%'||c=='^'||c=='(');
}

bool IsOperat(String s){
	return(s=="#"||s=="|"||s=="&"||s=="+"||s=="-"||s=="*" || s=="/" || s=="%"||s=="^"||s=="(");
}

int Out(char c){
	switch(c){
		case '#':
			return -1;
		case '|':
			return 1;
		case '&':
			return 2;
		case '+':
		case '-':
			return 6;
		case '*':
		case '/':
		case '%':
			return 7;
		case '^':
			return 8;
		case '(':
			return 9;
		default :
			break;
	}
	return -2;
}

int In(char c){
	switch(c){
		case '#':
			return -1;
		case '|':
			return 1;
		case '&':
			return 2;
		case '+':
		case '-':
			return 6;
		case '*':
		case '/':
		case '%':
			return 7;
		case '^':
			return 8;
		case '(':
			return 0;
		default :
			break;
	}
	return -2;
}

int Out(String s){
	if(s=="#"){return -1;}
	else if(s=="|"){return 1;}
	else if(s=="&"){return 2;}
	else if(s=="+" || s=="-"){return 6;}
	else if(s=="*" || s=="/" || s=="%"){return 7;}
	else if(s=="^"){return 8;}
	else if(s=="("){return 9;}
	else return -2;
}

int In(String s){
    if(s=="#"){return -1;}
	else if(s=="|"){return 1;}
	else if(s=="&"){return 2;}
	else if(s=="+" || s=="-"){return 6;}
	else if(s=="*" || s=="/" || s=="%"){return 7;}
	else if(s=="^"){return 8;}
	else if(s=="("){return 0;}
	else return -2;
}

String PrintCharStk(stack<char> stk1){
	String s = "",x;
	while(!stk1.IsEmpty()){
		x = stk1.pop();
		s += (" \"" + x + "\" ");
	}
	return s;
}

String PrintStringStk(stack<String> stk1){
	String s = "";
	while(!stk1.IsEmpty()){
		s += (" \"" + stk1.pop() + "\" ");
	}
	return s;
}

String InToPost(String s){
	Form1->Memo1->Lines->Add("\r\nInToPost =>");
	stack<char> stk1;
	stk1.push('#');
	String x,postfix = "",y;
	for(int i=1; i<=s.Length(); i++){
		y = s[i];
		Form1->Memo3->Lines->Add("s[i] = " + y + ", i = "+ IntToStr(i));
		if(s[i] == ')'){
			while((x = stk1.pop()) != '(') {
				postfix += x;
			}
		}
		else if(!IsOperat(s[i])){
			postfix += s[i];
			Form1->Memo1->Lines->Add("!IsOperat -> " + postfix);
		}
		else{
			while(Out(s[i]) <= In(stk1.stk[stk1.top])){
				x = stk1.pop();
				postfix += x;
				Form1->Memo1->Lines->Add("OutOperat <= InOperat -> " + postfix);
				Form1->Memo1->Lines->Add("Operator stack ->" + PrintCharStk(stk1));
			}
			stk1.push(s[i]);
		}
	}

	while((x = stk1.pop()) != '#'){
		postfix += x;
		Form1->Memo1->Lines->Add("remaining Operat -> " + postfix);
	}
	return postfix;
}

String PreToPost(String s){
	Form1->Memo1->Lines->Add("\r\nPreToPost =>");
	stack<String> stk1;
	stk1.push('#');
	String opd1,opt,postfix="";
	for(int i=1; i<=s.Length(); i++){
		postfix = s[i];
		Form1->Memo3->Lines->Add("s[i] = " + postfix + ", i = "+ IntToStr(i));
		if(!IsOperat(s[i])){
			while(!IsOperat(stk1.stk[stk1.top])){
				opd1 = stk1.pop();
				opt = stk1.pop();
				postfix = opd1 + postfix + opt;
				Form1->Memo1->Lines->Add(postfix + " = \"" + opd1 + "\" + \"" + s[i] + "\" + \"" + opt + "\"");
			}
			stk1.push(postfix);
			Form1->Memo1->Lines->Add("stack ->" + PrintStringStk(stk1));
		}
		else{
			stk1.push(s[i]);
            Form1->Memo1->Lines->Add("stack ->" + PrintStringStk(stk1));
		}
	}
    postfix = stk1.pop();
	String x = stk1.pop(); //#
	return postfix;
}

String PostToIn(String s){
	Form1->Memo1->Lines->Add("\r\nPostToIn =>");
	Form1->Memo2->Lines->Add("\r\nPostToIn =>");
	stack<String> stk1,stk2;
	String s1, s2, x, y, z;
	for(int i=1; i<=s.Length(); i++){
		z = s[i];
		Form1->Memo3->Lines->Add("s[i] = " + z + ", i = "+ IntToStr(i));
		if(!IsOperat(s[i])){
			stk2.push(s[i]);
			stk1.push("#");
			Form1->Memo1->Lines->Add("stack ->" + PrintStringStk(stk1));
			Form1->Memo2->Lines->Add("stack ->" + PrintStringStk(stk2));
		}
		else{
			s1 = stk1.pop(); s2 = stk1.pop();
			x = stk2.pop(); y = stk2.pop();
			Form1->Memo2->Lines->Add("--->s1 = " + s1 + ", s2 = " + s2 + ", x = " + x + ", y = " + y);
			if (Out(s[i])>In(s1) && x.Length()>1) x ="("+x+")";
			if (Out(s[i])>In(s2) && y.Length()>1) y ="("+y+")";
			stk2.push(y+z+x);
			stk1.push(s[i]);
			Form1->Memo1->Lines->Add("stack -->" + PrintStringStk(stk1));
			Form1->Memo2->Lines->Add("stack -->" + PrintStringStk(stk2));
		}
	}
	while(!stk1.IsEmpty()){
		x = stk1.pop();
	}
	return stk2.pop();
}

String PostToPre(String s){
	Form1->Memo1->Lines->Add("\r\nPostToPre =>");
	stack<String> stk1;
	for(int i=1; i<=s.Length(); i++){
		String x = s[i];
		Form1->Memo3->Lines->Add("s[i] = " + x + ", i = "+ IntToStr(i));
		if (!IsOperat(s[i])){
			stk1.push(s[i]);
			Form1->Memo1->Lines->Add("stack -->" + PrintStringStk(stk1));
		}
		else{
			String a = stk1.pop();
			String b = stk1.pop();
			stk1.push(x+b+a);
			Form1->Memo1->Lines->Add("stack -->" + PrintStringStk(stk1));
		}
	}
	return stk1.pop();
}

int Whichfix(String s){
	int oprtnum = 0, oprdnum = 0;
	for(int i=1;i<=s.Length();i++){
		if(s[i] !='(' && s[i]!=')'){
			IsOperat(s[i]) ? oprtnum++ : oprdnum++;
		}
	}
	if(oprtnum != oprdnum-1){
		Form1->Memo1->Lines->Add("Input Error");
		return 3;
	}
	for(int i=1;i<=s.Length();i++){
		if(s[i]!='('){
			if(IsOperat(s[i]) && (!IsOperat(s[i+1]))) return 0;//prefix i=�B��l i+1=�B�⤸
			else if((!IsOperat(s[i])) && IsOperat(s[i+1])) return 1;//infix i=�B�⤸ i+1=�B��l
			else if((!IsOperat(s[i])) && (!IsOperat(s[i+1])) && IsOperat(s[i+2])) return 2;//postfix i=�B�⤸ i+1=�B�⤸ i+2=�B��l
		}
	}
	Form1->Memo1->Lines->Add("Input Error");
	return 3;//means : i don't know what it is
}

void PrintLine(){
	String s = "";
	int w1 = Form1->Memo1->Width/8;
	int w2 = Form1->Memo2->Width/8;
	int w3 = Form1->Memo3->Width/8;
	for(s = "\r\n"; w1 >= 0; w1--) s+= "-";
	Form1->Memo1->Lines->Add(s);
	for(s = "\r\n"; w2 >= 0; w2--) s+= "-";
	Form1->Memo2->Lines->Add(s);
	for(s = "\r\n"; w3 >= 0; w3--) s+= "-";
	Form1->Memo3->Lines->Add(s);
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    Edit1->Text = "";
	Edit2->Text = "";
	Edit3->Text = "";
	String x;
	String s = ComboBox1->Text;
	int fix = Whichfix(s);
	if(fix==0){
        Label5->Font->Color = clBlue;
		Label5->Caption = "Prefix";
		Edit1->Text = s;
		x = PreToPost(s);
		Memo3->Lines->Add("Output ->" + x);
		Edit3->Text = x;
		x = PostToIn(x);
		Memo3->Lines->Add("Output ->" + x);
		Edit2->Text = x;
		PrintLine();
	}
	else if(fix==1){
		Label5->Font->Color = clBlue;
		Label5->Caption = "Infix";
		Edit2->Text = s;
		x = InToPost(s);
		Memo3->Lines->Add("Output ->" + x);
		Edit3->Text = x;
		x = PostToPre(x);
		Memo3->Lines->Add("Output ->" + x);
		Edit1->Text = x;
		PrintLine();
	}
	else if(fix==2){
		Label5->Font->Color = clBlue;
		Label5->Caption = "Postfix";
		Edit3->Text = s;
		x = PostToIn(s);
		Memo3->Lines->Add("Output ->" + x);
		Edit2->Text = x;
		x = PostToPre(s);
		Memo3->Lines->Add("Output ->" + x);
		Edit1->Text = x;
		PrintLine();
	}
	else if(fix==3){
		Label5->Font->Color = clRed;
		Label5->Caption = "Error";
	}
}
//---------------------------------------------------------------------------



