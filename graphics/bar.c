#include <stdint.h>
#include <stdlib.h>

#include "bar.h"
#include "../screen.h"


bar_t *init_bar(screen_t screen, int x1, int x2, int y1, int y2,
		bar_direction_t dir, color_t fg, color_t bg)
{
    bar_t *ret;
    int i, j;

    for (i = x1; i < x2; i++)
	for (j = y1; j < y2; j++)
	    put_pixel(screen, i, j, bg);

    ret = (bar_t *) malloc(sizeof(bar_t));
    ret->x1 = x1;
    ret->x2 = x2;
    ret->y1 = y1;
    ret->y2 = y2;
    ret->dir = dir;
    ret->oldval = 0;
    ret->fg = fg;
    ret->bg = bg;

    return ret;
}

void update_bar(screen_t screen, bar_t * bar, uint8_t value)
{
    int i, j;
    int min = 0, max = 0;
    color_t tmp;

    if (bar->dir == B_HORIZONTAL) {
	if (value < bar->oldval) {
	    min = value;
	    max = bar->oldval;
	    tmp = bar->bg;
	} else {
	    max = value;
	    min = bar->oldval;
	    tmp = bar->fg;
	}

	for (i = bar->x1 + min * (bar->x2 - bar->x1) / 0xff;
	     i < bar->x1 + max * (bar->x2 - bar->x1) / 0xff; i++)
	    for (j = bar->y1; j < bar->y2; j++)
		put_pixel(screen, i, j, tmp);
    } else {

	if (value < bar->oldval) {
	    min = value;
	    max = bar->oldval;
	    tmp = bar->bg;
	} else {
	    max = value;
	    min = bar->oldval;
	    tmp = bar->fg;
	}

	for (i = bar->x1; i < bar->x2; i++)
	    for (j = bar->y2 - max * (bar->y2 - bar->y1) / 0xff;
		 j < bar->y2 - min * (bar->y2 - bar->y1) / 0xff; j++)
		put_pixel(screen, i, j, tmp);
    }

    bar->oldval = value;
}

void delete_bar(screen_t screen, bar_t * bar)
{
    int i, j;

    for (i = bar->x1; i < bar->x2; i++)
	for (j = bar->y1; j < bar->y2; j++)
	    put_pixel(screen, i, j, bar->bg);

    free(bar);
}
