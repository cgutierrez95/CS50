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

        //Printing the blocks
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}