#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#define MAXLIST 4
#define boxx 25
#define boxy 7
#define boxs 40
#define boxw 10
static int kt;


struct tudien{
	string tugoc;
	string tuloai;
	string nghia;
};
struct Node{
	tudien data;
	Node *link;
};
struct List{
	Node *first, *last;
};


void setcolor(short x) {
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, x);
}
void gotoXY (int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void dicbox() {
	setcolor(15);
	gotoXY(boxx, boxy); 
	cout << char(201);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(187);
	gotoXY(boxx, boxy + 1); cout << char(186);
	setcolor(15);
	gotoXY(boxx+12, boxy+1);
	cout << "TU DIEN ANH VIET";
	setcolor(15);
	gotoXY(boxx + boxs + 1, boxy + 1); cout << char(186);
	gotoXY
	(boxx, boxy + 2); cout << char(200);
	for(int i = 1; i < boxs + 1; i++) {
		cout << char(205);
	}
	cout << char(188);
}
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void Initi(List &l)
{
	l.first=l.last=NULL;
}
Node* GetNode(tudien x)
{
	Node *p;
	p = new Node;
	if(p==NULL)
		return NULL;
	p->data=x;
	p->link=NULL;
	return p;
}
void AddLast(List &l,Node* a)
{
	if(l.first==NULL)
	{
		l.first=a;
		l.last=l.first;

	}
	else
	{
		l.last->link=a;
		l.last=a;
	}
}
void InsertLast(List &l,tudien x)
{
	Node* a=GetNode(x);
	if(a==NULL)
		return;
	AddLast(l,a);
}
void docfile(ifstream &filein, tudien &td)
{
	getline(filein,td.tugoc,'\n');
	getline(filein, td.tuloai,'\n');
	getline(filein, td.nghia,'@');
}
void ghifile(fstream &f, tudien a)
{
	f << a.tugoc;
	f << "\n";
	f << a.tuloai;
	f << "\n";
	f << a.nghia;
}
void ghifile1(fstream &f, tudien a)
{
	f << "@";
	f << a.tugoc;
	f << "\n";
	f << a.tuloai;
	f << "\n";
	f << a.nghia;
}
void inputtudien(ifstream &filein, List &l)
{
	string a;
	getline(filein,a,'@');
	while(!filein.eof())
	{
		tudien td;
		docfile(filein, td);
		InsertLast(l,td);
	}
}
void vietvaofile(List l,fstream &f)
{
	for(Node *i=l.first;i!=NULL;i=i->link)
		ghifile(f,i->data);
}
void vietvaofile1(List l,fstream &f)
{
	for(Node *i=l.first;i!=NULL;i=i->link)
		ghifile1(f,i->data);
}
tudien seach(List l,string tu)
{
	tudien a;
	a.tugoc="-1";
	a.tuloai="-1";
	a.nghia="-1";
	for(Node *i=l.first;i!=NULL;i=i->link)
		if(tu.compare(i->data.tugoc)==0)
			return i->data;
	return a;
}	
void xuattu(tudien td)
{
//	cout << "\ntu goc: " << td.tugoc;
	gotoXY(0,3);
	cout << td.tuloai;
	gotoXY(0,4);
	cout << td.nghia;
}
void xuattu1(tudien td)
{
	cout << td.tugoc;
	cout << "\n";
	cout << td.tuloai;
	cout << "\n";
	cout << td.nghia;
}
void tratu(List &l, List &past)
{
	ifstream filein;
	filein.open("abcd.txt",ios::in);
	inputtudien(filein,l);
	filein.close();
	string tu;
	char key_press;
    	int ascii_value;
	while(1)
	{
		system("cls");
		setcolor(8);
		cout << "Nhap vao tu ban muon tra....";
		setcolor(15);
		if(getch())
		system("cls");
		getline(cin,tu);
		tudien a=seach(l,tu);
		if(a.tugoc.compare("-1")==0)
			{
				gotoXY(0,10);
				cout << "Tu nay hien chua co trong tu dien.";
				gotoXY(0,11);
				cout << "Vui long cap nhat sau!";
			}
		else
			{
				xuattu(a);
				InsertLast(past,a);
			}
		setcolor(3);
		gotoXY(30,20);
		cout << "Nhan phim bat ky de tiep tuc.";
		gotoXY(30,21);
		cout << "Nhan ESC de quay lai menu\n";
		setcolor(15);
        	key_press=_getch();
        	ascii_value=key_press;
	 	if(ascii_value==27)
       	     break;
	}
	fstream f;
	f.open("output.txt", ios::out);
	vietvaofile(past,f);
	f.close();
}
void tuvuatra(List &l)
{
	if(l.first!=NULL)
	{
		for(Node *i=l.first;i!=NULL;i=i->link)
		xuattu1(i->data);
	}
	else
	{
		ifstream f;
		f.open("output.txt", ios::in);
		inputtudien(f,l);
		f.close();
		if(l.first!=NULL)
			for(Node *i=l.first;i!=NULL;i=i->link)
				xuattu1(i->data);
		else
		{
			gotoXY(40,15);
			cout << "Lan truoc ban khong tra tu nao!!";
		}
	}
}
void themtu(List &l)
{
	Initi(l);
	ifstream filein;
	filein.open("abcd.txt",ios::in);
	inputtudien(filein,l);
	filein.close();
	tudien a;
	a.tugoc="";
	a.tuloai="*";
	a.nghia="";
	int i=1;
	string m;
	cout<<"Tu goc: ";
	getline(cin,m);
	a.tugoc += m;
	cout<<"Tu loai: ";
	getline(cin,m);
	a.tuloai += m;
	gotoXY(0,25);
	setcolor(12);
	cout<<"Nhan ENTER de ket thuc!!";
	setcolor(15);
	gotoXY(0,4);
	while(1)
	{
		string n;
		cout<<"Nghia "<< i << " :";
		getline(cin,n);
		i++;
		if(n.empty())break;
		string v="-";
		v += n;
		v += "\n";
		a.nghia+=v;
	}
	InsertLast(l,a);
	system("cls");
	fstream f;
	f.open("abcd.txt",ios::out);
	vietvaofile1(l,f);
	f.close();
	gotoXY(0,3);
	setcolor(10);
	cout<<"Them thanh cong!!\n";
	setcolor(15);
	gotoXY(0,25);
	system("pause");	
}
void chtr()
{
	List l;
	List past;
	Initi(l);
	Initi(past);
	char* menu[]={"TRA TU","TU DA TRA","THEM TU MOI","THOAT"};
	int poin = 0,kt=1;
	int x=40, y=0;
	while(1)
	{
		system("cls");
		dicbox();
		for(int i=0;i<MAXLIST;i++)
		{
			if(poin==i)
			{
				setcolor(12);
				gotoXY(38,10+i);
				printf("%c %s %c",175,menu[i],174);
			}
			else
			{
				setcolor(15);
				gotoXY(40,10+i);
				printf("%s",menu[i]);
			}
		}
		while(1)
		{
			if(kbhit())
			{
				char key = getch();
				if(key==72)
				{
					if(poin > 0)
					{
						--poin;
					}
					else
					{						
						poin=MAXLIST-1;
					}
					break;
				}
				if(key==80)
				{
					
					if(poin < MAXLIST-1)
					{
						++poin;
					}
					else
					{						
						poin=0;
					}
					break;
				}
				if(key==13)
				{
					switch(poin)
					{
						case 0:
							tratu(l,past);
						break;
						case 1:
							system("cls");
							tuvuatra(past);
							system("pause");
						break;
						case 2:
							system("cls");
							themtu(l);
							break;
						case 3: 
						{
							system("cls");
							gotoXY(40,7);
							printf("HEN GAP LAI!!\n");
							kt=-1;
						}
					}
					break;
				}
			}
		}
		if(kt==-1)
			{
					break;
			}
	}
	gotoXY(40,8);
	printf("GOOGBYE!!!\n");
	getch();
}
int main(int argc, char *argv[])
{
	SetConsoleTitle("TUDIENANH-VIET");
	resizeConsole(800,500);
	chtr();
	setcolor(15);
	return 0;
}
