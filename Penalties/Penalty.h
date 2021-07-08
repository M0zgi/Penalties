#pragma once
#include"BTree.h"
#include"List.h"
#include<string>
#include<iomanip>
#include<fstream>



class Protokol
{
	string numTS;
	string date;
	string numPPN;
	string tag;
	int sum;
	bool pay = false;

public:
	Protokol() {}
	string getNumTS() { return numTS; }
	string getdate() { return date; }
	string getnumPPN() { return numPPN; }
	string gettag() { return tag; }
	int getsum() { return sum; }
	bool getpay() { return pay; }

	void setNumTS(string setNumTS) { numTS = setNumTS; }
	void setdate(string setdate) { date = setdate; }
	void setnumPPN(string setnumPPN) { numPPN = setnumPPN; }
	void settag(string settag) { tag = settag; }
	void setsum(int setsum) { sum = setsum; }
	void setpay(int setpay) { pay = setpay; }


	friend ostream& operator << (ostream& out, const Protokol& p);
	friend ostream& operator << (ostream& out, const Protokol* p);
	friend ofstream& operator << (ofstream& out, const Protokol* p);
	friend istream& operator >> (istream& in, Protokol& p);
	friend istream& operator >> (istream& in, Protokol* p);

};


ostream& operator<<(ostream& out, const Protokol& p)
{
	out << p.numTS << "  " << p.date << "    " << setw(13) << left << p.numPPN << setw(58) << p.tag << setw(12) << p.sum
		<< ((p.pay) ? "Оплачено" : "Не оплачено") << endl;
	return out;
}

ostream& operator<<(ostream& out, const Protokol* p)
{

	out  << left << " | " << setw(11) << p->numTS << "|"<< setw(12) << p->date << "| " << setw(15) << p->numPPN << "| "<< setw(56) << p->tag << "| " << setw(11) << p->sum
		<< "| "<< setw(16) << ((p->pay) ? "Оплачено" : "Не оплачено") << "|"<< endl;
	out << " +------------+------------+----------------+---------------------------------------------------------+------------+-----------------+\n";
	return out;
}

inline ofstream& operator<<(ofstream& out, const Protokol* p)
{
	static bool t = false;

	if (!t)
	{
		out << p->numTS << endl << p->date << endl << p->numPPN << endl << p->tag << endl << p->sum
			<< endl << ((p->pay) ? "1" : "0");
		t = true;
	}
	
	else
		out << endl << p->numTS << endl << p->date << endl << p->numPPN << endl << p->tag << endl << p->sum
		<< endl << ((p->pay) ? "1" : "0");

	return out;
}


inline istream& operator>>(istream& in, Protokol& p)
{
	cout << "Номер ТС   : "; getline(in, p.numTS);
	cout << "Дата       : "; getline(in, p.date);
	cout << "Номер КУоАП: "; getline(in, p.numPPN);
	cout << "Описание   : "; getline(in, p.tag);
	cout << "Сумма      : "; in >> p.sum;
	in.ignore();
	return in;
}

inline istream& operator>>(istream& in, Protokol* p)
{
	cout << "Номер ТС   : "; getline(in, p->numTS);
	cout << "Дата       : "; getline(in, p->date);
	cout << "Номер КУоАП: "; getline(in, p->numPPN);
	cout << "Описание   : "; getline(in, p->tag);
	cout << "Сумма      : "; in >> p->sum;
	in.ignore();
	return in;
}

class BasePenalty
{
	BTree<string, List<Protokol*>> base;

public:
	void menu();
	void addProtokol();
	void addProtokolFile();
	void print();
	void saveToFile();
	void printNum();
	void printRange();
	void find();
	void setPay();
};

void BasePenalty::menu()
{		
	ifstream innom("penalty.txt");

	if (innom.is_open())
	{
		while (!innom.eof())
		{
			char* buff = new char[80];
			Protokol* prot = new Protokol;
			int s;
			innom.getline(buff, 80);
			prot->setNumTS(buff);
			innom.getline(buff, 80);
			prot->setdate(buff);
			innom.getline(buff, 80);
			prot->setnumPPN(buff);
			innom.getline(buff, 80);
			prot->settag(buff);
			innom.getline(buff, 80);
			s = atoi(buff);
			prot->setsum(s);
			innom.getline(buff, 80);
			s = atoi(buff);
			prot->setpay(s);

			List<Protokol*>* list = base.get(prot->getNumTS());
			if (!list)
			{
				List<Protokol*> newList;
				newList.push_front(prot);
				base.push_r(prot->getNumTS(), newList);
			
			}
			else
			{
				list->push_front(prot);			
			}
			
		}

		cout << "Протоколы загржены из файла" << endl;
		system("pause");
	}
	
	do
	{
		system("cls");
		cout << "1. Добавить протокол" << endl;
		cout << "2. Печать всех" << endl;
		cout << "3. Поиск по номеру ТС" << endl;
		cout << "4. Установть оплату" << endl;
		cout << "5. Печать по диапазону номеров" << endl;
		cout << "0. Выход" << endl;
		int n;
		cin >> n;
		cin.ignore();
		switch (n)
		{
		case 1:
			addProtokol();
			break;
		case 2:
	
			system("cls");
			gotoxy(1, 0);
			cout << "+------------+------------+----------------+---------------------------------------------------------+------------+-----------------+\n";
			gotoxy(1, 1);
			cout << "|  Номер ТС  |    Дата    |   Номер КУоАП  |                      Описание                           |    Сумма   |  Статус оплаты  |\n";
			gotoxy(1, 2);
			cout << "+------------+------------+----------------+---------------------------------------------------------+------------+-----------------+\n";
			print();
			break;
		case 3:
			system("cls");
			printNum();
			break;
		case 5:
			printRange();
			break;
		case 0:
		{
			//addProtokolFile();
			base.printF();
			exit(0);
		}
			
		default:
			break;
		}

	} while (true);

}

inline void BasePenalty::addProtokol()
{
	cout << " Добавить протокол:" << endl;
	cout << "------------------------" << endl;
	Protokol* prot = new Protokol;
	cin >> prot;
	List<Protokol*>* list = base.get(prot->getNumTS());
	if (!list)
	{
		cout << "Данный номер ТС отсутсвует в базе и будет добавлен" << endl;
		List<Protokol*> newList;
		newList.push_front(prot);
		base.push_r(prot->getNumTS(), newList);

		ofstream fout;
		fout.open("penalty.txt", ios::app);

		if (fout.is_open())
		{
			fout << endl;
			fout << prot->getNumTS() << "\n";
			fout << prot->getdate() << "\n";
			fout << prot->getnumPPN() << "\n";
			fout << prot->gettag() << "\n";
			fout << prot->getsum() << "\n";
			fout << prot->getpay();
		}

		fout.close();
	}
	else
	{
		list->push_front(prot);
		ofstream fout;
		fout.open("penalty.txt", ios::app);
			
		if (fout.is_open())
			{		
			fout << endl;
			fout << prot->getNumTS() << "\n";
			fout << prot->getdate() << "\n";
			fout << prot->getnumPPN() << "\n";
			fout << prot->gettag() << "\n";
			fout << prot->getsum() << "\n";
			fout << prot->getpay();
			}
			
		fout.close();
	}
	cout << "Новый протокол добавлен" << endl;
}

inline void BasePenalty::addProtokolFile()
{
	
	//Protokol* prot = nullptr;

	//List<Protokol*> newList;
	
	//base.first(newList);

	List<Protokol*> *newList = base.first();

	cout << (*newList).getLength();

	/*for (size_t i = 0; i < newList.getLength(); i++)
	{
		prot = newList.operator[](i);

		ofstream fout;
		fout.open("penalty.txt");

		if (fout.is_open())
		{
			fout << endl;
			fout << prot->getNumTS() << "\n";
			fout << prot->getdate() << "\n";
			fout << prot->getnumPPN() << "\n";
			fout << prot->gettag() << "\n";
			fout << prot->getsum() << "\n";
			fout << prot->getpay();
		}

		fout.close();
	}*/
}

inline void BasePenalty::print()
{
	base.print();
	cout << endl;
	system("pause");
}

inline void BasePenalty::saveToFile()
{

}

inline void BasePenalty::printNum()
{
	cout << " Поиск протокола по номеру ТС:" << endl;
	cout << "------------------------" << endl;
	string num;
	cout << "Номер ТС: "; getline(cin, num);	
	List<Protokol*>* list = base.get(num);

	if (list)
	{
		gotoxy(1, 6);
		cout << "+------------+------------+----------------+---------------------------------------------------------+------------+-----------------+\n";
		gotoxy(1, 7);
		cout << "|  Номер ТС  |    Дата    |   Номер КУоАП  |                      Описание                           |    Сумма   |  Статус оплаты  |\n";
		gotoxy(1, 8);
		cout << "+------------+------------+----------------+---------------------------------------------------------+------------+-----------------+\n";
		list->print();
	}

	else
		cout << "Протокол по номер ТС " << num << " не найдено" << endl;

	system("pause");
}

inline void BasePenalty::printRange()
{
	cout << " Поиск протокола по диапазону номеров ТС:" << endl;
	cout << "------------------------" << endl;
	string num, num2;
	cout << "Начальный номер ТС: "; getline(cin, num);
	cout << "Конечный номер ТС: "; getline(cin, num2);

	//const unsigned SHIFT_ON_NUMBER = 2;
	//int size = num.length();
	//char *buffCh = new char[size];

	//for (size_t i = 0; i < size; i++)
	//{
	//	buffCh[i] = num[i];

	//	cout << buffCh[i];
	//}

	//buffCh[size] = '\0';

	//cout << endl;
	//while (buffCh)
	//{
	//	//num.erase(prev(num.end()));
	//	cout << buffCh << endl;

	//	buffCh -= 1;
	//}

	

	system("pause");
}