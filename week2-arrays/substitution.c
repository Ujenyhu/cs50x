#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Status Codes
const int STATUS_SUCCESS = 0;
const int STATUS_ERROR = 1;

//Cryptographic const
const int KEY_LENGTH = 26;

bool is_valid_key(string s);
void encrypt_text(string plaintext, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return STATUS_ERROR;
    }


    if (!is_valid_key(argv[1]))
    {
        return STATUS_ERROR;
    }

    string plaintext = get_string("plaintext:  ");

    printf("ciphertext: ");
    encrypt_text(plaintext, key);
    printf("\n");

    return STATUS_SUCCESS;
}

bool is_valid_key(string s)
{
    if(strlen(s) != KEY_LENGTH)
    {
        printf("Key must be %d characters.\n", KEY_LENGTH);
    }

    int letter_counts[KEY_LENGTH] = {0};
    for(int i = 0; i < KEY_LENGTH; i++)
    {
        // Every character must be alphabetical
        if (!isalpha(key[i]))
        {
            printf("Key must contain only alphabetical characters.\n");
            return false;
        }
    }
}
