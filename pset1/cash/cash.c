#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //Prompt user for an amount of change in dollars
    float dollars;
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);

    //Convert input in dollars in cents
    int cents = round(dollars * 100);
    //printf("%i\n", cents);

    //Use the largest coins possible, keeping track of coins used
    int n = cents;
    int t; //Number of 25c coins
    int x; //Number of 10c coins
    int y; //Number of 5c coins
    int z; //Number of 1c coins
    for (t = 0; n >= 25; t++)
    {
        n = n - 25;
    }
    //printf("%d %d\n", n, t);

    for (x = 0; n >= 10; x++)
    {
        n = n - 10;
    }
    //printf("%d %d\n", n, x);

    for (y = 0; n >= 5; y++)
    {
        n = n - 5;
    }
    //printf("%d\n", y);

    for (z = 0; n >= 1; z++)
    {
        n = n - 1;
    }
    //printf("%d\n", z);

    //Print the number of coins
    printf("%d\n", t + x + y + z);
}
