#include <stdint.h>
#include <stdlib.h>

#include "plot.h"
#include "../screen.h"
#include "../utils.h"



plot_t *init_plot(screen_t screen, int x1, int x2, int y1, int y2, color_t fg,
		  color_t bg)
{
    plot_t *ret;
    int i, j;

    for (i = x1; i < x2; i++)
	for (j = y1; j < y2; j++)
	    put_pixel(screen, i, j, bg);

    ret = (plot_t *) malloc(sizeof(plot_t));

    ret->x1 = x1;
    ret->x2 = x2;
    ret->y1 = y1;
    ret->y2 = y2;
    ret->fg = fg;
    ret->bg = bg;
    ret->i = 0;
    ret->oldval = 0;

    return ret;
}

void delete_plot(screen_t screen, plot_t * plot)
{
    int i, j;

    for (i = plot->x1; i < plot->x2; i++)
	for (j = plot->y1; j < plot->y2; j++)
	    put_pixel(screen, i, j, plot->bg);

    free(plot);
}

void update_plot(screen_t screen, plot_t * plot, uint8_t value)
{
    int j;

    plot->i = (plot->i + 1) % (plot->x2 - plot->x1);
    for (j = plot->y1; j < plot->y2; j++)
	if (j > plot->y2 - (plot->y2 - plot->y1) * value / 0xff)
	    put_pixel(screen, plot->i + plot->x1, j, plot->fg);
	else
	    put_pixel(screen, plot->i + plot->x1, j, plot->bg);
}
