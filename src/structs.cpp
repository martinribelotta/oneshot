/*
 * IGLU Iterfaz Grafica Libre del Usuario. (libre de usuarios) (Graphics user interface "free of users")
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
#include <iglu/structs.h>

#define Max(a,b)            ((a>b)? a:b)
#define Min(a,b)            ((a<b)? a:b)

TPoint operator+(TPoint a, TPoint b)
  { a+=b; return a; }
TPoint operator-(TPoint a, TPoint b)
  { a-=b; return b; }
int operator==(TPoint a, TPoint b)
  { return ((a.x==b.x) && (a.y==b.y)); }
int operator!=(TPoint a, TPoint& b)
  { return ((a.x!=b.x) || (a.y!=b.y)); }

void TRect::centeron (TRect& r, int absolute)
{
  if (absolute)
    move (r.a);
  move ((r.deltax()>>1)-(deltax()>>1), (r.deltay()>>1)-(deltay()>>1));
}

TRect Intersect(TRect& r1, TRect& r2)
{
  TRect temp; //(r1);
  temp.a.x = Max(r1.a.x, r2.a.x);
  temp.a.y = Max(r1.a.y, r2.a.y);
  temp.b.x = Min(r1.b.x, r2.b.x);
  temp.b.y = Min(r1.b.y, r2.b.y);
  return temp;
}

TRect Union(TRect& r1, TRect& r2)
{
  TRect temp(r1);
  temp.a.x = Min(r1.a.x, r2.a.x);
  temp.a.y = Min(r1.a.y, r2.a.y);
  temp.b.x = Max(r1.b.x, r2.b.x);
  temp.b.y = Max(r1.b.y, r2.b.y);
  return temp;
}

void TRect::Grow(int dx, int dy)
{
  a.x+=dx;
  b.x-=dx;
  a.y+=dy;
  b.y-=dy;
}

TPoint& Point (int a, int b) {
  static TPoint p;
  p = TPoint (a,b);
  return p;
}

TRect& Rect (int a, int b, int c, int d) {
  static TRect r;
  r = TRect(a,b,c,d);
  return r;
}

int TRect::isvalid () { return (deltax()>0) && (deltay()>0); }
