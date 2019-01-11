#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>
#include <sys/types.h>

/* Screen abstraction header file. Changing hardware/software
architecture should require only to rewrite these functions and structures. */


/**
   Screen data structure.
 */
typedef struct {
  /** Pointer to the framebuffer. */
    char *buffer;
  /** Framebuffer size. */
    size_t buflen;
  /** Width of the framebuffer. */
    int max_x;
  /** Height of the framebuffer. */
    int max_y;

} screen_t;

/**
   Color data structure.
 */
typedef struct {
  /** Red component. */
    uint8_t r;
  /** Green component. */
    uint8_t g;
  /** Blue component. */
    uint8_t b;
  /** Alpha component. */
    uint8_t a;
} color_t;


/**
   Draws a pixel on screen.

   @param screen Screen data structure.
   @param x X coordinate of the pixel.
   @param y Y coordinate of the pixel.
   @param color Color of the pixel.
 */
void put_pixel(screen_t screen, int x, int y, color_t color);

/**
   Draws a circle on screen.

   @param screen Screen data structure.
   @param x0 X coordinate of the circle center.
   @param y0 Y coordinate of the circle center.
   @param radius Radius of the circle.
   @param color Color of the circle.
 */
void draw_circle(screen_t screen, int x0, int y0, int radius, color_t color);

/**
   Draws a line on screen.

   @param screen Screen data structure.
   @param x0 First point's x coordinate.
   @param y0 First point's y coordinate.
   @param x1 Second point's x coordinate.
   @param y1 Second point's y coordinate.
   @param color Color of the line.
 */
void draw_line(screen_t screen, int x0, int y0, int x1, int y1, color_t color);

/**
   Draws a full polygon on screen.

   @param screen Screen data structure.
   @param x0 Smallest x coordinate of the polygon's vertexes.
   @param y0 Smallest y coordinate of the polygon's vertexes.
   @param x1 Largest x coordinate of the polygon's vertexes.
   @param y1 Largest y coordinate of the polygon's vertexes.
   @param x Array of x coordinates of the polygon's vertexes.
   @param y Array of y coordinates of the polygon's vertexes.
   @param n Number of the polygon's vertexes.
   @param color Color of the polygon.
 */
void fill_poly(screen_t screen, int x0, int y0, int x1, int y1, int *x, int *y,
	       int n, color_t color);

#endif
