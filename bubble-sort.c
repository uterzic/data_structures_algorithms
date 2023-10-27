#include "stdio.h"
#include "stdbool.h"

void swap(int array[], int item1, int item2)
{
    int temp = array[item1];
    array[item1] = array[item2];
    array[item2] = temp;
}

void sort(int array[], size_t sizeOfArray)
{
    bool isSorted = true;
    for (int i = 0; i < sizeOfArray; i++)
    {
        for (int j = 0; j < sizeOfArray; j++)
            if (array[j - 1] > array[j]) {
                swap(array, j, j - 1);
                isSorted = false;
        }
        if (isSorted)
            break;
    }
}

void printArray(int array[], size_t sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; i++)
    {
        printf("%d", array[i]);
    }
}


int main()
{
    int numbers[10] = { 5, 2, 3, 8, 6, 1, 9, 7, 10, 0};
    size_t sizeOfArray = sizeof(numbers) / sizeof(int);

    sort(numbers, sizeOfArray);


    printArray(numbers, sizeOfArray);
}