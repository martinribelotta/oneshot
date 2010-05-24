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
#ifndef _igluTShape_h
#define _igluTShape_h

#include <iglu/tview.h>
#include <iglu/screen.h>

#define shpNone             (-1)
#define shpPlane            (0)
#define shpHLine            (1)
#define shpVLine            (2)
#define shpDownBox          (3)
#define shpUpBox            (4)
#define shpBox3D            (5)

class TShape: public TView {
public:
  int type, width, bg, lt, sh;
  TShape (TRect& r, int t=shpPlane, int w=2,
      //     shadow       light             back ground
    int _1=EGA_BLACK, int _2=EGA_WHITE, int _3=EGA_LIGHTGRAY);
  virtual void Draw();
};


#endif
