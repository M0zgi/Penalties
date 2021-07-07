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
	friend istream& operator >> (istream& in, Protokol& p);
	friend istream& operator >> (istream& in, Protokol* p);

};


ostream& operator<<(ostream& out, const Protokol& p)
{
	out << p.numTS << "  " << p.date << "  " << setw(6) << left << p.numPPN << setw(20) << p.tag << setw(6) << p.sum
		<< ((p.pay) ? "Оплачено" : "Не оплачено") << endl;
	return out;
}

ostream& operator<<(ostream& out, const Protokol* p)
{
	out << p->numTS << "  " << p->date << "  " << setw(6) << left << p->numPPN << setw(20) << p->tag << setw(6) << p->sum
		<< ((p->pay) ? "Оплачено" : "Не оплачено") << endl;
	return out;
}

inline istream& operator>>(istream& in, Protokol& p)
{
	cout << "Номер ТС: "; getline(in, p.numTS);
	cout << "Дата    : "; getline(in, p.date);
	cout << "Номер ПП: "; getline(in, p.numPPN);
	cout << "Описание: "; getline(in, p.tag);
	cout << "Сумма   : "; in >> p.sum;
	in.ignore();
	return in;
}

inline istream& operator>>(istream& in, Protokol* p)
{
	cout << "Номер ТС: "; getline(in, p->numTS);
	cout << "Дата    : "; getline(in, p->date);
	cout << "Номер ПП: "; getline(in, p->numPPN);
	cout << "Описание: "; getline(in, p->tag);
	cout << "Сумма   : "; in >> p->sum;
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
		cout << "5. Печать по номеру" << endl;
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
			print();
			break;
		case 3:
			printNum();
			break;
		case 5:
			printRange();
			break;
		case 0:
		{

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
}

inline void BasePenalty::print()
{
	base.print();
	cout << endl;
	system("pause");
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