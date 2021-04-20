#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
const int keyUp = 72;
const int keyDown = 80;
const int enter = 13;
const int escape = 27;
const int backspace = 8;
const int sleepTime = 750;

int vvodCifr() {
	int chislo = 0, stepen = 0, maxStepen = -1, count = 0, T = 1;
	char number;
	int C[9] = { 0 }, i = 0;
	
	while (T) {
		switch (number = _getch()) {
		case enter: T = 0; break;
		case escape: exit(0); break;
		case backspace: {
			if (count > 0) {
				cout << "\b \b";
				count--;
			}
			if (i > 0) {
				C[i-1] = 0;
				i--;
			}
			if (maxStepen > -1) {
				maxStepen--;
			}
		}
		default: {
			if (count == 9) { break; }
			else if (number > 47 and number < 58) { cout << number - 48; C[i] = number - 48; i++; maxStepen++; count++; } break;
		}
		}
	}

	for (int j = (count - 1); j >= 0; j--)
	{
		chislo += (C[j] * pow(10, stepen));
		if (stepen < maxStepen) {
			stepen++;
		}
	}

	return chislo;
}

struct mData {
	int data;
	int index;
	mData *prev;
	mData *next; 
};

int main();

mData* addList() {
	system("cls");
	
	int count = 0, T = 1;
	mData *newElem;
	mData *tmp = NULL, *head = NULL, *tail = NULL;
	
	while (T) {
		system("cls");
		cout << "Введите размер списка: " << endl;
		count = vvodCifr();
		cout << endl;

		if (count == 0) {
			cout << "Размер списка 0, повторите ввод";
			Sleep(sleepTime);
			continue;
		}
		else if (count == 1) {			
			cout << "Введите элемент под номером 1:	";
			head = new mData;
			head->data = vvodCifr();
			head->index = 1;
			head->next = NULL;
			head->prev = NULL;
			return head;
			break;
		}
		else {
			for (int i = 0; i < count; i++) {
				newElem = new mData;
				newElem->next = head;
				head = newElem;
			}
			
			tmp = head;
			for (int i = 0; i < count; i++) {
				cout << "Введите элемент под номером " << i + 1 << ":	";
				if (tmp->next == NULL) {
					tmp->data = vvodCifr();
					tmp->index = i + 1;
					break;
				}
				tmp->data = vvodCifr();
				tmp->index = i + 1;
				tmp = tmp->next;
				cout << endl;
			}
			tmp = head;
			for (int i = 0; i < count; i++) {
				tmp->prev = tail;
				tail = tmp;
				tmp = tmp->next;
			}
			return head;
			break;
		}		
	}
}

void deleteList(mData *&head) {
	mData *next1;
	while (head) {
		next1 = head->next;
		delete head;
		head = next1;
	}
}

void addElement(mData *&head, mData *&tail) {
	int index = 0, T = 1, s = 0; 
	mData *tmp = NULL;
	mData *kek = NULL;
	tmp = head;
	
	do {
		s++;
		tmp = tmp->next;
	} while (tmp != NULL);
	
	while (T) {
		cout << endl;
		cout << "Введите индекс элемента, после которого хотите добавить новый элемент (для добавления первого элемента введите 0): ";
		index = vvodCifr();
		if ((index > s)) {
			cout << endl;
			cout << "Индекс выходит за рамки списка, повторите ввод";  
			Sleep(sleepTime);

			continue;
		}
		else { T = 0; }
	}
	
	cout << endl;
	tmp = head;
	for (int i = 0; i <= s; i++) {
		if (index == 0){
			
			cout << "Введите элемент: ";
			kek = new mData;
			kek->data = vvodCifr();
			kek->next = head;
			head->prev = kek;
			head = kek;
			kek->prev = NULL;
			break;
		}
		else if (i == index) {
			
			while (tmp->index != index) { tmp = tmp->next; }
			cout << "Введите элемент: ";
			kek = new mData;
			kek->data = vvodCifr();
			kek->next = tmp->next;
			tmp->next = kek;
			kek->prev = tmp;
			kek->next->prev = kek;
			break;
		}
		else if (index == s) {
			cout << "Введите элемент: ";
			kek = new mData;
			kek->data = vvodCifr();
			while (tmp->index != index) { tmp = tmp->next; }
			tmp->next = kek;
			kek->next = NULL;
			tail = kek;
			kek->prev = tmp;
			break;
		}
	}

	tmp = head;
	s = 0;
	do {
		s++;
		tmp = tmp->next;
	} while (tmp != NULL);
 
	tmp = head;
 	for (int i = 0; i < s; i++) {
		tmp->index = i + 1;
		tmp = tmp->next;
 	}
}

void deleteElement(mData *&head, mData *&tail) {
	int T = 1, index, s = 0;
	mData *del;
	mData *tmp = NULL;

	tmp = head;
	do {
		s++;
		tmp = tmp->next;
	} while (tmp != NULL);

	while (T) {
		cout << endl;
		cout << "Введите индекс элемента, который хотите удалить: ";
		index = vvodCifr();
		if ((index > s) or (index == 0)) {
			cout << endl;
			cout << "Индекс выходит за рамки списка, повторите ввод";
			Sleep(sleepTime);
			continue;
		}
		break;
	}

	tmp = head;
	if ((index == 1) and (s == 1)) {
		delete head;
		head = NULL;
		tail = NULL;
	}
	else if (index == 1) {
		tmp = head;
		head = head->next;
		head->prev = NULL;
		delete tmp;
	}
	else if (index == s) {
		while (tmp->index != (index - 1)) { tmp = tmp->next; }
		delete tmp->next;
		tmp->next = NULL;
		tail = tmp;
	}
	else {
		while (tmp->index != (index - 1)) { tmp = tmp->next; }
		del = tmp->next;
		tmp->next = tmp->next->next;
		tmp->next->prev = tmp;
		delete del;
	}

	tmp = head;
	s = 0;
	if (head == NULL) {

	}
	else {
		do {
			s++;
			tmp = tmp->next;
		} while (tmp != NULL);
	}
	tmp = head;
	if (head == NULL) {

	}
	else {
		for (int i = 0; i < s; i++) {
			tmp->index = i + 1;
			tmp = tmp->next;
		}
	}
}

void delGroup(mData *&head, mData *&tail) {
	mData *tmp1 = head, *tmp2 = tail;
	int T = 1, index1, index2, s = 0;

	do {
		s++;
		tmp1 = tmp1->next;
	} while (tmp1 != NULL);
	tmp1 = head;

	while (T) {
		cout << endl;
		cout << endl;
		cout << "Введите индекс элемента, с которого хотите удалить: ";
		index1 = vvodCifr();
		cout << endl;
		cout << "Введите индекс элемента, по который хотите удалить: ";
		index2 = vvodCifr();
		if ((index1 == 0) or (index1 > s) or (index2 == 0) or (index2 > s)) {
			cout << endl;
			cout << "Один или оба индекса введены неверно, повторите ввод";
			Sleep(sleepTime);
			continue;
		}
		T = 0;
	}

	mData *del;
	if (index2 < index1) {
		int c = index1;
		index1 = index2;
		index2 = c;
	}
	if (index1 == index2) {

		if ((index1 == 1) and (s == 1)) {
			delete head;
			head = NULL;
			tail = NULL;
		}
		else if (index1 == 1) {

			head = head->next;
			head->prev = NULL;
			delete tmp1;
		}
		else if (index1 == s) {
			while (tmp1->index != (index1 - 1)) { tmp1 = tmp1->next; }
			delete tmp1->next;
			tmp1->next = NULL;
			tail = tmp1;
		}
		else {
			while (tmp1->index != (index1 - 1)) { tmp1 = tmp1->next; }
			del = tmp1->next;
			tmp1->next = tmp1->next->next;
			tmp1->next->prev = tmp1;
			delete del;
		}
	}
	else {

		if ((index1 == 1) and (index2 == s)) {
			deleteList(head);
		}
		else if (index1 == 1) {

			for (int i = 0; i < (index2 - index1) + 1; i++) {
				del = tmp1;
				tmp1 = tmp1->next;
				delete del;
			}
			head = tmp1;
			head->prev = NULL;
		}
		else if (index2 == s) {
			for (int i = 0; i < (index2 - index1) + 1; i++) {
				del = tmp2;
				tmp2 = tmp2->prev;
				delete del;
			}
			tail = tmp2;
			tail->next = NULL;
		}
		else {
			while (tmp1->index != index1) {
				tmp1 = tmp1->next;
			}
			while (tmp2->index != index2) {
				tmp2 = tmp2->prev;
			}
			tmp2->next->prev = tmp1->prev;
			tmp1->prev->next = tmp2->next;
			for (int i = 0; i < (index2 - index1) + 1; i++) {
				del = tmp1;
				tmp1 = tmp1->next;
				delete del;
			}
		}
	}

	tmp1 = head;
	s = 0;
	if (head == NULL) {

	}
	else {
		do {
			s++;
			tmp1 = tmp1->next;
		} while (tmp1 != NULL);
	}
	tmp1 = head;
	if (head == NULL) {

	}
	else {
		for (int i = 0; i < s; i++) {
			tmp1->index = i + 1;
			tmp1 = tmp1->next;
		}
	}
}

void saveToFile(mData *head) {
	FILE *file;
	mData *tmp;
	int n;

	file = fopen("list.txt", "wb");
	tmp = head;
	while (tmp != NULL) {
		n = tmp->data;
		fwrite(&n, sizeof(int), 1, file);
		tmp = tmp->next;
	}
	fclose(file);
	cout << "\nСписок сохранен";
	Sleep(sleepTime);
}

mData* getFromFile() {
	FILE *file;
	mData *newElem, *head = NULL, *tmp, *tail = NULL;
	int s = 0;

	file = fopen("list.txt", "rb");
	fseek(file, 0, SEEK_END);
	s = ftell(file);
	s /= sizeof(int);
	if (s == 0) {
		cout << "\nФайл пуст";
		Sleep(sleepTime);
	}
	else {
		tmp = head;
		for (int i = 0; i < s; i++) {
			newElem = new mData;
			newElem->next = head;
			head = newElem;
		}
		tmp = head;
		for (int i = 0; i < s; i++) {
			tmp->prev = tail;
			tail = tmp;
			tmp = tmp->next;
		}
		fseek(file, 0, SEEK_SET);
		tmp = head;
		for (int i = 0; i < s; i++) {
			fread(&tmp->data, sizeof(int), 1, file);
			tmp = tmp->next;
		}
		tmp = head;
		for (int i = 0; i < s; i++) {
			tmp->index = i + 1;
			tmp = tmp->next;
		}
	}
	fclose(file);
	return head;
}

void print_mData(mData *head) {
	int s = 0;
	mData *tmp = NULL;
	tmp = head;

	if (head == 0) {
		
	}
	else {
		do {
			s++;
			tmp = tmp->next;
		} while (tmp != NULL);
	}
	tmp = head;
	if (head == 0) {

	}
	else {
		for (int i = 0; i < s; i++) {
			cout << "Элемент " << tmp->index << " - " << tmp->data << endl;
			tmp = tmp->next;
		}
	}
	cout << endl;
	if (head == 0) {
		cout << "Список пуст " << endl;
	}
	cout << "Длина списка:	" << s << endl;
	cout << endl;
		
}

int main() {
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);   
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo); 
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int key = 1, ex = 0, T = 1;
	char ch;
	mData *head = NULL, *tail = NULL, *tmp;
	
	while (T) {
		ex = 0;
		do {
			system("cls");
  			print_mData(head);
			cout << endl;
			cout << "1. Добавить элемент          "; if (key == 1) { cout << "<--"; }
			cout << endl;				          
			cout << "2. Удалить элемент           "; if (key == 2) { cout << "<--"; }
			cout << endl;				          
			cout << "3. Удалить список            "; if (key == 3) { cout << "<--"; }
			cout << endl;				          
			cout << "4. Создать список            "; if (key == 4) { cout << "<--"; }
			cout << endl;
			cout << "5. Удалить группу элементов  "; if (key == 5) { cout << "<--"; }
			cout << endl;
 			cout << "6. Сохранить список в файл   "; if (key == 6) { cout << "<--"; }
			cout << endl;
			cout << "7. Считать список из файла   "; if (key == 7) { cout << "<--"; }
			cout << endl;
			cout << endl;
			cout << "Выход - escape";
			cout << endl;

			ch = _getch();
			if (ch == 'а') {
				ch = _getch();
			}
			switch (ch)
			{
			case '1': key = 1; ex = 1; break; 
			case '2': key = 2; ex = 1; break;
			case '3': key = 3; ex = 1; break;
			case '4': key = 4; ex = 1; break;
			case '5': key = 5; ex = 1; break;
			case '6': key = 6; ex = 1; break;
			case '7': key = 7; ex = 1; break;
			case keyUp: if (key > 1) key--; break;
			case keyDown: if (key < 7) key++; break;
			case enter: ex = 1; break;
			case escape: exit(0); break;
			default:  break;
			}
		} while (ex == 0);

		switch (key) {
		case 1: {
			if (head == 0) { cout << "\nНеобходимо создать список"; Sleep(sleepTime); break; }
			else {
				addElement(head, tail);
				break;
			}
		}
		case 2: {
			if (head == 0) { cout << "\nНеобходимо создать список"; Sleep(sleepTime); break; }
			else {
				deleteElement(head, tail);
				break;
			}
		}
		case 3: {
			if (head == 0) { cout << "\nНеобходимо создать список"; Sleep(sleepTime); break; }
			else {
				deleteList(head); 
				break;
			}
		}
		case 4: {
			if (head != 0){ cout << "\nСписок уже создан, сначала удалите старый список"; Sleep(sleepTime); break; }
			else {
				head = addList();
				tmp = head;
				while (tmp->next != NULL) {
					tmp = tmp->next;
				}
				tail = tmp;
				break;
			}
		case 5:
			if (head == 0) { cout << "\nНеобходимо создать список"; Sleep(sleepTime); break; }
			else {
				delGroup(head, tail);
				break;
			}
		case 6:
			if (head == 0) { cout << "\nНеобходимо создать список"; Sleep(sleepTime); break; }
			else {
				saveToFile(head);
				break;
			}
		case 7:
			if (head != 0) { cout << "\nСписок уже создан, сначала удалите старый список"; Sleep(sleepTime); break; }
			else {
				head = getFromFile();
				tmp = head;
				if (tmp != NULL) {
					while (tmp->next != NULL) {
						tmp = tmp->next;
					}
					tail = tmp;
				}
				break;
			}
		}
		default: break;
		}
	}

	system("pause");
	return 0;
}