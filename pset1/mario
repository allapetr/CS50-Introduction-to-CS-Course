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
    for (int x = 0; x < n; x++)
    {
        for (int z = 0; z < n - (x + 1); z++)
        {
            printf(" ");
        }
        for (int y = 0; y < x + 1; y++)
        {
            printf("#");
        }
        printf("\n");
    }
}
