#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>

#include "include/stb_image.h"
#include "include/stb_image_resize.h"

#define MAX_IMAGES 100

int main(int argc, char *argv[])
{
    int new_width = 80;
    int new_height = 80;

    char chars[] = ".:-=+*#%@";
    int chars_len = strlen(chars);

    char *images[MAX_IMAGES];
    int img_idx = 0;

    if (argc < 2)
    {
        printf("No image file provided!");
        return 1;
    }
    for (int i = 0; i < argc; i++)
    {
        if (strstr(argv[i], ".jpg") || (strstr(argv[i], ".png")))
        {
            images[img_idx] = argv[i];
            ++img_idx;
        }
    }

    for (int i = 0; i < img_idx; i++)
    {
        char *image = images[i];
        int width, height, channels;

        unsigned char *pixels = stbi_load(image, &width, &height, &channels, 3);

        if (pixels == NULL)
        {
            printf("Failed to load image: %s", image);
            stbi_image_free(pixels);
            continue;
        }

        unsigned char *resized_pixels = (unsigned char *)malloc(new_width * new_height * channels);

        stbir_resize_uint8(pixels, width, height, 0, resized_pixels, new_width, new_height, 0, channels);

        for (int row_idx = 0; row_idx < new_height; row_idx++)
        {
            for (int col_idx = 0; col_idx < new_width; col_idx++)
            {
                unsigned char red = *resized_pixels++;
                unsigned char green = *resized_pixels++;
                unsigned char blue = *resized_pixels++;

                float average = (red + green + blue) / 3.0f;
                int char_idx = (int)(chars_len * (average / 255.0f));
                putchar(chars[char_idx]);
            }

            putchar('\n');
        }

        stbi_image_free(pixels);
    }

    return 0;
}
