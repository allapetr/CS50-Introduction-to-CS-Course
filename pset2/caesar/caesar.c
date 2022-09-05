#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Get key
    //1.Check the number of arguments
    if (argc != 2)
    {
        printf("Error! Too many arguments provided!\n");
        return 1;
    }

    //printf("Success!\n");

    //2.Check the type of char in string
    string k = argv[1];
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (isdigit(k[i]))
        {
            printf("%i\n", atoi(k));
        }
        else
        {
            printf("Usage: ./caesar key\n");
        }
    }

    //Convert k to int
    int key = atoi(k);
    
    //Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    //Encipher
    string s = plaintext;
    string ciphertext;
    string c = s;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (islower(s[i]))
        {
            c[i] = (((s[i] - 'a') + key) % 26) + 'a';
        }
        else if (isupper(s[i]))
        {
            c[i] = (((s[i] - 'A') + key) % 26) + 'A';
        }
    }
    printf("Ciphertext: %s\n", c);


    //Print ciphertext


}
