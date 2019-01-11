#include <stdint.h>
#include <stdlib.h>

#include "radar.h"
#include "../screen.h"
#include "../utils.h"


radar_t *init_radar(screen_t screen, int x, int y, int radius, int n, int ticks,
		    radar_fill_t fill, color_t fg, color_t bg)
{
    radar_t *ret;
    int i;

    for (i = 0; i < n; i++)
	draw_line(screen, x, y, radius * cos(6.28 / n * i) + x,
		  radius * sin(6.28 / n * i) + y, fg);

    for (i = 1; i <= ticks; i++)
	draw_circle(screen, x, y, radius / ticks * i, fg);


    ret = (radar_t *) malloc(sizeof(radar_t));
    ret->x = x;
    ret->y = y;
    ret->radius = radius;
    ret->n = n;
    ret->ticks = ticks;
    ret->fill = fill;
    ret->oldx = (int *) calloc(n, sizeof(int));
    ret->oldy = (int *) calloc(n, sizeof(int));
    ret->valx = (int *) calloc(n, sizeof(int));
    ret->valy = (int *) calloc(n, sizeof(int));
    ret->fg = fg;
    ret->bg = bg;

    for (i = 0; i < n; i++) {
	ret->oldx[i] = x;
	ret->oldy[i] = y;
    }

    return ret;
}

void update_radar(screen_t screen, radar_t * radar, uint8_t * values)
{
    int i;

    if (radar->fill == R_NOFILL)
	for (i = 0; i < radar->n; i++)
	    draw_line(screen, radar->oldx[i], radar->oldy[i],
		      radar->oldx[(i + 1) % radar->n],
		      radar->oldy[(i + 1) % radar->n], radar->bg);
    else
	fill_poly(screen, radar->x - radar->radius, radar->y - radar->radius,
		  radar->x + radar->radius, radar->y + radar->radius,
		  radar->oldx, radar->oldy, radar->n, radar->bg);

    for (i = 1; i <= radar->ticks; i++)
	draw_circle(screen, radar->x, radar->y,
		    radar->radius / radar->ticks * i, radar->fg);


    /* calcola nuovi values */
    radar->valx = (int *) calloc(radar->n, sizeof(int));
    radar->valy = (int *) calloc(radar->n, sizeof(int));
    for (i = 0; i < radar->n; i++) {
	radar->valx[i] =
	    values[i] * radar->radius / 0xff * cos(6.28 * i / radar->n) +
	    radar->x;
	radar->valy[i] =
	    values[i] * radar->radius / 0xff * sin(6.28 * i / radar->n) +
	    radar->y;
    }


    if (radar->fill == R_NOFILL)
	for (i = 0; i < radar->n; i++)
	    draw_line(screen, radar->valx[i], radar->valy[i],
		      radar->valx[(i + 1) % radar->n],
		      radar->valy[(i + 1) % radar->n], radar->fg);
    else
	fill_poly(screen, radar->x - radar->radius, radar->y - radar->radius,
		  radar->x + radar->radius, radar->y + radar->radius,
		  radar->valx, radar->valy, radar->n, radar->fg);
    for (i = 0; i < radar->n; i++)
	draw_line(screen, radar->x, radar->y,
		  radar->radius * cos(6.28 / radar->n * i) + radar->x,
		  radar->radius * sin(6.28 / radar->n * i) + radar->y,
		  radar->fg);

    free(radar->oldx);
    free(radar->oldy);
    radar->oldx = radar->valx;
    radar->oldy = radar->valy;
}

void delete_radar(screen_t screen, radar_t * radar)
{
    int i;

    if (radar->fill == R_NOFILL)
	for (i = 0; i < radar->n; i++)
	    draw_line(screen, radar->oldx[i], radar->oldy[i],
		      radar->oldx[(i + 1) % radar->n],
		      radar->oldy[(i + 1) % radar->n], radar->bg);
    else
	fill_poly(screen, radar->x - radar->radius, radar->y - radar->radius,
		  radar->x + radar->radius, radar->y + radar->radius,
		  radar->oldx, radar->oldy, radar->n, radar->bg);
    for (i = 0; i < radar->n; i++)
	draw_line(screen, radar->x, radar->y,
		  radar->radius * cos(6.28 / radar->n * i) + radar->x,
		  radar->radius * sin(6.28 / radar->n * i) + radar->y,
		  radar->bg);

    for (i = 1; i <= radar->ticks; i++)
	draw_circle(screen, radar->x, radar->y,
		    radar->radius / radar->ticks * i, radar->bg);

    free(radar->oldx);
    free(radar->oldy);
    free(radar->valx);
    free(radar->valy);
    free(radar);
}
