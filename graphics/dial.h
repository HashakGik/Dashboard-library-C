#ifndef DIAL_H
#define DIAL_H

#include "../screen.h"

/** Dial directions. */
typedef enum { D_COUNTERCLOCKWISE, D_CLOCKWISE } dial_direction_t;

/** Dial data structure. */
typedef struct {
  /** X coordinate of the center. */
    int x;
  /** Y coordinate of the center. */
    int y;
  /** Radius of the dial. */
    int radius;
  /** Number of ticks dividing the dial's quadrant. */
    int ticks;
  /** Arc length in radians of the dial. */
    double arc;
  /** Phase in radians of the needle when the input is 0. */
    double phase;
  /** Direction of the dial. */
    dial_direction_t dir;
  /** Old value for the variable. Required for redrawing the needle. */
    uint8_t oldval;
  /** Foreground color. */
    color_t fg;
  /** Background color. */
    color_t bg;
} dial_t;


/**
   Instantiates a dial and draws the quadrant.

   @param screen Screen data structure.
   @param x X coordinate of the center of the dial.
   @param y Y coordinate of the center of the dial.
   @param radius Radius of the dial.
   @param ticks Number of ticks dividing the dial's quadrant.
   @param arc Arc length in radians of the dial.
   @param phase Phase in radians of the needle when the input is 0.
   @param dir Direction of the dial.
   @param fg Foreground color.
   @param bg Background color.
   @return The allocated dial.
 */
dial_t *init_dial(screen_t screen, int x, int y, int radius, int ticks,
		  double arc, double phase, dial_direction_t dir,
		  color_t fg, color_t bg);

/**
   Updates a dial with an input value.

   @param screen Screen data structure.
   @param dial Dial to be updated.
   @param value Input value.
 */
void update_dial(screen_t screen, dial_t * dial, uint8_t value);

/**
   Deallocates the dial and clears the region it ws placed in.

   @param screen Screen data structure.
   @param dial Dial to be deallocated.
 */
void delete_dial(screen_t screen, dial_t * dial);

#endif
