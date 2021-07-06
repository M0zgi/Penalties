#pragma once
#include"BTree.h"
#include"List.h"
#include<string>
#include<iomanip>



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
	void print();
	void find();
	void setPay();
};

void BasePenalty::menu()
{
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
		case 0:
			exit(0);
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
	}
	else
	{
		list->push_front(prot);
	}
	cout << "Новый протокол добавлен" << endl;
}

inline void BasePenalty::print()
{
	base.print();
	system("pause");
}
