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
#include <iglu/tshape.h>

TShape::TShape (TRect& r, int t, int w, int _1, int _2, int _3):
  TView(r),type(t),width(w), bg(_3), lt(_2), sh(_1)
{
}

void TShape::Draw()
{
  TRect r(Bounds);  int i;
  if (bg!=-1)
    gui_drawrectfill(Bounds, bg);
  for (i=0; i<width; i++) {
    switch (type) {
      case shpDownBox:
	gui_drawrect(r, sh);
	gui_drawhline(r.a.x, r.b.y, r.b.x, lt);
	gui_drawvline(r.b.x, r.a.y, r.b.y, lt);
      break;
      case shpUpBox:
	gui_drawrect(r, lt);
	gui_drawhline(r.a.x, r.b.y, r.b.x, sh);
	gui_drawvline(r.b.x, r.a.y, r.b.y, sh);
      break;
      case shpBox3D: {
	int topleft, botomright;
	if (i<(width>>1))
	  (topleft = sh, botomright = lt);
	else
	  (topleft = lt, botomright = sh);
	gui_drawrect(r, topleft);
	gui_drawhline(r.a.x, r.b.y, r.b.x, botomright);
	gui_drawvline(r.b.x, r.a.y, r.b.y, botomright);
      } break;
      case shpHLine:
	gui_drawhline(Bounds.a.x, r.a.y+(r.deltay()>>1)+i+1, Bounds.b.x, lt);
	gui_drawhline(Bounds.a.x, r.a.y+(r.deltay()>>1)-i, Bounds.b.x, sh);
      break;
      case shpVLine:
	gui_drawvline(Bounds.a.x+(r.deltax()>>1)+i+1, r.a.y, Bounds.b.y, lt);
	gui_drawvline(Bounds.a.x+(r.deltax()>>1)-i, r.a.y, Bounds.b.y, sh);
      break;
      case shpPlane:
	gui_drawrect (r, sh);
      break;
    }
    r.a.x++;   r.a.y++;   r.b.x--;   r.b.y--;
  }
}
