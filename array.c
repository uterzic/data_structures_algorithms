#include <stdio.h>
#include <stdlib.h>

#define ALLOCATION_SIZE 4

struct Array
{
    int* numbers;
    int count;
    int allocated;
};

struct Array *napraviArray()
{
    struct Array *nov = malloc(sizeof(struct Array));
    if (nov == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    nov->numbers = malloc(sizeof(int) * ALLOCATION_SIZE);
    nov->count = 0;
    nov->allocated = ALLOCATION_SIZE;

    return nov;
}

int pronadjiIndex(struct Array* array, int number)
{
    for (int i = 0; i < array->count; i++)
    {
        if (array->numbers[i] == number) return i;
    }

    return -1;
}

void dodaj(struct Array* array, int number) 
{
    if (array->count == array->allocated)
    {
        printf("Realocated memory. Added +%d bytes\n", ALLOCATION_SIZE);
        array->numbers = realloc(array->numbers, sizeof(int) * (array->allocated + ALLOCATION_SIZE));
        array->allocated += ALLOCATION_SIZE;
    }

    array->numbers[array->count++] = number;
}

void ispisi(struct Array* array)
{
    printf("Array has %d elements.\n", array->count);

    for (int i = 0; i < array->count; i++)
    {
        printf("Number on index %d: %d\n", i, array->numbers[i]);
    }
}

void brisiNaIndexu(struct Array* array, int index) 
{
    for (int i = index; i < array->count - 1; i++)
    {
        array->numbers[i] = array->numbers[i+1];
    }

    array->count--;

    if (array->allocated - ALLOCATION_SIZE >= array->count )
    {
        printf("Realocated memory. Removed -%d bytes\n", ALLOCATION_SIZE);
        array->numbers = realloc(array->numbers, sizeof(int) * (array->allocated - ALLOCATION_SIZE));
        array->allocated -= ALLOCATION_SIZE;
    }
}

void dodajNaPocetak(struct Array* array, int number)
{
    if (array->count == array->allocated)
    {
        printf("Realocated memory. Added +%d bytes\n", ALLOCATION_SIZE);
        array->numbers = realloc(array->numbers, sizeof(int) * (array->allocated + ALLOCATION_SIZE));
        array->allocated += ALLOCATION_SIZE;
    }

    for (int i = array->count; i > 0; i--)
    {
        array->numbers[i] = array->numbers[i - 1];
    }

    array->numbers[0] = number;
    array->count++;
}

int main()
{
    struct Array *brojevi = napraviArray();
    
    dodaj(brojevi, 10);
    dodaj(brojevi, 20);
    dodaj(brojevi, 30);
    dodaj(brojevi, 40);
    dodaj(brojevi, 60);
    printf("Number is found on index: %d\n", pronadjiIndex(brojevi, 30));
    dodajNaPocetak(brojevi, 50);
    brisiNaIndexu(brojevi, 2);

    ispisi(brojevi);

    free(brojevi);
    return 0;
}
