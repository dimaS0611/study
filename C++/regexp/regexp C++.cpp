#include <iostream> 
#include <regex> 
#include <fstream> 

using namespace std;

int main()
{

	ifstream input("in.txt");

	if (!input.is_open()) {
		cout << "Error! File is not open!" << endl;
	}
	else if (input.peek() == EOF) {
		cout << "File is empty!" << endl;
	}
	else {
		regex number("^[A-Z]{1,3}\\s(?!(SS|SD))[A-Z]{1,2}[1-9]\\d{3}$");
		string strforinput;
		int counter = 0;
		while (input.peek() != EOF) 
		{
			getline(input, strforinput);
			if (!regex_match(strforinput, number)) {
				++counter;
			}
		}
		cout << "Number of wrong cars numbers: " << counter;
	}
	return 0;
}
