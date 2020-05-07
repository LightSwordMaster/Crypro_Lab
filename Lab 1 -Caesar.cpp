
/*
  * Лабораторная 1 - шифр цезаря
  * File:   main.cpp
  * Author: spiryanin.2015
  *
  * Created on 30 апреля 2020 г., 2:14
  */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

string encode(string str_message, int key)     
// Функция для кодирования сообщений на русском и английском
{

	char ch;
	for (int j = 0; str_message[j] != '\0'; ++j) {

		ch = str_message[j];

		if (ch >= 'a' && ch <= 'z') {
			str_message[j] = char(int(ch + key - 'a') % 26 + 'a');
		}
		if (ch >= 'A' && ch <= 'Z') {
			str_message[j] = char(int(ch + key - 'A') % 26 + 'A');
		}
		if (ch >= -32 && ch <= -1) {  // диапазон в кодировке консоли для строчных русских букв
			ch = ch + 32;
			str_message[j] = char('а' + (ch + key) % 32);
		}
		if (ch >= -64 && ch <= -33) { // диапазон в кодировке консоли для заглавных русских букв
			ch = ch + 64;
			str_message[j] = char('А' + (ch + key) % 32);
		}


	}
	return str_message;
}

string decode(string str_message, int key)
// функция для декодирования сообщения на русском и английском
{
	char ch;
	for (int j = 0; j<str_message.length(); ++j) {

		ch = str_message[j];

		if (ch >= 'a' && ch <= 'z') {
			str_message[j] = char(int(ch + 26 - key - 'a') % 26 + 'a');
		}
		else if (ch >= 'A' && ch <= 'Z') {
			str_message[j] = char(int(ch + 26 -  key - 'A') % 26 + 'A');
		}
		else if (ch >= -32 && ch <= -1) { // диапазон в кодировке консоли для строчных русских букв
			ch = ch + 32;
			str_message[j] = char('а' + (ch + 32 - key) % 32);
		}
		else if (ch >= -64 && ch <= -33) { // диапазон в кодировке консоли для заглавных русских букв
			ch = ch + 64;
			str_message[j] = char('А' + (ch + 32 - key) % 32);
		}

	}
	return str_message;
}


/*
 *
 */
int main(int argc, char** argv) {
	ifstream in_file("input.txt");
	ofstream out_file("output.txt");
	int mode=1;   //переменная для выбора режима работы программы: кодирование/декодирование и д.р.
	string inp;
	int  key;

	SetConsoleCP(1251);            // поддержка русского в консоли на ввод и вывод
	SetConsoleOutputCP(1251);


while(mode!=0)
{
	in_file.clear();                 //  т.к. функция может вызываться многократно, то нужно очистить флаги (доходим до eof) 
	in_file.seekg(0, ios::beg);      // и вернуться в начало
	cout << "Type 1 to encode string" << endl;
	cout << "Type 2 to decode string" << endl;
	cout << "Type 3 to encode file" << endl;
	cout << "Type 4 to decode file" << endl;
	cout << "Type 5 to brute force string" << endl;

	cin >> mode;
	switch (mode)
	{
	case 1:  // кодирование по ключу
	{
		cout << "Enter a message to encrypt: " << endl;
		cin >> inp;
		cout << "Enter key: " << endl;
		cin >> key;
		cout << "Encrypted message: ";
		cout << encode(inp, key) << endl;

	}
	break;
	case 2: // декодирование по ключу
	{
		cout << "Enter a message to decrypt: " << endl;
		cin >> inp;
		cout << "Enter key: " << endl;
		cin >> key;
		cout << "Decrypted message: ";
		cout << decode(inp, key) << endl;

	}
	break;
	case 3: // кодирование файла
	{
		cout << "Enter key: " << endl;
		cin >> key;
		if (in_file.is_open())
		{
			while (std::getline(in_file, inp))
			{
				out_file << encode(inp, key) << endl;
			}
		}
	}
	break;
	case 4: //декодирование файла
	{
		cout << "Enter key: " << endl;
		cin >> key;
		if (in_file.is_open())
		{
			while (std::getline(in_file, inp))
			{
				out_file << decode(inp, key) << endl;
			}
		}
	}
	break;
	case 5: // брут форс строки 
	{
		int n = 26; // длина английского алфавита
		cout << "Enter a message to decrypt: " << endl;
		cin >> inp;
		cout << "Possible messages" << endl;
		if (inp[0] >= -128 && inp[0] <= -17) // диапазон символов для русского
			n = 32;                          // алфавит без ё, т.к. ё стоит отдельно в таблице символов
		for (int i = 1; i <= n; i++)
			cout << decode(inp, i) << endl;
	}
	break;


	}

	cout << "Type 0 to exit or any other number to continue" << endl;
	cin >> mode;
}
	in_file.close();
	out_file.close();
	return 0;
}

