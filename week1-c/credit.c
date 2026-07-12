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

    // Confirm network or card type by prefix
    int prefix = get_leading_digits(card_number, length);
    classify_network(length, prefix);

    return 0;
}


bool validate_luhn(long card_number)
{
    int total_sum = 0;
    bool alternate = false;

    while (card_number > 0)
    {
        int current_digit = card_number % 10;

        if (alternate)
        {
            int multiplied = current_digit * 2;
            // Sum the digits of the product
            total_sum += (multiplied % 10) + (multiplied / 10);
        }
        else
        {
            total_sum += current_digit;
        }

        alternate = !alternate;
        card_number /= 10;
    }

    return (total_sum % 10 == 0);
}


 //Calculates total length.

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


int get_leading_digits(long card_number, int digit_count)
{
    // Scale downward until only the top 2 digits remain
    while (card_number >= 100)
    {
        card_number /= 10;
    }
    return (int)card_number;
}

void classify_network(int length, int prefix)
{
    int primary_digit = prefix / 10;

    // AMEX: 15 digits, starting with 34 or 37
    if (length == 15 && (prefix == 34 || prefix == 37))
    {
        printf("AMEX\n");
    }
    // MASTERCARD: 16 digits, starting with 51, 52, 53, 54, or 55
    else if (length == 16 && prefix >= 51 && prefix <= 55)
    {
        printf("MASTERCARD\n");
    }
    // VISA: 13 or 16 digits, starting with 4
    else if ((length == 13 || length == 16) && primary_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
