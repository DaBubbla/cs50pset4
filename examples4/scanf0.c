
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int x;
    printf("x: ");
    scanf("%i", &x); //& = get the address of this var
    printf("x: %i\n", x);
}