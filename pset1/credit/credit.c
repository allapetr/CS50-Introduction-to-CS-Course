#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Get number from user
    long long n;
    n = get_long("Number: ");

    long long z = n, z1 = n, z2 = n;

    //Extract the last digit of the number
    long long t = n / 10;
    //printf("%lld\n", t);

    //Sum of every other digit
    int m;
    int sum = 0;
    do
    {
        m = (t % 10) * 2;
        t = t / 100;

        if (m < 10)
        {
            sum += m;
        }
        else
        {
            sum += (m / 10) + (m % 10);
        }
        //printf("%lld %d %d\n", t, m, sum);
    }
    while (t > 0);

    //Sum of other digits
    int x;
    int sum_2 = 0;
    do
    {
        x = n % 10;
        n = n / 100;

        sum_2 += x;

        //printf("%lld %d %d\n", n, x, sum_2);
    }
    while (n > 0);

    //Add everything- go further or print invalid
    if ((sum + sum_2) % 10 == 0)
    {
        //printf("%s\n", "VALID");

        //Calculate length of number
        long long y;
        int i;
        for (i = 0; z > 0; i++)
        {
            y = z / 10;
            z = z / 10;
            //printf("%lld %d\n", y, i);
        }

        //Calculate first two digits
        int a;
        for (a = 0; a < i - 2; a++)
        {
            z1 = z1 / 10;
        }
        //printf("%d %lld\n", a, z1);

        //Calculate first digit
        int b;
        for (b = 0; b < i - 1; b++)
        {
            z2 = z2 / 10;
        }
        //printf("%d %lld\n", b, z2);

        //Print AMEX, MASTERCARD or VISA
        if (i == 15 && (z1 == 34 || z1 == 37))
        {
            printf("AMEX\n");
        }
        else if (i == 16 && (z1 >= 51 && z1 <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if (i == 13 || (i == 16 && z2 == 4))
        {
            printf("VISA\n");
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
