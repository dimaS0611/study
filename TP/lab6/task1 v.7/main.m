//
//  main.m
//  Fibonacci
//
//  Created by Dmitry Semenovich on 1.04.21.
//

#import <Foundation/Foundation.h>

int nextFibonacci(int num)
{
    int first = 1;
    int second = 1;
    int res = 0;
    
    if(num == 0)
    {
        return 1;
    }
    if(num == 1)
    {
        return 2;
    }
    for(int i = 2; res <= num; ++i)
    {
        res = first + second;
        first = second;
        second = res;
    }
    
    return res;
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        int num = 0;
        NSLog(@"Enter the number to find next Fibonacci number after him: ");
        scanf("%i", &num);
        
        int res = nextFibonacci(num);
        NSLog(@"Next Fibonacci number aftter %i = %i", num, res);
        
    }
    return 0;
}
