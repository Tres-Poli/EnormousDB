#pragma once
#include "DataBaseController.h"
#include <iostream>
#include "List.h"
#include <fstream>
#include <iomanip>

class UIController
{
private:
	const char* _consoleChars = ">>> ";
	int _gotNodes;

public:
	const char* DefineSex(Sex sex)
	{
		switch (sex)
		{
		case Male: return "Male";
		case Female: return "Female";
		}
	}
	const char* DefineEduForm(EduFormat form)
	{
		switch (form)
		{
		case Fulltime: return "Fulltime";
		case Evening: return  "Evening";
		case Distance: return "Distance";
		}
	}
	Sex DefineSex(std::string sex)
	{
		if (sex == "male" || sex == "Male") return Male;
		return Female;
	}
	EduFormat DefineEduForm(std::string form)
	{
		if (form == "Fulltime") return Fulltime;
		else if (form == "Evening") return Evening;
		return Distance;
	}
	int GetNodesLoaded()
	{
		return _gotNodes;
	}
	void ErrorMessage(const char* message)
	{
		std::cout << _consoleChars << "Error: " << message << std::endl;
	}
	void InfoMessage(const char* message1, const char* message2)
	{
		std::cout << _consoleChars << message1 << "\t" << message2 << std::endl;
	}
	void InfoMessage(const char* message1, int message2)
	{
		std::cout << _consoleChars << message1 << "\t" << message2 << std::endl;
	}
	int InputStudentId()
	{
		int id;
		std::cout << _consoleChars << "Enter student id..." << std::endl;
		std::cin >> id;
		return id;
	}
	void PrintSexCount(int* sexCount)
	{
		InfoMessage("Male count  ", sexCount[0]);
		InfoMessage("Female count", sexCount[1]);
	}
	void PrintStudent(Student* student)
	{
		std::string sex = DefineSex(student->Sex);
		std::string eduForm = DefineEduForm(student->EduFormat);

		std::cout << "==================================================================" << std::endl;
		std::cout << "||  First name: " << student->FirstName << std::endl;
		std::cout << "||  Last name: " << student->LastName << std::endl;
		std::cout << "||  Ext name: " << student->ExtName << std::endl;
		std::cout << "||  Sex: " << sex << std::endl;
		std::cout << "||  Group #: " << student->GroupNum << std::endl;
		std::cout << "||  List #: " << student->ListNum << std::endl;
		std::cout << "||  Education format: " << eduForm << std::endl;
		std::cout << "||  Smart: " << student->Smart << std::endl;
		std::cout << "||" << std::endl;
		for (int i = 0; i < 3; ++i)
		{
			std::cout << "||  "<< i + 1 << " exam: " << student->SessionResults[i] << std::endl;
		}
		for (int i = 3; i < 8; ++i)
		{
			std::cout << "||  " << i - 2 << " diff: " << student->SessionResults[i] << std::endl;
		}
		std::cout << "||  Resident: " << student->Resident << std::endl;
		std::cout << "||  Family income: " << student->FamilyIncome << std::endl;
		std::cout << "||  Last modify: " << student->LastChangeDate << std::endl;
		std::cout << "==================================================================" << std::endl;
	}
	Student* InputStudent()
	{
		Student* toSend = new Student();
		std::cout << "Enter first name:\t";
		std::cin >> toSend->FirstName;

		std::cout << "Enter last name:\t";
		std::cin >> toSend->LastName;

		std::cout << "Enter ext name:\t\t";
		std::cin >> toSend->ExtName;

		std::cout << "Enter sex:\t";
		std::string sex;
		std::cin >> sex;
		toSend->Sex = DefineSex(sex);

		std::cout << "Enter group num:\t";
		std::cin >> toSend->GroupNum;

		std::cout << "Enter list num:\t";
		std::cin >> toSend->ListNum;

		std::cout << "Enter education format:\t";
		std::string eduFormat;
		std::cin >> eduFormat;
		toSend->EduFormat = DefineEduForm(eduFormat);

		int* sessionResults = new int[8];
		for (int i = 0; i < 3; ++i)
		{
			std::cout << "Enter the mark for " << i + 1 << " exam:\t";
			int mark;
			std::cin >> mark;
			sessionResults[i] = mark;
		}
		for (int i = 3; i < 8; ++i)
		{
			std::cout << "Enter the mark for " << i - 2 << " diff:\t";
			int mark;
			std::cin >> mark;
			sessionResults[i] = mark;
		}
		toSend->SessionResults = sessionResults;

		std::cout << "Enter is student is resident:\t";
		std::string resident;
		std::cin >> resident;
		toSend->Resident = atoi(resident.c_str());

		std::cout << "Enter student's family income:\t";
		std::string income;
		std::cin >> income;
		toSend->FamilyIncome = atoi(income.c_str());

		return toSend;
	}
	// Метод для загрузки узлов из файла
	Student** LoadFile(std::string file)
	{
		Student** result = new Student*[100];
		int counter = 0;
		std::ifstream fileStream;
		fileStream.open(file);
		std::string buff;
		while (!fileStream.eof())
		{
			Student* node = new Student();
			std::string buff;
			std::getline(fileStream, buff);
			node->LastName = buff; buff.clear(); std::getline(fileStream, buff);
			node->FirstName = buff; buff.clear(); std::getline(fileStream, buff);
			node->ExtName = buff; buff.clear(); std::getline(fileStream, buff);
			node->Sex = DefineSex(buff); buff.clear(); std::getline(fileStream, buff);
			node->GroupNum = std::atoi(buff.c_str()); buff.clear(); std::getline(fileStream, buff);
			node->ListNum = std::atoi(buff.c_str()); buff.clear();
			int* sessionMarks = new int[8];
			for (int i = 0; i < 8; ++i)
			{
				std::getline(fileStream, buff);
				sessionMarks[i] = std::atoi(buff.c_str());
				buff.clear();
			} std::getline(fileStream, buff);
			node->SessionResults = sessionMarks;
			node->EduFormat = DefineEduForm(buff); buff.clear(); std::getline(fileStream, buff);
			node->LastChangeDate = buff; buff.clear(); std::getline(fileStream, buff);
			node->Resident = std::atoi(buff.c_str()); buff.clear(); std::getline(fileStream, buff);
			node->FamilyIncome = std::atoi(buff.c_str()); buff.clear();
			result[counter] = node;
			counter++;
		}
		_gotNodes = counter;
		return result;
	}
};