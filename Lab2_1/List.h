#pragma once

#include "StudentModel.h"
#include "UIController.h"

struct Node
{
	Student* Value = nullptr;
	Node* Prev = nullptr;
	Node* Next = nullptr;
};
// ќсновное хранилище узлов (двусв€зный список)
class List
{
private:
	Node* _begin = nullptr;
	Node* _end = nullptr;
	UIController* _ui = new UIController();

	int _size;

	void Swap(Student* a, Student* b)
	{
		Student* buff = a;
		a = b;
		b = buff;
	}
	int Partition(Student** arr, int low, int high, bool smart)
	{
		Student* pivot = arr[high];
		int i = -1;

		for (int j = 0; j <= high - 1; j++)
		{
			if (smart)
			{
				if (arr[j]->Smart <= pivot->Smart)
				{
					i++;
					Swap(arr[i], arr[j]);
				}
			}
			else
			{
				if (arr[j]->FamilyIncome <= pivot->FamilyIncome)
				{
					i++;
					Swap(arr[i], arr[j]);
				}
			}
		}
		Swap(arr[i + 1], arr[high]);
		return (i + 1);
	}
	void QuickSort(Student** arr, int low, int high, bool smart)
	{
		if (low < high)
		{
			int pi = Partition(arr, low, high, smart);

			QuickSort(arr, low, pi - 1, smart);
			QuickSort(arr, pi + 1, high, smart);
		}
	}
public: 
	void AddRange(Student** nodes, int size)
	{
		for (int i = 0; i < size; ++i)
			AddBack(nodes[i]);
		delete(nodes);
	}
	void AddBack(Student* value)
	{
		Node* node = new Node();
		node->Value = value;
		if (_begin == nullptr && _end == nullptr)
		{
			_end = _begin = node;
			_size = 1;
		}
		else
		{
			_end->Next = node;
			node->Prev = _end;
			_end = node;
			_size++;
		}
	}
	void RemoveBack()
	{
		if (_begin == nullptr && _end == nullptr)
			return;
		if (_begin == _end && _begin != nullptr)
		{
			delete(_begin);
			_begin = _end = nullptr;

		}
		else
		{
			_end->Prev->Next = nullptr;
			Node* toDelete = _end;
			_end = _end->Prev;

			delete(toDelete);
		}
		_size--;
	}

	Student* FindById(int id)
	{
		Node* curr = _begin;
		while (curr != nullptr)
		{
			if (curr->Value->id == id)
				return curr->Value;
			curr = curr->Next;
		}
		return nullptr;
	}
	int* CountSex()
	{
		int* sexCount = new int[2];
		sexCount[0] = sexCount[1] = 0;
		Node* curr = _begin;
		while (curr != nullptr)
		{
			if (curr->Value->Sex == Male)
				sexCount[0]++;
			else
				sexCount[1]++;
			curr = curr->Next;
		}
		return sexCount;
	}
	void PrintNodesByGroup(int group)
	{
		Node* curr = _begin;
		while (curr != nullptr)
		{
			if (curr->Value->GroupNum == group)
				_ui->PrintStudent(curr->Value);
			curr = curr->Next;
		}
	}
	void PrintAllList()
	{
		Node* curr = _begin;
		while (curr != nullptr)
		{
			_ui->PrintStudent(curr->Value);
			curr = curr->Next;
		}
	}
	void PrintWithScholarship()
	{
		Node* curr = _begin;
		bool scholarshop = true;
		while (curr != nullptr)
		{
			if (curr->Value->EduFormat != Fulltime)
			{
				curr = curr->Next;
				continue;
			}
			for (int i = 0; i < 8; ++i)
			{
				if (curr->Value->SessionResults[i] < 4)
					scholarshop = false;
			}
			if(scholarshop) _ui->PrintStudent(curr->Value);
			curr = curr->Next;
			scholarshop = true;
		}
	}
	void PrintWOScholarship()
	{
		Node* curr = _begin;
		bool scholarshop = true;
		while (curr != nullptr)
		{
			if (curr->Value->EduFormat != Fulltime)
			{
				_ui->PrintStudent(curr->Value);
				curr = curr->Next;
				continue;
			}
			for (int i = 0; i < 8; ++i)
			{
				if (curr->Value->SessionResults[i] < 4)
					scholarshop = false;
			}
			if (!scholarshop) _ui->PrintStudent(curr->Value);
			curr = curr->Next;
			scholarshop = true;
		}
	}
	void PrintWithMarks(int* marks, int size)
	{
		Node* curr = _begin;
		while (curr != nullptr)
		{
			bool falseMark = false;
			for (int i = 0; i < 8; ++i)
			{
				bool hitMark = false;
				for (int j = 0; j < size; ++j)
				{
					if (curr->Value->SessionResults[i] == marks[j]) hitMark = true;
				}
				if (!hitMark) falseMark = true;
			}
			if(!falseMark) _ui->PrintStudent(curr->Value);
			curr = curr->Next;
		}
	}
	void PrintWithNumList(int num)
	{
		Node* curr = _begin;
		while (curr != nullptr)
		{
			if (curr->Value->ListNum == num)
				_ui->PrintStudent(curr->Value);
			curr = curr->Next;
		}
	}
	void PrintChangedToday(char* date)
	{
		Node* curr = _begin;
		while (curr != nullptr)
		{
			if (curr->Value->LastChangeDate == date)
				_ui->PrintStudent(curr->Value);
			curr = curr->Next;
		}
	}
	void PrintTop(int topSize)
	{
		Student** arr = ToArray(_size);
		QuickSort(arr, 0, _size - 1, true);
		if (_size <= topSize) PrintAllList();
		else for (int i = 0; i < topSize; ++i)
				_ui->PrintStudent(arr[i]);
		delete(arr);
	}
	void PrintTopForHostel (int topSize)
	{
		List* newList = GetRidOfNotResidents();
		Student** arr = newList->ToArray(newList->_size);
		QuickSort(arr, 0, newList->_size - 1, false);
		int limiter = 0;
		if (_size <= topSize) PrintAllList();
		else for (int i = topSize - 1; i >= 0; --i)
		{
			_ui->PrintStudent(arr[i]);
		}
		delete(arr);
		delete(newList);
	}
	List* GetRidOfNotResidents()
	{
		List* newList = new List();
		Node* curr = _begin;
		while (curr != nullptr)
		{
			if (curr->Value->Resident == false)
			{
				curr = curr->Next;
				continue;
			}
			newList->AddBack(curr->Value);
			curr = curr->Next;
		}
		return newList;
	}
	Student** ToArray(int size)
	{
		Student** arr = new Student*[size];
		int counter = 0;
		Node* curr = _begin;
		while (curr != nullptr)
		{
			arr[counter] = curr->Value;
			curr = curr->Next;
			counter++;
		}
		return arr;
	}
	~List()
	{
		Node* curr = _begin;
		while (curr != nullptr)
		{
			Node* tmp = curr->Next;
			delete(curr);
			curr = tmp;
		}
		delete(_ui);
	}
};