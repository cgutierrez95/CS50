#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    //Get user input text.
    string text = get_string("Text: ");

    // Define variables.
    int text_len = strlen(text);

    float letters = 0;

    float words = 0;

    float sentences = 0;

    float L = 0;

    float S = 0;

    float index = 0;

    // Examine the text looking for letters, words an sentences.
    for (int i = 0; i <= text_len; i++)
    {

        if (isalpha(text[i]))
        {
            letters++;
        }

        if (isspace(text[i]))
        {
            words++;
        }

        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    //Adds one more word to te words.
    words++;
    
    //Evaluate the results with Coleman-Liau index
    L = (letters / words) * 100;
    
    S = (sentences / words) * 100;
    
    index = (0.0588 * L) - (0.296 * S) - 15.8;

    index = round(index);
    
    //Print the final result.
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    
    if (index >= 1 && index < 16)
    {
        printf("Grade %i\n", (int) index);
    }
}

