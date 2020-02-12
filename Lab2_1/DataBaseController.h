#pragma once

#include <string>
#include "DateTime.h"
#include "List.h"


enum Sex
{
	Male,
	Female
};

enum EduFormat
{
	FullTime,
	Evening,
	Distance
};

class SessionResults
{
public:
	short Exam1;
	short Exam2;
	short Exam3;

	short Diff1;
	short Diff2;
	short Diff3;
	short Diff4;
	short Diff5;
};

class Student
{
public:
	int id;

	std::string LastName;
	std::string FirstName;
	std::string ExtName;

	Sex Sex;

	int GroupNum;
	int ListNum;

	SessionResults* SessionResults;

	EduFormat EduFormat;

	DateTime* LastChangeDate;
};

class DataBaseController
{
private:
	static List<Student> _storage;
	static int _currId;

public:
	DataBaseController()
	{
		_currId = 1;
	}
	void AddNode(Student* student)
	{
		_currId++;
		student->id = _currId;
		_storage.AddBack(student);
	}
	Student* GetById(int id)
	{
		
	}
	List<Student>* GetStorage()
	{
		return &_storage;
	}
};