#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Ask the user the change owed.
    float change_owed;
    do
    {
        change_owed = get_float("How much: \n");
    }
    while (change_owed < 0);

    //Round the cents
    int cents = round(change_owed * 100);
    
    int coins = 0;

    //Loop for assigning currency
    while (cents > 0)
    {
        while (cents >= 25) //Quarters
        {

            cents = cents - 25;
           
            coins++;
        }

        while (cents >= 10) //Dimes
        {
            
            cents = cents - 10;
            
            coins++;
        }

        while (cents >= 5) //Nickels
        {
            cents = cents - 5;
            
            coins++;
        }

        while (cents >= 1) //Pennies
        {
            cents = cents - 10;
            
            coins++;
        }
    }
    
    //Print the number of coins used.
    printf("%i\n", coins);
}