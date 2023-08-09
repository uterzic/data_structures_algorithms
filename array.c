#include <stdio.h>
#include <stdlib.h>

#define ALLOCATION_SIZE 4

struct Array
{
    int* numbers;
    int count;
    int allocated;
};

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
        printf("Realocated memory +%d bytes\n", ALLOCATION_SIZE);
        array->numbers = realloc(array->numbers, sizeof(int) * (array->allocated + ALLOCATION_SIZE));
        array->allocated += ALLOCATION_SIZE;
    }
    array->numbers[array->count++] = number;
}

void ispisi(struct Array* array)
{
    for (int i = 0; i < array->count; i++)
    {
        printf("%d\n", array->numbers[i]);
    }
}

void brisi(struct Array* array, int index) 
{
    for (int i = index; i < array->count - 1; i++)
    {
        array->numbers[i] = array->numbers[i+1];
    }

    array->count--;

    if (array->allocated - ALLOCATION_SIZE >= array->count )
    {
        printf("Realocated memory -%d bytes\n", ALLOCATION_SIZE);
        array->numbers = realloc(array->numbers, sizeof(int) * (array->allocated - ALLOCATION_SIZE));
        array->allocated -= ALLOCATION_SIZE;
    }
}

void dodajNaPocetak(struct Array* array, int number)
{
    if (array->count == array->allocated)
    {
        printf("Realocated memory +%d bytes\n", ALLOCATION_SIZE);
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
    struct Array brojevi = { NULL, 0, ALLOCATION_SIZE };
    
    // Allocate memory for the numbers array
    brojevi.numbers = malloc(sizeof(int) * ALLOCATION_SIZE);
    if (brojevi.numbers == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    dodaj(&brojevi, 1);
    dodaj(&brojevi, 2);
    dodaj(&brojevi, 3);
    dodaj(&brojevi, 4);
    printf("Count %d\n", brojevi.count);
    printf("%d\n", pronadjiIndex(&brojevi, 3));
    dodajNaPocetak(&brojevi, 5);
    ispisi(&brojevi);

    free(brojevi.numbers);
    return 0;
}
