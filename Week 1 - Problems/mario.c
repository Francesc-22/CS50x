#include <cs50.h>
#include <stdio.h>

void print_block(int n);
void print_space(int n);
bool check_height(int n);

int main(void)
{
    int height = get_int("Height: ");

    do
    {
        check_height(height);
        height = get_int("Height: ");
    }
    while (!check_height(height));

    for (int i = 0; i < height; i++)
    {
        for (int j=0; j < height - i - 1; j++)
        {
            print_space(1);
        }

        print_block(i + 1);
        print_space(2);
        print_block(i + 1);
        printf("\n");
    }
}

// Print a block of hashes.
void print_block(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}

// Print a block of spaces.
void print_space(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

// Check if the height is valid.
bool check_height(int n)
{
    if (n < 1 || n > 8)
    {
        printf("Height must be between 1 and 8.\n");
        return false;
    }
    else
    {
        return true;
    }
}
