#include <iostream>
#include <conio.h>
#include <windows.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#define KEY_UP  72
#define KEY_DOWN  80
#define KEY_RIGHT 77 
#define KEY_LEFT  75
#include "graphics.h"
using namespace std;
struct textNode {
	char ch;
	textNode* next, *prev;
};

void addToList(textNode *&head, textNode *&tail, textNode *&cursor, char ch, int& size)
{
	if (head == nullptr)
	{
		head = tail = new textNode;
		head->ch = ch;
		head->next = nullptr;
		head->prev = nullptr;
		cursor = head;
		size = 1;
	}
	else
	{
		tail->next = new textNode;
		textNode *temp = tail;
		tail = tail->next;
		tail->ch = ch;
		tail->next = nullptr;
		tail->prev = temp;
		cursor = tail;
		size++;
	}
}
void printList(textNode *head, textNode *cursor, int &top, int &left, int &right, int &bottom, int &X)
{
	int line = 15;
	textNode *curr = head;
	while (curr != nullptr)
	{
		int i = 0;
		int y = 15;
		char cha[2] = { '\0','\0' };
		char t = curr->ch;
		cha[0] = t;
		if (t == 13 || t == '0')
		{
			moveto(0, line);
			line = line + 15;
			i = 1;
		}
		if (t == 32 || t == '1')
		{
			outtext(" ");
			i = 1;
		}
		if (i == 0)
		{
			if (curr->ch == cursor->ch)
			{
				rectangle(0 + left, 15 + top, 7 + right, 20 + bottom);
				outtext(cha);
				X = getx();
			}
			else
			{
				outtext(cha);
				X = getx();
			}
		}
		if (X >= 280)
		{
			moveto(0, line);
			line = line + 15;
			X = 0;
			i = 1;
		}
		curr = curr->next;
	}
}
void printList1(textNode *tail)
{
	textNode *curr = tail;
	while (curr != nullptr)
	{
		char cha[2] = { '\0','\0' };
		char t = curr->ch;
		cha[0] = t;
		outtext(cha);
		curr = curr->next;
	}
}
void removeFromList(textNode *&head, textNode *&tail, textNode *&cursor)
{
	textNode *curr = head;
	while (curr != nullptr && curr->next != tail)
	{
		curr = curr->next;
	}
	if (head == cursor)
	{
		delete head;
		head = nullptr;
		cursor = nullptr;
		tail = nullptr;
	}
	else
	{
		delete tail;
		tail = curr;
		cursor = tail;
		tail->next = nullptr;
	}

}
void addAtCursor(textNode *&head, textNode *&tail, textNode *&cursor, char ch, int &size)
{

	textNode *curr = head;
	textNode *prev = nullptr;
	while (curr != nullptr && curr != cursor)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr == nullptr && prev == nullptr)//list is empty//  <-
	{
		head = tail = new textNode;
		head->ch = ch;
		head->next = nullptr;
		head->prev = nullptr;
		cursor = head;
		size = 1;
	}
	else if (cursor == nullptr && head != nullptr) // when cursor is pointing to null but list is not empty
	{
		textNode *temp = new textNode;
		temp->ch = ch;
		temp->next = head;
		temp->prev = nullptr;
		head = temp;
		cursor = head;
		size++;
	}

	else if (curr == cursor && curr->next != nullptr) // in between 
	{
		textNode *temp = new textNode;
		temp->next = curr->next;
		curr->next = temp;
		temp->ch = ch;
		temp->prev = curr;
		cursor = temp;
		size++;
	}
	else if (curr == cursor && curr->next == nullptr) //at end //  <-
	{
		textNode *temp = cursor;
		textNode *temp2 = tail;
		curr->next = new textNode;
		tail = curr->next;
		tail->ch = ch;
		tail->next = nullptr;
		tail->prev = temp2;
		cursor = tail;
		size++;
	}
}
void removeAtCursor(textNode *&head, textNode *&tail, textNode *&cursor, int &size)
{
	textNode *prev = nullptr;
	textNode *curr = head;
	while (curr != nullptr && curr != cursor)
	{
		prev = curr;
		curr = curr->next;
	}
	if (head != nullptr)
	{
		if (curr == cursor && curr == head && curr->next != nullptr) // first ch but other are presnet
		{
			head = curr->next;
			head->prev = nullptr;
			cursor = head;
			delete curr;
			size--;
		}

		else if (prev == nullptr && curr == cursor) //  only one character
		{
			delete curr;
			head = nullptr;
			cursor = nullptr;
			size = 0;
		}
		else if (curr == cursor && curr->next == nullptr) // at last 
		{
			delete curr;
			prev->next = nullptr;
			cursor = prev;
			size--;
		}
		else if (curr == cursor && curr->next != nullptr) // middle
		{

			textNode *temp = new textNode;  //new
			temp = curr->next;     //new
			prev->next = curr->next;
			delete curr;
			temp->prev = prev;    //new
			cursor = prev;
			size--;
		}
	}
}

bool ToFind(textNode *head, int sizeOfMain, textNode *toFind, int sizeOfFind, int &count)
{
	textNode *currOfFind = toFind;
	textNode *currOfMain = head;

	int i = 0, found = 0;
	while (i < (sizeOfMain + 2 - sizeOfFind) && currOfMain != nullptr)
	{
		currOfFind = toFind;
		if (currOfMain->ch == currOfFind->ch)
		{
			found = 1;
			for (int j = 1; j < sizeOfFind - 1; j++)
			{
				currOfFind = currOfFind->next;
				currOfMain = currOfMain->next;
				if (currOfMain->ch != currOfFind->ch)
				{
					if (count == 0)
					{
						found = 0;
						break;
					}
					else
						break;
				}
			}
			if (found == 1)
				count++;
		}
		currOfMain = currOfMain->next;
		i++;
	}
	return found;
}
void ToReplace(textNode *&head, textNode *&tail, textNode *&cursor, int &sizeOfMain, textNode *&toFind, int sizeOfFind, int &count, textNode *&hr, int toReplaceSize)
{
	textNode *currOfFind = toFind;
	textNode *currOfMain = head;
	count = 0;
	bool find = ToFind(head, sizeOfMain, toFind, sizeOfFind, count);
	if (find == true)
	{
		currOfFind = toFind;
		currOfMain = head;
		textNode **temp = nullptr;
		temp = new textNode*[count];
		int index = 0;
		int i = 0, found = 0, counter = 0, flag = 0;
		while (i <= (sizeOfMain) && currOfMain != nullptr)
		{
			flag = 1;
			currOfFind = toFind;
			textNode *t2 = currOfMain;
			textNode *cmain = currOfMain;
			for (int j = 1; j < sizeOfFind - 1 && cmain!= nullptr; j++)
			{
				
				if (cmain->ch != currOfFind->ch)
				{
					flag = 0;
				}
				currOfFind = currOfFind->next;
				cmain = cmain->next;
			}
			if(flag==1)
			{
				temp[index] = t2;
				index++;
			}
			currOfMain = currOfMain->next;
			i++;
		}
		textNode *newhead = nullptr;
		textNode *newtail = nullptr;
		textNode *newcursor = nullptr;
		textNode *currOfhr = hr;  // head2
		currOfFind = toFind;
		sizeOfMain = 0;
		currOfMain = head;
		while (currOfMain != temp[0])
		{
			addAtCursor(newhead, newtail, newcursor, currOfMain->ch, sizeOfMain);
			currOfMain = currOfMain->next;
		}
		if (count > 1)
		{
			for (int i = 1; i < count; i++)
			{
				currOfhr = hr;
				while (currOfhr != nullptr)
				{
					addAtCursor(newhead, newtail, newcursor, currOfhr->ch, sizeOfMain);
					currOfhr = currOfhr->next;
				}
				currOfFind = toFind;
				while (currOfFind != nullptr && currOfMain != nullptr) // newwwwwwwwww
				{
					currOfFind = currOfFind->next;
					currOfMain = currOfMain->next;
				}
				while (currOfMain != temp[i] && currOfMain->ch != NULL) // n1
				{
					addAtCursor(newhead, newtail, newcursor, currOfMain->ch, sizeOfMain);
					currOfMain = currOfMain->next;
				}
			}
			currOfhr = hr;
			while (currOfhr != nullptr)
			{
				addAtCursor(newhead, newtail, newcursor, currOfhr->ch, sizeOfMain);
				currOfhr = currOfhr->next;
			}
			currOfFind = toFind;
			while (currOfFind != nullptr && currOfMain != nullptr) // newwwwwww
			{
				currOfFind = currOfFind->next;
				currOfMain = currOfMain->next;
			}
			while (currOfMain != nullptr)
			{
				addAtCursor(newhead, newtail, newcursor, currOfMain->ch, sizeOfMain);
				currOfMain = currOfMain->next;
			}
		}
		else
		{
			currOfhr = hr;
			while (currOfhr != nullptr)
			{
				addAtCursor(newhead, newtail, newcursor, currOfhr->ch, sizeOfMain);
				currOfhr = currOfhr->next;
			}
			currOfFind = toFind;
			while (currOfFind != nullptr  && currOfMain != nullptr) // <-----
			{
				currOfFind = currOfFind->next;
				currOfMain = currOfMain->next;
			}
			while (currOfMain != nullptr)
			{
				addAtCursor(newhead, newtail, newcursor, currOfMain->ch, sizeOfMain);
				currOfMain = currOfMain->next;
			}
		}

		currOfMain = head;        // deallocation
		textNode *t = nullptr;
		while (currOfMain != nullptr)
		{
			t = currOfMain;
			currOfMain = currOfMain->next;
			delete t;
		}
		t = nullptr;
		head = newhead;
		tail = newtail;
		cursor = newcursor;
	}
	else
		outtext("Not Found!");
}

int main()
{
	int window_ID = initwindow(300, 300, "Text Editor");
	setbkcolor(15);
	setcolor(0);
	textNode *head = NULL;
	textNode *tail = NULL;
	textNode *cursor = NULL;
	int size = 0;
	int q = 0, r = 0;
	char ch[2] = { '\0','\0' };
	ifstream fin;
	ofstream fout;

	int x = 10;
	int y = 10;
	int left = 0, right = 0, top = 0, bottom = 0;
	int line = 0;
	int g = 15;
	int X = 0, Y = 0;
	int y_axis = 15, y_axis1 = 20;

	while (true) //keep displaying
	{
		rectangle(0 + left, 15 + top, 7 + right, 20 + bottom);

		ch[0] = getch();   //read the key-press


		if (ch[0] >= 32 && ch[0] <= 126)  // any character	
		{
			if (getx() <= 270)
			{
				addAtCursor(head, tail, cursor, ch[0], size);
				clearviewport();
				left += 7;
				right += 7;
				printList(head, cursor, top, left, right, bottom, X);
			}
			else
			{
				addAtCursor(head, tail, cursor, ch[0], size);
				clearviewport();
				top += 15;
				bottom += 15;
				left = right = 0;
				left += 7;
				right += 7;
				printList(head, cursor, top, left, right, bottom, X);
			}

		}
		else if (ch[0] == 8)  // Back Space
		{
			if (getx() >= 2)
			{
				removeAtCursor(head, tail, cursor, size);
				clearviewport();
				left -= 7;
				right -= 7;
				printList(head, cursor, top, left, right, bottom, X);
			}
			else if (getx() <= 2 && gety() >= 2)
			{
				removeAtCursor(head, tail, cursor, size);
				clearviewport();
				left = right = 280;
				top -= 15;
				bottom -= 15;
				left -= 7;
				right -= 7;
				printList(head, cursor, top, left, right, bottom, X);
			}
		}
		else if (ch[0] == 13) // enter
		{
			addToList(head, tail, cursor, ch[0], size);
			cleardevice();
			top += 15;
			bottom += 15;
			left = 0, right = 0;
			printList(head, cursor, top, left, right, bottom, X);
		}
		else if (ch[0] == 0)          // arrow keys
		{
			ch[0] = getch();
			if (ch[0] == KEY_RIGHT)
			{

				if (cursor->next != nullptr)
				{
					if (getx() <= 280)
					{
						cleardevice();
						printList(head, cursor, top, left, right, bottom, X);
						cursor = cursor->next;
						left += 7;
						right += 7;
					}
				}
			}
			else if (ch[0] == KEY_LEFT)
			{

				if (cursor->prev != nullptr)
				{
					if (getx() >= 0)
					{
						cleardevice();
						printList(head, cursor, top, left, right, bottom, X);
						cursor = cursor->prev;
						left -= 7;
						right -= 7;
					}
				}
			}
			else if (ch[0] == KEY_UP)
			{
				if (cursor->next != nullptr)
				{
					if (getx() <= 280)
					{
						cleardevice();
						printList(head, cursor, top, left, right, bottom, X);
						cursor = cursor->next;
						left += 7;
						right += 7;
					}
				}
			}
			else if (ch[0] == KEY_DOWN)
			{
				if (cursor->prev != nullptr)
				{
					if (getx() >= 0)
					{
						cleardevice();
						printList(head, cursor, top, left, right, bottom, X);
						cursor = cursor->prev;
						left -= 7;
						right -= 7;
					}
				}
			}
		}
		else if (ch[0] == 19)  // CTRL+S
		{

			fout.open("Output.txt");
			fout << size;
			textNode *curr = head;
			while (curr != nullptr)
			{
				if (curr->ch == 32)
				{
					fout << 1;
				}
				else if (curr->ch == 13)
				{
					fout << 0;
				}
				else
					fout << curr->ch;
				curr = curr->next;
			}
			fout.close();
		}
		else if (ch[0] == 12)  // CTRL+L
		{
			{
				int row = 15, a, b;
				fin.open("Output.txt");
				textNode *curr = head;
				textNode *temp = head;
				textNode *prev = head;
				while (curr != nullptr)  // deallocation od list
				{
					temp = curr->next;
					delete curr;
					curr = temp;
				}
				head = nullptr;
				cursor = nullptr;
				tail = nullptr;

				head = new textNode;
				head->prev = nullptr;
				curr = head;
				prev = head;

				cursor = head;
				cleardevice();
				int i = 0, sizeOfList = 0;
				fin >> sizeOfList;
				while (i < sizeOfList)
				{
					fin >> cursor->ch;
					char c[2] = { '\0','\0' };
					c[0] = cursor->ch;

					if (c[0] == '1')
						outtext(" ");
					else if (c[0] == '0')
					{
						moveto(0, row);
						row += 15;
					}
					else
					{
						outtext(c);
						a = getx();
						b = gety();
					}
					if (i == sizeOfList - 1)
					{
						cursor->next = nullptr;
						curr = cursor;
						tail = cursor;
						cursor = tail;
					}
					else
					{
						cursor->next = new textNode;
						curr = cursor;
						cursor = cursor->next;
						cursor->prev = curr;
					}
					i++;
				}
				cursor = tail = curr;
				cleardevice();
				right = left = a;
				top = bottom = b;
				printList(head, tail, top, left, right, bottom, X);
				fin.close();
			}
		}
		else if (ch[0] == 6)  // CTRL+F
		{
			int current_W = initwindow(200, 200, "To Find");
			setcurrentwindow(current_W);
			textNode *h = nullptr;
			textNode *t = nullptr;
			textNode *c = nullptr;
			int findSize = 0, count = 0;
			while (ch[0] != 13)
			{
				ch[0] = getch();
				addAtCursor(h, t, c, ch[0], findSize);
				cleardevice();
				printList(h, c, top, left, right, bottom, X);
			}
			ch[0] = getch();
			if (ch[0] == 13)
			{
				bool found = ToFind(head, size, h, findSize, count);

				if (found == true)
				{
					outtext(" Given Pattern Found ");
				}
				else
					outtext("Given Pattern Not Found!");

			}
			ch[0] = getch();
			if (ch[0] == 13)
			{
				closegraph(CURRENT_WINDOW);
				setcurrentwindow(window_ID);
			}

		}
		else if (ch[0] == 18)  // CTRL+R
		{
			int Replace_W = initwindow(200, 200, "To Replace");
			setcurrentwindow(Replace_W);
			textNode *h = nullptr;
			textNode *t = nullptr;
			textNode *c = nullptr;
			textNode *hr = nullptr;
			textNode *tr = nullptr;
			textNode *cr = nullptr;
			textNode*Head = nullptr;
			c = h;
			cr = head;
			int findSize = 0, toReplaceSize = 0, count = 0;
			while (ch[0] != 13)
			{
				ch[0] = getch();
				addAtCursor(h, t, c, ch[0], findSize);
				cleardevice();
				printList(h, c, top, left, right, bottom, X);
			}
			if (ch[0] == 13)
				cleardevice();
			ch[0] = getch();
			while (ch[0] != 13)
			{

				addAtCursor(hr, tr, cr, ch[0], toReplaceSize);
				cleardevice();
				printList(hr, cr, top, left, right, bottom, X);
				ch[0] = getch();
			}

			if (ch[0] == 13)
			{
				ToReplace(head, tail, cursor, size, h, findSize, count, hr, toReplaceSize);
			}
			ch[0] = getch();
			if (ch[0] == 13)
			{
				closegraph(CURRENT_WINDOW);
				setcurrentwindow(window_ID);
				cleardevice();
				printList(head, cursor, top, left, right, bottom, X);
			}
		}
		textNode *shiftStart;
		textNode *shiftEnd;
		textNode *newhead = nullptr;
		textNode *newtail = nullptr;
		textNode *newcursor = nullptr;
		int shiftKey;
		shiftKey = GetAsyncKeyState(VK_SHIFT);
		if (shiftKey == 1)
		{
			int shiftCount = 0;

			if (shiftKey == 1)
			{
				while (ch[0] != 22 && ch[0] != 24 && ch[0] != 3)
				{

					shiftKey = getch();
					ch[0] = shiftKey;
					ch[0] = getch();
					if (ch[0] == KEY_RIGHT)
					{
						shiftCount++;
						if (shiftCount == 1)
						{
							cursor = cursor->next;
							shiftStart = cursor;
							shiftEnd = cursor;
							ch[0] = cursor->ch;
							setbkcolor(GREEN);
							outtext(ch);
						}
						else
						{
							cursor = cursor->next;
							shiftEnd = cursor;
							ch[0] = cursor->ch;
							setbkcolor(10);
							outtext(ch);
						}

					}
					else if (ch[0] == KEY_LEFT)
					{
						if (cursor != nullptr)
						{
							shiftCount++;
							if (shiftCount == 1)
							{
								shiftStart = cursor;
								shiftEnd = cursor;
								ch[0] = cursor->ch;
								setbkcolor(10);
								outtext(ch);
								cursor = cursor->prev;
							}
							else
							{

								shiftEnd = cursor;
								ch[0] = cursor->ch;
								setbkcolor(10);
								outtext(ch);
								cursor = cursor->prev;
							}

						}
					}
				}

			}
		}
		else if (ch[0] == 3)  // CTRL+C
		{
			textNode *currOfMain = shiftStart;
			int s;
			while (currOfMain != shiftEnd)
			{
				addAtCursor(newhead, newtail, newcursor, currOfMain->ch, s);
				currOfMain = currOfMain->next;
			}
			addAtCursor(newhead, newtail, newcursor, currOfMain->ch, s);
		}
		else if (ch[0] == 22)  // CTRL+V
		{
			textNode *newc = cursor->next;
			textNode *c = head;
			//int s;
			while (c != cursor)
			{
				addAtCursor(newhead, newtail, newcursor, c->ch, size);
				c = c->next;
			}
			addAtCursor(newhead, newtail, newcursor, c->ch, size);

			textNode *currOfMain = shiftStart;
			int s;
			while (currOfMain != shiftEnd)
			{
				addAtCursor(newhead, newtail, newcursor, currOfMain->ch, s);
				currOfMain = currOfMain->next;
			}
			//addAtCursor(newhead, newtail, newcursor, currOfMain->ch, s);
			while (newc != nullptr)
			{
				addAtCursor(newhead, newtail, newcursor, newc->ch, s);
				newc = newc->next;
			}
			cleardevice();
			head = newhead;
			tail = newtail;
			cursor = newcursor;
			printList(newhead, newcursor, top, left, right, bottom, X);

		}
		else if (ch[0] == 24)  // CTRL+X
		{
			textNode *newc = cursor->next;
			textNode *c = head;
			//int s;
			while (c != cursor)
			{
				addAtCursor(newhead, newtail, newcursor, c->ch, size);
				c = c->next;
			}
			addAtCursor(newhead, newtail, newcursor, c->ch, size);

			textNode *currOfMain = shiftStart;
			int s;
			while (currOfMain != shiftEnd)
			{
				addAtCursor(newhead, newtail, newcursor, currOfMain->ch, s);
				currOfMain = currOfMain->next;
			}
			//addAtCursor(newhead, newtail, newcursor, currOfMain->ch, s);
			while (newc != nullptr)
			{
				addAtCursor(newhead, newtail, newcursor, newc->ch, s);
				newc = newc->next;
			}
			cleardevice();
			head = newhead;
			tail = newtail;
			cursor = newcursor;
			printList(newhead, newcursor, top, left, right, bottom, X);
		}

		// Extra 
		outstreamxy(130, 270);
		bgiout << " characters";
		int u = getx(), v = gety();
		outstreamxy(u + 5, v);
		bgiout << size;
	}
	return 0;
}



















