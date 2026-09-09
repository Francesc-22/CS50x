#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long credit = get_long("Credit: ");
    bool other = false;
    int result = 0;

    while (credit > 0)
    {
        long number = credit % 10;

        if (other)
        {
            number = number * 2;
            if (number > 9)
            {
                result += (number % 10) + (number / 10);
            }
            else
            {
                result += number;
            }
        }
        else
        {
            result += number;
        }
        other = !other;
        credit /= 10;
    }

    if (result % 10 == 0)
    {
        printf("VALID\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
