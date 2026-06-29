//Uncomment only one of the following lines to select your display.
//#define USE_ILI9341   //2.4 inch 320x240 TFT Feather Wing
//#define USE_HX8357    //3.5 inch 480x320 TFT Feather Wing
//#define USE_HALLOWING //Adafruit Hallowing M0 Express
//#define USE_PYGAMER   //Adafruit PyGamer M4 Express
#define USE_GIGA_GFX    //Arduino Giga R1 with display
//#define USE_MCUFRIEND     // 2.8 inch 240x320 MCUFRIEND displays
#include "board_select.h"

// Example program for font collections. Shows mixed font strings,
// and the use of print() and getTextBound() on them.

#include "FontCollection.h"

// Uses libraries:
// Any graphics library inheriting from Adafruit

// Text and UI symbol fonts go into a font collection.
// This one is for 18pt Sans
#include <fonts/FreeSans18pt7b.h>
#include <fonts/UISymbolSans18pt7b.h>
FontCollection fc18(&display, &FreeSans18pt7b, &UISymbolSans18pt7b, 1, 1);

// This one is for 12pt Sans; too small on Giga but useful on the smaller displays
#include <fonts/FreeSans12pt7b.h>
#include <fonts/UISymbolSans12pt7b.h>
FontCollection fc12(&display, &FreeSans12pt7b, &UISymbolSans12pt7b, 1, 1);

// This one is for 24pt Sans
#include <fonts/FreeSans24pt7b.h>
#include <fonts/UISymbolSans24pt7b.h>
FontCollection fc24(&display, &FreeSans24pt7b, &UISymbolSans24pt7b, 1, 1);

// Colours in RGB565.
#define CYAN    (uint16_t)0x07FF
#define RED     (uint16_t)0xf800
#define BLUE    (uint16_t)0x001F
#define GREEN   (uint16_t)0x07E0
#define MAGENTA (uint16_t)0xF81F
#define WHITE   (uint16_t)0xffff
#define BLACK   (uint16_t)0x0000
#define YELLOW  (uint16_t)0xFFE0
#define GREY (uint16_t)display.color565(0x7F, 0x7F, 0x7F)
#define DKGREY (uint16_t)display.color565(0x3F, 0x3F, 0x3F)

void setup()
{
  int16_t x = 20, y = 20;
  int16_t xr, yr;
  uint16_t wr, hr;

  Serial.begin(9600);
  while(!Serial) {}

  Initialize_Display();

  display.fillScreen(0);

  // Draw the string, and a grey rect around its bounds.
  fc12.getTextBounds("Text font 12 Sans", x, y, &xr, &yr, &wr, &hr);
  display.drawRect(xr, yr, wr, hr, GREY);
  fc12.drawText("Text font 12 Sans", x, y, WHITE);
  y += 30;
  // Include the hex codes for symbol characters in the string to gets its bounds.
  fc12.getTextBounds("Symbol font \x8\x19", x, y, &xr, &yr, &wr, &hr);
  display.drawRect(xr, yr, wr, hr, GREY);
  fc12.drawText("Symbol font \x8\x19", x, y, WHITE);

  y += 40;
  if (y > DHEIGHT)
    return;
  fc18.getTextBounds("Text font 18 Sans", x, y, &xr, &yr, &wr, &hr);
  display.drawRect(xr, yr, wr, hr, GREY);
  fc18.drawText("Text font 18 Sans", x, y, WHITE);
  y += 40;
  fc18.getTextBounds("Symbol font \x8\x19", x, y, &xr, &yr, &wr, &hr);
  display.drawRect(xr, yr, wr, hr, GREY);
  fc18.drawText("Symbol font \x8\x19", x, y, WHITE);

  y += 50;
  if (y > DHEIGHT)
    return;
  fc24.getTextBounds("Text font 24 Sans", x, y, &xr, &yr, &wr, &hr);
  display.drawRect(xr, yr, wr, hr, GREY);
  fc24.drawText("Text font 24 Sans", x, y, WHITE);
  y += 50;
  fc24.getTextBounds("Symbol font \x8\x19", x, y, &xr, &yr, &wr, &hr);
  display.drawRect(xr, yr, wr, hr, GREY);
  fc24.drawText("Symbol font \x8\x19", x, y, WHITE);

  y += 80;
  if (y > DHEIGHT)
    return;
  fc24.getTextBounds("24 Sans double", x, y, &xr, &yr, &wr, &hr, 2);
  display.drawRect(xr, yr, wr, hr, GREY);
  display.setCursor(x, y);
  fc24.drawText("24 Sans double", x, y, WHITE, 2);
  y += 80;
  fc24.getTextBounds("Symbol font \x8\x19", x, y, &xr, &yr, &wr, &hr, 2);
  display.drawRect(xr, yr, wr, hr, GREY);
  fc24.drawText("Symbol font \x8\x19", x, y, WHITE, 2);
}

void loop() {

}