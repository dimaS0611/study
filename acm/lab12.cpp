#include <iostream>

double solver(double x, int k)
{
    double e = std::pow(10, -k);
    float result;

    __asm
    {
        push EAx
        push ECx

        FLD1            // y=1  ST(2)
        FADD[x]         // y=1+x

        FLD[x]          // a=x  ST(1)

        FLD1            // d    ST(0)

        mov ECx, 10000
        __loop:
        
        FLD1
        FADD      // d+=1
        

        FXCH ST(1)
        FMUL[x]          // a*=x
        FDIV ST, ST(1)   // a/=d
        FXCH ST(1)

        FXCH ST(2)
        FADD ST, ST(1)   // y+=a
        FXCH ST(2)

        FLD[e]
        FCOMIP ST, ST(2)
        jnc __exit

        loop __loop

        __exit:
        FSTP ST(0)      // pop d
        FSTP ST(0)      // pop a
        FSTP[result]    // save result

        pop ECx
        pop EAx
    }

    return result;

    /*
    double fact = 1, sum = 1;
    double eps = std::pow(10, -k);
   
    for (int i = 1; fact > eps; ++i)
    {
        fact *= x / i;
        sum += fact;
    }

    return sum;
    */
}


int main()
{
    double x;
    int k;
    
    std::cout << "Enter x t o calculate exp^x : ";
    std::cin >> x;

    std::cout << "Enter number of deciminal places: ";
    std::cin >> k;

    std::cout << "(std result) exp^x = " << std::exp(x) << std::cout.precision(k + 1);
    std::cout << "\n(func result) exp^x = " << solver(x,k) << std::cout.precision(k + 1);
}

