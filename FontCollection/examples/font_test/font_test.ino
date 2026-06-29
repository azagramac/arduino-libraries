/*
 * Program to test custom fonts for Adafruit GFX library.
 * See https://learn.adafruit.com/creating-custom-symbol-font-for-adafruit-gfx-library/
 * for details.
 *
 * This version uses FontCollection to combine a text font and a symbol font
 * into one collection to print strings with both ascii and symbol character codes.
 */
#include <Wire.h>

//Uncomment only one of the following lines to select your display.
//#define USE_ILI9341   //2.4 inch 320x240 TFT Feather Wing
//#define USE_HX8357    //3.5 inch 480x320 TFT Feather Wing
//#define USE_HALLOWING //Adafruit Hallowing M0 Express
//#define USE_PYGAMER   //Adafruit PyGamer M4 Express
#define USE_GIGA_GFX    // Arduino Giga R1 and its display
//#define USE_MCUFRIEND     // 2.8 inch MCUFRIEND displays
#include "board_select.h"
#include "FontCollection.h"


/*
 * We will attempt to create a symbol font to complement text font.
 * This version is for the Sans fonts.
 * Any character in the range 32-127 will use the FreeSans font. 
 * Outside that range will be one of our custom symbols.
 * The UISymbol fonts have characters in the range 0-31.
 */
#include <Fonts/FreeSans18pt7b.h>

/*
 * This is our custom symbol font. It can be stored as a separate tab of this sketch or
 * in Arduino/libraries/My_Fonts folder which you would create. We do not recommend putting it in
 * Arduino/libraries/Fonts in case you ever need to delete and reinstall the GFX Library.
 */
#include <Fonts/UISymbolSans18pt7b.h>

/*
 * The font collection joins these fonts at relative sizes of 1x.
 */
FontCollection fc(&display, &FreeSans18pt7b, &UISymbolSans18pt7b, 1, 1);

uint8_t  Magnifier;
uint16_t First_Glyph;
uint16_t delta_c, delta_r, base_r;

/*
 * Display characters on the screen starting with First_Glyph until you hit
 * last character of the font or run out of space on the screen.
 */
void Show(void)  {
  /*
   * Although our characters are at most 16 pixels wide, we're going to space them
   * an arbitrary horizontal amount DELTA_C for readability. Similarly the vertical 
   * spacing is set at DELTA_R for readability. The BASE_R is a vertical adjustment 
   * that is the distance from the top of the cell to the baseline of the character.
   * Obtain as much as possible information from the font itself (see setup())
   */
  uint8_t Max_C = DWIDTH / (delta_c * Magnifier);
  uint8_t Max_R = DHEIGHT / (delta_r * Magnifier);
  uint16_t NumChar = Max_C * Max_R; 
  //uint16_t Last_Glyph = min(First_Glyph+NumChar-1, max(text_font->last, symbol_font->last));
  uint16_t Last_Glyph = min(First_Glyph+NumChar-1, 126);
  Serial.print("Displaying "); Serial.print(NumChar, DEC);
  Serial.print(" glyphs in "); Serial.print(Max_R, DEC);
  Serial.print(" rows by "); Serial.print(Max_C, DEC);
  Serial.println(" columns.");
  Serial.print("Magnifier:"); Serial.println(Magnifier, DEC);
  Serial.print("Displaying characters:"), 
  Serial.print(First_Glyph, DEC); 
  Serial.print(" through ");
  Serial.println(Last_Glyph, DEC);
  Serial.println();
  display.fillScreen(COLOR_BLACK);  //Clear the screen
  if(Magnifier>1){    //If magnified, draw a grid for reference
    for (uint16_t C=0; C<DWIDTH; C=C+(delta_c*Magnifier)) {
      display.drawFastVLine(C,0,DHEIGHT,COLOR_YELLOW); 
    }
    for (uint16_t R=0; R<DHEIGHT; R=R+(delta_r*Magnifier)) {
      display.drawFastHLine(0,R,DWIDTH,COLOR_YELLOW); 
    }
  }

  uint8_t I=0;
  uint8_t Glyph;
  for (Glyph = First_Glyph; Glyph <= Last_Glyph; Glyph++) 
  {
    fc.drawText
    (
      Glyph, 
      (I % Max_C) * delta_c * Magnifier, 
      (base_r*Magnifier) + (I / Max_C) * delta_r * Magnifier,
      COLOR_WHITE, 
      Magnifier
    ); 
    I++;
  }
}

void setup() {  
  Serial.begin(9600);while(! Serial) {}; delay (1000);
  Serial.println("Type a positive number to adjust the first character displayed.");
  Serial.println("Type a negative number to change the magnifier. ie -2 multiplied by two.");
  Initialize_Display();
  delay (1000);
  Magnifier=1;
  First_Glyph=0;

  // Get cell size from 'M' size in the text font
  int16_t x1, y1;
  uint16_t w, h;
  fc.getTextBounds("M", 0, 0, &x1, &y1, &delta_c, &delta_r, Magnifier);
  delta_c += 8;
  delta_r += 6;
  base_r = delta_c - 3;
  Serial.print("Delta C/R/Base ");
  Serial.print(delta_c);
  Serial.print(" ");
  Serial.print(delta_r);
  Serial.print(" ");
  Serial.println(base_r);

  Show ();
}

void loop() {
  int16_t val;
  if(Serial.available()) {
    val= Serial.parseInt();
    if (val<0) {
      Magnifier=-val;
    } else {
      First_Glyph=val;
    }
    while(Serial.available())  {Serial.read();};
    Show ();
  }
}
