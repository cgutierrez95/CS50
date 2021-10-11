#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    int n = 0;
    
    int check = 0;

    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    int letters_len = sizeof(letters);

    //Determines if only one argument is passed
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Determines if the argument passed has a 26 character lenght.
    int arglen = strlen(argv[1]);

    if (arglen < 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Determines if the argument passed has 26 characters.
    string argument = argv[1];

    for (int i = 0; i < arglen; i++)
    {
        if (isalpha(argument[i]) == 0)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    //Determines if the cipher has all the letters in the alphabet.
    for (int i = 0; i < letters_len; i++)
    {
        for (int j = 0; j < arglen; j++)
        {
            if (letters[i] == tolower(argument[j]))
            {
                check = 1;    
            }
        }
        
        if (check == 0)
        {
            printf("The key does not contain all letters in the alphabet\n");
            return 1;
        }
        
        check = 0;
    }

    // Ask the user for the plaintext.
    string input = get_string("Plaintext:  ");

    //Examine the input to cipher it
    int input_len = strlen(input);

    printf("ciphertext: ");

    for (int j = 0; j < input_len; j++)
    {
        //Print in case of a letter
        if (isalpha(input[j]))
        {
            // Determines the position of the letter in the alphabet.
            for (int k = 0; k < letters_len; k++)
            {
                if (tolower(input[j]) == letters[k])
                {
                    n = k;
                }
            }

            // Lowercase
            if (islower(input[j]))
            {
                printf("%c", tolower(argument[n]));
            }

            // Uppercase
            if (isupper(input[j]))
            {
                printf("%c", toupper(argument[n]));
            }
        }

        //Print in case of a non-alphabetical character
        if (!isalpha(input[j]))
        {
            printf("%c", input[j]);
        }
    }
    printf("\n");
}