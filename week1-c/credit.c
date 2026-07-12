#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>

bool validate_luhn(long card_number);
int get_card_length(long card_number);
int get_leading_digits(long card_number, int digit_count);
void classify_network(int length, int prefix);
