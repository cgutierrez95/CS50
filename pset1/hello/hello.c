#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Asking the users for their names.
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}