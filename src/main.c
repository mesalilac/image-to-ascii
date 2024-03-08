#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <string.h>

#include "include/stb_image.h"

#define MAX_IMAGES 100

int main(int argc, char *argv[])
{
    char chars[] = "^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
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
        unsigned char *data = stbi_load(image, &width, &height, &channels, 3);

        if (data == NULL)
        {
            printf("Failed to load image: %s", image);
            stbi_image_free(data);
            continue;
        }

        /* printf("Loaded image with a width of %dpx, a height of %dpx, and %d channels\n", width, height, channels); */

        unsigned char *pixels = data;

        for (int row_idx = 0; row_idx < height; row_idx++)
        {
            for (int col_idx = 0; col_idx < width; col_idx++)
            {
                unsigned char red = *pixels++;
                unsigned char green = *pixels++;
                unsigned char blue = *pixels++;

                float average = (red + green + blue) / 3.0f;
                int char_idx = (int)(chars_len * (average / 255.0f));
                putchar(chars[char_idx]);
            }

            putchar('\n');
        }

        stbi_image_free(data);
    }

    return 0;
}
