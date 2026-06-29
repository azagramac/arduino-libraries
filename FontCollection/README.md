# Font collections
A font collection is a set of fonts with non-overlapping character code ranges, usually
an ASCII text font and a symbol font using codes 0-31. They are treated as a single font for
drawing text and getting the text bounds. Setting the correct font is handled internally, and the font
collection only has to be declared once up front.

Dependencies:
- Giga GFX library (or any that inherit from Adafruit)

## Symbol fonts
A set of symbol fonts is provided in 12, 18 and 24 pt. They are weighted to suit the FreeSans
text fonts supplied with Adafruit GFX. The codes 0-31 are provided with useful UI elements
(such as play/stop/pause, tick, cross, hamburger, various arrows, etc.). They are derived from the
symbol fonts in https://learn.adafruit.com/creating-custom-symbol-font-for-adafruit-gfx-library/

The examples show using font collection in different sizes, and a list of all the characters
in a font collection. It's derived from https://github.com/cyborg5/font_test reworked to use
a font collection for drawing text.

A useful program for manipulating these fonts is at [gilesp1729/FontCompiler](https://github.com/gilesp1729/FontCompiler)

