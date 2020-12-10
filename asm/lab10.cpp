#include <iostream>

int swap(int num)
{
    __asm
    {
        push EAx
        push EBx
        push ECx
        push EDx

        mov EAx,[num] // çàïèñûâàåò num â [EAx]
        mov ECx,0

     lb_while:
        cmp EAx,0 // óñëîâèå ïîêà [EAx] != 0
        je lb_exit

        mov EDx,0
        mov EBx,10
        div EBx // [EDx,EAx] / [EBx] => [EAX] (EAx ÷àñòíîå, EDx îñòàòîê)
        mov EDi,EDx // çàïîìèíàåì îñòàòîê îò äåëåíèÿ èç [EDX] â [EDi]

        xchg EAx,ECx // ìåíÿåì ìåñòàìè çíà÷åíèÿ [EAx] è [ÅÑõ]
        mul  EBx // [EAx] * [EBx]
        xchg ECx,EAx // ìåíÿåì ìåñòàìè çíà÷åíèÿ [ECx] è  [ÅAx]

        add ECx,EDi // ïðèáàâëÿåì ê ECx EDi

        jmp lb_while

    lb_exit:
        mov [num],ECx // çàïèñûâàåì çíà÷åíèå [ECx] => num

        pop EDx
        pop ECx
        pop EBx
        pop EAx
    }

    return num;

    /*  àíàëîã ô-èè Acm íà C++
   
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


