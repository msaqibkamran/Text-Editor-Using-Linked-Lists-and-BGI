#include<iostream>
#include<conio.h>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<string.h>
using namespace std;

void ToFind(char data[], char ToFind[])
{
	int size = strlen(ToFind);
	int found = 0,count=0;
	for (int i = 0; data[i] != '\0'; i++)
	{
		if (strncmp(ToFind, &data[i], size) == 0)
		{
			found = 1;
			count++;
		}
	}
	if (found == 1)
	{
		cout <<ToFind<< " Found " << count << " times" << endl;
	}
	else
		cout << "Not Found!";
}
void ToReplace(char data[], char ToFind[],char ReplaceWith[])
{
	int size = strlen(ToFind);
	int found = 0, count = 0;
	for (int i = 0; data[i] != '\0'; i++)
	{
		if (strncmp(ToFind, &data[i], size) == 0)
		{
			found = 1;
			count++;
		}
	}
		
	if (found == 1)
	{
		cout << ToFind << " Found " << count << " times" << endl;

		int len = strlen(ReplaceWith);
		for (int i = 0; data[i] != '\0'; i++)
		{
			if (strncmp(ToFind, &data[i], size) == 0)
			{
				int j = i, k = 0;
				if (size == len)
				{
					while (k < len)
					{

						data[j++] = ReplaceWith[k++];

					}
				}
				else if (size>len)
				{
					while (k < len)
					{
						data[j++] = ReplaceWith[k++];

					}
					int nLen = size - len;
					while (data[j] != '\0')
					{
						data[j] = data[j + nLen];
						j++;
					}
				}
				else
				{
					while (k < len)
					{
						data[j++] = ReplaceWith[k++];

					}
				}
			}
		}
	}
	else
		cout << "Not Found!";
	
}

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
		textNode *temp=tail;
		tail = tail->next;
		tail->ch = ch;
		tail->next = nullptr;
		tail->prev = temp;
		cursor = tail;
		size++;
	}
}
void printList(textNode *head)
{
	textNode *curr = head;
	while (curr != nullptr)
	{
		cout << curr->ch << " ";
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
	delete tail;
	tail = curr;
	cursor = tail;
	tail->next = nullptr;

}
void addInOrder(textNode *&head, textNode *&tail, textNode *&cursor,char ch, int &size)
{
	//int flag = 0;
	textNode *curr = head;
	textNode *prev = nullptr;
	while (curr != nullptr && curr!=cursor)
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
	else if (cursor==nullptr && head != nullptr) // when cursor is pointing to null but list is not empty
	{
		textNode *temp = new textNode;
		temp->ch = ch;
		temp->next =head;
		temp->prev = nullptr;
		head = temp;
		cursor = head;
		size++;
	}
	
	else if(curr == cursor && curr->next != nullptr) // in between 
	{
		textNode *temp = new textNode;
		textNode *temp2 = nullptr;
		temp2 = curr->next;
		curr->next = temp;
		temp->ch = ch;
		temp->next = temp2;
		cursor = temp;
		size++;
	}
	else if (curr == cursor && curr->next == nullptr) //at end //  <-
	{
		textNode *temp = tail;
		tail->next = new textNode;
		tail = tail->next;
		tail->ch = ch;
		tail->next = nullptr;
		tail->prev = temp;
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

			prev->next = nullptr;
			cursor = prev;
			delete curr;
			size--;
		}
		else if (curr == cursor && curr->next != nullptr) // middle
		{

			prev->next = curr->next;
			delete curr;
			cursor = prev;
			size--;
		}
	}
}





int main()
{
	textNode *head = NULL;
	textNode *tail = NULL;
	textNode *cursor = NULL;
	int size = 0;
	char ch[] = {'S','a','q','i','b','\0' };
	

//	cursor = cursor->prev;
	
	addInOrder(head, tail, cursor, ch[0], size);
	addInOrder(head, tail, cursor, ch[1], size);
	addInOrder(head, tail, cursor, ch[2], size);
	addInOrder(head, tail, cursor, ch[3], size);

	
	cursor = cursor->prev->prev->prev->prev;

	//cout << cursor->ch << endl;
	addInOrder(head, tail, cursor, ch[4], size);
	
	printList(head);
	/*cout << endl;
	cout << cursor->ch << endl;	
	addInOrder(head, tail, cursor, ch[0]+5, size);
	printList(head);
	cout << endl;
	cout << cursor->ch << endl;*/
	

	

	

	_getch();
}













//char data[] = "My name is Saqib hello i m fine! Saqib";
//char tofind[] = "Nice";
//char toreplace[] = "Atif";
//ToFind(data, tofind);
//cout << endl;
//ToReplace(data, tofind, toreplace);
//cout << endl;
//cout << data;