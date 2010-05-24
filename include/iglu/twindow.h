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
#ifndef _igluTWindow_h
#define _igluTWindow_h

#include <iglu/tctainer.h>
#include <iglu/tbutton.h>
#include <iglu/tmenu.h>

#define WinBorder                     (3)
#define WinTitleH                     (Ht*2)

class TWindow: public TContainer {
protected:
//  TCharButton *xb;
  TView *resizearea, *titleBar;
  TPoint minimumSize;
public:
  TMenuBar *menu;
  char *title;

  TWindow (TRect& r, char *s);

  virtual void getClientArea (TRect& r, int rel=1);
  void setMenuWindow (TMenuBar *m);

  virtual void GotFocus ();
  virtual void LostFocus ();

  virtual void Hide ();
  virtual void Show ();

  virtual void insert (TView *q);
  virtual void detach (TView *q);

  virtual void Draw ();
  virtual void DrawDecorate ();
  virtual void HandleEvent (TEvent& e);
  virtual void resize( int w, int h );
};

#endif
