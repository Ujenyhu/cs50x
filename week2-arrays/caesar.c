#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Status Codes
const int STATUS_SUCCESS = 0;
const int STATUS_ERROR = 1;

const int ALPHABET_SIZE = 26;

bool only_digits(string s);
void encrypt_text(string plaintext, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return STATUS_ERROR;
    }

    // ensure the string is strictly numeric characters
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return STATUS_ERROR;
    }

    //Convert the string argument to an integer primitive
    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext:  ");

    printf("ciphertext: ");
    encrypt_text(plaintext, key);
    printf("\n");

    return STATUS_SUCCESS;
}

//Validates that a string buffer contains exclusively numeric characters.

bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}


void encrypt_text(string plaintext, int key)
{
    // Calculate the absolute shift position once to handle keys > 26
    int shift = key % ALPHABET_SIZE;

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];

        if (isupper(c))
        {
            // ASCII to 0-25 relative offset for uppercase
            char shifted = ((c - 'A') + shift) % ALPHABET_SIZE + 'A';
            printf("%c", shifted);
        }
        else if (islower(c))
        {
            // Map ASCII to 0-25 relative offset for lowercase
            char shifted = ((c - 'a') + shift) % ALPHABET_SIZE + 'a';
            printf("%c", shifted);
        }
        else
        {
            // Non alphabets shows completely unecrypted
            printf("%c", c);
        }
    }
}
