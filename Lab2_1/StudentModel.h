#pragma once

#include <string>

static enum Sex
{
	Male,
	Female
};

static enum EduFormat
{
	Fulltime,
	Evening,
	Distance
};

// Основная модель узла базы данных
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

	int* SessionResults;

	EduFormat EduFormat;

	std::string LastChangeDate;

	int Smart;

	bool Resident;
	int FamilyIncome;
};