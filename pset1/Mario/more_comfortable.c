#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Get height from user
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    //Build piramid
    for (int i = 0; i < n; i++) //Height
    {
        for (int j = 0; j < n - (i + 1); j++) //Spaces
        {
            printf(" ");
        }
        for (int t = 0; t < i + 1; t++)
        {
            printf("#");
        }
        printf("  ");
        for (int t = 0; t < i + 1; t++)
        {
            printf("#");
        }
        printf("\n");
    }
}


