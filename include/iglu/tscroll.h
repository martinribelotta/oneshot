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
#ifndef _igluTScroll_h
#define _igluTScroll_h

#include <iglu/tview.h>
#include <iglu/commands.h>

#define VScroll 'H'
#define HScroll 'V'

#define SizeBar 16

#define isChangeUp(x)      ((x&0x80000000)!=0L)
#define isChangeDown(x)    ((x&0x80000000)==0L)
#define ScrollValue(x)     (x&0x7FFFFFFF)

class TScroll: public TView {
protected:
  char hv;

  int setPosForPoint (TPoint& pos);
  void getCursorGeomOf (TRect& r, int p);
  void getCursorGeom (TRect& r);
public:
  long max, min, pos, inc;

  TScroll (TPoint p, int len, int _hv);

  virtual void Draw ();
  virtual void MouseEvent (TEvent&);
  virtual void TimerEvent (TEvent&);
  virtual void GotFocus ();
  virtual void LostFocus ();
  virtual void resize( int w, int h );
  virtual void RecuestAlign( TRect& a, TRect& b );

  void SetPos (int);
};

#endif /* _igluTScroll_h */
