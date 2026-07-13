#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/**
 * NOTE: This implementation uses a three call traversal strategy O(3N).
 * It complies with the assignment's modular function specifications. In production,
 * this should be refactored into a single-pass O(N) loop that calculates the letters,
 * words, and sentences simultaneously to avoid redundant memory scans.
 */

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_coleman_liau(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");

    // handle empty input immediately to prevent division by zero
    if (strlen(text) == 0)
    {
        printf("Before Grade 1\n");
        return 0;
    }

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Calculate the grade level
    int grade = calculate_coleman_liau(letters, words, sentences);

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

    return 0;
}

int count_letters(string text)
{
    int letters = 0;

    // Loop to count alphabet characters
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int space_count = 0;

    // Count words by tracking spaces
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            space_count++;
        }
    }

    // Account for the final word after the last space
    return space_count + 1;
}

int count_sentences(string text)
{
    int sentences = 0;

    // Count sentences based on punctuation marks
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}

int calculate_coleman_liau(int letters, int words, int sentences)
{
    // Calculate averages per 100 words using floating-point math
    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;

    // Apply Coleman-Liau index formula
    float index = 0.0588 * L - 0.296 * S - 15.8;

    return (int) round(index);
}
