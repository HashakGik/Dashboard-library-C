#include <stdint.h>
#include <stdlib.h>

#include "dial.h"
#include "../screen.h"
#include "../utils.h"



dial_t *init_dial(screen_t screen, int x, int y, int radius, int ticks,
		  double arc, double phase, dial_direction_t dir, color_t fg,
		  color_t bg)
{
    int i;
    double j, k;
    dial_t *ret;

    for (i = 0; i < arc * 200; i++) {
	j = radius * cos(i / 200.0 + phase) + x;
	k = radius * sin(i / 200.0 + phase) + y;

	put_pixel(screen, j, k, fg);
    }

    int l;
    for (l = 0; l <= ticks; l++) {
	for (i = 0; i < radius * 0.15; i++) {
	    j = x + (radius - i) * cos(phase + l * arc / ticks);
	    k = y + (radius - i) * sin(phase + l * arc / ticks);
	    put_pixel(screen, j, k, fg);
	}
    }

    ret = (dial_t *) malloc(sizeof(dial_t));
    ret->x = x;
    ret->y = y;
    ret->radius = radius;
    ret->ticks = ticks;
    ret->arc = arc;
    ret->phase = phase;
    ret->dir = dir;
    ret->oldval = 0;
    ret->fg = fg;
    ret->bg = bg;

    return ret;
}

void update_dial(screen_t screen, dial_t * dial, uint8_t value)
{
    uint8_t tmp;

    tmp = (dial->dir == D_CLOCKWISE) ? 0xff - dial->oldval : dial->oldval;
    draw_line(screen, dial->x, dial->y,
	      dial->radius * 0.8 * cos(dial->phase + dial->arc * tmp / 255.0) +
	      dial->x,
	      dial->radius * 0.8 * sin(dial->phase + dial->arc * tmp / 255.0) +
	      dial->y, dial->bg);
    tmp = (dial->dir == D_CLOCKWISE) ? 0xff - value : value;
    draw_line(screen, dial->x, dial->y,
	      dial->radius * 0.8 * cos(dial->phase + dial->arc * tmp / 255.0) +
	      dial->x,
	      dial->radius * 0.8 * sin(dial->phase + dial->arc * tmp / 255.0) +
	      dial->y, dial->fg);

    dial->oldval = value;

}

void delete_dial(screen_t screen, dial_t * dial)
{
    int i;
    uint8_t tmp;
    double j, k;

    tmp = (dial->dir == D_CLOCKWISE) ? 0xff - dial->oldval : dial->oldval;
    draw_line(screen, dial->x, dial->y,
	      dial->radius * 0.8 * cos(dial->phase + dial->arc * tmp / 255.0) +
	      dial->x,
	      dial->radius * 0.8 * sin(dial->phase + dial->arc * tmp / 255.0) +
	      dial->x, dial->bg);

    for (i = 0; i < dial->arc * 200; i++) {
	j = dial->radius * cos(i / 200.0 + dial->phase) + dial->x;
	k = dial->radius * sin(i / 200.0 + dial->phase) + dial->y;

	put_pixel(screen, j, k, dial->bg);
    }

    int l;
    for (l = 0; l <= dial->ticks; l++) {
	for (i = 0; i < dial->radius * 0.15; i++) {
	    j = dial->x + (dial->radius - i) * cos(dial->phase +
						   l * dial->arc / dial->ticks);
	    k = dial->y + (dial->radius - i) * sin(dial->phase +
						   l * dial->arc / dial->ticks);
	    put_pixel(screen, j, k, dial->bg);
	}
    }

    free(dial);
}
