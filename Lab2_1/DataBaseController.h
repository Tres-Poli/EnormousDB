#pragma once

#include <string>
#include "List.h"
#include "StudentModel.h"
#include <ctime>

class DataBaseController
{
private:
	List* _storage = new List();
	int _currId;

public:
	DataBaseController()
	{
		_currId = 0;
	}
	~DataBaseController()
	{
		delete(_storage);
	}
	void AddNode(Student* student)
	{
		_currId++;
		student->id = _currId;
		student->Smart = 0;
		for (int i = 0; i < 8; ++i)
			student->Smart += student->SessionResults[i];
		_storage->AddBack(student);
	}
	void AddRange(Student** students, int size)
	{
		for (int i = 0; i < size; ++i)
		{
			_currId++;
			students[i]->id = _currId;
			int smart = 0;
			for (int j = 0; j < 8; ++j)
				smart += students[i]->SessionResults[j];
			students[i]->Smart = smart;
		}
		_storage->AddRange(students, size);
	}
	Student* GetById(int id)
	{
		return _storage->FindById(id);
	}
	int* GetSexCount()
	{
		return _storage->CountSex();
	}
	List* GetStorage()
	{
		return _storage;
	}
};