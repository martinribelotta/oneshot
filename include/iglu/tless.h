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
#ifndef _igluTLess_h
#define _igluTLess_h

#include <iglu/tview.h>
#include <iglu/tscroll.h>
#include <stdio.h>

class TLessBase: public TView {
protected:
  TScroll *sh, *sv;

  int calclend ();
public:
  int linestart, lineend, linemax;
  TLessBase (TRect& r);
  virtual void Draw ();
  virtual void HandleEvent (TEvent& e);
  virtual void moverel (int dx, int dy);
  virtual void RecuestAlign (TRect& bo, TRect& bn);

  virtual void DrawText ();
  virtual char *getline (int n) = 0;
};

class TLessFile: public TLessBase {
protected:
  FILE *f;
  char *buffer;
  int *eolseek;
public:
  TLessFile (TRect& r, char *filename);
  ~TLessFile ();
  virtual char *getline (int l);
};

#endif
