#include <iostream>

int swap(int num)
{
    __asm
    {
        push EAx
        push EBx
        push ECx
        push EDx

        mov EAx,[num] // ���������� num � [EAx]
        mov ECx,0

     lb_while:
        cmp EAx,0 // ������� ���� [EAx] != 0
        je lb_exit

        mov EDx,0
        mov EBx,10
        div EBx // [EDx,EAx] / [EBx] => [EAX] (EAx �������, EDx �������)
        mov EDi,EDx // ���������� ������� �� ������� �� [EDX] � [EDi]

        xchg EAx,ECx // ������ ������� �������� [EAx] � [���]
        mul  EBx // [EAx] * [EBx]
        xchg ECx,EAx // ������ ������� �������� [ECx] �  [�Ax]

        add ECx,EDi // ���������� � ECx EDi

        jmp lb_while

    lb_exit:
        mov [num],ECx // ���������� �������� [ECx] => num

        pop EDx
        pop ECx
        pop EBx
        pop EAx
    }

    return num;

    /*  ������ �-�� Acm �� C++
   
    int swapNum = 0;

    while (num != 0)
    {
        swapNum = (swapNum * 10) + (num % 10);
        num /= 10;
    }

    return swapNum;
*/
}

int main()
{
    int num = 0;
    std::cout << "Enter the number: ";
    std::cin >> num;

    int res = swap(num);

    std::cout << "\nResult: " << res;
}


