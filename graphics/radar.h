#ifndef RADAR_H
#define RADAR_H

#include "../screen.h"
/** Radar polygon filling options. */
typedef enum { R_FILL, R_NOFILL } radar_fill_t;

/** Radar plot data structure. */
typedef struct {
  /** X coordinate of the center. */
    int x;
  /** Y coordinate of the center. */
    int y;
  /** Radius of the radar. */
    int radius;
  /** Number of axes (and therefore input values). */
    int n;
  /** Number of circumferences ticking the axes. */
    int ticks;
  /** Old x coordinates for the values. Required for redrawing the values. */
    int *oldx;
  /** Old y coordinates for the values. Required for redrawing the values. */
    int *oldy;
  /** New x coordinates for the values. */
    int *valx;
  /** New y coordinates for the values. */
    int *valy;
  /** Polygon filling option of the radar. */
    radar_fill_t fill;
  /** Foreground color. */
    color_t fg;
  /** Background color. */
    color_t bg;
} radar_t;

/**
   Instantiates a radar plot and draws the axes.

   @param screen Screen data structure.
   @param x X coordinate of the center.
   @param y Y coordinate of the center.
   @param radius Radius of the radar.
   @param n Number of axes.
   @param ticks Number of circumferences ticking the axes.
   @param fill Filling option of the radar.
   @param fg Foreground color.
   @param bg Background color.
   @return The allocated radar plot.
 */
radar_t *init_radar(screen_t screen, int x, int y, int radius, int n,
		    int ticks, radar_fill_t fill, color_t fg, color_t bg);

/**
   Updates a radar plot with an array of inputs.
   
   @param screen Screen data structure.
   @param radar Radar plot to be updated.
   @param values Input values.
 */
void update_radar(screen_t screen, radar_t * radar, uint8_t * values);

/**
   Deallocates the radar plot and clears the region it was placed in.

   @param screen Screen data structure.
   @param radar Radar plot to be deallocated.
 */
void delete_radar(screen_t screen, radar_t * radar);

#endif
