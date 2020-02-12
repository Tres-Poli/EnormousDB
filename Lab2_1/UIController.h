#pragma once
#include "DataBaseController.h"
#include <iostream>

class UIController
{
public:
	void ErrorMessage(const char* message)
	{
		std::cout << ">>>>> Error: " << message << std::endl;
	}
	void PrintStudent(Student* student)
	{
		const char* sex;
		const char* eduForm;
		switch (student->EduFormat)
		{
		case FullTime: sex = "Full time"; break;
		case Evening: sex = "Evening"; break;
		case Distance: sex = "Distance"; break;
		}
		switch (student->Sex)
		{
		case Male: sex = "Male"; break;
		case Female: sex = "Female"; break;
		}

		std::cout << "||  Last name: " << student->LastName << std::endl;
		std::cout << "||  First name: " << student->FirstName << std::endl;
		std::cout << "||  Ext name: " << student->ExtName << std::endl;
		std::cout << "||  Sex: " << sex << std::endl;
		std::cout << "||  Group #: " << student->GroupNum << std::endl;
		std::cout << "||  List #: " << student->ListNum << std::endl;
		std::cout << "||  Education format: " << eduForm << std::endl;
		//std::cout << "||  Last changed: " << student->LastName << std::endl;
		std::cout << "||  " << student->LastName << std::endl;
		/*std::cout << "||  First exam: " << student->SessionResults->Exam1 << std::endl;
		std::cout << "||  Second exam: " << student->SessionResults->Exam2 << std::endl;
		std::cout << "||  Third exam: " << student->SessionResults->Exam3 << std::endl;
		std::cout << "||  " << student->LastName << std::endl;
		std::cout << "||  First diff: " << student->SessionResults->Diff1 << std::endl;
		std::cout << "||  Second diff: " << student->SessionResults->Diff2 << std::endl;
		std::cout << "||  Third diff: " << student->SessionResults->Diff3 << std::endl;
		std::cout << "||  Fourth diff: " << student->SessionResults->Diff4 << std::endl;
		std::cout << "||  Fiveth diff: " << student->SessionResults->Diff5 << std::endl;*/
	}

	Student* InputStudent()
	{
		Student* toSend = new Student();
		std::cout << "Enter first name:\t";
		std::cin >> toSend->FirstName;

		std::cout << "Enter last name:\t";
		std::cin >> toSend->LastName;

		std::cout << "Enter ext name:\t";
		std::cin >> toSend->ExtName;

		std::string sex;
		std::cout << "Enter sex:\t";
		std::cin >> sex;
		if (sex == "Male") toSend->Sex = Male;
		else toSend->Sex = Female;

		std::cout << "Enter group num:\t";
		std::cin >> toSend->GroupNum;

		std::cout << "Enter list num:\t";
		std::cin >> toSend->ListNum;

		std::string eduFormat;
		std::cout << "Enter list num:\t";
		std::cin >> eduFormat;
		if (eduFormat == "FullTime") toSend->EduFormat = FullTime;
		else if (eduFormat == "Evening") toSend->EduFormat = Evening;
		else toSend->EduFormat = Distance;
	}
};