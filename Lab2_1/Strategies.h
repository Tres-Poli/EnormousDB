#pragma once
#include "DataBaseController.h"
#include "UIController.h"

static class Strategies
{
private:
	DataBaseController _db;
	UIController _Ui;
	Student* _loadedStudent;
public:
	void AddStudentStrat()
	{
		if (_loadedStudent == nullptr) _Ui.ErrorMessage("Student not loaded");
		_db.AddNode(_loadedStudent);
	}
	void LoadStudentStrat()
	{

	}


};