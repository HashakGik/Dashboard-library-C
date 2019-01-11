#include <stdint.h>
#include <stdlib.h>

#include "accelerometer.h"
#include "../screen.h"
#include "../utils.h"


accelerometer_t *init_accelerometer(screen_t screen, int x, int y, int length,
				    int rings, accelerometer_shape_t shape,
				    color_t fg, color_t bg)
{
    accelerometer_t *ret;
    int i, j, l;

    if (shape == A_SQUARE)
	for (j = 1; j <= rings; j++)
	    for (i = -length / rings / 2 * j; i < length / rings / 2 * j; i++) {
		put_pixel(screen, x + i, y - length / rings / 2 * j, fg);
		put_pixel(screen, x + i, y + length / rings / 2 * j, fg);
		put_pixel(screen, x - length / rings / 2 * j, y + i, fg);
		put_pixel(screen, x + length / rings / 2 * j, y + i, fg);
    } else
	for (l = 1; l <= rings; l++)
	    draw_circle(screen, x, y, length / 2 / rings * l, fg);

    ret = (accelerometer_t *) malloc(sizeof(accelerometer_t));
    ret->x = x;
    ret->y = y;
    ret->length = length;
    ret->rings = rings;
    ret->shape = shape;
    ret->fg = fg;
    ret->bg = bg;
    ret->oldx = 0;
    ret->oldy = 0;

    return ret;
}

void update_accelerometer(screen_t screen, accelerometer_t * accelerometer,
			  uint8_t valx, uint8_t valy)
{
    int i, j, l;

    if (accelerometer->shape == A_SQUARE)
	for (j = 1; j <= accelerometer->rings; j++)
	    for (i = -accelerometer->length / accelerometer->rings / 2 * j;
		 i < accelerometer->length / accelerometer->rings / 2 * j; i++)
	    {
		put_pixel(screen, accelerometer->x + i,
			  accelerometer->y - accelerometer->length /
			  accelerometer->rings / 2 * j, accelerometer->fg);

		put_pixel(screen, accelerometer->x + i, accelerometer->y +
			  accelerometer->length / accelerometer->rings / 2 * j,
			  accelerometer->fg);

		put_pixel(screen, accelerometer->x - accelerometer->length /
			  accelerometer->rings / 2 * j, accelerometer->y + i,
			  accelerometer->fg);

		put_pixel(screen, accelerometer->x + accelerometer->length /
			  accelerometer->rings / 2 * j, accelerometer->y + i,
			  accelerometer->fg);
    } else
	for (l = 1; l <= accelerometer->rings; l++)
	    draw_circle(screen, accelerometer->x, accelerometer->y,
			accelerometer->length / 2 / accelerometer->rings * l,
			accelerometer->fg);

    for (i = -2; i <= 2; i++)
	for (j = -2; j <= 2; j++) {
	    put_pixel(screen, accelerometer->x - accelerometer->length / 2 +
		      accelerometer->oldx * accelerometer->length / 0xff + i,
		      accelerometer->y - accelerometer->length / 2 +
		      accelerometer->oldy * accelerometer->length / 0xff,
		      accelerometer->bg);

	    put_pixel(screen, accelerometer->x - accelerometer->length / 2 +
		      accelerometer->oldx * accelerometer->length / 0xff,
		      accelerometer->y - accelerometer->length / 2 +
		      accelerometer->oldy * accelerometer->length / 0xff + i,
		      accelerometer->bg);
	}

    for (i = -2; i <= 2; i++)
	for (j = -2; j <= 2; j++) {
	    put_pixel(screen, accelerometer->x - accelerometer->length / 2 +
		      valx * accelerometer->length / 0xff + i,
		      accelerometer->y - accelerometer->length / 2 +
		      valy * accelerometer->length / 0xff, accelerometer->fg);

	    put_pixel(screen, accelerometer->x - accelerometer->length / 2 +
		      valx * accelerometer->length / 0xff, accelerometer->y -
		      accelerometer->length / 2 + valy * accelerometer->length /
		      0xff + i, accelerometer->fg);
	}

    accelerometer->oldx = valx;
    accelerometer->oldy = valy;
}

void delete_accelerometer(screen_t screen, accelerometer_t * accelerometer)
{
    int i, j, l;

    if (accelerometer->shape == A_SQUARE)
	for (j = 1; j <= accelerometer->rings; j++)

	    for (i = -accelerometer->length / accelerometer->rings / 2 * j;
		 i < accelerometer->length / accelerometer->rings / 2 * j;
		 i++) {
		put_pixel(screen, accelerometer->x + i,
			  accelerometer->y -
			  accelerometer->length / accelerometer->rings / 2 * j,
			  accelerometer->bg);
		put_pixel(screen, accelerometer->x + i,
			  accelerometer->y +
			  accelerometer->length / accelerometer->rings / 2 * j,
			  accelerometer->bg);
		put_pixel(screen,
			  accelerometer->x -
			  accelerometer->length / accelerometer->rings / 2 * j,
			  accelerometer->y + i, accelerometer->bg);
		put_pixel(screen,
			  accelerometer->x +
			  accelerometer->length / accelerometer->rings / 2 * j,
			  accelerometer->y + i, accelerometer->bg);
    } else
	for (l = 1; l <= accelerometer->rings; l++)
	    draw_circle(screen, accelerometer->x, accelerometer->y,
			accelerometer->length / 2 / accelerometer->rings * l,
			accelerometer->bg);

    for (i = -2; i <= 2; i++)
	for (j = -2; j <= 2; j++) {
	    put_pixel(screen,
		      accelerometer->x - accelerometer->length / 2 +
		      accelerometer->oldx * accelerometer->length / 0xff + i,
		      accelerometer->y - accelerometer->length / 2 +
		      accelerometer->oldy * accelerometer->length / 0xff,
		      accelerometer->bg);
	    put_pixel(screen,
		      accelerometer->x - accelerometer->length / 2 +
		      accelerometer->oldx * accelerometer->length / 0xff,
		      accelerometer->y - accelerometer->length / 2 +
		      accelerometer->oldy * accelerometer->length / 0xff + i,
		      accelerometer->bg);
	}

    free(accelerometer);

}
