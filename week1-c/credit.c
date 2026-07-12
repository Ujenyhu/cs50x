#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>

bool validate_luhn(long card_number);
int get_card_length(long card_number);
int get_leading_digits(long card_number, int digit_count);
void classify_network(int length, int prefix);

// American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers.
const int min_length = 13;
const int max_length =16;

int main(void)
{
    long card_number = get_long("Number: ");

    // Validate Length
    int length = get_card_length(card_number);
    if (length < min_length || length > max_length)
    {
        printf("INVALID\n");
        return 0;
    }

    // Luhn Validation
    if (!validate_luhn(card_number))
    {
        printf("INVALID\n");
        return 0;
    }

    // 4. Prefix Extraction and Final Network Resolution
    int prefix = get_leading_digits(card_number, length);
    classify_network(length, prefix);

    return 0;
}
