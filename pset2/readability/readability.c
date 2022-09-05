#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//This function returns number of alphabets in text
int count_letters(string text)
{
    int total_letters = 0;

    //Loop through characters
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i]; //define individual character of text

        //check if characters are alphabets
        if (isalpha(c))
        {
            total_letters++;
        }
    }
    return total_letters;
}

int count_words(string text)
{
    int total_words = 1;

    //Loop through words
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 32)
        {
            total_words++;
        }
    }
    return total_words;
}

int count_sentences(string text)
{
    int total_sentences = 0;

    //Loop through sentences
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            total_sentences++;
        }
    }
    return total_sentences;

}

int main(void)
{
    //Get text as input from user
    string text = get_string("Text: ");
    printf("Text: %s\n", text);

    //Call functions for counting
    int letters = count_letters(text);
    printf("Letters: %d\n", letters);

    int words = count_words(text);
    printf("Words: %d\n", words);

    int sentences = count_sentences(text);
    printf("Sentences: %d\n", sentences);

    //Calculate averages per 100
    float L = (letters / (float)words) * 100; //letters/words
    printf("Av letters %f\n", L);

    float S = (sentences / (float)words) * 100; //words/sentences
    printf("Av wordss %f\n", S);

    //Calculate Coleman-Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;
    printf("Index %f\n", index);

    //Print result
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}
