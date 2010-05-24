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

#ifndef _igluTCheck_h
#define _igluTCheck_h

#include <iglu/tbutton.h>

class TCheckBox: public TAbstButton {
public:
  char *caption;
  int checked; // 1: Checked, 0: Unchecked

  TCheckBox (TRect& r, char *s):
    TAbstButton (r, 0), caption (s), checked(0) { }
  virtual void DrawState (int st);
  virtual void Assert (TEvent&);
};

class TRadioBox: public TAbstButton {
public:
  char *caption;

  TRadioBox (TRect& r, char *s): TAbstButton(r, 0), caption(s) { }
  virtual void DrawState (int st);
  virtual void Assert (TEvent&);
  // dectect if radio button is selected via focus (State&stFocus)
  int isSelect () { return State&stFocus; }
};

#endif
