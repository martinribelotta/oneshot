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
#include <iglu/tscroll.h>
#include <iglu/screen.h>
#include <iglu/tshape.h>

TScroll::TScroll (TPoint p, int len, int _hv):
  TView (Rect(p.x, p.y, 0,0)), max(0), min(0), pos(0), inc(1), hv(_hv)
{
  State &=~stFocusheable;
  if (_hv==HScroll) { // Horizontal
    Bounds.b.x = len;
    Bounds.b.y = Bounds.a.y + SizeBar;
    Align = vaPreservH;
  } else {            // Vertical
    Bounds.b.x = Bounds.a.x + SizeBar;
    Bounds.b.y = len;
    Align = vaPreservW;
  }
}

// Reftur 1 if change ocurrence, 0 is not change
int TScroll::setPosForPoint (TPoint& p)
{
  int i;
  TRect r;
  if (hv==HScroll) p.y = Bounds.a.y + (Bounds.deltay()>>1);
  else p.x = Bounds.a.x + (Bounds.deltax()>>1);
  for (i=min; i<=max; i+=inc) {
    getCursorGeomOf (r, i);
    if (r.contain(p))
      return i;
  }
  return min-1;
}

void TScroll::getCursorGeom (TRect& r) {
  getCursorGeomOf (r, pos);
}

void TScroll::getCursorGeomOf (TRect& r, int p)
{
/*  int cx, cy, cw, ch;
  int deltav, vp;
  r = Bounds;
  r.Grow(1,1);
  if (inc)
    vp = p/inc, deltav = (max-min+1) / inc;
  else
    vp = 0, deltav=0;
  if (max==min)
    vp = 0, deltav=0;
  if (hv==HScroll) { // Orizontal
    if (deltav)
      cw = r.deltax ()/deltav;
    else
      cw = r.deltax();
    ch = r.deltay ();
    cx = r.a.x + cw*vp;
    cy = r.a.y;
  } else { // Vertical
    cw = r.deltax ();
    if (deltav)
      ch = r.deltay ()/deltav;
    else
      ch = r.deltay();
    cw = r.deltax ();
    cx = r.a.x;
    cy = r.a.y + ch*vp;
  }
  r = TRect(cx, cy, cx+cw, cy+ch);*/
  r = Bounds;
  r.Grow( 1, 1 );
  p -= min;
  if ( hv==HScroll ) {
    double delta = (max-min)/(double)inc+1;
    double stepSize = Bounds.deltax()/delta;
    double zp = ((double)p)/((double)inc);
    r.b.x = r.a.x+(int)stepSize;
    r.moverel( (int)( stepSize*zp ), 0 );
  } else {
    double delta = (max-min)/(double)inc+1;
    double stepSize = Bounds.deltay()/delta;
    double zp = ((double)p)/((double)inc);
    r.b.y = r.a.y+(int)stepSize;
    r.moverel( 0, (int)( stepSize*zp ) );
  }

}

void TScroll::GotFocus ()
{
  if (State&stFocus) return;
  TView::GotFocus ();
  doDraw ();
}

void TScroll::LostFocus ()
{
  if (State&stFocus) {
    TView::LostFocus ();
    doDraw ();
  }
}

void TScroll::Draw ()
{
  TRect r;
  TShape shp (Bounds, shpPlane, 1, EGA_BLACK, EGA_BLACK, EGA_LIGHTGRAY);
  shp.Draw ();
//  r2.Grow (2,2);
//  gui_drawrectfill (r2, EGA_LIGHTGRAY);
  getCursorGeom (r);
  shp = TShape (r, shpUpBox, 1, EGA_DARKGRAY, EGA_WHITE, EGA_LIGHTGRAY);//-1);
  shp.Draw ();
//  r2.Grow (-1,-1);
//  gui_drawrect (r2, EGA_BLACK);
}

void TScroll::MouseEvent (TEvent& e)
{
//  if (State&stFocus) {
    if (e.type&evMouseDown) {
      TRect r;
      getCursorGeom (r);
      if (Bounds.contain(e.pos)) {
	SetState (stSelect, 1);
	if (!r.contain (e.pos))
	  SetPos (setPosForPoint (e.pos));
      }
    }
    if (State&stSelect) {
      if (e.type&evMouseUp)
         SetState (stSelect, 0);
      if (e.type&evMouseMove)
	 SetPos (setPosForPoint (e.pos));
    }
//  }
}

void TScroll::TimerEvent (TEvent&)
{
}

void TScroll::SetPos (int p)
{
  if ((pos!=p) && (p<=max) && (p>=min)) {
    long ud = (p>pos)? 0x80000000L: 0L;
    pos = p;
    doDraw ();
    TMessage m (cmChangeScroll, this, (pos&0x7FFFFFFFl)|ud);
    EventManager.SendMessage (m);
  }
}

void TScroll::resize( int w, int h )
{
  TView::resize( w, h );
  SetPos( pos );
}

void TScroll::RecuestAlign( TRect& a, TRect& b )
{
  TView::RecuestAlign( a, b );
  SetPos( pos );
}
