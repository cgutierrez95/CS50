#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask the user the starting population.
    int start;
    do
    {
        start = get_int("Starting Population: \n");
    }
    while (start < 9);

    // Ask th euser the ending population.
    int end;
    do
    {
        end = get_int("Ending Population: \n");
    }
    while (end < start);

    //Doing the population calculations.
    int years = 0;
    while (start < end)
    {
        start = start + (start / 3) - (start / 4);
        years++;
    }


    // Printing the number of years.
    printf("Years: %i\n", years);
}