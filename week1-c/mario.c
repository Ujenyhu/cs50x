#include <cs50.h>
#include <stdio.h>

int get_pyramid_height(void);
void render_pyramid(int height);
void print_characters(char character, int count);

int main(void)
{
    int height = get_pyramid_height();

    render_pyramid(height);

    return 0;
}
