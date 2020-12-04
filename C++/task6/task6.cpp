#include <fstream>
#include <string>
#include <iostream>
#include <stack>

int smiles_and_brackets(const std::string& str)
{
	std::stack<char> str_in;

	char prev = 0;
	for (char ch : str)
	{
		if (prev == ':') {
			prev = ch;
			continue;
		}

		if (ch == '(' || ch == '[' || ch == '{') {
			str_in.push(ch);
		}

		else if (ch == ')' || ch == ']' || ch == '}')
		{
			if (str_in.empty())
				return  1;

			char close = (ch == ')') ? '(' : (ch == ']') ? '[' : '{';

			if (str_in.top() == close)
				return 2;
			str_in.pop();
		}

		prev = ch;
	}

	if (!str_in.empty())
		return 0;

	return (str_in.empty()) ? 0 :  3;
}

int main()
{
	//open file
	std::ifstream txt_in("d:/temp/smiles.in");
	
	if (!txt_in.is_open()) {
		std::cout << "file is not found.\n";
		return -1;
	}

	std::ofstream txt_out;
	txt_out.open("d:/temp/smiles.out", std::ios::out);

	if (!txt_out.is_open()) {
		std::cout << "file is not create.\n";
		return -2;
	}

	while (!txt_in.eof()) 
	{
		std::string str;
		std::getline(txt_in, str);
		txt_out << smiles_and_brackets(str) << "\n";
	}

	txt_out.close();
	txt_in.close();

	return 0;
}
