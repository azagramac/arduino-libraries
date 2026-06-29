#ifndef FONT_COLLECTION_H
#define FONT_COLLECTION_H

#include <Adafruit_GFX.h>

// ---------------------------------------------------------------------------------

// Provide a class to hold a text and a UISymbol font. This may then be passed
// to other UI elements to get a consistent look and feel.

// A font collection contains two or more fonts with non-overlapping character
// code ranges. The font for each character is chosen based on its code.
// The GFX is required for getting character bounds and displaying strings from the
// font collection.

// A string containing mixed font characters can be printed or queried for bounds.
// The size given to these routines is multiplied by the size declared at creation
// of the collection so that the font sizes can be kept consistent with each other.
// drawText passes all parameters needed to draw the text, to bring text linto line
// with other GFX graphics calls. Setting states like size, color etc. are not used.

// Passing NULL for the text font will use the system font, but be careful
// of the text sizes. Usually the text and symbol sizes are the same, but the
// system font requires a larger size to be compatible since it starts at only 6 pixels.
// e.g. GU_FontCollection(&gfx, NULL, &some_symbol_font, 3, 1)
// There is also a problem with the Y baseline, which is intractable. So mixing
// the default font and symbol fonts is not recommended (and it looks rubbish)

// Passing NULL for the symbol font is OK if you are not using symbols. If a
// character exists in both fonts it will be found in the first.
class FontCollection
{
public:
  FontCollection(Adafruit_GFX *gfx, const GFXfont *text_font, const GFXfont *symbol_font, int tsize = 1, int ssize = 1)
    {_gfx = gfx; _text_font = text_font; _symbol_font = symbol_font; _textsize = tsize; _symsize = ssize; }
  ~FontCollection() { }

  // This public so others can see it
  Adafruit_GFX *_gfx;

  // Draw a string or single character at the given location, or following on from
  // the last string drawn if no location given. Color and size also default to last used.
  void drawText(const char *string, int16_t xpos, int16_t ypos, uint16_t color, uint8_t size_mult = 1);

  void drawText(const char *string, int16_t xpos, int16_t ypos)
  {
    drawText(string, xpos, ypos, _textcolor, _multiplier);
  }

  void drawText(const char *string)
  {
    drawText(string, _gfx->getCursorX(), _gfx->getCursorY(), _textcolor, _multiplier);
  }

  // Single character versions.
  void drawText(uint8_t ch, int16_t xpos, int16_t ypos, uint16_t color, uint8_t size_mult = 1);

  void drawText(uint8_t ch, int16_t xpos, int16_t ypos)
  {
    drawText(ch, xpos, ypos, _textcolor, _multiplier);
  }

  void drawText(uint8_t ch)
  {
    drawText(ch, _gfx->getCursorX(), _gfx->getCursorY(), _textcolor, _multiplier);
  }


  // Get the bounding rectangle of a string
  void getTextBounds(const char *string,
                    int16_t xpos, int16_t ypos,
                    int16_t *x, int16_t *y,
                    uint16_t *w, uint16_t *h,
                    uint8_t size_mult = 1);

private:
  const GFXfont *_text_font;
  const GFXfont *_symbol_font;
  int _textsize;
  int _symsize;
  int _multiplier = 1;
  uint16_t _textcolor = 0xFFFF;

  // Find the font to be used for a character code.
  // Set the font in GFX and return its ptr and size.
  // Return false if the code cannot be found in any font.
  bool find_font(char ch, const GFXfont **curr_font, int *curr_size);

  // charBounds analog.
  void charBounds(unsigned char c, int16_t *x, int16_t *y,
                  int16_t *minx, int16_t *miny, int16_t *maxx,
                  int16_t *maxy, uint8_t size_mult = 1);
};

#endif // def FONT_COLLECTION_H
