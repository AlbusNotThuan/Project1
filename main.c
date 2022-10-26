#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "./headers/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./headers/stb_image_write.h"

unsigned char *uc_arrayNew_1d(int _size)
{
    return (unsigned char *)calloc(_size, sizeof(unsigned char));
}


unsigned char *way2(unsigned char *weather_forecast, unsigned char *background, unsigned char *foreground, int width, int height, int channel, int channel_bg)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int one_pixel_diff= 0;
            for (int k = 0; k < channel; k++)
                {
                    one_pixel_diff += abs(foreground[i * width * channel + j * channel + k] - background[i * width * channel_bg + j * channel_bg + k]);
                    
                }
            if (one_pixel_diff>140)
                    {
                        for (int k = 0; k < 4; k++) 
                        weather_forecast[i * width * 3 + j * 3 + k] = foreground[i * width * channel + j * channel + k];
                    }
        }
    }
    return weather_forecast;
}


int main()
{
    // declare variables
    int width, height, channel;
    int width_bg, height_bg, channel_bg;
    int width_fg, height_fg, channel_fg;

    char background_img[] = "./images/background.png";
    char foreground_img[] = "./images/foreground.png";
    char weather_forecase_img[] = "./images/weather_forecast.jpg";
    char save_path[] = "./images/result.png";

    // read image data
    unsigned char *background = stbi_load(background_img, &width_bg, &height_bg, &channel_bg, 0);
    unsigned char *foreground = stbi_load(foreground_img, &width_fg, &height_fg, &channel_fg, 0);
    unsigned char *weather_forecast = stbi_load(weather_forecase_img, &width, &height, &channel, 0);
    if (background == NULL || foreground == NULL || weather_forecast == NULL)
    {
        printf("\nError in loading the image\n");
        exit(1);
    }
    // printf("Width = %d\nHeight = %d\nChannel = %d\n", width, height, channel);
    // printf("\nWidth_bg = %d\nHeight_bg = %d\nChannel_bg = %d\n", width_bg, height_bg, channel_bg);
    // printf("\nWidth_fg = %d\nHeight_fg = %d\nChannel_fg = %d\n", width_fg, height_fg, channel_fg);


    unsigned char *attemp2 = way2(weather_forecast, background, foreground, width, height, channel_fg, channel_bg);
    stbi_write_png(save_path, width, height, 3, attemp2, width*channel);
    printf("New image saved to %s\n", save_path);
}