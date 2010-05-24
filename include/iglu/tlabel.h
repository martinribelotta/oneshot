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
#ifndef _igluTLabel_h
#define _igluTLabel_h

#include <iglu/tview.h>
#include <iglu/screen.h>

class TLabel: public TView {
protected:
  char *caption;
  int fg, bg;
public:
  TLabel (TRect& r, const char *s, int fore=EGA_BLACK, int back=EGA_LIGHTGRAY);
  ~TLabel ();
  virtual void Draw ();

  void SetText(const char *);
};

#endif /* _igluTLabel_h */
