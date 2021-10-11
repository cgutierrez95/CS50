#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
    
int main(int argc, string argv[])
{
    // Determines if only one arguments is passed.
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Determines if the argument passed is a number.
    int arglen = strlen(argv[1]);

    string argument = argv[1];

    for (int i = 0; i < arglen; i++)
    {
        if (isdigit(argument[i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Determines if it is a positive number.
    int number = atoi(argument);

    int new_number = 0;

    if (number < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Determines the number of jumps.
    number = number % 26;

    //Ask the user for the input.
    string input = get_string("plaintext:  ");

    int inputlen = strlen(input);

    printf("ciphertext: ");

    // Examines the user input to cipher it.
    for (int j = 0; j < inputlen; j++)
    {
        // Prints the same number or special character.
        if (!isalpha(input[j]))
        {
            printf("%c", input[j]);
        }

        // Prints for the lower letters
        if (isalpha(input[j]) && islower(input[j]))
        {
            if (input[j] + number > 122)
            {
                new_number = (input[j] + number) - 122;

                printf("%c", input[j] - (input[j] - 96) + new_number);
            }
            else
            {
                printf("%c", input[j] + number);
            }
        }
        
        //Prints for the upper letters
        if (isalpha(input[j]) && isupper(input[j]))
        {
            if (input[j] + number > 90)
            {
                new_number = (input[j] + number) - 90;

                printf("%c", input[j] - (input[j] - 64) + new_number);
            }
            else
            {
                printf("%c", input[j] + number);
            }
        }
    }
    printf("\n");
}