#include <cstring>
#include <exception>
#include "Person.h"
#include "PersonException.h"
#pragma warning(disable:4996)

int Person::next_ID = 0;

void Person::erase() {
	delete[] name;
}

void Person::clone(const Person& p) {
	name = new char[strlen(p.name) + 1];
	std::strcpy(name, p.name);
}

Person::Person(const char* value_name, Gender value_gender, const Person* value_mother, const Person* value_father = nullptr) :ID(++next_ID) {
	CreatingPerson(value_name, value_gender);
	if (value_mother->gender_of_person != Female && value_mother != nullptr) {
		throw PersonException();
	}

	if (value_father->gender_of_person != Male && value_father != nullptr) {
		throw PersonException();
	}
	mother = value_mother;
	father = value_father;
}

Person::Person() :ID(++next_ID) 
{}

Person::Person(const char* value_name, Gender value_gender) : ID(++next_ID)
{
	CreatingPerson(value_name, value_gender);
	if (this->ID != 1 && this->ID != 2)
		throw PersonException();
}

void Person::CreatingPerson(const char* value_name, Gender value_gender) {
	if (value_name == nullptr)
		throw PersonException();
	if (value_name[0] == 0)
		throw PersonException();
	name = new char[strlen(value_name) + 1];
	std::strcpy(name, value_name);
	Set_Gender(value_gender);
}

Person::Person(const Person& p) :ID(++next_ID) {
	clone(p);
}

const int Person::GetID() {
	return ID;
}

Person& Person::operator=(const Person& p) {
	if (this == &p)
		return *this;
	if (this != nullptr) {
		delete[] name;
	}
	name = new char[strlen(p.name) + 1];
	std::strcpy(name, p.name);
	return *this;
}

Person::~Person() {
	erase();
}

void Person::Set_Gender(Gender value_gender) {
	gender_of_person = value_gender;
}

const int Person::Get_ID() {
	return this->ID;
}

const char* Person::Get_Name() const {
	return this->name;
}

const Gender Person::Get_Gender() {
	return this->gender_of_person;
}

const char* Person::Get_Mother() const {
	if (this->ID == 0 || this->ID == 1) {
		throw PersonException();
	}
	else {
		return mother->Get_Name();
	}
}

const char* Person::Get_Father() const {
	if (this->ID == 0 || this->ID == 1) {
		throw PersonException();
	}
	if (this->father == nullptr) {
		throw PersonException();
	}
	else {
		return father->Get_Name();
	}
}

Person* Person::GiveBirth(const char* value_name, Gender gender, Person* value_father) {
	if (value_name == nullptr)
		throw PersonException();
	if (value_name[0] == '\0')
		throw PersonException();
	if (this->gender_of_person != Gender::Female)
		throw "Only woman can be mother!";

	const Person* mother = this;
	if (value_father != nullptr && value_father->gender_of_person != Gender::Male)
		throw "Only men can be father!";

	Person* child = new Person(value_name, gender, mother, value_father);
	return child;

}