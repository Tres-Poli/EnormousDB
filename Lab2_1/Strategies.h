#pragma once
#include "DataBaseController.h"
#include "UIController.h"
#include <ctime>

class Strategies
{
private:
	// Инициализация объекта для работы с базой данных
	DataBaseController* _db;
	// Инициализация объекта для работы с пользовательским интерфейсом
	UIController* _ui;
	// Указатель на текущий объект для определнных операций
	Student* _loadedStudent;

	void DefineParameter(std::string parameter)
	{

	}
public:
	Strategies()
	{
		_ui = new UIController();
		_db = new DataBaseController();
	}
	void AddStudent()
	{
		if (_loadedStudent == nullptr)
		{
			_ui->ErrorMessage("Student not loaded");
			return;
		}
		time_t seconds = time(NULL);
		tm timeInfo; char str[20];
		if (localtime_s(&timeInfo, &seconds) == 0) strftime(str, sizeof(str), "%e/%m/%Y", &timeInfo);
		_loadedStudent->LastChangeDate = str;
		_db->AddNode(_loadedStudent);
	}

	void LoadStudent()
	{
		_loadedStudent = _ui->InputStudent();
	}

	void ShowStudent(int id)
	{
		Student* student = _db->GetById(id);
		_loadedStudent = student;
		if (student == nullptr)
		{
			_ui->ErrorMessage("There is no student with such id");
			return;
		}
		_ui->PrintStudent(student);
	}

	void ShowAllStudents()
	{
		_db->GetStorage()->PrintAllList();
	}

	void ShowStudentsByGroup(int group)
	{
		_db->GetStorage()->PrintNodesByGroup(group);
	}

	void ShowSexCount()
	{
		int* sexCounted = _db->GetSexCount();
		_ui->PrintSexCount(sexCounted);
	}

	void ShowWithScholarship()
	{
		_db->GetStorage()->PrintWithScholarship();
	}

	void ShowWOScholarship()
	{
		_db->GetStorage()->PrintWOScholarship();
	}

	void ChangeStudentInfo(int id, std::string paramenter)
	{
		Student* student = _db->GetById(id);

	}

	void ShowWithMarks(int* marks, int size)
	{
		_db->GetStorage()->PrintWithMarks(marks, size);
	}

	void ShowWithNumList(int num)
	{
		_db->GetStorage()->PrintWithNumList(num);
	}

	void ShowTop(int sizeTop)
	{
		_db->GetStorage()->PrintTop(sizeTop);
	}

	void ShowTopHostel(int sizeTop)
	{
		_db->GetStorage()->PrintTopForHostel(sizeTop);
	}

	void LoadFromFile(std::string fileName)
	{
		Student** fromFile = _ui->LoadFile(fileName);
		_db->AddRange(fromFile, _ui->GetNodesLoaded());
	}

	void ChangeGroup(int group)
	{
		if (_loadedStudent == nullptr)
		{
			_ui->ErrorMessage("Student should be loaded");
			return;
		}
		time_t seconds = time(NULL);
		tm timeInfo; char str[20];
		if (localtime_s(&timeInfo, &seconds) == 0) strftime(str, sizeof(str), "%e/%m/%Y", &timeInfo);
		_loadedStudent->LastChangeDate = str;
		if (_loadedStudent == nullptr)
		{
			_ui->ErrorMessage("Student not loaded");
			return;
		}
		_loadedStudent->GroupNum = group;
	}
	void ChangeListNum(int num)
	{
		if (_loadedStudent == nullptr)
		{
			_ui->ErrorMessage("Student should be loaded");
			return;
		}
		time_t seconds = time(NULL);
		tm timeInfo; char str[20];
		if (localtime_s(&timeInfo, &seconds) == 0) strftime(str, sizeof(str), "%e/%m/%Y", &timeInfo);
		_loadedStudent->LastChangeDate = str;
		if (_loadedStudent == nullptr)
		{
			_ui->ErrorMessage("Student not loaded");
			return;
		}
		_loadedStudent->ListNum = num;
	}
	void ChangeEduForm(std::string form)
	{
		if (_loadedStudent == nullptr)
		{
			_ui->ErrorMessage("Student should be loaded");
			return;
		}
		time_t seconds = time(NULL);
		tm timeInfo; char str[20];
		if (localtime_s(&timeInfo, &seconds) == 0) strftime(str, sizeof(str), "%e/%m/%Y", &timeInfo);
		_loadedStudent->LastChangeDate = str;
		if (_loadedStudent == nullptr)
		{
			_ui->ErrorMessage("Student not loaded");
			return;
		}
		_loadedStudent->EduFormat = _ui->DefineEduForm(form);
	}
	void ShowChangedToday()
	{
		time_t seconds = time(NULL);
		tm timeInfo; char str[20];
		if (localtime_s(&timeInfo, &seconds) == 0) strftime(str, sizeof(str), "%e/%m/%Y", &timeInfo);
		_db->GetStorage()->PrintChangedToday(str);
	}

	~Strategies()
	{
		delete(_ui);
		delete(_db);
	}
};