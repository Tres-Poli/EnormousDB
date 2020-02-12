#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Strategies.h"

class CommandInterpreter
{
private:
	const char* _addNode = "addstudent";
	const char* _help = "help";
	const char* _exit = "exit";

	static enum Commands
	{
		AddStudent,
		Unrecognized,
		Help,
		Exit
	};

	int InterpreteCommand(std::string command)
	{
		if (command == _addNode)		return AddStudent;
		if (command == _help)           return Help;
		if (command == _exit)           return Exit;
		return Unrecognized;
	}

	// command contains of commandName[0] and arguments [1], [2], [3], ...
	bool DefineStrategy(std::vector<std::string> command)
	{
		int commandNum = InterpreteCommand(command[0]);
		switch (commandNum)
		{
		case AddStudent:
		{
			Strategies::AddStudentStrat();
		}
		case Help:
		{
			std::cout << "Im nearby, ask me plz ^^\n";
			break;
		}
		case Unrecognized:
		{
			std::cout << "Command unrecognized. Type \"help\" to see all available commands\n";
			break;
		}
		case Exit:
		{
			//delete(_exec);
			return true;
		}
		}
		return false;
	}

public:
	void Start()
	{
		while (true)
		{
			std::cout << ">>> ";

			std::vector<std::string> fullCommand;
			std::string currCommand;
			std::getline(std::cin, currCommand);

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
};