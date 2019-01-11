#ifndef PLOT_H
#define PLOT_H

#include "../screen.h"

/** Plot data structure. */
typedef struct {
  /** X coordinate of the top left corner. */
    int x1;
  /** X coordinate of the bottom right corner. */
    int x2;
  /** Y coordinate of the top left corner. */
    int y1;
  /** Y coordinate of the bottom right corner. */
    int y2;
  /** Old value for the variable. */
    uint8_t oldval;
  /** Counter for the current abscissa of the plot. */
    int i;
  /** Foreground color. */
    color_t fg;
  /** Background color. */
    color_t bg;
} plot_t;

/**
   Instantiates a plot and clears the are it will be shown in.

   @param screen Screen data structure.
   @param x1 X coordinate of the top left corner.
   @param x2 X coordinate of the bottom right corner.
   @param y1 Y coordinate of the top left corner.
   @param y2 Y coordinate of the bottom right corner.
   @param fg Foreground color.
   @param bg Background color.
   @return The allocated plot.
 */
plot_t *init_plot(screen_t screen, int x1, int x2, int y1, int y2, color_t fg,
		  color_t bg);

/**
   Updates a plot with an input value.

   @param screen Screen data structure.
   @param plot Plot to be updated.
   @param value Input value.
 */
void update_plot(screen_t screen, plot_t * plot, uint8_t value);

/**
   Deallocates the plot and clears the region it was placed in.

   @param screen Screen data structure.
   @param plot Plot to be deallocated.
 */
void delete_plot(screen_t screen, plot_t * plot);

#endif
