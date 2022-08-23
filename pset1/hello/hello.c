#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Asking user for name
    string name = get_string("What is your name?\n");
    //Greeting user
    printf("Hello, %s\n", name);
}
