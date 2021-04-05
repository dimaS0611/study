#include <iostream>
#include "Person.h"
#include "PersonException.h"

int main() {
	
	setlocale(LC_ALL, "Russian");
	Person Adam("Adam", Male);
	Person Eva("Eva", Female);

	std::cout << "������� 2 ���������: ���� � ���." << std::endl;
	std::cout << "������ ����� ����������� ������� ������ ���� ����� � ���." << "\n\n";
	
	try {
		std::cout << Adam.Get_Mother() << std::endl;
		std::cout << Eva.Get_Mother() << std::endl;
	}
	catch (PersonException & ex) {
		std::cout << ex.Error("Mother field is missing") << std::endl;

		std::cout << "�� �������� ������ � ���, ��� ���� ���� �����������, � ��� ������, ��� ��� ������� �� ����� � ���!" << std::endl;
		std::cout << "������ �������� ������� ���������!" << "\n\n";
	}

	std::cout << "���� ������ ������� ��������� �������� ����, �� ������� - 1. ���� �������� - 2" << "\n\n";
	
	short gender_checker = 0;
	Person* person_1 = nullptr;
	
	for (;;) {
		std::cin >> gender_checker;
		
		if (gender_checker == 1) {	
			try {
				person_1 = Eva.GiveBirth("Julia", Female, &Adam);
			}
			catch (PersonException & ex) {
				std::cout << ex.Error("Fields set incorrectly") << std::endl;
			}
			break;
		}
		else if (gender_checker == 2) {
			try {
				person_1 = Eva.GiveBirth("Alex", Male, &Adam);
			}
			catch (PersonException & ex) {
				std::cout << ex.Error("Fields set incorrectly") << std::endl;
			}
			break;
		}
		else {
			std::cout << "������ ����� ������ 1 ��� 2!" << std::endl;
		}
	}

	std::cout << "�� ������� ������ ���������! ��� ��� ���������� � ��: " << std::endl;
	std::cout << "���: " << person_1->Get_Name() << std::endl;
	std::cout << "���: " << person_1->Get_Gender() << std::endl;
	std::cout << "��� ID � ����� ������ ��������: " << person_1->Get_ID() << std::endl;
	try {
		std::cout << "���� ���������: " << person_1->Get_Mother() << std::endl;
		std::cout << "���� ���������: " << person_1->Get_Father() << std::endl;
	}
	catch (PersonException & ex) {
		std::cout << ex.Error("Unknown field") << std::endl;
	}
	delete person_1;
	return 0;
}
