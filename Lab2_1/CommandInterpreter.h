#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Strategies.h"

class CommandInterpreter
{
private:
	// Предопределенные значения комманд
	const char* _loadStudent = "load_student";
	const char* _addNode = "add_student";
	const char* _help = "help";
	const char* _exit = "exit";
	const char* _showStudent = "show_student";
	const char* _showAllStudents = "show_all_students";
	const char* _showStudentsByGroup = "show_students_by_group";
	const char* _showSexCount = "show_sex_count";
	const char* _showWithScholarship = "show_with_scholarship";
	const char* _showWOScholarship = "show_wo_scholarship";
	const char* _allowableMarks = "show_with_marks";
	const char* _showWithNumList = "show_with_num_in_list";
	const char* _showTop = "show_top";
	const char* _loadFromFile = "load_from_file";
	const char* _showChangedToday = "show_changed_today";
	const char* _showTopForHostel = "show_top_hostel";

	const char* _changeGroupNum = "change_group_num";
	const char* _changeListNum = "change_list_num";
	const char* _changeEduForm = "change_edu_form";

	// Инициализация объекта для обработки комманд
	Strategies* _strategies = new Strategies();
	// Инициализация объекта для работы с пользовательским интерфейсом
	UIController* _ui = new UIController();

	// Вынесенные в перечисления комманды для работы со switch-ом
	static enum Commands
	{
		LoadStudent,
		AddStudent,
		ShowStudent,
		ShowAllStudents,
		ShowStudentsByGroup,
		ShowSexCount,
		ShowWithScholarship,
		ShowWOScholarship,
		ShowWithMarks,
		ShowWithNumList,
		ShowChangedToday,
		ShowTop,
		ShowTopHostel,
		ChangeListNum,
		ChangeEduForm,
		ChangeGroupNum,
		LoadFromFile,
		Unrecognized,
		Help,
		Exit
	};

	// Явное сравнение поступившей комманды с предопределенными значениями
	int InterpreteCommand(std::string command)
	{
		if (command == _loadStudent)			return LoadStudent;
		if (command == _addNode)				return AddStudent;
		if (command == _help)					return Help;
		if (command == _exit)					return Exit;
		if (command == _showStudent)			return ShowStudent;
		if (command == _showAllStudents)		return ShowAllStudents;
		if (command == _showStudentsByGroup)	return ShowStudentsByGroup;
		if (command == _showSexCount)			return ShowSexCount;
		if (command == _showWithScholarship)	return ShowWithScholarship;
		if (command == _showWOScholarship)		return ShowWOScholarship;
		if (command == _allowableMarks)			return ShowWithMarks;
		if (command == _showWithNumList)		return ShowWithNumList;
		if (command == _showTop)				return ShowTop;
		if (command == _loadFromFile)			return LoadFromFile;
		if (command == _changeGroupNum)			return ChangeGroupNum;
		if (command == _changeListNum)			return ChangeListNum;
		if (command == _changeEduForm)			return ChangeEduForm;
		if (command == _showChangedToday)		return ShowChangedToday;
		if (command == _showTopForHostel)		return ShowTopHostel;
		return Unrecognized;
	}

	// Метод, определяющий дальнейшее поведения программы
	// command contains commandName[0] and arguments [1], [2], [3], ...
	bool DefineStrategy(std::vector<std::string> command)
	{
		int commandNum = InterpreteCommand(command[0]);
		switch (commandNum)
		{
		case LoadStudent:
		{
			if(command.size() == 1)

			_strategies->LoadStudent();
			break;
		}
		case AddStudent:
		{
			_strategies->AddStudent();
			break;
		}
		case Help:
		{
			std::cout << "Im nearby, ask me plz ^^\n";
			break;
		}
		case ShowStudent:
		{
			if (command.size() != 2)
			{
				_ui->ErrorMessage("ID is required");
				return false;
			}
			int id = std::atoi(command[1].c_str());
			_strategies->ShowStudent(id);
			break;
		}
		case ShowAllStudents:
		{
			_strategies->ShowAllStudents();
			break;
		}
		case ShowStudentsByGroup:
		{
			if (command.size() != 2)
			{
				_ui->ErrorMessage("Group num is required");
				return false;
			}
			int id = std::atoi(command[1].c_str());
			_strategies->ShowStudentsByGroup(id);
			break;
		}
		case ShowSexCount:
		{
			_strategies->ShowSexCount();
			break;
		}
		case ShowWithScholarship:
		{
			_strategies->ShowWithScholarship();
			break;
		}
		case ShowWOScholarship:
		{
			_strategies->ShowWOScholarship();
			break;
		}
		case ShowWithMarks:
		{
			if (command.size() < 2)
			{
				_ui->ErrorMessage("Marks are required");
				return false;
			}
			int* marks = new int[command.size() - 1];
			for (int i = 0; i < command.size() - 1; ++i)
				marks[i] = atoi(command[i + 1].c_str());
			_strategies->ShowWithMarks(marks, command.size() - 1);
			break;
		}
		case ShowWithNumList:
		{
			if (command.size() != 2)
			{
				_ui->ErrorMessage("Num in list is required");
				return false;
			}
			int num = std::atoi(command[1].c_str());
			_strategies->ShowWithNumList(num);
			break;
		}
		case ShowTop:
		{
			if (command.size() != 2)
			{
				_ui->ErrorMessage("Top size is required");
				return false;
			}
			int size = std::atoi(command[1].c_str());
			_strategies->ShowTop(size);
			break;
		}
		case ShowTopHostel:
		{
			if (command.size() != 2)
			{
				_ui->ErrorMessage("Top size is required");
				return false;
			}
			int size = std::atoi(command[1].c_str());
			_strategies->ShowTopHostel(size);
			break;
		}
		case LoadFromFile:
		{
			if (command.size() != 2)
			{
				_ui->ErrorMessage("File name is required");
				return false;
			}
			_strategies->LoadFromFile(command[1]);
			break;
		}
		case ChangeGroupNum:
		{
			if (command.size() != 2)
			{
				_ui->ErrorMessage("Group num is required");
				return false;
			}
			_strategies->ChangeGroup(std::atoi(command[1].c_str()));
			break;
		}
		case ChangeListNum:
		{
			if (command.size() != 2)
			{
				_ui->ErrorMessage("List num is required");
				return false;
			}
			_strategies->ChangeListNum(std::atoi(command[1].c_str()));
			break;
		}
		case ChangeEduForm:
		{
			if (command.size() != 2)
			{
				_ui->ErrorMessage("Edu from is required");
				return false;
			}
			_strategies->LoadFromFile(command[1]);
			break;
		}
		case Unrecognized:
		{
			std::cout << "Command unrecognized. Type \"help\" to see all available commands\n";
			break;
		}
		case ShowChangedToday:
		{
			_strategies->ShowChangedToday();
			break;
		}
		case Exit:
		{
			Dispose();
			return true;
		}
		}
		return false;
	}

public:
	// Запуск интерпретатора комманд
	void Start()
	{
		std::vector<std::string> fullCommand;
		while (true)
		{
			std::cout << ">>> ";

			std::string currCommand;
			std::getline(std::cin, currCommand);
			if (currCommand.size() == 0) std::getline(std::cin, currCommand);

			std::string commandPart;
			for (int i = 0; i < currCommand.length(); ++i)
			{
				if (currCommand[i] == ' ' && !commandPart.empty())
				{
					fullCommand.push_back(commandPart);
					commandPart.clear();
				}
				else
				{
					commandPart.push_back(currCommand[i]);
				}
			}
			fullCommand.push_back(commandPart);
			if (DefineStrategy(fullCommand)) break;

			fullCommand.clear();
		}
	}
	// Очистка памяти
	void Dispose()
	{
		delete(_strategies);
		delete(_ui);
	}
};