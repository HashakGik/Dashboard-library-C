#include <stdint.h>
#include <stdlib.h>

#include "symbol.h"
#include "dashboard.h"
#include "ascii.h"
#include "../screen.h"
#include "../utils.h"




void put_symbol(screen_t screen, int id, int x, int y, color_t color)
{
    int i, j, k;
    color_t tmp;

    for (k = 0, i =
	 id * DASHBOARD_WIDTH * DASHBOARD_HEIGHT * DASHBOARD_BYTES_PER_PIXEL;
	 i <
	 (id +
	  1) * DASHBOARD_WIDTH * DASHBOARD_HEIGHT * DASHBOARD_BYTES_PER_PIXEL;
	 i += DASHBOARD_WIDTH * DASHBOARD_BYTES_PER_PIXEL, k++)
	for (j = 0; j < DASHBOARD_WIDTH * DASHBOARD_BYTES_PER_PIXEL;
	     j += DASHBOARD_BYTES_PER_PIXEL) {
	    tmp.r = DASHBOARD_PIXEL_DATA[i + j] & color.r;
	    tmp.g = DASHBOARD_PIXEL_DATA[i + j + 1] & color.g;
	    tmp.b = DASHBOARD_PIXEL_DATA[i + j + 2] & color.b;
	    put_pixel(screen, j / DASHBOARD_BYTES_PER_PIXEL + x, k + y, tmp);
	}

}

void delete_symbol(screen_t screen, int x, int y, color_t bg)
{
    int i, j;
    for (i = 0; i < DASHBOARD_HEIGHT; i++)
	for (j = 0; j < DASHBOARD_WIDTH; j++)
	    put_pixel(screen, j + x, i + y, bg);
}


void put_char(screen_t screen, char id, int x, int y, color_t color)
{
    int i, j, k;
    color_t tmp;

    for (k = 0, i = id * ASCII_WIDTH * ASCII_HEIGHT * ASCII_BYTES_PER_PIXEL;
	 i < (id + 1) * ASCII_WIDTH * ASCII_HEIGHT * ASCII_BYTES_PER_PIXEL;
	 i += ASCII_WIDTH * ASCII_BYTES_PER_PIXEL, k++)
	for (j = 0; j < ASCII_WIDTH * ASCII_BYTES_PER_PIXEL;
	     j += ASCII_BYTES_PER_PIXEL) {
	    tmp.r = ASCII_PIXEL_DATA[i + j] & color.r;
	    tmp.g = ASCII_PIXEL_DATA[i + j + 1] & color.g;
	    tmp.b = ASCII_PIXEL_DATA[i + j + 2] & color.b;
	    put_pixel(screen, j / ASCII_BYTES_PER_PIXEL + x, k + y, tmp);
	}

}

void delete_char(screen_t screen, int x, int y, color_t bg)
{
    int i, j;
    for (i = 0; i < ASCII_HEIGHT; i++)
	for (j = 0; j < ASCII_WIDTH; j++)
	    put_pixel(screen, j + x, i + y, bg);
}

void print(screen_t screen, int x, int y, char *str, color_t color)
{
    int i, tmpx = x, tmpy = y;

    for (i = 0; str[i] != '\0'; i++) {
	if (str[i] == '\n') {
	    tmpy += ASCII_HEIGHT;
	    tmpx = x;
	} else if (str[i] != '\0') {
	    put_char(screen, str[i], tmpx, tmpy, color);
	    tmpx += ASCII_WIDTH;
	}
    }

}
