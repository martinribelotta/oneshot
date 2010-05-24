/*
 * IGLU Iterfaz Grafica Libre del Usuario.
 * Copyright (C) 2005 Martin Alejandro Ribelotta
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#ifndef _igluScreen_h
#define _igluScreen_h

#include <iglu/structs.h>
#include <iglu/mousehdl.h>

extern void initGUI (void);
extern void doneGUI ();
extern void gui_drawpixel (int x, int y, int color);
extern int gui_getpixel (int x, int y);
extern void gui_drawline (int xa, int ya, int xb, int yb, int cl);
extern void gui_drawvline (int x, int y, int dx, int cl);
extern void gui_drawhline (int x, int y, int dx, int cl);
extern void gui_drawpolyline (int n, int *points, int color);
extern void gui_drawrect (TRect& r, int color);
extern void gui_drawrectfill (TRect& r, int color);
extern void gui_drawrrect (TRect &r, int color);
extern void gui_drawcircle (int x, int y, int radius, int color);
extern void gui_drawcirclefill (int x, int y, int radius, int color);
extern void gui_outtextxy (int x, int y, char *s, int center, int fg, int bg);
extern int gui_textw (char *s);
extern int gui_texth (char *s);
extern void gui_setclip (TRect& r);
extern void gui_getclip (TRect& r);
extern void gui_wmode(int mode);
extern void gui_drawelipse (int ax, int ay, int bx, int by, int cl);
extern void gui_drawfillelipse (int ax, int ay, int bx, int by, int cl);
extern void gui_drawpixmap (int x, int y, int w, int h, char *b, char *p);

extern void gui_flush ();

inline void gui_drawpixel(TPoint& p, int cl)
  { gui_drawpixel(p.x, p.y, cl); }
inline int gui_getpixel(TPoint& p)
  { return gui_getpixel(p.x, p.y); }

#define EGA_BLACK                 0
#define EGA_BLUE                  1
#define EGA_GREEN                 2
#define EGA_CYAN                  3
#define EGA_RED                   4
#define EGA_MAGENTA               5
#define EGA_BROWN                 6
#define EGA_LIGHTGRAY             7
#define EGA_DARKGRAY              8
#define EGA_LIGHTBLUE             9
#define EGA_LIGHTGREEN            10
#define EGA_LIGHTCYAN             11
#define EGA_LIGHTRED              12
#define EGA_LIGHTMAGENTA          13
#define EGA_YELLOW                14
#define EGA_WHITE                 15

#define COPY_PUT                  0
#define XOR_PUT                   1
#define AND_PUT                   2
#define OR_PUT                    3
#ifdef __GRX__
#define IMAGE_PUT                 5
#endif

extern int Wt, Ht;
extern int MaxX, MaxY;

#endif
