#include <stdlib.h>

#include "screen.h"
#include "utils.h"

void put_pixel(screen_t screen, int x, int y, color_t color)
{
    if (x >= 0 && x < screen.max_x && y >= 0 && y < screen.max_y) {
	screen.buffer[(int) x * 4 + (int) y * screen.max_x * 4] = color.b;
	screen.buffer[(int) x * 4 + (int) y * screen.max_x * 4 + 1] = color.g;
	screen.buffer[(int) x * 4 + (int) y * screen.max_x * 4 + 2] = color.r;
	screen.buffer[(int) x * 4 + (int) y * screen.max_x * 4 + 3] = color.a;
    }

}

void draw_circle(screen_t screen, int x0, int y0, int radius, color_t color)
{
    /* Midpoint Circle algorithm implementation, based on:
       https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
     */
    int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

    while (x >= y) {
	put_pixel(screen, x0 + x, y0 + y, color);
	put_pixel(screen, x0 + y, y0 + x, color);
	put_pixel(screen, x0 - y, y0 + x, color);
	put_pixel(screen, x0 - x, y0 + y, color);
	put_pixel(screen, x0 - x, y0 - y, color);
	put_pixel(screen, x0 - y, y0 - x, color);
	put_pixel(screen, x0 + y, y0 - x, color);
	put_pixel(screen, x0 + x, y0 - y, color);


	if (err <= 0) {
	    y++;
	    err += dy;
	    dy += 2;
	}
	if (err > 0) {
	    x--;
	    dx += 2;
	    err += dx - (radius << 1);
	}
    }
}


void draw_line(screen_t screen, int x0, int y0, int x1, int y1, color_t color)
{
    /* Bresenham's line algorithm implementation, based on:
       https://en.wikipedia.org/wiki/Bresenham's_line_algorithm
     */
    int dx, dy, err, yi, xi, x, y;
    if ((y1 - y0) * (y1 - y0) < (x1 - x0) * (x1 - x0)) {
	if (x0 > x1) {
	    dx = x0 - x1;
	    dy = y0 - y1;
	    yi = 1;
	    if (dy < 0) {
		yi = -1;
		dy = -dy;
	    }
	    err = 2 * dy - dx;
	    y = y1;
	    for (x = x1; x < x0; x++) {
		put_pixel(screen, x, y, color);
		if (err > 0) {
		    y += yi;
		    err -= 2 * dx;
		}
		err += 2 * dy;
	    }
	} else {
	    dx = x1 - x0;
	    dy = y1 - y0;
	    yi = 1;
	    if (dy < 0) {
		yi = -1;
		dy = -dy;
	    }
	    err = 2 * dy - dx;
	    y = y0;
	    for (x = x0; x < x1; x++) {
		put_pixel(screen, x, y, color);
		if (err > 0) {
		    y += yi;
		    err -= 2 * dx;
		}
		err += 2 * dy;
	    }
	}
    } else {
	if (y0 > y1) {
	    dy = y0 - y1;
	    dx = x0 - x1;
	    xi = 1;
	    if (dx < 0) {
		xi = -1;
		dx = -dx;
	    }
	    err = 2 * dx - dy;
	    x = x1;
	    for (y = y1; y < y0; y++) {
		put_pixel(screen, x, y, color);
		if (err > 0) {
		    x += xi;
		    err -= 2 * dy;
		}
		err += 2 * dx;
	    }
	} else {
	    dy = y1 - y0;
	    dx = x1 - x0;
	    xi = 1;
	    if (dx < 0) {
		xi = -1;
		dx = -dx;
	    }
	    err = 2 * dx - dy;
	    x = x0;
	    for (y = y0; y < y1; y++) {
		put_pixel(screen, x, y, color);
		if (err > 0) {
		    x += xi;
		    err -= 2 * dy;
		}
		err += 2 * dx;
	    }
	}
    }
}

void fill_poly(screen_t screen, int x0, int y0, int x1, int y1, int *x, int *y,
	       int n, color_t color)
{
    /* Slow scanline algorithm, based on:
       http://alienryderflex.com/polygon_fill
     */
    int i, j, k, l;
    /* The intercepts list will have a maximum of n - 1 elements. */
    int *intercepts = (int *) calloc(n - 1, sizeof(int));

    for (i = y0; i < y1; i++) {
	k = 0;
	j = n - 1;
	for (l = 0; l < n; l++) {
	    if ((y[l] < i && y[j] >= i) || (y[j] < i && y[l] >= i))
		intercepts[k++] =
		    x[l] + 1.0 * (i - 1.0 * y[l]) / (1.0 * y[j] -
						     y[l]) * (1.0 * x[j] -
							      x[l]);
	    j = l;
	}

	sort(intercepts, k);

	/* Fills alternatively between every two intercepts. */
	for (j = 0; j < k && intercepts[j] < x1; j += 2) {
	    if (intercepts[j + 1] > x0) {
		if (intercepts[j] < x0)
		    intercepts[j] = x0;
		if (intercepts[j + 1] > x1)
		    intercepts[j + 1] = x1;

		for (l = intercepts[j]; l < intercepts[j + 1]; l++)
		    put_pixel(screen, l, i, color);
	    }
	}
    }

    free(intercepts);
}
