#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Ask for the credit card number.
    long credit_card;

    do
    {
        credit_card = get_long("Enter your credit card: \n");
    }
    while (credit_card < 0);

    // Variable Declaration
    int digit = 0; //Takes a single digit each time of the credit card.

    int counter = 0; //Counts how many passes in thw while loop.

    int even_digit = 0; //Saves when the even digit has two digits.

    int sum = 0; // Stores the check sum.

    int first_digit = 0; //Stores the first digit.

    int second_digit = 0; //Stores the second digit.
    
    int check = 0; //save second digit

    while (credit_card != 0) //Start analyzing the credit card.
    {
        
        digit = (credit_card % 10);
        
        if ((credit_card / 100) == 0 && (check == 0))
        {
            second_digit = digit;
            check = 1; 
        }
        
        credit_card = (credit_card / 10);
        counter++;
        
        if ((credit_card % 10) == 0)
        {
            first_digit = digit;
        }
        
        if ((counter % 2) > 0) // Take the odd digits.
        {
            sum = (sum + digit);
        }

        if ((counter % 2) == 0) //Take the even digits.
        {
            digit *= 2;

            if (digit >= 10)
            {
                for (int j = 0; j < 2; j++)
                {
                    even_digit = (digit % 10);
                    digit = (digit / 10);
                    sum = (sum + even_digit);
                }
            }
            else
            {
                sum = (sum + digit);
            }
        }
    }

    // Final evaluations for the result
    if ((sum % 10) == 0)
    {
        if ((first_digit == 4) && (counter == 13 || counter == 16))
        {
            printf("VISA\n");
        }
        else if ((first_digit == 3) && (second_digit == 4 || second_digit == 7) && (counter == 15))
        {
            printf("AMEX\n");
        }
        else if ((first_digit == 5) && (counter == 16))
        {
            if (second_digit == 1 || second_digit == 2 || second_digit == 3 || second_digit == 4 || second_digit == 5)
            {
                printf("MASTERCARD\n");      
            }
            else
            {
                printf("INVALID\n"); 
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
