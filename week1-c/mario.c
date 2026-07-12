#include <cs50.h>
#include <stdio.h>

int get_pyramid_height(void);
void render_pyramid(int height);
void print_characters(char character, int count);

//Bind user's valid height values to [1, 8] inclusive
const int minHeight = 1;
const int maxHeight = 8;

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
    while (height < minHeight || height > maxHeight)

    return height;
}


void render_pyramid(int height)
{
    for(int row = 1; row <= height; row++)
    {

    }
}
