#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <linux/fb.h>

#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>

#include <time.h>
#include <stdint.h>
#include <stdlib.h>



#include "graphics/graphics.h"
#include "graphics/dashboard.h"

#include "screen.h"
#include "utils.h"

#include "graphics/ascii.h"
#include "graphics/dashboard.h"


/* Simple demo on framebuffer. Displays eleven controls. */
void demo(screen_t screen);

/* Entrypoint. Sets the framebuffer and launches the demo. */
int main()
{
    struct fb_var_screeninfo screen_info;
    struct fb_fix_screeninfo fixed_info;
    char *buffer = NULL;
    size_t buflen;
    int fd = -1;
    int r = 1;

    int max_x, max_y;

    fd = open("/dev/fb0", O_RDWR);
    if (fd >= 0) {
	if (!ioctl(fd, FBIOGET_VSCREENINFO, &screen_info) &&
	    !ioctl(fd, FBIOGET_FSCREENINFO, &fixed_info)) {
	    buflen = screen_info.yres_virtual * fixed_info.line_length;
	    buffer = mmap(NULL,
			  buflen, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	    if (buffer != MAP_FAILED) {
		max_y = screen_info.yres;
		max_x = screen_info.xres;

		screen_t screen = { buffer, buflen, max_x, max_y };

		demo(screen);

		r = 0;
	    } else {
		perror("mmap");
	    }
	} else {
	    perror("ioctl");
	}
    } else {
	perror("open");
    }
    if (buffer && buffer != MAP_FAILED)
	munmap(buffer, buflen);
    if (fd >= 0)
	close(fd);

    return r;
}


void demo(screen_t screen)
{
    color_t bg, red, green, blue, white, tmp;
    dial_t *speed, *oil_temp;
    bar_t *cold, *hot;
    radar_t *filled, *empty;
    accelerometer_t *round, *squared;
    plot_t *monochrome, *multicolor, *threshold;

    char labels[5][6] = { "Lorem", "ipsum", "dolor", "sit", "amet" };

    /* 11 graphic elements are drawn in a 4 x 3 grid on screen. */
    int w = screen.max_x / 4;
    int h = screen.max_y / 3;

    int i, j;

    /* Initialize the colors. */
    bg.r = red.r = green.r = blue.r = tmp.r = 0x00;
    bg.g = red.g = green.g = blue.g = tmp.g = 0x00;
    bg.b = red.b = green.b = blue.b = tmp.b = 0x00;
    bg.a = red.a = green.a = blue.a = tmp.a = white.a = 0xff;

    white.r = red.r = 0xff;
    white.g = green.g = 0xff;
    white.b = blue.b = 0xff;

    /* Clears the screen. */
    for (i = 0; i < screen.max_x; i++)
	for (j = 0; j < screen.max_y; j++)
	    put_pixel(screen, i, j, bg);

    /* Initialize the controls. */
    speed = init_dial(screen, w * 0 + w / 2, h * 0 + h / 2,
		      ((w < h) ? w : h) / 2, 20, 3.14 * 3 / 2,
		      3.14 * 3 / 4, D_COUNTERCLOCKWISE, green, bg);

    print(screen, w * 0 + w / 2 - 3 * ASCII_WIDTH,
	  h * 0 + h / 2 + 4 * ASCII_HEIGHT, "Speed", white);

    oil_temp = init_dial(screen, w * 1 + w / 2, h * 0 + h / 2,
			 ((w < h) ? w : h) / 2, 5, 3.14 / 2, 3.14,
			 D_CLOCKWISE, white, bg);

    cold = init_bar(screen, w * 2, w * 2 + 20, h * 0,
		    h * 1 - 20, B_VERTICAL, blue, bg);

    put_symbol(screen, DASH_FROST, w * 2 + 40, h * 0, blue);
    hot = init_bar(screen, w * 2 + 20, w * 3, h * 1 - 20, h * 1,
		   B_HORIZONTAL, red, bg);

    put_symbol(screen, DASH_ATTENTION, w * 3 - DASHBOARD_WIDTH,
	       h * 1 - 20 - DASHBOARD_HEIGHT, red);

    filled = init_radar(screen, w * 0 + w / 2, h * 1 + h / 2,
			((w < h) ? w : h) / 2, 10, 7, R_FILL, white, bg);
    empty = init_radar(screen, w * 1 + w / 2, h * 1 + h / 2,
		       ((w < h) ? w : h) / 4, 5, 3, R_NOFILL, red, bg);

    round = init_accelerometer(screen, w * 3 - w / 2, h * 1 + h / 2,
			       ((w < h) ? w : h), 4, A_CIRCLE, green, bg);
    squared = init_accelerometer(screen, w * 4 - w / 2, h * 1 + h / 2,
				 ((w < h) ? w : h), 1, A_SQUARE, blue, bg);

    monochrome = init_plot(screen, w * 0, w * 1 - 10, h * 2 + 1,
			   h * 3, white, bg);

    multicolor = init_plot(screen, w * 1, w * 3 - 10, h * 2 + 1,
			   h * 3, white, bg);

    threshold =
	init_plot(screen, w * 3, w * 4 - 10, h * 2 + 1, h * 3, white, bg);

    /* Print the labels for the radar. */
    for (i = 0; i < 5; i++)
	print(screen,
	      w * 1 + w / 2 + +((w < h) ? w : h) / 2.5 * cos(6.28 / 5 * i),
	      h * 1 + h / 2 - ((w < h) ? w : h) / 2.5 * sin(6.28 / 5 * i),
	      labels[i], red);

    /* Main loop. Generate the input for the controls and update them. */
    uint8_t valx, valy, vals[10];
    for (i = 0; i < 1200; i++) {
	/* Simulate an input. */
	valx =
	    (uint8_t) ((sin(i / 50.0) + cos(i / 50.0 * 1.73) + 2) / 4 * 0xff);

	/* Update a color based on the input. */
	tmp.r = valx;
	tmp.g = 0;
	tmp.b = 0xff - valx;

	/* Controls with static color. */
	update_dial(screen, speed, valx);
	update_dial(screen, oil_temp, valx);
	update_bar(screen, cold, valx);
	update_bar(screen, hot, 0xff - valx);
	update_plot(screen, monochrome, valx);

	/* Controls with variable color. */
	put_symbol(screen, DASH_OIL, w * 1 + w / 2, h * 0 + h / 2, tmp);
	multicolor->fg = tmp;
	update_plot(screen, multicolor, valx);

	/* Threshold-based controls. */
	if (valx > 0x7f) {
	    threshold->fg.r = 0x00;
	    threshold->fg.g = 0xff;
	    threshold->fg.b = 0x00;

	    delete_symbol(screen, w * 3 + w / 2, h * 0 + h / 2, bg);
	} else {
	    threshold->fg.r = 0xff;
	    threshold->fg.g = 0x00;
	    threshold->fg.b = 0x00;

	    put_symbol(screen, DASH_MASTER, w * 3 + w / 2, h * 0 + h / 2, red);
	}
	update_plot(screen, threshold, valx);

	/* Simulate two inputs. */
	valx =
	    (uint8_t) ((2 * sin(4 * i / 200.0) * cos(i / 200.0) +
			2) / 4 * 0xff);
	valy =
	    (uint8_t) ((2 * sin(4 * i / 200.0) * sin(i / 200.0) +
			2) / 4 * 0xff);

	/* Update the accelerometers. */
	update_accelerometer(screen, round, valx, valy);
	update_accelerometer(screen, squared, valx, valy);

	/* Simulate 10 inputs. */
	for (j = 0; j < 10; j++)
	    vals[j] = (uint8_t) ((j + 1) * i & 0xff);
	/* Update the radars. The second one will read only 5 of the 10 values. */
	update_radar(screen, filled, vals);
	update_radar(screen, empty, vals);

	/* Simulate a waiting for the next inputs. */
	usleep(25000);

    }

    /* Deallocate the controls. */
    delete_dial(screen, speed);
    delete_dial(screen, oil_temp);
    delete_bar(screen, cold);
    delete_bar(screen, hot);
    delete_radar(screen, filled);
    delete_radar(screen, empty);
    delete_accelerometer(screen, round);
    delete_accelerometer(screen, squared);
    delete_plot(screen, monochrome);
    delete_plot(screen, multicolor);
    delete_plot(screen, threshold);

    /* Clear the screen. */
    for (i = 0; i < screen.max_x; i++)
	for (j = 0; j < screen.max_y; j++)
	    put_pixel(screen, i, j, bg);
}
