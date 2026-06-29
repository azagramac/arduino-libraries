#include "Arduino.h"
#include "FontCollection.h"
#include "pgmaccess.h"

// Provide a class to hold a text and a UISymbol font. This may then be passed
// to other UI elements to get a consistent look and feel. A string containing mixed font
// characters can be printed or queried for bounds. The size given to these routines is
// multiplied by the size declared at creation of the collection so that the font sizes
// can be kept consistent with each other.


// Determine the bounds of a character. It's just like charBounds() in GFX, but
// takes no heed of newlines (since they may be valid characters) or wrapping.
// The X position is advanced by the character's advance width.
void FontCollection::charBounds(unsigned char c, int16_t *x, int16_t *y,
                                  int16_t *minx, int16_t *miny, int16_t *maxx,
                                  int16_t *maxy, uint8_t size_mult)
{
  const GFXfont *gfxFont;
  int tsize;

  _multiplier = size_mult;

  // Find the character's font. The font may be NULL, in which
  // case it is the default system font.
  if (!find_font(c, &gfxFont, &tsize))
    return;

  if (gfxFont)
  {
    uint8_t first = pgm_read_byte(&gfxFont->first);
    GFXglyph *glyph = pgm_read_glyph_ptr(gfxFont, c - first);
    uint8_t gw = pgm_read_byte(&glyph->width),
            gh = pgm_read_byte(&glyph->height),
            xa = pgm_read_byte(&glyph->xAdvance);
    int8_t xo = pgm_read_byte(&glyph->xOffset),
          yo = pgm_read_byte(&glyph->yOffset);
    int16_t x1 = *x + xo * tsize, y1 = *y + yo * tsize,
            x2 = x1 + gw * tsize - 1, y2 = y1 + gh * tsize - 1;
    if (x1 < *minx)
      *minx = x1;
    if (y1 < *miny)
      *miny = y1;
    if (x2 > *maxx)
      *maxx = x2;
    if (y2 > *maxy)
      *maxy = y2;
    *x += xa * tsize;
  }
  else
  { // Default font
    int x2 = *x + tsize * 6 - 1, // Lower-right pixel of char
        y2 = *y + tsize * 8 - 1;
    if (x2 > *maxx)
      *maxx = x2; // Track max x, y
    if (y2 > *maxy)
      *maxy = y2;
    if (*x < *minx)
      *minx = *x; // Track min x, y
    if (*y < *miny)
      *miny = *y;
    *x += tsize * 6; // Advance x one char
  }
}

// Get the bounding rectangle of a string, similar to getTextBounds.
// No newlines or wrapping are supported.
void FontCollection::getTextBounds(const char *string, int16_t xpos, int16_t ypos,
                                    int16_t *x, int16_t *y, uint16_t *w, uint16_t *h,
                                    uint8_t size_mult)
{
  int16_t minx = 0x7FFF, miny = 0x7FFF, maxx = -1, maxy = -1;
  GFXfont *curr_font;

  *x = xpos;
  *y = ypos;
  *w = *h = 0;
  for (int i = 0; i < strlen(string); i++)
  {
    charBounds(string[i], &xpos, &ypos, &minx, &miny, &maxx, &maxy, size_mult);
    if (maxx >= minx)
    {
      *x = minx;
      *w = maxx - minx + 1;
    }
    if (maxy >= miny)
    {
      *y = miny;
      *h = maxy - miny + 1;
    }
  }
}

// Draw a string at the given cursor location. Other variants ar in the header.
// Not taking heed of newline or CR, since they may be valid symbol characters.
void FontCollection::drawText(const char *string, int16_t xpos, int16_t ypos,
                              uint16_t color, uint8_t size_mult)
{
  const GFXfont *gfxFont;
  int textsize;
  int i, len;

  _gfx->setCursor(xpos, ypos);
  _gfx->setTextColor(color);
  _textcolor = color;
  _multiplier = size_mult;
  len = strlen(string);
  for (i = 0; i < len; i++)
  {
    uint8_t c = string[i];
    drawText(c);
  }
}

// Draw a single character.
void FontCollection::drawText(uint8_t c, int16_t xpos, int16_t ypos,
                              uint16_t color, uint8_t size_mult)
{
  const GFXfont *gfxFont;
  int textsize;

  _gfx->setCursor(xpos, ypos);
  _gfx->setTextColor(color);
  _textcolor = color;
  _multiplier = size_mult;
  if (find_font(c, &gfxFont, &textsize))
  {
    int cursor_x = _gfx->getCursorX();
    int cursor_y = _gfx->getCursorY();
    if (!gfxFont)
    { // 'Classic' built-in font
      _gfx->drawChar(cursor_x, cursor_y, c, _textcolor, _textcolor, textsize);
      cursor_x += textsize * 6; // Advance x one char
    }
    else
    { // Custom font
      uint8_t first = pgm_read_byte(&gfxFont->first);
      if ((c >= first) && (c <= (uint8_t)pgm_read_byte(&gfxFont->last)))
      {
        GFXglyph *glyph = pgm_read_glyph_ptr(gfxFont, c - first);
        uint8_t w = pgm_read_byte(&glyph->width),
                h = pgm_read_byte(&glyph->height);
        if ((w > 0) && (h > 0))
        { // Is there an associated bitmap?
          _gfx->drawChar(cursor_x, cursor_y, c, _textcolor, _textcolor, textsize);
        }
        cursor_x +=
            (uint8_t)pgm_read_byte(&glyph->xAdvance) * (int16_t)textsize;
      }
    }
    _gfx->setCursor(cursor_x, cursor_y);
  }
}


// Find the font to be used for a character code.
// Set the font in GFX and return its ptr and size.
// Returns false if the code cannot be found in any font.
bool FontCollection::find_font(char ch, const GFXfont **curr_font, int *curr_size)
{
  int first, last;

  // Do something different when the fist (text) font pointer is NULL.
  // The default system font will be used instead.
  if (_text_font == NULL)
  {
    first = 32;
    last = 126;
  }
  else
  {
    first = pgm_read_byte(&_text_font->first);
    last = pgm_read_byte(&_text_font->last);
  }

  // Text font defaults to system font, symfont defaults to nothing shown.
  if (ch >= first && ch <= last)
  {
    _gfx->setTextSize(_multiplier * _textsize);
    _gfx->setFont(_text_font);
    *curr_font = _text_font;
    *curr_size = _multiplier * _textsize;
    return true;
  }
  else if (_symbol_font != NULL)
  {
    if (ch >= pgm_read_byte(&_symbol_font->first) && ch <= pgm_read_byte(&_symbol_font->last))
    {
      _gfx->setTextSize(_multiplier * _symsize);
      _gfx->setFont(_symbol_font);
      *curr_font = _symbol_font;
      *curr_size = _multiplier * _symsize;
      return true;
    }
  }
  *curr_font = NULL;
  return false;
}
