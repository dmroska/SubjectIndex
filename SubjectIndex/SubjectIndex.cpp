#include <iostream> 
#include <string> 
#include <windows.h>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>

using namespace std;

//������:
/*
1) ������������ ����������� ��������� +
1. � ���������� + � �������
2. �� ����� +
2)����� ����������� ��������� +
3)���������� ����������� ��������� � ���� +
4)������ ������� ������� ��� ��������� ����� +
5)���������� ����� � ���������� ���������  +
6)�������� ����� �� ���������� ���������� +
7)�������� ����� ����������� ��������� +
*/

//��������� �����
struct Word
{
	string word; //�����
	vector<int> a; //������ �������, ��� ����������� �����
};

class SubjectIndex //������ ����� ���������� ���������
{   
private:
	//��������� ���� ������
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

	//1)������������ ����������� ���������
	void FromFile(); //������������ �� �����
	void FromTheKeyboard(); //������������ � ����������
	void HelpFromTheKeyboard(ifstream &in); //��������� ����� ���� 

	//2)����� ����������� ���������
	void Print_2();
	void Print(Node*root); //����������� ����� ����������� ���������

	//3)���������� ����������� ��������� � ����
	void SaveFile();
	void Save1(ofstream &fout, Node* root); //����������� ���������� ����������� ��������� � ����

	//4)����� ������� ������� ��� ��������� �����
	void Search();

	//5)���������� ����� � ���������� ���������.
	void AddNode2();  //���������� ����� � ���������� ��������� ����� ����������
	void AddNode(Word *w); //���������� �����

    //6)�������� ����� �� ���������� ���������
	void Delete();
	void Delete2(string w, Node*&root); //����������� ��������

	//7)�������� ����� ����������� ���������
	void DestroySubjectIndex1(Node*& root);

	void MenuFormationOfTheSubjectIndex(); //���� ������������ ����������� ���������
public:
	//�����������, ����������
	SubjectIndex(); //�����������
	~SubjectIndex(); //����������
	void DestroySubjectIndex(Node*& root);

	//����
	void Menu(); //������� ����
	
};

//�����������, ����������
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

//1)������������ ����������� ���������
void SubjectIndex::FromFile()
	{
		string path = "1.txt";

		ifstream in;
		in.open(path, ofstream::app);

		if (!in.is_open())
		{
			cout << "������ �������� �����!";
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
		cout << "���������� ��������� �����������";
	}
void SubjectIndex::FromTheKeyboard()
	{
	cout << "������������ ����������� ���������" << endl;
	cout << "������� ����� ����?" << endl; 
	int size;
	cout << "�����: "; cin >> size; cout << endl;

	cout << "����� �����: ����� � ����� ������ ������ ������� � ���� ������" << endl << endl;

	string path= "2.txt";

		ofstream fout;
		fout.open(path); 
		if (!fout.is_open())
		{
			cout << "������ �������� �����!";
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
		cout << endl << "����� ������� � ����: \"2.txt\"" << endl;

		ifstream in;
		in.open(path);
		HelpFromTheKeyboard(in); //����������������
		in.close();
		cout << "���������� ��������� �����������";
	}
void SubjectIndex::HelpFromTheKeyboard(ifstream &in)
{
	if (!in.is_open())
	{
		cout << "������ �������� �����!";
	}
	else
		while (!in.eof())
		{
			Word* w = new Word;
			string str1;
			str1 = "";

			in >> str1; //������ �����
			w->word = str1; //���������� ����� � ��������� �����
			string str;
			str = "";
			getline(in, str); //�tr - ������, ��� �������� �����

			//��������� ������ � ������� � ������ �����
			istringstream ss(str); 
			int mas[10];
			int n = 0;
			while (ss >> mas[n++]);
			n--;

			for (int i = 0; i < n; i++) //������� ������� ����� � ������ ��������� �����
				w->a.insert(w->a.end(), mas[i]);
			AddNode(w);//���������� ����� � ������
		}
}

//2)����� ����������� ��������
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

//3)���������� ����������� ��������� � ����
void SubjectIndex::SaveFile()
{
	ofstream fout;
	fout.open("Header.h"); 
	Save1(fout, mainroot);
	fout.close();
	cout << endl << "���������� ��������� ������� ������� � ����: \"Header.h\"";
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

//4)����� ������� ������� ��� ��������� �����
void SubjectIndex::Search()
{
	string str;
	cout << "������� ������� �����: ";
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
				cout << "����� ����� ���� � ���������� ���������";
				return;
			}
			else
				cur = cur->left;
		}
		else
			if (cur->right == NULL)
			{
				cout << "����� ����� ���� � ���������� ���������";
				return;
			}
			else
				cur = cur->right;
	}
}

//5)���������� ����� � ���������� ���������. 
void SubjectIndex::AddNode(Word *w)
{
	if (mainroot == NULL)
	{
		mainroot = new Node(w);
		return; //����� �� �������
	}
	Node *cur = mainroot;
	//��������� ���� (�������)
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
	cout << "������� �����, ������� ������ ��������: ";
	cin >> w1->word; cout << endl;
	cout << "������� ���������� ��������, �� ������� ����� �����: ";
	int z;
	cin >> z; cout << endl;
	int x;
	for (int i = 0; i < z; i++)
	{
		cout << "������� ����� ��������, �� ������� ����� �����: ";
		cin >> x;
		w1->a.insert(w1->a.end(), x);
	}
	AddNode(w1);
}

//6)�������� ����� �� ���������� ���������.
void SubjectIndex::Delete()
{
	string str;
	cout << "������� �����, ������� ������ �������: ";
	cin >> str; cout << endl;
	
	Delete2(str, mainroot);
}
void SubjectIndex::Delete2(string w, Node*&root)
{
	if (root == NULL) 
	{
		cout << "������� ����� ����  � ���������� ���������!";
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

//7)�������� ����� ����������� ���������.
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

//���� (�������� � �������� ������ - system("CLS");)
void SubjectIndex::Menu()
{
	
	cout << "" << endl;
		cout << "                     _____________________________________________________" << endl;
		cout << "                    |                                                     |"<< endl;
		cout << "                    |                 �������� ��������                   |"<< endl;
		cout << "                    |                                                     |"<< endl;
		cout << "                    | - 1 -  ������������ ����������� ���������.          |"<< endl;
		cout << "                    | - 2 -  ����� ����������� ���������.                 |"<< endl;
		cout << "                    | - 3 -  ���������e ����������� ��������� � ����.     |"<< endl;
		cout << "                    | - 4 -  ������ ������� ������� ��� ��������� �����.  |"<< endl;
		cout << "                    | - 5 -  ���������� ����� � ���������� ���������.     |"<< endl;
		cout << "                    | - 6 -  �������� ����� �� ���������� ���������.      |"<< endl;
		cout << "                    | - 7 -  �������� ����� ����������� ���������.        |"<< endl;
		cout << "                    | - 0 -  ���������� ������.                           |"<< endl;
		cout << "                    |_____________________________________________________|"<< endl;
		cout << "" << endl;
		cout << "��� �����: ";
		
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
	cout << "                                     |  �������� ��������  |"<< endl;
	cout << "                                     |                     |"<< endl;
	cout << "                                     | - 1 -  � ����������.|"<< endl;
	cout << "                                     | - 2 -  �� �����.    |"<< endl;
	cout << "                                     | - 0 -  �����.       |"<< endl;
	cout << "                                     |_____________________|"<< endl;
	cout << "" << endl;
	cout << "��� �����: ";

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
