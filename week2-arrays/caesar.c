#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// status codes
const int STATUS_SUCCESS = 0;
const int STATUS_ERROR = 1;

// Cryptographic constants
const int ALPHABET_SIZE = 26;

bool only_digits(string text);

int main(int argc, string argv[])
{
    // Only one command line is expected
    if(argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return STATUS_ERROR;
    }

    if(!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return STATUS_ERROR;
    }

    // Convert ASCII argument to integer primitive
    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");
    encrypt_and_print_text(plaintext, key);
    printf("\n");

    return STATUS_SUCCESS;
}


bool only_digits(string s)
{
    for(int i = 0, n = strlen(s); i < n; i++)
    {
        if(!isdigit(s[i]))
        {
            return false;
        }
    }

    return true;
}


void encrypt_text(string plaintext, int key)
{
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        int shift = n % 26;
        char c = plaintext[i];

        if (isupper(c))
        {
            // Convert ASCII to 0-25 base, shift dynamically, restore ASCII offset
            char shifted = ((c - 'A') + key) % ALPHABET_SIZE + 'A';
            printf("%c", shifted);
        }
        else if (islower(c))
        {
            // Convert ASCII to 0-25 base, shift dynamically, restore ASCII offset
            char shifted = ((c - 'a') + key) % ALPHABET_SIZE + 'a';
            printf("%c", shifted);
        }
        else
        {
            // Pass-through layer for spaces, numbers, and punctuation
            printf("%c", c);
        }
    }
