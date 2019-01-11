#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include "../screen.h"

/** Accelerometer shapes. */
typedef enum { A_CIRCLE, A_SQUARE } accelerometer_shape_t;

/** Accelerometer data structure. */
typedef struct {
  /** X coordinate of the center. */
    int x;
  /** Y coordinate of the center. */
    int y;
  /** Length/diameter. */
    int length;
  /** Number of concentric rings/squares to be drawn. */
    int rings;
  /** Shape. */
    accelerometer_shape_t shape;
  /** Old value for the first variable. Required for redrawing the cross. */
    uint8_t oldx;
  /** Old value for the second variable. Required for redrawing the cross. */
    uint8_t oldy;
  /** Foreground color. */
    color_t fg;
  /** Background color. */
    color_t bg;
} accelerometer_t;

/**
   Instantiates an accelerometer and draws it.

   @param screen Screen data structure.
   @param x X coordinate of the center of the accelerometer.
   @param y Y coordinate of the center of the accelerometer.
   @param length Length/diameter of the accelerometer.
   @param rings Number of rings to be drawn.
   @param shape Shape of the accelerometer.
   @param fg Foreground color.
   @param bg Background color.
   @return The allocated accelerometer.
 */
accelerometer_t *init_accelerometer(screen_t screen, int x, int y, int length,
				    int rings, accelerometer_shape_t shape,
				    color_t fg, color_t bg);

/**
   Updates an accelerometer with two given inputs, showing a cross.

   @param screen Screen data structure.
   @param accelerometer Accelerometer to be updated.
   @param valx First input. It will move the cross horizontally.
   @param valy Second input. It will move the cross vertically.
 */
void update_accelerometer(screen_t screen, accelerometer_t * accelerometer,
			  uint8_t valx, uint8_t valy);

/**
   Deallocates the accelerometer and clears the region it was placed in.

   @param screen Screen data structure.
   @param accelerometer Accelerometer to be deallocated.
 */
void delete_accelerometer(screen_t screen, accelerometer_t * accelerometer);

#endif
