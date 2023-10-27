#include "stdio.h"

void swap(int array[], int index1, int index2)
{
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

void sort(int array[], size_t sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; i++)
    {
        for (int j = i; j < sizeOfArray; j++)
        {
            if (array[j] < array[i])
                swap(array, i, j);
        }
    }
}
void printArray(int array[], size_t sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; i++)
    {
        printf("%d ", array[i]);
    }
}

int main()
{
    int numbers[10] = { 5, 2, 3, 8, 6, 1, 9, 7, 10, 0};
    size_t sizeOfArray = sizeof(numbers) / sizeof(int);

    sort(numbers, sizeOfArray);

    printArray(numbers, sizeOfArray);
}