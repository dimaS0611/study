#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct Car
{
  char* _model;
  int _price;
};

// Function that sort the array of cars by price
void sortArray(struct Car* arr, int size)
{
  int i = 0;
  int j = size - 1;

  int mid = arr[size/2]._price;

  while(i <= j)
  {
    while(arr[i]._price < mid)
    {
      i++;
    }

    while(arr[j]._price > mid)
    {
      j--;
    }

    if(i <= j)
    {
      struct Car temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;

      i++;
      j--;
    }
  }

  if(j > 0)
  {
    sortArray(arr, j + 1);
  }

  if(i < size)
  {
    sortArray(&arr[i], size - i);  
  }
}

// Main Function
int main(int argc, char* argv[])
{
    int size = argc - 1;
    struct Car *carsArray; 
    carsArray = (struct Car*)calloc(size, sizeof(struct Car));

    srand(time(NULL));
    for (int i = 0; i < size; ++i)
    {
        carsArray[i]._model = argv[i + 1];
        carsArray[i]._price = rand();
    }

    sortArray(carsArray, size);

    printf("Model of the middle car price in list - %s, price - %d", carsArray[size / 2]._model, carsArray[size / 2]._price);

    free(carsArray);
}
