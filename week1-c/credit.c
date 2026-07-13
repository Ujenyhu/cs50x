#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

// American Express rules
const int AMEX_LENGTH = 15;
const int AMEX_PREFIX_1 = 34;
const int AMEX_PREFIX_2 = 37;

// MasterCard rules
const int MC_LENGTH = 16;
const int MC_PREFIX_MIN = 51;
const int MC_PREFIX_MAX = 55;

// Visa rules
const int VISA_LENGTH_SHORT = 13;
const int VISA_LENGTH_LONG = 16;
const int VISA_PREFIX_MATCH = 4;

bool validate_luhn(long card_number);
int get_card_length(long card_number);
int get_leading_digits(long card_number, int card_length, int digits_to_extract);
void classify_network(int length, long card_number);

int main(void)
{
    long card_number = get_long("Number: ");

    // Validate Length
    int length = get_card_length(card_number);

    // Luhn Validation
    if (!validate_luhn(card_number))
    {
        printf("INVALID\n");
        return 0;
    }

    // Confirm network or card type by prefix
    classify_network(length, card_number);

    return 0;
}

bool validate_luhn(long card_number)
{
    int total_sum = 0;
    bool process_alternate = false;

    while (card_number > 0)
    {
        // Extract the far right digit
        int digit = card_number % 10;

        if (process_alternate)
        {
            int product = digit * 2;
            // Add the individual digits of the product together
            total_sum += (product % 10) + (product / 10);
        }
        else
        {
            total_sum += digit;
        }

        // Flip the flag to process every other number
        process_alternate = !process_alternate;

        // Drop the processed number off the right side
        card_number /= 10;
    }

    return (total_sum % 10 == 0);
}

int get_card_length(long card_number)
{
    int length = 0;

    // Drop digits from right to left to compute total length
    while (card_number > 0)
    {
        length++;
        card_number /= 10;
    }
    return length;
}

int get_leading_digits(long card_number, int card_length, int digits_to_extract)
{
    long divisor = 1;
    int shifts_needed = card_length - digits_to_extract;

    // Calculate the exact power of 10 needed to shift the number
    for (int i = 0; i < shifts_needed; i++)
    {
        divisor *= 10;
    }

    return (int) (card_number / divisor);
}

void classify_network(int length, long card_number)
{
    // AMEX: 15 digits, starting with 34 or 37
    if (length == AMEX_LENGTH)
    {
        int prefix = get_leading_digits(card_number, length, 2);
        if (prefix == AMEX_PREFIX_1 || prefix == AMEX_PREFIX_2)
        {
            printf("AMEX\n");
            return;
        }
    }

    // MASTERCARD: 16 digits, starting with 51, 52, 53, 54, or 55
    if (length == MC_LENGTH)
    {
        int prefix = get_leading_digits(card_number, length, 2);
        if (prefix >= MC_PREFIX_MIN && prefix <= MC_PREFIX_MAX)
        {
            printf("MASTERCARD\n");
            return;
        }
    }

    // VISA: 13 or 16 digits, starting with 4
    if (length == VISA_LENGTH_SHORT || length == VISA_LENGTH_LONG)
    {
        int prefix = get_leading_digits(card_number, length, 1);
        if (prefix == VISA_PREFIX_MATCH)
        {
            printf("VISA\n");
            return;
        }
    }

    printf("INVALID\n");
}
