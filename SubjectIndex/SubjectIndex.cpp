#include <iostream> 
#include <string> 
#include <windows.h>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>

using namespace std;

//методы:
/*
1) формирование предметного указателя +
1. с клавиатуры + с костылём
2. из файла +
2)Вывод предметного указателя +
3)сохранения предметного указателя в файл +
4)вывода номеров страниц для заданного слова +
5)добавление слова в предметный указатель  +
6)удаление слова из предметого указателья +
7)удаление всего пердметного указателя +
*/

//структура слова
struct Word
{
	string word; //слово
	vector<int> a; //номера страниц, где встречается слово
};

class SubjectIndex //создаю класс предметный указатель
{   
private:
	//структура узла дерева
	struct Node 
	{
		Word* word; 

		Node* left;
		Node* right;

		Node(Word* word)
		{
			this->word = word;
			left = right = NULL;
		}
	};

	Node* mainroot;

	//1)формирование предметного указателя
	void FromFile(); //формирование из файла
	void FromTheKeyboard(); //формирование с клавиатуры
	void HelpFromTheKeyboard(ifstream &in); //обработка через файл 

	//2)вывод предметного указателя
	void Print_2();
	void Print(Node*root); //рекурсивный вывод предметного указателя

	//3)сохранение предметного указателя в файл
	void SaveFile();
	void Save1(ofstream &fout, Node* root); //рекурсивное сохранение предметного указателя в файл

	//4)вывод номеров страниц для заданного слова
	void Search();

	//5)добавление слова в предметный указатель.
	void AddNode2();  //добавление слова в предметный указатель через клавиатуру
	void AddNode(Word *w); //добавление слова

    //6)удаление слова из предметого указателя
	void Delete();
	void Delete2(string w, Node*&root); //рекурсивное удаление

	//7)удаление всего пердметного указателя
	void DestroySubjectIndex1(Node*& root);

	void MenuFormationOfTheSubjectIndex(); //меню формирование предметного указателя
public:
	//конструктор, деструктор
	SubjectIndex(); //конструктор
	~SubjectIndex(); //диструктор
	void DestroySubjectIndex(Node*& root);

	//меню
	void Menu(); //главное меню
	
};

//конструктор, деструктор
SubjectIndex::SubjectIndex()
{
	mainroot = NULL;
}
SubjectIndex::~SubjectIndex()
{
	DestroySubjectIndex(mainroot);
}
void SubjectIndex::DestroySubjectIndex(Node*& root)
{
	if (root != NULL)
	{
		DestroySubjectIndex(root->right);
		DestroySubjectIndex(root->left);
	}
	delete root;
}

//1)формирование предметного указателя
void SubjectIndex::FromFile()
	{
		string path = "1.txt";

		ifstream in;
		in.open(path, ofstream::app);

		if (!in.is_open())
		{
			cout << "Ошибка открытия файла!";
		}
		else
		{
			
			while (!in.eof())
			{
				Word* w = new Word;
				string str1;
				str1  = "";

				in >> str1;
				w->word = str1;
				string str;
				str = "";
				getline(in, str); 

				istringstream ss(str);
				int mas[10];
				int n = 0;
				while (ss>>mas[n++]);
				n--;
				for (int i = 0; i < n; i++)

				w->a.insert(w->a.end(), mas[i]);
				AddNode(w);
			}
		}
		in.close();
		cout << "Предметный указатель сформирован";
	}
void SubjectIndex::FromTheKeyboard()
	{
	cout << "Формирование предметного указателя" << endl;
	cout << "Сколько будет слов?" << endl; 
	int size;
	cout << "Ответ: "; cin >> size; cout << endl;

	cout << "Форма ввода: слово и через пробел номера страниц с этим словом" << endl << endl;

	string path= "2.txt";

		ofstream fout;
		fout.open(path); 
		if (!fout.is_open())
		{
			cout << "Ошибка открытия файла!";
		}
		else
		{
			for (int i = 0; i < size+1; i++)
			{
				if (i != 0)
					fout << endl;
				char str[256];
				cin.getline(str, 256);
    
				fout << str;
			}
		}

		fout.close();
		cout << endl << "Текст сохранён в файл: \"2.txt\"" << endl;

		ifstream in;
		in.open(path);
		HelpFromTheKeyboard(in); //потомучтокостыль
		in.close();
		cout << "Предметный указатель сформирован";
	}
void SubjectIndex::HelpFromTheKeyboard(ifstream &in)
{
	if (!in.is_open())
	{
		cout << "Ошибка открытия файла!";
	}
	else
		while (!in.eof())
		{
			Word* w = new Word;
			string str1;
			str1 = "";

			in >> str1; //ввывод слова
			w->word = str1; //сохранение слова в структуру слова
			string str;
			str = "";
			getline(in, str); //сtr - строка, где хранятся числа

			//обработка строки с числами в массив чисел
			istringstream ss(str); 
			int mas[10];
			int n = 0;
			while (ss >> mas[n++]);
			n--;

			for (int i = 0; i < n; i++) //перевод массива чисел в вектор структуры слова
				w->a.insert(w->a.end(), mas[i]);
			AddNode(w);//добавление слова в дерево
		}
}

//2)вывод предметного указател
void SubjectIndex::Print_2()
{
	Print(mainroot);
}
void SubjectIndex::Print(Node*root)
{
	if (root != NULL)
	{
		Print(root->left);
		cout << (root->word->word) << " ";
		for (int i = 0; i < root->word->a.size(); i++)
		{
			if (i != 0) cout << " ";
			cout << root->word->a[i];

		}
		cout << endl;
		Print(root->right);
	}
}

//3)сохранение предметного указателя в файл
void SubjectIndex::SaveFile()
{
	ofstream fout;
	fout.open("Header.h"); 
	Save1(fout, mainroot);
	fout.close();
	cout << endl << "Предметный указатель успешно сохранён в файл: \"Header.h\"";
}
void SubjectIndex::Save1(ofstream &fout,Node* root)
{
	if (root != NULL)
	{
		Save1(fout, root->left);
		fout << (root->word->word) << " ";
		for (int i = 0; i < root->word->a.size(); i++)
		{
			if (i != 0) fout << ", ";
			fout << root->word->a[i];
		}
		fout << endl;
		Save1(fout, root->right);
	}
}

//4)вывод номеров страниц для заданного слова
void SubjectIndex::Search()
{
	string str;
	cout << "Введите искомое слово: ";
	cin >> str;
	Node *cur = mainroot;
	vector<int> help;

	while (true)
	{
		if (cur->word->word == str)
		{
			help = cur->word->a;
			for (int j = 0; j < help.size(); j++)
				cout << help[j] << ", ";
			return;
		}

		if (cur->word->word > str)
		{
			if (cur->left == NULL)
			{
				cout << "Этого слова нету в предметном указателе";
				return;
			}
			else
				cur = cur->left;
		}
		else
			if (cur->right == NULL)
			{
				cout << "Этого слова нету в предметном указателе";
				return;
			}
			else
				cur = cur->right;
	}
}

//5)добавление слова в предметный указатель. 
void SubjectIndex::AddNode(Word *w)
{
	if (mainroot == NULL)
	{
		mainroot = new Node(w);
		return; //выход из функции
	}
	Node *cur = mainroot;
	//сравнение слов (сделать)
	while (true)
	{
		if (cur->word->word == w->word)
		{
			for (int i = 0; i < w->a.size(); i++)
			{
				cur->word->a.insert(cur->word->a.end(), w->a[i]);
			}
			return;
		}

		if (cur->word->word > w->word)
		{
			if (cur->left == NULL)
			{
				cur->left = new Node(w);
				break;
			}
			else
				cur = cur->left;
		}
		else
			if (cur->right == NULL)
			{
				cur->right = new Node(w);
				break;
			}
			else
				cur = cur->right;
	}
}
void SubjectIndex::AddNode2()
{
	Word* w1 = new Word;
	cout << "Введите слово, которое хотите добавить: ";
	cin >> w1->word; cout << endl;
	cout << "Введите количество страницы, на которых будет слово: ";
	int z;
	cin >> z; cout << endl;
	int x;
	for (int i = 0; i < z; i++)
	{
		cout << "Введите номер страницы, на которой будет слово: ";
		cin >> x;
		w1->a.insert(w1->a.end(), x);
	}
	AddNode(w1);
}

//6)удаление слова из предметого указателя.
void SubjectIndex::Delete()
{
	string str;
	cout << "Введите слово, которое хотите удалить: ";
	cin >> str; cout << endl;
	
	Delete2(str, mainroot);
}
void SubjectIndex::Delete2(string w, Node*&root)
{
	if (root == NULL) 
	{
		cout << "Данного слова нету  в предметном указателе!";
		return;
	}
		
	if (root->word->word == w)
	{
		Node* help = root;
		if (root->right == NULL)
		{
			root = root->left;
			delete help;
		}
		else
			if (root->left == NULL)
			{
				root = root->right;
				delete help;
			}
			else
			{
				Node* r = root->right;
				if (r->left == NULL)
				{
					r->left = root->left;
					root = r;
					delete help;
				}
				else
				{
					Node* p = r->left;
					while (p->left != NULL)
					{
						p = p->left;
						r = r->left;
					}
					help->word = p->word;
					r->left = p->right;
					delete p;
				}
			}

	}
	else
		if (root->word->word > w)
			Delete2(w, root->left);
		else
			Delete2(w, root->right);
}

//7)удаление всего пердметного указателя.
void SubjectIndex::DestroySubjectIndex1(Node*& root)
{
	if (root->right != NULL)
	{
		DestroySubjectIndex(root->right);
	}

	if (root->left != NULL)
	{
		DestroySubjectIndex(root->left);
	}

	delete root;
	root = NULL;
}

//меню (поиграть с очисткой экрана - system("CLS");)
void SubjectIndex::Menu()
{
	
	cout << "" << endl;
		cout << "                     _____________________________________________________" << endl;
		cout << "                    |                                                     |"<< endl;
		cout << "                    |                 Выберете действие                   |"<< endl;
		cout << "                    |                                                     |"<< endl;
		cout << "                    | - 1 -  формирование предметного указателя.          |"<< endl;
		cout << "                    | - 2 -  вывод предметного указателя.                 |"<< endl;
		cout << "                    | - 3 -  сохранениe предметного указателя в файл.     |"<< endl;
		cout << "                    | - 4 -  вывода номеров страниц для заданного слова.  |"<< endl;
		cout << "                    | - 5 -  добавление слова в предметный указатель.     |"<< endl;
		cout << "                    | - 6 -  удаление слова из предметого указателя.      |"<< endl;
		cout << "                    | - 7 -  удаление всего пердметного указателя.        |"<< endl;
		cout << "                    | - 0 -  завершение работы.                           |"<< endl;
		cout << "                    |_____________________________________________________|"<< endl;
		cout << "" << endl;
		cout << "Ваш ответ: ";
		
		char a;
		cin >> a;
	
		

		cout << endl;
		switch (a) {
		case '1': MenuFormationOfTheSubjectIndex(); break;
		case '2': Print_2();  Menu(); break;
		case '3': SaveFile(); Menu(); break;
		case '4': Search(); Menu(); break; 
		case '5': AddNode2(); Menu(); break; 
		case '6': Delete(); Menu(); break; 
		case '7': DestroySubjectIndex1(mainroot); Menu(); break;
		case '0': break;
		}
}
void SubjectIndex::MenuFormationOfTheSubjectIndex()
{
	system("CLS");
	cout << "" << endl;
	cout << "                                      _____________________" << endl;
	cout << "                                     |                     |"<< endl;
	cout << "                                     |  Выберете действие  |"<< endl;
	cout << "                                     |                     |"<< endl;
	cout << "                                     | - 1 -  с клавиатуры.|"<< endl;
	cout << "                                     | - 2 -  из файла.    |"<< endl;
	cout << "                                     | - 0 -  назад.       |"<< endl;
	cout << "                                     |_____________________|"<< endl;
	cout << "" << endl;
	cout << "Ваш ответ: ";

	char b;
	cin >> b;

	cout << endl;
	switch (b)
	{
	case '1': FromTheKeyboard(); Menu(); break;
	case '2': FromFile(); Menu(); break;
	case '0': Menu(); break;
	}
}	

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	SubjectIndex s;
	s.Menu();
	system("pause");
	return 0;
}
