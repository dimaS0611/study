#include <iostream>

int charCounter(const std::string &str) 
{
	int maxCount = 0;
	const char* ps = str.data();

	__asm
	{
		push EAx
		push EBx
		push ECx
		push ESi

		mov ESi, [ps]
		mov ECx, 0

		mov Ah, 0
		mov EBx, 0
		__loop:
		mov Al, Ah
			mov Ah, BYTE PTR[ESi]
			add ESi, 1

			cmp Al, Ah
			jne __not_equal
			add EBx, 1
			jmp __try_exit
			__not_equal :
		cmp EBx, ECx
			jle __less
			mov ECx, EBx
			__less :
		mov EBx, 1

			__try_exit :
			cmp Ah, 0
			jne __loop

			mov[maxCount], ECx

			pop ESi
			pop ECx
			pop EBx
			pop EAx
	}


	return maxCount;

	/*
	int size = str.length();
	int counter = 1, max = 0;
	
	for (int i = 0; i < size; ++i)
	{
		if (str[i] == str[i + 1])
			counter++;
		else if (counter > 0)
		{
			max = max < counter ? counter : max;
			counter = 1;
		}
	}

	return max;
	*/
}

int main()
{
	int res = 0;
	std::string input;

	std::cout << "Enter a line of digits: ";
	std::cin >> input;

	res = charCounter(input);
	std::cout << "The maximum number of digits coming in a row: " << res;
}
