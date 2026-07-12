#include <cs50.h>
#include <stdio.h>

int get_pyramid_height(void);
void render_pyramid(int height);
void print_characters(char character, int count);

// valid height should be [1, 8] inclusive
const int min_height = 1;
const int max_height = 8;

int main(void)
{
    int height = get_pyramid_height();

    render_pyramid(height);

    return 0;
}

int get_pyramid_height(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < min_height || height > max_height);

    return height;
}

void render_pyramid(int height)
{
    for (int row = 1; row <= height; row++)
    {
        // indentation spaces on the left start
        int spaces = height - row;
        print_characters(' ', spaces);

        // Left pyramid segment
        print_characters('#', row);

        // The divider gap
        printf("  ");

        // Right segment
        print_characters('#', row);

        printf("\n");
    }
}

void print_characters(char character, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("%c", character);
    }
}
