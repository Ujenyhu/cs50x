#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Status Codes
const int STATUS_SUCCESS = 0;
const int STATUS_ERROR = 1;

//Cryptographic const
const int KEY_LENGTH = 26;

string validate_key(string key);
string encrypt_text(string plaintext, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return STATUS_ERROR;
    }

    string error_message = validate_key(argv[1]);
    if (error_message != NULL)
    {
        printf("%s", error_message);
        return STATUS_ERROR;
    }

    string plaintext = get_string("plaintext:  ");

    string ciphertext = encrypt_text(plaintext, argv[1]);
    printf("ciphertext: %s\n", ciphertext);

    return STATUS_SUCCESS;
}

string validate_key(string key)
{
    if(strlen(key) != KEY_LENGTH)
    {
        return ("Key must be %d characters.\n", KEY_LENGTH);
    }

    int letter_counts[KEY_LENGTH] = {0};
    for(int i = 0; i < KEY_LENGTH; i++)
    {
        if (!isalpha(key[i]))
        {
            return "Key must contain only alphabetical characters.\n";
        }

        // Map character TO its 0-25 absolute position (Case-insentive)
        int alphabet_index = tolower(key[i]) - 'a';

        // Detect duplicate within the key string
        letter_counts[alphabet_index]++;
        if (letter_counts[alphabet_index] > 1)
        {
            return "Key must not contain duplicate characters.\n";
        }
    }

    return NULL;
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
