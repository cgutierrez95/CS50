#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask user the height of the pyramid.
    int height;
    do
    {
        height = get_int("Height: \n");
    }
    while (height > 8 || height < 1);

    //Building the pyramid
    for (int i = 0; i < height; i++)
    {

        //Spacing
        for (int k = 0; k < (height - (i + 1)); k++)
        {
            printf(" ");
        }

        //Printing the left-half pyramid
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        
        //Printing jumps
        printf(" ");
        printf(" ");
        
        //Printing the right-half pyramid
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}