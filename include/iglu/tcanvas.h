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
#ifndef _igluTVanvas_h
#define _igluTVanvas_h

#include <iglu/tctainer.h>
#include <iglu/screen.h>
#include <iglu/tscroll.h>

#define expand(r)   r.a.x, r.a.y, r.b.x, r.b.y

class TScrollCanvas: public TContainer {
  TScroll h, v;
  int oldposx, oldposy;
public:
  int virtualw, virtualh;

  // Params: r, virtual width, virtual height
  TScrollCanvas (TRect& r, int vw, int vh);

  void moveall (int newx, int newy);

  virtual void moverel (int dx, int dy);
  virtual void Draw ();
  virtual void HandleEvent (TEvent& e);
  virtual void RecuestAlign (TRect&, TRect&);
  virtual void getClientArea( TRect& r, int v=1 );
};

// Drawable: Baseclass for element in TScrollCanvas
class TDrawable: public TView {
public:
  int color;
  TDrawable(TRect&r, int cl): TView(r), color(cl) { }
  // Ignore TView::HandleEvent for more speed
  virtual void HandleEvent (TEvent&) { }
};

class TRectangle: public TDrawable { public:
  TRectangle (TRect& r, int cl): TDrawable(r, cl) { }
  virtual void Draw () { gui_drawrect(Bounds, color); }
};

class TFillRectangle: public TDrawable { public:
  TFillRectangle(TRect&r, int cl): TDrawable(r,cl) { }
  virtual void Draw () { gui_drawrectfill(Bounds, color); }
};

class TCircle: public TDrawable { public:
  TCircle (TRect&r, int cl): TDrawable(r, cl) { }
  virtual void Draw () { gui_drawelipse(expand(Bounds), color); }
};

class TFillCircle: public TDrawable { public:
  TFillCircle (TRect&r, int cl): TDrawable(r, cl) { }
  virtual void Draw () { gui_drawfillelipse(expand(Bounds), color); }
};

class TLine: public TDrawable { public:
  TLine (TRect&r, int cl): TDrawable(r, cl) { }
  virtual void Draw () { gui_drawline(expand(Bounds), color); }
};

#endif /* _igluTVanvas_h */
