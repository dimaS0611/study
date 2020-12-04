#include <iostream>
#include "Person.h"
#include "PersonException.h"

int main() {
	
	setlocale(LC_ALL, "Russian");
	Person Adam("Adam", Male);
	Person Eva("Eva", Female);

	std::cout << "Созданы 2 персонажа: Адам и Ева." << std::endl;
	std::cout << "Сейчас будет произведена попытка узнать мать Адама и Евы." << "\n\n";
	
	try {
		std::cout << Adam.Get_Mother() << std::endl;
		std::cout << Eva.Get_Mother() << std::endl;
	}
	catch (PersonException & ex) {
		std::cout << ex.Error("Mother field is missing") << std::endl;

		std::cout << "Мы получили ошибку о том, что поле Мать отсутствует, а это значит, что род начался от Адама и Евы!" << std::endl;
		std::cout << "Сейчас создадим первого персонажа!" << "\n\n";
	}

	std::cout << "Если хотите создать персонажа женского пола, то введите - 1. Если мужского - 2" << "\n\n";
	
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
			std::cout << "Ввести можно только 1 или 2!" << std::endl;
		}
	}

	std::cout << "Вы создали нового персонажа! Вот вся информация о нём: " << std::endl;
	std::cout << "Имя: " << person_1->Get_Name() << std::endl;
	std::cout << "Пол: " << person_1->Get_Gender() << std::endl;
	std::cout << "Его ID в нашем дереве эволюции: " << person_1->Get_ID() << std::endl;
	try {
		std::cout << "Мать персонажа: " << person_1->Get_Mother() << std::endl;
		std::cout << "Отец персонажа: " << person_1->Get_Father() << std::endl;
	}
	catch (PersonException & ex) {
		std::cout << ex.Error("Unknown field") << std::endl;
	}
	delete person_1;
	return 0;
}
