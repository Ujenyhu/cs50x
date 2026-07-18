#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Status Codes
const int STATUS_SUCCESS = 0;
const int STATUS_ERROR = 1;

//Cryptographic const
const int KEY_LENGTH = 26;

//validation const (An enum would be largely preferred but to avoid going out of the course scope, this will do)
const int VALID_KEY = 0;
const int ERROR_INVALID_LENGTH = 1;
const int ERROR_NON_ALPHA = 2;
const int ERROR_DUPLICATE = 3;


int validate_key(string key);
string encrypt_text(string plaintext, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return STATUS_ERROR;
    }

    switch (validate_key(argv[1]))
    {
        case ERR_INVALID_LENGTH:
            printf("Key must be %d characters.\n", KEY_LENGTH);
            return STATUS_ERROR;

        case ERROR_NOT_ALPHA:
            printf("Key must contain only alphabetical characters.\n");
            return STATUS_ERROR;

        case ERROR_DUPLICATE:
            printf("Key must not contain duplicate characters.\n");
            return STATUS_ERROR;

        case VALID_KEY:
            break; // Proceed with the program
    }

    string plaintext = get_string("plaintext:  ");

    string ciphertext = encrypt_text(plaintext, argv[1]);
    printf("ciphertext: %s\n", ciphertext);

    return STATUS_SUCCESS;
}


int validate_key(string key)
{
    if (strlen(key) != KEY_LENGTH)
    {
        return ERROR_INVALID_LENGTH;
    }

    // Track duplicates
    bool letter_seen[KEY_LENGTH] = {false};

    for (int i = 0; i < KEY_LENGTH; i++)
    {
        if (!isalpha(key[i]))
        {
            return ERROR_NON_ALPHA;
        }

        // Map character TO its 0-25 absolute position (Case-insentive)
        int alphabet_index = tolower(key[i]) - 'a';

        // Detect duplicate within the key string
        if (letter_seen[alphabet_index])
        {
            return ERROR_DUPLICATE;
        }

        letter_seen[alphabet_index] = true;
    }

    return VALID_KEY;
}



/*
** Find 0-indexed position
** look up key for substitution
** enfoce case-sensitivity. Must be in the smae case as the plaintext
** Maintain symbols, punctuation, and white spaces. No mutation
*/
string encrypt_text(string plaintext, string key)
{
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char target = plaintext[i];

        if (isupper(target))
        {
            int index = target - 'A';
            plaintext[i] = toupper(key[index]);
        }
        else if (islower(target))
        {
            int index = target - 'a';
            plaintext[i] =  tolower(key[index]);
        }
    }
    return plaintext;
}
