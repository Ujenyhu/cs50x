#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/**
 * NOTE: This implementation uses a three call traversal strategy O(3N).
 * It complies with the assignment's function specifications. In production,
 * this should be refactored into a single O(N) loop that calculates the letters,
 * words, and sentences simultaneously to avoid redundant memory scans.
 */

// Coleman-Liau formula constants
const float COEFFICIENT_LETTERS = 0.0588f;
const float COEFFICIENT_SENTENCES = 0.296f;
const float FORMULA_CONSTANT = 15.8f;

// Grade scoring limits
const int MAX_GRADE_THRESHOLD = 16;
const int MIN_GRADE_THRESHOLD = 1;

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_coleman_liau(int letters, int words, int sentences);

int main(void)
{
    string text = get_string("Text: ");

    if (strlen(text) == 0)
    {
        printf("Before Grade 1\n");
        return 0;
    }

    // Count parameters in text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Calculate the grade level
    int grade = calculate_coleman_liau(letters, words, sentences);

    if (grade >= MAX_GRADE_THRESHOLD)
    {
        printf("Grade 16+\n");
    }
    else if (grade < MIN_GRADE_THRESHOLD)
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

    // count alphabet characters
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
    int words = 0;

    // Count words by tracking spaces
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // A word end is hit when the current char is data and the next is a delimiter or null
        if (text[i] != ' ' && (text[i + 1] == ' ' || text[i + 1] == '\0'))
        {
            words++;
        }
    }
    return words;
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
    // Calculate averages per 100 words
    float L = ((float) letters / words) * 100.0f;
    float S = ((float) sentences / words) * 100.0f;

    // Apply Coleman-Liau index formula
    float index = (COEFFICIENT_LETTERS * L) - (COEFFICIENT_SENTENCES * S) - FORMULA_CONSTANT;

    return (int) round(index);
}
