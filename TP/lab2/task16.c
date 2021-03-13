#include <stdio.h>

int main()
{
	int v1; // скорость 1
	int v2; // скорость 2

	printf("Enter the speed km/h: ");
	scanf("%d", &v1);

	printf("Enter the speed m/s: ");
	scanf("%d", &v2);

	 v1 = (v1 * 1000) / 3600; // перевод скорости из км/ч в м/с

        if(v1 > v2)
        {
                printf("1st speed is greater than the second");
        }
        else
                printf("2nd speed is greater than the first");

        return 0;

}
