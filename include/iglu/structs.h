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
#ifndef _igluStructs_h
#define _igluStructs_h

#ifndef NULL
#define NULL 0
#endif

struct TPoint {
  int x, y;

  TPoint() { x=y=0; }
  TPoint(int a, int b): x(a), y(b) { }

  TPoint& operator+=(TPoint& p)
    { x+=p.x;  y+=p.y; return *this; }
  TPoint& operator-=(TPoint& p)
    { x-=p.x;  y-=p.y; return *this; }
  void assign(int a, int b) { x=a; y=b; }
};

TPoint operator+(TPoint a, TPoint b);
TPoint operator-(TPoint a, TPoint b);
int operator==(TPoint a, TPoint b);
int operator!=(TPoint a, TPoint b);

struct TRect {
  TPoint a, b;

  TRect(): a(0,0), b(0,0) { }
  TRect(int ax, int ay, int bx, int by): a(ax,ay), b(bx,by) { }
  TRect(const TPoint& A, const TPoint& B): a(A), b(B) { }

  void assign(int ax, int ay, int bx, int by)
    { a.assign(ax,ay); b.assign(bx,by); }
  void assign(TPoint& A, TPoint& B)
    { a=A; b=B; }

  void move(int x, int y)
    { moverel(x-a.x, y-a.y); }
  void moverel(int dx, int dy)
    { a.x+=dx; a.y+=dy; b.x+=dx; b.y+=dy; }
  void move(TPoint& p)
    { move(p.x, p.y); }
  void moverel(TPoint& p)
    { moverel(p.x, p.y); }

  int contain(int x, int y)
    { return ((x>=a.x) && (y>=a.y) && (x<=b.x) && (y<=b.y)); }
  int contain(TPoint& p)
    { return contain(p.x, p.y); }

  int deltax() { return (b.x-a.x); }
  int deltay() { return (b.y-a.y); }

  void Grow(int dx, int dy);

  int isvalid ();
  void centeron (TRect& r, int absolute=0); // absolute move this to r.a
};

/** Common ancestor of any objects  */
class TObject { public:
  TObject () { }
  virtual ~TObject () { }
};

extern TRect Intersect(TRect& r1, TRect& r2);
extern TRect Union(TRect& r1, TRect& r2);

extern TRect& Rect(int, int, int ,int);
extern TPoint& Point (int, int);

// Para estar mas a gusto ahora que programo con Qt 4.X.X
typedef class TPoint QPoint;
typedef class TRect QRect;
typedef class TObject QObject;

#ifdef __TURBOC__
enum bool {
	false=0,
	true=1
};
#endif

#endif

