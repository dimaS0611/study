#include <iostream>

int swap(int num)
{
    __asm
    {
        push EAx
        push EBx
        push ECx
        push EDx

        mov EAx,[num] // записывает num в [EAx]
        mov ECx,0

     lb_while:
        cmp EAx,0 // условие пока [EAx] != 0
        je lb_exit

        mov EDx,0
        mov EBx,10
        div EBx // [EDx,EAx] / [EBx] => [EAX] (EAx частное, EDx остаток)
        mov EDi,EDx // запоминаем остаток от деления из [EDX] в [EDi]

        xchg EAx,ECx // меняем местами значения [EAx] и [ЕСх]
        mul  EBx // [EAx] * [EBx]
        xchg ECx,EAx // меняем местами значения [ECx] и  [ЕAx]

        add ECx,EDi // прибавляем к ECx EDi

        jmp lb_while

    lb_exit:
        mov [num],ECx // записываем значение [ECx] => num

        pop EDx
        pop ECx
        pop EBx
        pop EAx
    }

    return num;

    /*  аналог ф-ии Acm на C++
   
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


