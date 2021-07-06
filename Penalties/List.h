#pragma once
#include<iostream>
#include"MyData.h"
#include<Windows.h>

using namespace std;

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}




template<class T>
class List
{
	MyData<T>* first = nullptr;
	MyData<T>* last = nullptr;
	int length = 0;

public:
	~List() { clear(); };
	List() {}
	List(const List<T>& obj);
	//List operator=(const List & obj);
	void push_front(T val);
	void push_back(T val);
	void push_at(T val, int ind);
	T pop_front();
	T pop_back();
	T pop_at(int ind);
	T peek_front();
	T peek_back();
	T peek_at(int ind);
	T operator[](int ind) const;
	bool isEmpty();
	void print();
	void print(int x, int y);
	void clear();
	int  getLength();
	void sort();
	void sort_reverse();
	List<T> operator+(const List& obj);
	List<T> operator*(const List& obj);

	template<class T>
	friend ostream& operator <<(ostream& out, const List<T>& obj);

};

template<class T>
inline List<T>::List(const List<T>& obj)
{
	for (size_t i = 0; i < obj.length; i++)
	{
		push_back(obj[i]);
	}
}

template<class T>
inline void List<T>::push_front(T val)
{
	if (length == 0)
	{
		first = new MyData<T>;
		first->value = val;
		last = first;
	}
	else
	{
		MyData<T>* temp = new MyData<T>;
		temp->value = val;
		temp->next = first;
		first = temp;
	}
	length++;
}

template<class T>
inline void List<T>::push_back(T val)
{
	if (length == 0)
	{
		first = last = new MyData<T>;
		first->value = val;
	}
	else
	{
		MyData<T>* temp = new MyData<T>;
		temp->value = val;
		last->next = temp;
		last = temp;
	}
	length++;
}

template<class T>
inline void List<T>::push_at(T val, int ind)
{
	if (ind == 0)
		push_front(val);
	else
	{
		if (ind == length)
			push_back(val);
		else
		{
			MyData<T>* temp = new MyData<T>;
			temp->value = val;
			MyData<T>* temp2 = first;
			for (size_t i = 0; i < ind - 1; i++)
			{
				temp2 = temp2->next;
			}
			temp->next = temp2->next;
			temp2->next = temp;
			length++;
		}
	}
}

template<class T>
inline T List<T>::pop_front()
{
	if (length == 0)
	{
		return T();
	}
	MyData<T>* temp = first;
	first = first->next;
	T val = temp->value;
	delete temp;
	length--;
	return val;
}

template<class T>
inline T List<T>::pop_back()
{
	if (length == 0)
	{
		return T();
	}

	T val = last->value;
	MyData<T>* temp = first;
	for (int i = 0; i < length - 2; i++)
	{
		temp = temp->next;
	}
	delete last;
	temp->next = nullptr;
	last = temp;
	length--;
	if (length == 0)
		last = first = nullptr;
	return val;
}

template<class T>
inline T List<T>::pop_at(int ind)
{
	if (ind >= 0 && ind < length)
	{
		if (ind == 0)
			return pop_front();
		else
		{
			if (ind == length - 1)
				return pop_back();
			else
			{
				MyData<T>* temp2 = first;
				for (int i = 0; i < ind - 1; i++)
				{
					temp2 = temp2->next;
				}
				MyData<T>* temp = temp2->next;
				T val = temp->value;
				temp2->next = temp->next;
				delete temp;
				length--;
			}
		}
	}
	else
	{
		return T();
	}
}

template<class T>
inline T List<T>::peek_front()
{
	return (*this)[0]; // this->operator[](0)
}

template<class T>
inline T List<T>::peek_back()
{
	return this->operator[](length - 1);
}

template<class T>
ostream& operator<<(ostream& out, const List<T>& obj)
{
	if (obj.length == 0)
	{
		out << "List empty";
		return out;
	}
	MyData<T>* temp = obj.first;
	while (temp)
	{
		out << temp->value;
		temp = temp->next;
	}
	return out;
}

template<class T>
inline T List<T>::operator[](int ind) const
{
	MyData<T>* temp = first;
	for (size_t i = 0; i < ind; i++)
	{
		temp = temp->next;
	}
	return temp->value;
}

template<class T>
inline void List<T>::print()
{
	if (length == 0)
	{
		cout << "List empty";
		return;
	}
	MyData<T>* temp = first;
	while (temp)
	{
		cout << temp->value << endl;
		temp = temp->next;
	}
}

template<class T>
inline void List<T>::print(int x, int y)
{
	MyData<T>* temp = first;
	while (temp)
	{
		gotoxy(x, y);
		cout << temp->value << endl;
		temp = temp->next;
		y++;
	}
}

template<class T>
inline void List<T>::clear()
{
	while (length)
		pop_front();
}

template<class T>
inline int List<T>::getLength()
{
	return length;
}
