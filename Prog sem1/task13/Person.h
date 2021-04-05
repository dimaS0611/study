#include <cstring>
#include <exception>
#pragma once

	enum Gender
	{
		Male,
		Female
	};

	class Person {
	private:
		char* name;
		const Person* mother;
		const Person* father;
		const int ID;
		static int next_ID;
		void erase();
		void clone(const Person&);
		Gender gender_of_person;
		void Set_Gender(Gender);
	public:
		const int GetID();
		void CreatingPerson(const char*, Gender);
		Person(const char*, Gender, const Person*, const Person*);
		Person(const char*, Gender);
		Person(const Person&);
		Person();
		virtual ~Person();
		Person& operator = (const Person&);
		const int Get_ID();
		const char* Get_Name() const;
		const Gender Get_Gender();
		const char* Get_Mother() const;
		const char* Get_Father() const;

		Person* GiveBirth(const char*, Gender, Person*);

	};

