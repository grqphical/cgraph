// ================================================================
//  cgraph - A minimal, single header graphing library written in C
//
//  Project Homepage: <https://github.com/grqphical/cgraph>
//
//  Made by Nathan Jacobson <https://nathanjacobson.ca>
//
//  LICENSE:
//  Copyright © 2025 Nathan Jacobson
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the “Software”), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// ================================================================

#ifndef CGRAPH_H
#define CGRAPH_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14159265358979323846

// This is so we don't have to use malloc so much.
// Labels on a graph shouldn't be larger than 128 characters
// TODO: possible add a preprocessor flag to use malloc instead
#define CGRAPH_MAX_STRING_SIZE 128

// The font used by cgraph is an 8x8 simple font sourced from:
// <https://github.com/dhepper/font8x8/>

#define CGRAPH_FONT_SIZE 8

char cg__font[128][8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0000 (nul)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0001
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0002
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0003
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0004
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0005
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0006
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0007
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0008
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0009
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000A
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000B
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000C
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000D
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000E
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+000F
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0010
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0011
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0012
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0013
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0014
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0015
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0016
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0017
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0018
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0019
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001A
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001B
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001C
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001D
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001E
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+001F
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0020 (space)
    {0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00}, // U+0021 (!)
    {0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0022 (")
    {0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00}, // U+0023 (#)
    {0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00}, // U+0024 ($)
    {0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00}, // U+0025 (%)
    {0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00}, // U+0026 (&)
    {0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0027 (')
    {0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00}, // U+0028 (()
    {0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00}, // U+0029 ())
    {0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00}, // U+002A (*)
    {0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00}, // U+002B (+)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06}, // U+002C (,)
    {0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00}, // U+002D (-)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00}, // U+002E (.)
    {0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00}, // U+002F (/)
    {0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00}, // U+0030 (0)
    {0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00}, // U+0031 (1)
    {0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00}, // U+0032 (2)
    {0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00}, // U+0033 (3)
    {0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00}, // U+0034 (4)
    {0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00}, // U+0035 (5)
    {0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00}, // U+0036 (6)
    {0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00}, // U+0037 (7)
    {0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00}, // U+0038 (8)
    {0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00}, // U+0039 (9)
    {0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00}, // U+003A (:)
    {0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06}, // U+003B (;)
    {0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00}, // U+003C (<)
    {0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00}, // U+003D (=)
    {0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00}, // U+003E (>)
    {0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00}, // U+003F (?)
    {0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00}, // U+0040 (@)
    {0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00}, // U+0041 (A)
    {0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00}, // U+0042 (B)
    {0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00}, // U+0043 (C)
    {0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00}, // U+0044 (D)
    {0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00}, // U+0045 (E)
    {0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00}, // U+0046 (F)
    {0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00}, // U+0047 (G)
    {0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00}, // U+0048 (H)
    {0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+0049 (I)
    {0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00}, // U+004A (J)
    {0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00}, // U+004B (K)
    {0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00}, // U+004C (L)
    {0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00}, // U+004D (M)
    {0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00}, // U+004E (N)
    {0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00}, // U+004F (O)
    {0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00}, // U+0050 (P)
    {0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00}, // U+0051 (Q)
    {0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00}, // U+0052 (R)
    {0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00}, // U+0053 (S)
    {0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+0054 (T)
    {0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00}, // U+0055 (U)
    {0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00}, // U+0056 (V)
    {0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00}, // U+0057 (W)
    {0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00}, // U+0058 (X)
    {0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00}, // U+0059 (Y)
    {0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00}, // U+005A (Z)
    {0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00}, // U+005B ([)
    {0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00}, // U+005C (\)
    {0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00}, // U+005D (])
    {0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00}, // U+005E (^)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF}, // U+005F (_)
    {0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+0060 (`)
    {0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00}, // U+0061 (a)
    {0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00}, // U+0062 (b)
    {0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00}, // U+0063 (c)
    {0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00}, // U+0064 (d)
    {0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00}, // U+0065 (e)
    {0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00}, // U+0066 (f)
    {0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F}, // U+0067 (g)
    {0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00}, // U+0068 (h)
    {0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+0069 (i)
    {0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E}, // U+006A (j)
    {0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00}, // U+006B (k)
    {0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00}, // U+006C (l)
    {0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00}, // U+006D (m)
    {0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00}, // U+006E (n)
    {0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00}, // U+006F (o)
    {0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F}, // U+0070 (p)
    {0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78}, // U+0071 (q)
    {0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00}, // U+0072 (r)
    {0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00}, // U+0073 (s)
    {0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00}, // U+0074 (t)
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00}, // U+0075 (u)
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00}, // U+0076 (v)
    {0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00}, // U+0077 (w)
    {0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00}, // U+0078 (x)
    {0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F}, // U+0079 (y)
    {0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00}, // U+007A (z)
    {0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00}, // U+007B ({)
    {0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00}, // U+007C (|)
    {0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00}, // U+007D (})
    {0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // U+007E (~)
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}  // U+007F
};

// ============================================================
// cg_image
// ============================================================

// represents an RGB colour
typedef struct {
  uint8_t r, g, b;
} cg_colour;

// for any Americans using this library
#define cg_color cg_colour

// the available output formats for cgraph
typedef enum output_format { PPM } cg_output_format;

// stores an image in memory
typedef struct {
  cg_colour *data;
  int width;
  int height;
} cg_image;

// creates a new iamge with the given width and height
cg_image cg_new_image(int width, int height);

// sets a pixel to a certain colour in a given image
void cg_image_set_pixel(cg_image *img, int x, int y, cg_colour c);
// draws a rectangle at x,y with the given width, height and colour on the
// provided image
void cg_image_draw_rect(cg_image *img, int x, int y, int width, int height,
                        cg_colour c);
// draws a circle at x,y with the given radius and colour on the provided image
void cg_image_draw_circle(cg_image *img, int x_center, int y_center, int radius,
                          cg_colour c);
// draws a slice of a circle
//
// the origin of the circle is at x,y
// the start angle is which angle on the unit circle the slice should be drawn
// from, the percentage is how much of the circle should be filled
void cg_image_draw_circle_slice(cg_image *img, int x_center, int y_center,
                                int radius, int start_angle, float percentage,
                                cg_colour c);
// draws text on the given image using the included bitmap font
void cg_image_draw_text(cg_image *img, const char *text, int scale, int x_pos,
                        int y_pos, cg_colour c);
// exports an image to the provided file in the provided format
void cg_image_export(cg_image img, const char *output_file,
                     cg_output_format format);
// frees an image
void cg_image_free(cg_image img);

// ============================================================
// cg_bar_graph
// ============================================================

// represents a singular bar in a bar graph
typedef struct {
  double amount;
  cg_colour colour;
  char label[CGRAPH_MAX_STRING_SIZE];
} cg_bar;

// Dynamic Array to store bars inside of the bar graph
#define cg__INITIAL_DA_CAPACITY 256

#define dynamic_array(type)                                                    \
  typedef struct {                                                             \
    type *items;                                                               \
    size_t count;                                                              \
    size_t capacity;                                                           \
  } cg__##type##_dynamic_array;                                                \
  inline static cg__##type##_dynamic_array cg__new_##type##_dynamic_array() {  \
    cg__##type##_dynamic_array da;                                             \
    da.capacity = cg__INITIAL_DA_CAPACITY;                                     \
    da.count = 0;                                                              \
    da.items = (type *)malloc(da.capacity * sizeof(type));                     \
                                                                               \
    return da;                                                                 \
  }

// macro to append an element to a dynamic array
#define cg__dynamic_array_append(da, element)                                  \
  do {                                                                         \
    if (da.count >= da.capacity) {                                             \
      da.capacity *= 2;                                                        \
      da.items = realloc(da.items, da.capacity * sizeof(*da.items));           \
    }                                                                          \
    da.items[da.count++] = element;                                            \
  } while (0);

// a dynamic array of bars, used to store the bar data in the bar graph
dynamic_array(cg_bar);

// stores the data for a bar graph
typedef struct {
  cg__cg_bar_dynamic_array bars;
  int bar_count;
  char title[CGRAPH_MAX_STRING_SIZE];
} cg_bar_graph;

cg_bar_graph cg_new_bar_graph(const char *title);
// adds a bar with the given label and amount to a bar graph
void cg_bar_graph_add_bar(cg_bar_graph *bg, const char *label, double amount,
                          cg_colour c);
// renders a bar graph to an image
cg_image cg_bar_graph_render(cg_bar_graph *bg);
// frees a bar graph
void cg_bar_graph_free(cg_bar_graph bg);

// ============================================================
// cg_pie_graph
// ============================================================

// represents a slice within a pie graph
typedef struct {
  double amount;
  char label[CGRAPH_MAX_STRING_SIZE];
  cg_colour colour;
} cg_slice;

// again, we use a dynamic array to store the slices in the pie graph
dynamic_array(cg_slice);

// stores all the data for a pie graph
typedef struct {
  cg__cg_slice_dynamic_array slices;
  int slice_count;
  int total;
  char title[CGRAPH_MAX_STRING_SIZE];
} cg_pie_graph;

cg_pie_graph cg_new_pie_graph(const char *title);
// adds a slice to the pie graph with the given label and amount
void cg_pie_graph_add_slice(cg_pie_graph *pg, const char *label, double amount,
                            cg_colour c);
// renders the pie graph to an image
// if donut is true, a background coloured circle will be drawn on top, only
// showing the outer edge of the pie chart, creating a donut chart
cg_image cg_pie_graph_render(cg_pie_graph *pg, bool donut);
// frees the pie graph
void cg_pie_graph_free(cg_pie_graph pg);

// ============================================================
// cg_scatter_plot
// ===========================================
typedef struct {
  double x;
  double y;
} cg_vector2;

typedef struct {
  cg_vector2 pos;
  cg_colour colour;
} cg_point;

dynamic_array(cg_point);

typedef struct {
  cg__cg_point_dynamic_array points;
  int count;
  char title[CGRAPH_MAX_STRING_SIZE];
  char x_axis_label[CGRAPH_MAX_STRING_SIZE];
  char y_axis_label[CGRAPH_MAX_STRING_SIZE];
} cg_scatter_plot;

cg_scatter_plot cg_new_scatter_plot(const char *title, const char *x_axis_label,
                                    const char *y_axis_label);
void cg_scatter_plot_add_point(cg_scatter_plot *plot, cg_vector2 point,
                               cg_colour colour);
cg_image cg_scatter_plot_render(cg_scatter_plot *plot);
void cg_scatter_plot_free(cg_scatter_plot plot);

#ifdef CGRAPH_IMPLEMENTATION

// ============================================================
// cg_image
// ============================================================
inline cg_image cg_new_image(int width, int height) {
  cg_image img;
  img.width = width;
  img.height = height;
  img.data = (cg_colour *)malloc(sizeof(cg_colour) * width * height);

  return img;
}

inline void cg_image_set_pixel(cg_image *img, int x, int y, cg_colour c) {
  if (x >= img->width || y >= img->height) {
    perror("coordinate outside of image range");
    exit(2);
  }

  int index = (y * img->width) + x;
  img->data[index] = c;
}

inline void cg_image_draw_rect(cg_image *img, int x, int y, int width,
                               int height, cg_colour c) {
  int endX = x + width;
  int endY = y + height;

  if (endX > img->width)
    endX = img->width;
  if (endY > img->height)
    endY = img->height;

  int startX = (x < 0) ? 0 : x;
  int startY = (y < 0) ? 0 : y;

  for (int i = startY; i < endY; i++) {
    int rowOffset = i * img->width;

    for (int j = startX; j < endX; j++) {
      img->data[rowOffset + j] = c;
    }
  }
}

inline void cg_image_draw_circle(cg_image *img, int x_center, int y_center,
                                 int radius, cg_colour c) {

  for (int y = -radius; y <= radius; y++) {
    for (int x = -radius; x <= radius; x++) {
      if (x * x + y * y <= radius * radius) {
        cg_image_set_pixel(img, x_center + x, y_center + y, c);
      }
    }
  }
}

inline void cg_image_draw_circle_slice(cg_image *img, int x_center,
                                       int y_center, int radius,
                                       int start_angle, float percentage,
                                       cg_colour c) {
  float start_angle_rads = (float)start_angle * (PI / 180);
  start_angle_rads = fmodf(start_angle_rads, 2.0f * PI);

  float sweep_rad = (percentage / 100.0f) * (2.0f * PI);
  float end_rad = start_angle_rads + sweep_rad;

  for (int x = 0; x < img->width; x++) {
    for (int y = 0; y < img->height; y++) {
      float dx = x - x_center;
      float dy = y - y_center;

      float dist_sq = dx * dx + dy * dy;

      if (dist_sq <= radius * radius) {
        float angle = atan2(dy, dx);
        if (angle < 0)
          angle += 2.0 * PI;

        if (end_rad > 2.0f * PI) {
          if (angle >= start_angle_rads || angle <= (end_rad - 2.0f * PI)) {
            cg_image_set_pixel(img, x, y, c);
          }
        } else {
          if (angle >= start_angle_rads && angle <= end_rad) {
            cg_image_set_pixel(img, x, y, c);
          }
        }
      }
    }
  }
}

inline void cg_image_draw_text(cg_image *img, const char *text, int scale,
                               int x_pos, int y_pos, cg_colour c) {
  int width = strlen(text) * CGRAPH_FONT_SIZE;
  int endX = x_pos + width;
  int endY = y_pos + CGRAPH_FONT_SIZE;

  if (endX > img->width)
    endX = img->width;
  if (endY > img->height)
    endY = img->height;

  int startX = (x_pos < 0) ? 0 : x_pos;

  for (int i = 0; i < strlen(text); i++) {
    char *bitmap = cg__font[(int)text[i]];

    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {

        if (!(bitmap[y] & 1 << x))
          continue;

        int drawPositionX = startX + (i * CGRAPH_FONT_SIZE * scale) + x * scale;
        cg_image_draw_rect(img, drawPositionX, y_pos + y * scale, scale, scale,
                           c);
      }
    }
  }
}

static void cg__image_export_ppm(cg_image img, const char *output_file) {
  FILE *fptr = fopen(output_file, "wb");
  if (!fptr)
    return;

  fprintf(fptr, "P6\n%d %d\n255\n", img.width, img.height);
  for (int i = 0; i < img.width * img.height; i++) {
    fputc(img.data[i].r, fptr);
    fputc(img.data[i].g, fptr);
    fputc(img.data[i].b, fptr);
  }

  fclose(fptr);
}

inline void cg_image_export(cg_image img, const char *output_file,
                            cg_output_format format) {
  switch (format) {
  case PPM:
    cg__image_export_ppm(img, output_file);
    break;
  default:
    perror("unsupported image format for cgraph");
    exit(3);
  }
}

inline void cg_image_free(cg_image img) { free(img.data); }

// ============================================================
// cg_bar_graph
// ============================================================

cg_bar_graph cg_new_bar_graph(const char *title) {
  cg_bar_graph bg;
  strcpy(bg.title, title);
  bg.bar_count = 0;
  bg.bars = cg__new_cg_bar_dynamic_array();

  return bg;
}

inline void cg_bar_graph_add_bar(cg_bar_graph *bg, const char *label,
                                 double amount, cg_colour c) {

  cg_bar bar;

  bar.amount = amount;
  bar.colour = c;
  strcpy(bar.label, label);

  cg__dynamic_array_append(bg->bars, bar);
  bg->bar_count++;
}

// helper function that determines the "nice number" to increment a graph by
// used to determine which numbers should appear at each interval on the Y-Axis
// of bar graphs
static float cg__nice_num(float localRange, bool round) {
  float exponent = floor(log10(localRange));
  float fraction = localRange / pow(10, exponent);
  float niceFraction;

  if (round) {
    if (fraction < 1.5)
      niceFraction = 1;
    else if (fraction < 3)
      niceFraction = 2;
    else if (fraction < 7)
      niceFraction = 5;
    else
      niceFraction = 10;
  } else {
    if (fraction <= 1)
      niceFraction = 1;
    else if (fraction <= 2)
      niceFraction = 2;
    else if (fraction <= 5)
      niceFraction = 5;
    else
      niceFraction = 10;
  }
  return niceFraction * pow(10, exponent);
}

inline cg_image cg_bar_graph_render(cg_bar_graph *bg) {
  const int canvas_size = 512;
  const int padding = 60; // margin around the whole graph
  const int title_y = 20;
  const int label_offset = 15; // space for X-axis labels below the line
  const int axis_thickness = 2;

  // calculate the interval used for the "ticks" on the Y-axis
  double max_val = 0;
  for (int i = 0; i < bg->bar_count; i++) {
    if (bg->bars.items[i].amount > max_val)
      max_val = bg->bars.items[i].amount;
  }

  const int num_ticks = 6;
  double range = cg__nice_num(max_val, false);
  double tick_interval = cg__nice_num(range / (num_ticks - 1), true);
  double axis_max = ceil(max_val / tick_interval) * tick_interval;

  // define the actual graph's drawing area
  int graph_left = padding;
  int graph_right = canvas_size - padding;
  int graph_bottom = canvas_size - padding;
  int graph_top = padding + 40; // extra room for the title

  int graph_width = graph_right - graph_left;
  int graph_height = graph_bottom - graph_top;

  double scale = (double)graph_height / axis_max;
  cg_image img = cg_new_image(canvas_size, canvas_size);
  cg_image_draw_rect(&img, 0, 0, canvas_size, canvas_size,
                     (cg_colour){255, 255, 255});

  // Title Rendering
  int title_x = (canvas_size / 2) - (strlen(bg->title) * CGRAPH_FONT_SIZE * 2);
  cg_image_draw_text(&img, bg->title, 4, title_x, title_y,
                     (cg_colour){0, 0, 0});

  // "tick" and Y-axis label rendering
  for (int i = 0; i < num_ticks; i++) {
    double tick_value = i * tick_interval;

    // start at bottom, work way up to top
    int y_pos = graph_bottom - (int)(tick_value * scale);

    if (y_pos < graph_top)
      continue;

    cg_image_draw_rect(&img, graph_left, y_pos, graph_width, 1,
                       (cg_colour){200, 200, 200});

    char buf[32];
    sprintf(buf, "%.0f", tick_value);
    int text_x = graph_left - (strlen(buf) * CGRAPH_FONT_SIZE) - 5;
    cg_image_draw_text(&img, buf, 1, text_x, y_pos - (CGRAPH_FONT_SIZE / 2),
                       (cg_colour){0, 0, 0});
  }

  // render the actual bars
  int bar_padding = 15;
  int total_bar_area_width = graph_width / bg->bar_count;
  int bar_width = total_bar_area_width - bar_padding;

  for (int i = 0; i < bg->bar_count; i++) {
    cg_bar bar = bg->bars.items[i];

    int h = (int)(bar.amount * scale);
    int x = graph_left + (i * total_bar_area_width) + (bar_padding / 2);
    int y = graph_bottom - h; // Start at bottom line and grow UP

    cg_image_draw_rect(&img, x, y, bar_width, h, bar.colour);

    int label_x =
        x + (bar_width / 2) - (strlen(bar.label) * CGRAPH_FONT_SIZE / 2);
    cg_image_draw_text(&img, bar.label, 2, label_x, graph_bottom + label_offset,
                       (cg_colour){0, 0, 0});
  }

  // draw the borders

  cg_image_draw_rect(&img, graph_left, graph_top, axis_thickness, graph_height,
                     (cg_colour){0, 0, 0});
  cg_image_draw_rect(&img, graph_left, graph_bottom, graph_width,
                     axis_thickness, (cg_colour){0, 0, 0});

  return img;
}

inline void cg_bar_graph_free(cg_bar_graph bg) { free(bg.bars.items); }

// ============================================================
// cg_pie_graph
// ============================================================

inline cg_pie_graph cg_new_pie_graph(const char *title) {
  cg_pie_graph pg;
  pg.slice_count = 0;
  pg.slices = cg__new_cg_slice_dynamic_array();
  pg.total = 0;
  strcpy(pg.title, title);

  return pg;
}

void cg_pie_graph_add_slice(cg_pie_graph *pg, const char *label, double amount,
                            cg_colour c) {
  cg_slice s;

  s.amount = amount;
  strcpy(s.label, label);
  s.colour = c;

  cg__dynamic_array_append(pg->slices, s);
  pg->total += amount;
  pg->slice_count++;
}

cg_image cg_pie_graph_render(cg_pie_graph *pg, bool donut) {
  const int canvas_size = 512;
  const int padding = 80;
  const int title_y = 10;

  cg_image img = cg_new_image(canvas_size, canvas_size);

  cg_image_draw_rect(&img, 0, 0, canvas_size, canvas_size,
                     (cg_colour){255, 255, 255});

  int title_x = (canvas_size / 2) - (strlen(pg->title) * CGRAPH_FONT_SIZE * 2);
  cg_image_draw_text(&img, pg->title, 4, title_x, title_y,
                     (cg_colour){0, 0, 0});

  float current_angle = 0.0f;

  int label_start_y = canvas_size - 40;
  int label_start_x = padding / 2;
  const int label_gap_x = 15;
  const int label_rect_size = 24;

  for (int i = 0; i < pg->slice_count; i++) {
    cg_slice s = pg->slices.items[i];

    float ratio = (float)s.amount / pg->total;
    float slice_percentage = ratio * 100.0f;

    cg_image_draw_circle_slice(&img, canvas_size / 2, canvas_size / 2,
                               canvas_size / 2 - padding, current_angle,
                               slice_percentage, s.colour);
    current_angle += (ratio * 360.0f);

    int label_offset_x = i * (label_gap_x + label_rect_size +
                              strlen(s.label) * CGRAPH_FONT_SIZE * 2);

    cg_image_draw_rect(&img, label_start_x + label_offset_x, label_start_y,
                       label_rect_size, label_rect_size, s.colour);
    cg_image_draw_text(&img, s.label, 2,
                       label_start_x + label_rect_size + CGRAPH_FONT_SIZE / 2 +
                           label_offset_x,
                       label_start_y + 4, (cg_colour){0, 0, 0});
  }

  const float donut_hole_radius_pct = 0.7;
  if (donut)
    cg_image_draw_circle(&img, canvas_size / 2, canvas_size / 2,
                         donut_hole_radius_pct * (canvas_size / 2.0 - padding),
                         (cg_colour){255, 255, 255});

  return img;
}

void cg_pie_graph_free(cg_pie_graph pg) { free(pg.slices.items); }

// ============================================================
// cg_scatter_plot
// ============================================================

inline cg_scatter_plot cg_new_scatter_plot(const char *title,
                                           const char *x_axis_label,
                                           const char *y_axis_label) {
  cg_scatter_plot plot;
  plot.count = 0;
  plot.points = cg__new_cg_point_dynamic_array();
  strcpy(plot.title, title);
  strcpy(plot.x_axis_label, x_axis_label);
  strcpy(plot.y_axis_label, y_axis_label);

  return plot;
}

inline void cg_scatter_plot_add_point(cg_scatter_plot *plot, cg_vector2 point,
                                      cg_colour colour) {
  cg_point p;
  p.pos = point;
  p.colour = colour;

  cg__dynamic_array_append(plot->points, p);
  plot->count++;
}

inline cg_image cg_scatter_plot_render(cg_scatter_plot *plot) {
  const int canvas_size = 512;
  const int padding = 60; // margin around the whole graph
  const int title_y = 20;
  // const int label_offset = 15; // space for X-axis labels below the line
  const int axis_thickness = 2;

  cg_image img = cg_new_image(canvas_size, canvas_size);
  cg_image_draw_rect(&img, 0, 0, canvas_size, canvas_size,
                     (cg_colour){255, 255, 255});

  // calculate the interval used for the "ticks" on the Y and X axis
  double max_val_x = INT32_MIN;
  double max_val_y = INT32_MIN;
  for (int i = 0; i < plot->count; i++) {
    if (plot->points.items[i].pos.x > max_val_x)
      max_val_x = plot->points.items[i].pos.x;
    if (plot->points.items[i].pos.y > max_val_y)
      max_val_y = plot->points.items[i].pos.y;
  }

  const int graph_top = padding + 2 * title_y;
  const int graph_left = padding;
  const int graph_right = canvas_size - padding;
  const int graph_bottom = canvas_size - padding;

  int graph_width = graph_right - graph_left;
  int graph_height = graph_bottom - graph_top;

  // Title Rendering
  int title_x =
      (canvas_size / 2) - (strlen(plot->title) * CGRAPH_FONT_SIZE * 2);
  cg_image_draw_text(&img, plot->title, 4, title_x, title_y,
                     (cg_colour){0, 0, 0});

  // Render the points
  double scale_x = graph_width / max_val_x;
  double scale_y = graph_height / max_val_y;

  const int point_radius = 4;

  for (int i = 0; i < plot->count; i++) {
    cg_point p = plot->points.items[i];
    cg_image_draw_circle(&img, graph_right - (graph_width - p.pos.x * scale_x),
                         graph_bottom - (graph_height - p.pos.y * scale_y),
                         point_radius, p.colour);
  }

  // Border Rendering
  cg_image_draw_rect(&img, graph_left, graph_bottom, graph_width,
                     axis_thickness, (cg_colour){0, 0, 0});
  cg_image_draw_rect(&img, graph_left, graph_top, axis_thickness, graph_height,
                     (cg_colour){0, 0, 0});

  return img;
}

inline void cg_scatter_plot_free(cg_scatter_plot plot) {
  free(plot.points.items);
}

#endif

#endif
