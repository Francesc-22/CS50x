// Scrabble

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int count_score(string word);

int main(void)
{
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");

    int score1 = count_score(p1);
    int score2 = count_score(p2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int count_score(string word)
{
    int score = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        char letter = toupper(word[i]);
        if (letter == 'A' || letter == 'E' || letter == 'I' || letter == 'L' || letter == 'N' ||
            letter == 'O' || letter == 'R' || letter == 'S' || letter == 'T' || letter == 'U')
        {
            score += 1;
        }
        else if (letter == 'D' || letter == 'G')
        {
            score += 2;
        }
        else if (letter == 'B' || letter == 'C' || letter == 'M' || letter == 'P')
        {
            score += 3;
        }
        else if (letter == 'F' || letter == 'H' || letter == 'V' || letter == 'W' || letter == 'Y')
        {
            score += 4;
        }
        else if (letter == 'K')
        {
            score += 5;
        }
        else if (letter == 'J' || letter == 'X')
        {
            score += 8;
        }
        else if (letter == 'Q' || letter == 'Z')
        {
            score += 10;
        }
    }

    return score;
}
