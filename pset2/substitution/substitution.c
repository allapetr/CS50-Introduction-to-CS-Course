#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Get key
    //1.Check argc
    if (argc > 2)//too many arguments
    {
        printf("Too many arguments provided!\n");
        return 1;
    }

    if (argc == 1)//no arguments
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //2.Check argv[1]
    if (strlen(argv[1]) != 26)//check if length = 26
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string k = argv[1];//check if it contains only alphabets
    for (int i = 0, n = strlen(k); i < n; i++)
    {
        if (! isalpha(k[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    int flag[26];
    for (int i = 0; i < 26; ++i)
    {
        flag[i] = 0;
    }

    for (int i = 0, n = strlen(k); i < n; i++)
    {
        int ix;
        char c = k[i];
        if (islower(c))
        {
            ix = c - 97;//link arrays for lower
        }
        else
        {
            ix = c - 65; //link arrays for upper
        }

        //check for repetitions
        if (flag[ix] == 1)
        {
            return 1;
        }
        else
        {
            flag[ix] = 1;
        }
    }

    //Convert key to uppercase
    for (int i = 0, n = strlen(k); i < n; ++i)
    {
        if (islower(k[i]))
        {
            k[i] = toupper(k[i]);
        }
    }

    //Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    //Substitution
    string ciphertext = plaintext;
    for (int i = 0, n = strlen(plaintext); i < n; ++i)
    {
        if (isupper(plaintext[i]))
        {
            int ix = plaintext[i] - 'A';
            ciphertext[i] = k[ix];
        }

        if (islower(plaintext[i]))
        {
            int ix = plaintext[i] - 'a';
            ciphertext[i] = k[ix] + 32;
        }
    }
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}
