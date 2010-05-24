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
#ifndef _flares_Inputs_h
#define _flares_Inputs_h

#include <iglu/screen.h>
#include <iglu/tview.h>

class TInputLine: public TView {
public:
  char *text;
  int maxlen, pos, len;

  TInputLine (TRect& r, int l);
  ~TInputLine () { delete text; }

  virtual void Draw ();
  virtual void HandleEvent (TEvent& e);

  void insertChar(int p, int c);
  void deleteChar(int p);
  void setPos (int p);

  void setText (char *text);

  virtual void GotFocus();
  virtual void LostFocus();
};

#endif /* _flares_Inputs_h */
