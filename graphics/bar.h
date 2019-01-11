#ifndef BAR_H
#define BAR_H

#include "../screen.h"

/** Bar directions. */
typedef enum { B_HORIZONTAL, B_VERTICAL } bar_direction_t;

/** Bar data structure. */
typedef struct {
  /** X coordinate of the top left corner. */
    int x1;
  /** X coordinate of the bottom right corner. */
    int x2;
  /** Y coordinate of the top left corner. */
    int y1;
  /** Y coordinate of the bottom right corner. */
    int y2;
  /** Direction of the bar. */
    bar_direction_t dir;
  /** Old value for the variable. Required for redrawing the bar. */
    uint8_t oldval;
  /** Foreground color. */
    color_t fg;
  /** Background color. */
    color_t bg;
} bar_t;

/**
   Instantiates a bar and clears the area it will be shown in.

   @param screen Screen data structure.
   @param x1 X coordinate of the top left corner.
   @param x2 X coordinate of the bottom right corner.
   @param y1 Y coordinate of the top left corner.
   @param y2 Y coordinate of the bottom right corner.
   @param dir Direction of the bar.
   @param fg Foreground color.
   @param bg Background color.
   @return The allocated bar.
 */
bar_t *init_bar(screen_t screen, int x1, int x2, int y1, int y2,
		bar_direction_t dir, color_t fg, color_t bg);

/**
   Updates a bar with an input value.

   @param screen Screen data structure.
   @param bar Bar to be updated.
   @param value Input value.
 */
void update_bar(screen_t screen, bar_t * bar, uint8_t value);

/**
   Deallocates the bar and clears the region it was placed in.

   @param screen Screen data structure.
   @param bar Bar to be deallocated.
 */
void delete_bar(screen_t screen, bar_t * bar);

#endif
