#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>

// Card constraints
const int MIN_CARD_LENGTH = 13;
const int MAX_CARD_LENGTH = 16;

// American Express routing values
const int AMEX_LENGTH = 15;
const int AMEX_PREFIX_1 = 34;
const int AMEX_PREFIX_2 = 37;

// MasterCard routing values
const int MC_LENGTH = 16;
const int MC_PREFIX_MIN = 51;
const int MC_PREFIX_MAX = 55;

// Visa routing values
const int VISA_LENGTH_SHORT = 13;
const int VISA_LENGTH_LONG = 16;
const int VISA_PREFIX_MATCH = 4;

bool validate_luhn(long card_number);
int get_card_length(long card_number);
int get_prefix(long card_number, int card_length);
void classify_network(int length, int prefix);

int main(void)
{
    long card_number = get_long("Number: ");

    // Validate length
    int length = get_card_length(card_number);
    if (length < MIN_CARD_LENGTH || length > MAX_CARD_LENGTH)
    {
        printf("INVALID\n");
        return 0;
    }

    // Validate the card against Luhn's mathematical checksum
    if (!validate_luhn(card_number))
    {
        printf("INVALID\n");
        return 0;
    }

    // Get the identifying prefix and resolve the network provider
    int prefix = get_prefix(card_number, length);
    classify_network(length, prefix);

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

        // Toggle state back and forth to target alternate digits
        process_alternate = !process_alternate;

        // Drop the processed digit off the right side
        card_number /= 10;
    }

    return (total_sum % 10 == 0);
}

/**
 * Calculates total count of digits present inside the input primitive.
 */
int get_card_length(long card_number)
{
    int length = 0;
    while (card_number > 0)
    {
        length++;
        card_number /= 10;
    }
    return length;
}

/**
 * Drops trailing numbers simultaneously to isolate the top 2 leading digits.
 */
int get_prefix(long card_number, int card_length)
{
    long divisor = 1;
    int shifts_needed = card_length - 2;

    // Build the scale factor needed to shift the number decimal place
    for (int i = 0; i < shifts_needed; i++)
    {
        divisor *= 10;
    }

    return (int)(card_number / divisor);
}

/**
 * Appears to matching rules to output specific network string literals.
 */
void classify_network(int length, int prefix)
{
    // Extract the absolute first digit for Visa checking
    int first_digit = prefix / 10;

    if (length == AMEX_LENGTH && (prefix == AMEX_PREFIX_1 || prefix == AMEX_PREFIX_2))
    {
        printf("AMEX\n");
    }
    else if (length == MC_LENGTH && prefix >= MC_PREFIX_MIN && prefix <= MC_PREFIX_MAX)
    {
        printf("MASTERCARD\n");
    }
    else if ((length == VISA_LENGTH_SHORT || length == VISA_LENGTH_LONG) && first_digit == VISA_PREFIX_MATCH)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
