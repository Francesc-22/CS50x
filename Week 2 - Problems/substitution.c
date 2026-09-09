#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string cipher(string key, string plaintext);
int check_key(string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("1 Command-Line Argument Required.\n");
        return 1;
    }

    check_key(argv[1]);

    string plaintext = get_string("plaintext: ");
    string ciphertext = cipher(argv[1], plaintext);

    printf("ciphertext: %s\n", ciphertext);
    return 0;
}


string cipher(string key, string plaintext)
{
    char *ciphertext = malloc(strlen(plaintext) + 1);
    strcpy(ciphertext, plaintext);

    for (int i = 65; i <= 90; i++)
    {
        for (int j = 0; j < strlen(plaintext); j++)
        {
            if (plaintext[j] == i)
            {
                ciphertext[j] = toupper(key[i - 65]);
            }
            else if (plaintext[j] == i + 32)
            {
                ciphertext[j] = tolower(key[i - 65]);
            }
        }
    }

    return ciphertext;
}



int check_key(string key)
{
    if (strlen(key) != 26)
    {
        printf("Invalid Key. 26 Characters Needed.\n");
        return 1;
    }
    else
    {
        for (int i = 0; i < 26; i++)
        {
            if (!isalpha(key[i]))
            {
                printf("Invalid Key. Only Alphabetic Characters.\n");
                return 1;
            }
            for (int j = 1; j < 26; j++)
            {
                if (toupper(key[i]) == toupper(key[j]) && i != j)
                {
                    printf("Invalid Key. Repited Characters Detected.\n");
                    return 1;
                }
            }
        }
    }

    return 0;
}
