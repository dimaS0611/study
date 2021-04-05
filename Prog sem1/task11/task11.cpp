#include <iostream>

class Person {
private:
	char* name;
	static int next_ID;
	const int ID;

public:
	Person(const char* aname) {
		name = new char[strlen(aname) + 1];
		strcpy(name, aname);
	}

	Person(const Person& d) {
		name = new char[strlen(d.name) + 1];
		strcpy(name, d.name);
	}

	int GetID() { return ID; }

	~Person() {
		delete[] name;
	}
};


int main()
{

}

