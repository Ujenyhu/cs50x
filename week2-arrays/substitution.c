#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Status Codes
const int STATUS_SUCCESS = 0;
const int STATUS_ERROR = 1;

//Cryptographic const
const int KEY_LENGTH = 26;

bool is_valid_key(string key);
void encrypt_text(string plaintext, string key);

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
    encrypt_text(plaintext, argv[1]);
    printf("\n");

    return STATUS_SUCCESS;
}

bool is_valid_key(string key)
{
    if(strlen(key) != KEY_LENGTH)
    {
        printf("Key must be %d characters.\n", KEY_LENGTH);
        return false;
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

        // Map character TO its 0-25 absolute position (Case-insentive)
        int alphabet_index = tolower(key[i]) - 'a';

        // Detect duplicate within the key string
        letter_counts[alphabet_index]++;
        if (letter_counts[alphabet_index] > 1)
        {
            printf("Key must not contain duplicate characters.\n");
            return false;
        }
    }

    return true;
}

void encrypt_text(string plaintext, string key)
{
    int n = strlen(plaintext);
    for(int i = 0; i < n; i++)
    {
        char target = plaintext[i];

        /*
        ** Find 0-indexed position
        ** look up key for substitution
        ** enfoce case-sensitivity. Must be in the smae case as the plaintext
        ** Maintain symbols, punctuation, and white spaces. No mutation
        */
        if (isupper(target))
        {
            int index = target - 'A';
            printf("%c", toupper(key[index]));
        }
        else if (islower(target))
        {
            int index = target - 'a';
            printf("%c", tolower(key[index]));
        }
        else
        {
            printf("%c", target);
        }
    }
}
