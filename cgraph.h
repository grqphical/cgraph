// ================================================================
//  cgraph - A minimal, single header graphing library written in C
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================================
// Image Output
// ============================================================
typedef struct {
  int r, g, b;
} Colour;

typedef enum output_format { PPM } OutputFormat;

typedef struct {
  Colour *data;
  int width;
  int height;
} Image;

Image *new_image(int width, int height);
void image_set_pixel(Image *img, int x, int y, Colour c);
void image_draw_rect(Image *img, int x, int y, int width, int height, Colour c);
void image_export(Image *img, const char *output_file, OutputFormat format);

// #ifdef CGRAPH_IMPLEMENTATION

// ============================================================
// Image Output
// ============================================================
inline Image *new_image(int width, int height) {
  Image *img = (Image *)malloc(sizeof(Image));
  img->width = width;
  img->height = height;
  img->data = (Colour *)malloc(sizeof(Colour) * width * height);

  return img;
}

inline void image_set_pixel(Image *img, int x, int y, Colour c) {
  if (x >= img->width || y >= img->height) {
    perror("coordinate outside of image range");
    exit(2);
  }

  int index = (y * img->width) + x;
  img->data[index] = c;
}

inline void image_draw_rect(Image *img, int x, int y, int width, int height,
                            Colour c) {
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

static int digits(int n) {
  int total = 0;
  for (int i = 0; i <= n; i *= 10) {
    total += 1;
  }
  return total;
}

static void image_export_ppm(Image *img, const char *output_file) {
  FILE *fptr = fopen(output_file, "wb");
  if (!fptr)
    return;

  fprintf(fptr, "P6\n%d %d\n255\n", img->width, img->height);
  for (int i = 0; i < img->width * img->height; i++) {
    fputc(img->data[i].r, fptr);
    fputc(img->data[i].g, fptr);
    fputc(img->data[i].b, fptr);
  }

  fclose(fptr);
}

inline void image_export(Image *img, const char *output_file,
                         OutputFormat format) {
  switch (format) {
  case PPM:
    image_export_ppm(img, output_file);
    break;
  default:
    perror("unsupported image format for cgraph");
    exit(3);
  }
}

// #endif

#endif
