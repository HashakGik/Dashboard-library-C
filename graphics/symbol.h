#ifndef SYMBOL_H
#define SYMBOL_H

#include "../screen.h"

/**
   Draws a symbol on screen.
   
   @param screen Screen data structure.
   @param id Symbol ID (@see dashboard.h)
   @param x X coordinate of the top left corner of the symbol.
   @param y Y coordinate of the top left corner of the symbol.
   @param color Color of the symbol.
 */
void put_symbol(screen_t screen, int id, int x, int y, color_t color);

/** Clears a symbol from screen (draws a rectangle of DASHBOARD_WIDTH x 
    DASHBOARD_HEIGHT).

    @param screen Screen data structure.
    @param x X coordinate of the top left corner.
    @param y Y coordinate of the top left corner.
    @param bg Background color.
*/
void delete_symbol(screen_t screen, int x, int y, color_t bg);

/**
   Draws an ASCII character on screen.

   @param screen Screen data structure.
   @param c Character to be drawn.
   @param x X coordinate of the character.
   @param y Y coordinate of the character.
   @param color Character color.
 */
void put_char(screen_t screen, char c, int x, int y, color_t color);

/**
   Clears a character from screen (draws a rectangle of ASCII_WIDTH x
   ASCII_HEIGHT).

   @param screen Screen data structure.
   @param x X coordinate of the character.
   @param y Y coordinate of the character.
   @param bg Background color.
 */
void delete_char(screen_t screen, int x, int y, color_t bg);

/**
   Writes a string up to a \0 character. If there is a \n,
   continues on a new line.

   @param screen Screen data structure.
   @param x X coordinate of the first character.x
   @param y Y coordinate of the first character.
   @param str String to be drawn.
   @param color String color.
 */
void print(screen_t screen, int x, int y, char *str, color_t color);

#endif
