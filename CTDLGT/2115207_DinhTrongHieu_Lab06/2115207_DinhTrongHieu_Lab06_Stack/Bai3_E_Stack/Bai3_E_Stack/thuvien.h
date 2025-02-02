﻿typedef char Data;
#define MAX 100
struct NODE
{
	Data info;
	NODE* pNext;
};
struct  STACK
{
	NODE* pHead;
	NODE* pTail;
};
NODE* GetNode(Data x);
void CreatStack(STACK& s);
void Push(STACK& s, Data x);


NODE* GetNode(Data x)
{
	NODE* p;
	p = new NODE;
	if (p != NULL)
	{
		p->info = x;
		p->pNext = NULL;
	}
	return p;
}
//Tao DS rong
void CreatStack(STACK& s)
{
	s.pHead = s.pTail = NULL;
}
//Ham chen x vao dau s
void Push(STACK& s, Data x)
{
	NODE* new_ele = GetNode(x);
	if (new_ele == NULL)
	{
		cout << "\nsoi cap phat bo nho! khong thuc hien duoc thao tac nay";
		return;
	}
	if (s.pHead == NULL)
	{
		s.pHead = new_ele; s.pTail = s.pHead;
	}
	else
	{
		new_ele->pNext = s.pHead;
		s.pHead = new_ele;
	}
}
Data Pop(STACK& s)
{
	Data x;
	NODE* p;
	if (s.pHead == NULL)
	{
		return NULL;
	}
	x = s.pHead->info;
	p = s.pHead;
	s.pHead = s.pHead->pNext;
	delete p;
	if (s.pHead == NULL)
		s.pTail = NULL;
	return x;
}
//================================================
void Printf(char* a) {
	for (int i = 0; a[i] != NULL; i++) {
		cout << a[i];
	}
}
int LaKySo(char c) {
	if (c >= '0' && c <= '9') {
		return 1;
	}
	return 0;
}

void Chen_Cuoi_Chuoi(char sout[], char c) {
	int i;
	for (i = 0; sout[i] != NULL; i++) {

	}
	sout[i] = c;
	sout[++i] = NULL;


}
int So(char c)
{
	return c - '0';
}
int LaToanTu(char c) {
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
		return 1;
	return 0;
}
int Do_UuTien_ToanTu(char c) {
	if (c == '*' || c == '/' || c == '%')
		return  2;
	else if (c == '+' || c == '-')
		return 1;
	return 0;
}
char* TrungTo_HauTo(char sin[])
{
	char sout[MAX];
	sout[0] = NULL;
	STACK s;//stack luu cac toan tu
	char c; //Ky tu hien hanh - dang xet
	Data x; //luu toan tu o dinh stack trong thao tac Pop(s);
	int i; //duyet chuoi vao : sin
	CreatStack(s);
	// duyet tu trai sang phai cac ptu cua bieu thuc trung to P
	for (i = 0; sin[i] != NULL; i++)
	{
		c = sin[i];//ky tu dang xet
		if (LaKySo(c) == 1) //la ky so : toan hang
			Chen_Cuoi_Chuoi(sout, c); //chen c vao cuoi sout
		else
			if (c == '(')
				Push(s, c);//day '(' vao stack s
			else
				if (c == ')')
				{
					x = Pop(s);
					while (x != '(')
					{
						Chen_Cuoi_Chuoi(sout, x);
						x = Pop(s);
					}
				}
				else // la toan hang
				{
					while (s.pHead != NULL && LaToanTu(s.pHead->info) == 1)
						if (Do_UuTien_ToanTu(s.pHead->info) >= Do_UuTien_ToanTu(c))
						{
							x = Pop(s);
							Chen_Cuoi_Chuoi(sout, x);
						}
						else
							break;
					//Push toan tu dang xet vao s
					Push(s, c);
				}
	}//da het sin
	while (s.pHead != NULL) //lay cac toan tu trong s chen vao cuoi sout
	{
		x = Pop(s);
		Chen_Cuoi_Chuoi(sout, x);
	}
	
	return sout;
}
//Tính giá trị biểu thức đại số dạng hậu tố
int Tinh_BT_HauTo(char a[])
{
	int i;
	char c;
	char x, y;
	STACK s;
	CreatStack(s);
	for (i = 0; a[i] != NULL; i++)
	{
		c = a[i];
		if (LaKySo(c) == 1)
		{
			x = So(c);
			Push(s, x);
		}
		else //toan tu
		{
			x = Pop(s);
			y = Pop(s);
			switch (c)
			{
			case '+':
				Push(s, y + x);
				break;
			case '-':
				Push(s, y - x);
				break;
			case '*':
				Push(s, y * x);
				break;
			case '/':
				Push(s, y / x);
				break;
			case '%':
				Push(s, y % x);
				break;
			}
		}
	}//Ket thuc bieu thuc hau to
	return s.pHead->info; //Gia tri bieu thuc hau to
}