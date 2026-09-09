#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float count_grade(string text);

int main(void)
{
    string text = get_string("Text: ");
    float grade = count_grade(text);
    grade = round(grade);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %0.0f\n", grade);
    }

    return 0;
}

float count_grade(string text)
{
    float number_words = 1;
    int number_letters = 0;
    int number_sentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            number_letters += 1;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            number_sentences += 1;
        }
        else if (text[i] == ' ')
        {
            number_words += 1;
        }
    }

    float L = (number_letters / number_words) * 100;
    float S = (number_sentences / number_words) * 100;

    float grade = 0.0588 * L - 0.296 * S - 15.8;

    return grade;
}
